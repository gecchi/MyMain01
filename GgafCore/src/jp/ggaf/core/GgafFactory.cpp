#include "jp/ggaf/core/GgafFactory.h"

#include "jp/ggaf/core/GgafGod.h"
#include "jp/ggaf/core/GgafOrder.h"
#include "jp/ggaf/core/GgafGarbageBox.h"
#include "jp/ggaf/core/actor/GgafActor.h"
#include "jp/ggaf/core/scene/GgafScene.h"
#include "jp/ggaf/core/GgafProperties.h"


using namespace GgafCore;

//������
GgafOrder* GgafFactory::ROOT_ORDER = nullptr;
GgafOrder* GgafFactory::CREATING_ORDER = nullptr;
#ifdef _MSC_VER
volatile bool GgafFactory::_is_working_flg   = true;
volatile bool GgafFactory::_have_to_rest_flg = false;
volatile bool GgafFactory::_is_resting_flg   = false;
volatile bool GgafFactory::_was_finished_flg = false;
#else
volatile std::atomic<bool> GgafFactory::_is_working_flg(true);
volatile std::atomic<bool> GgafFactory::_have_to_rest_flg(false);
volatile std::atomic<bool> GgafFactory::_is_resting_flg(false);
volatile std::atomic<bool> GgafFactory::_was_finished_flg(false);
#endif

GgafMainActor* GgafFactory::obtainActor(uint64_t prm_order_no, GgafObject* prm_pReceiver) {
    return (GgafMainActor*)GgafFactory::obtain(prm_order_no, prm_pReceiver);
}

GgafMainScene* GgafFactory::obtainScene(uint64_t prm_order_no, GgafObject* prm_pReceiver) {
    return (GgafMainScene*)GgafFactory::obtain(prm_order_no, prm_pReceiver);
}


//���̃��\�b�h�̓��C���X���b�h�����s����B
void GgafFactory::order(uint64_t prm_order_no,
                        GgafObject* (*prm_pFunc)(void*, void*, void*),
                        GgafObject* prm_pOrderer,
                        GgafObject* prm_pReceiver,
                        void* prm_pArg1,
                        void* prm_pArg2,
                        void* prm_pArg3) {

    _TRACE2_("GgafFactory::order ���q:("<<prm_pOrderer<<")�� �ʃX���b�h�̍H�ꂳ��A [" << prm_order_no << "/"<<prm_pReceiver<<"]������Ƃ��Ă�`�B");
    //���ɒ������Ă��Ȃ����`�F�b�N
    GgafOrder* pOrder = GgafFactory::ROOT_ORDER;
    while (pOrder) {
        if (pOrder->_order_no == prm_order_no &&  pOrder->_pReceiver == prm_pReceiver) {
            _TRACE_("���x���� GgafFactory::order ������ƁA[" << prm_order_no << "/"<<prm_pReceiver<<"]�́A�Q�d�������Ă��܂���I�A�������܂��B�Ӑ}���Ă��܂����H");
            return;
        }
        if (pOrder->_is_last_order_flg) {
            break;
        }
        pOrder = pOrder->_pOrder_next;
    }
    //���͖����ł���悤�Ȃ̂Ő擪�ɃX�g�b�N
    GgafOrder* pOrder_new;
    pOrder_new = NEW GgafOrder(prm_order_no);
    pOrder_new->_pObject_creation=nullptr;
    pOrder_new->_pFunc = prm_pFunc;
    pOrder_new->_pOrderer = prm_pOrderer;
    pOrder_new->_pReceiver = prm_pReceiver;
    pOrder_new->_time_of_order = timeGetTime();
    pOrder_new->_pArg1 = prm_pArg1;
    pOrder_new->_pArg2 = prm_pArg2;
    pOrder_new->_pArg3 = prm_pArg3;
    pOrder_new->_progress = 0;
    if (GgafFactory::ROOT_ORDER == nullptr) {
        _TRACE2_("GgafFactory::order ���q:("<<prm_pOrderer<<")�� �����A�H��͋�������ł��ˁB����������A�����ł����ˁH�B");
        pOrder_new->_is_first_order_flg = true;
        pOrder_new->_is_last_order_flg = true;
        pOrder_new->_pOrder_next = pOrder_new;
        pOrder_new->_pOrder_prev = pOrder_new;
        GgafFactory::ROOT_ORDER = pOrder_new;
        GgafFactory::CREATING_ORDER = pOrder_new;
    } else {
        _TRACE2_("GgafFactory::order ���q:("<<prm_pOrderer<<")�� �������܂��Ă܂��ˁA���X�����������܂��B");
        pOrder_new->_is_first_order_flg = false;
        pOrder_new->_is_last_order_flg = true;
        GgafOrder* pOrder_last;
        pOrder_last = GgafFactory::ROOT_ORDER->_pOrder_prev;
        pOrder_last->_is_last_order_flg = false;
        pOrder_last->_pOrder_next = pOrder_new;
        pOrder_new->_pOrder_prev = pOrder_last;
        pOrder_new->_pOrder_next = GgafFactory::ROOT_ORDER;
        GgafFactory::ROOT_ORDER->_pOrder_prev = pOrder_new;
    }
}

int GgafFactory::chkProgress(uint64_t prm_order_no) {
    GgafOrder* pOrder;
    pOrder = GgafFactory::ROOT_ORDER;
    if (pOrder == nullptr) {
        return -1;
    }
    while (GgafFactory::_is_working_flg) {
        if (pOrder->_order_no == prm_order_no) {
            return pOrder->_progress;
        } else {
            if (pOrder->_is_last_order_flg) {
                return -1;
            } else {
                pOrder = pOrder->_pOrder_next;
            }
        }
    }
    return -2;
}

void* GgafFactory::obtain(uint64_t prm_order_no, GgafObject* prm_pReceiver) {
    _TRACE2_("GgafFactory::obtain �����l:"<< (prm_pReceiver ? prm_pReceiver->toString() : "nullptr") <<"("<<prm_pReceiver<<")�� �܂��ǁA["<<prm_order_no<<"/"<<prm_pReceiver<<"]�����ɗ��܂�������ƁB");
    GgafOrder* pOrder;
    GgafOrder* pOrder_my_next;
    GgafOrder* pOrder_my_prev;
    DWORD waittime = 0;
    pOrder = GgafFactory::ROOT_ORDER;
    void* objectCreation;

    if (pOrder == nullptr) {
        //������������G���[�����I�A�G���[���b�Z�[�W�����B
        _TRACE_("GgafFactory::obtain ������������G���[�����I");
        GgafFactory::debuginfo();
        throwGgafCriticalException("GgafFactory::obtain("<<prm_order_no<<") Error! �������X�g��nullptr�őS�Đ����ς݂��Ă��܂��B\n"<<
                                   "oreder��obtain�̑Ή������Ă��܂���B\n"<<
                                   "���l(obtain�Ăь�)="<<(prm_pReceiver ? prm_pReceiver->toString() : "nullptr")<<"("<<prm_pReceiver<<")");
    }

    //obtain���C�����[�v
    while (GgafFactory::_is_working_flg) {
        if (pOrder->_order_no == prm_order_no && (pOrder->_pReceiver == nullptr || pOrder->_pReceiver == prm_pReceiver) ) {
            while (GgafFactory::_is_working_flg) {
                if (pOrder->_progress < 2) {
                    _TRACE2_("GgafFactory::obtain �����l:"<<(prm_pReceiver ? prm_pReceiver->toString() : "nullptr")<<"("<<prm_pReceiver<<")�� �˂��H�꒷����A["<<prm_order_no<<"/"<<prm_pReceiver<<"]�̐����܂��`�H�A5�~���b�����҂������悤�BpOrder->_progress="<<(pOrder->_progress));
#ifdef _DEBUG
                    //�f�o�b�O���̓^�C���A�E�g����
#else

                    if (waittime > 1000*600) { //��10��
                        _TRACE_("GgafFactory::obtain �^�C���A�E�g�G���[�����I");
                        GgafFactory::debuginfo();
                        //�^�C���A�E�g�G���[�����I�A�G���[���b�Z�[�W�����B
                        throwGgafCriticalException("GgafFactory::obtain Error! ����["<<pOrder->getDebuginfo()<<"]�̐����҂����ԃ^�C���A�E�g�A�擾�ł��܂���B\n"<<
                                                   "���炩�̗��R�Ń��C���X���b�h����~���Ă���\�����傫���ł��B"<<
                                                   "���l(obtain�Ăь�)="<<(prm_pReceiver ? prm_pReceiver->toString() : "nullptr")<<"("<<prm_pReceiver<<")");
                    } else {
                    }
#endif
                    END_SYNCHRONIZED1; // <----- �r���I��
                    Sleep(5);
                    BEGIN_SYNCHRONIZED1; // ----->�r���J�n
                    waittime += 5;
                    if (pOrder->_progress == 1) {
                        //����ς�
                        _TRACE_N_("�������A");
                        continue; //�҂�
                    } else if (pOrder->_progress == 0) {
                        //������H
                        pOrder = GgafFactory::ROOT_ORDER; //������x�ŏ�����T������B
                        _TRACE_N_("�҂��āA");
                        break;
                    } else if (pOrder->_progress == 2) {
                        //����
                        pOrder = GgafFactory::ROOT_ORDER; //������x�ŏ�����T������B
                        _TRACE_N_("�����A");
                        break;
                    }
                } else {

#ifdef MY_DEBUG
                    if (waittime > 0) {
                        _TRACE_N_("�E�E�E���܂������܂����B");
                    }
#endif
                    _TRACE2_("GgafFactory::obtain �����l:"<<(prm_pReceiver ? prm_pReceiver->toString() : "nullptr")<<"("<<prm_pReceiver<<")�� ��`���A["<<prm_order_no<<"/"<<prm_pReceiver<<"]�͐��������ł��ˁB�������ɁI");
                    if (pOrder->_is_first_order_flg && pOrder->_is_last_order_flg) {
                        //�Ō�̈�� obtain
                        objectCreation = pOrder->_pObject_creation;
                        pOrder->_pObject_creation = nullptr;
                        GGAF_DELETE(pOrder);
                        pOrder = nullptr;
                        GgafFactory::ROOT_ORDER = nullptr;
                        GgafFactory::CREATING_ORDER = nullptr;
                        _TRACE2_("GgafFactory::obtain �����l:"<<(prm_pReceiver ? prm_pReceiver->toString() : "nullptr")<<"("<<prm_pReceiver<<")�� ���A�Ƃ���ł����H��͋�ł��ˁB�ɂɂȂ�����H�A�˂��H");
                        return (void*)objectCreation;
                    } else {
                        //���Ԃ�obtain�A�����q�������B
                        pOrder_my_next = pOrder->_pOrder_next;
                        pOrder_my_prev = pOrder->_pOrder_prev;
                        pOrder_my_prev->_pOrder_next = pOrder_my_next;
                        pOrder_my_next->_pOrder_prev = pOrder_my_prev;
                        if (pOrder->_is_last_order_flg) {
                            pOrder_my_prev->_is_last_order_flg = true;
                        }
                        if (pOrder->_is_first_order_flg) {
                            GgafFactory::ROOT_ORDER = pOrder_my_next;
                            pOrder_my_next->_is_first_order_flg = true;
                        }
                        if (GgafFactory::CREATING_ORDER == pOrder) {
                            GgafFactory::CREATING_ORDER = pOrder_my_next;
                        }
                        objectCreation = pOrder->_pObject_creation;
                        pOrder->_pObject_creation = nullptr;
                        GGAF_DELETE(pOrder);
                        pOrder = nullptr;

                        return (void*)objectCreation;
                    }
                }
            }
        } else {
            if (pOrder->_is_last_order_flg) {
                _TRACE_("GgafFactory::obtain �����̌`�Ղ������A�擾�o���Ȃ��G���[�����I");
                GgafFactory::debuginfo();
                //�����̌`�Ղ������A�擾�o���Ȃ��G���[�����I�A�G���[���b�Z�[�W�����B
                throwGgafCriticalException("GgafFactory::obtain Error! ���H�꒷���S���T���܂������ǁA����Ȓ���("<<(prm_pReceiver ? prm_pReceiver->toString() : "nullptr")<<"����ւ� �����ԍ�:"<<prm_order_no<<"/"<<prm_pReceiver<<")�́A����܂���B\n "<<
                                           "oreder() �� GgafFactory::obtain() �̑Ή������Ă��܂���Boreder()�R��A�����͓��� GgafFactory::obtain() ���Q��ȏサ�Ă܂��񂩁H�B\n"<<
                                           "���F���l(obtain�Ăь�)="<<(prm_pReceiver ? prm_pReceiver->toString() : "nullptr")<<"("<<prm_pReceiver<<") �ł����B\n" <<
                                           "�i�����Ȃ݂ɁA���ݍH��̍ŏI�I�[�_�[�́A�����ԍ�("<<pOrder->_order_no<<"/"<<pOrder->_pReceiver<<")�ŁA������(order�Ăь�)=("<<pOrder->_pOrderer<<") �ł����j");
            } else {
                pOrder = pOrder->_pOrder_next;
            }
        }
    }
    if (GgafGod::_pException_factory) {
        throw *(GgafGod::_pException_factory);
    }
    return nullptr;
}

void GgafFactory::beginRest() {
    _TRACE_("GgafFactory::beginRest() ���_���H��A�x�e���Ȃ���");
    GgafFactory::_have_to_rest_flg = true;
}

bool GgafFactory::isResting() {
    if (GgafFactory::_is_resting_flg) {
        _TRACE_("GgafFactory::isResting() �H��x�~���");
    } else {
        _TRACE_("GgafFactory::isResting() �H��ғ����");
    }
    return GgafFactory::_is_resting_flg;
}

void GgafFactory::finishRest() {
    _TRACE_("GgafFactory::beginRest() ���_���H��A�x�e�͂����܂��B���������I");
    GgafFactory::_have_to_rest_flg = false;
}

//�H��ɂ��ߍ���ł���S�ẴC���X�^���X��j��
//�_(GgafGod)���A�v���I�������Ɏ��s����\��B
void GgafFactory::clean() {
    _TRACE2_("GgafFactory::clean ���_�� �H���|���J�n");
    GgafOrder* pOrder = GgafFactory::ROOT_ORDER;
    if (pOrder == nullptr) {
        _TRACE2_("GgafFactory::clean ���_�� �������H��ɉ��������I�I");
        return;
    }
    while (GgafFactory::_is_working_flg || GgafFactory::_was_finished_flg == false) {
        Sleep(10);
        _TRACE_("GgafFactory::clean ���_�� �H�ꂪ�܂������Ă��܂��E�E�E");
    }

    GgafFactory::debuginfo();

    while (true) {
        if (pOrder->_is_last_order_flg) {
            _TRACE2_("GgafFactory::clean ���_�� ���i�폜["<<pOrder->getDebuginfo()<<"]�A�Ō�̃X�g�b�N");
            GGAF_DELETE(pOrder);
            pOrder = nullptr;
            GgafFactory::ROOT_ORDER = nullptr;
            GgafFactory::CREATING_ORDER = nullptr;
            break;
        } else {
            _TRACE2_("GgafFactory::clean ���_�� ���i�폜["<<pOrder->getDebuginfo()<<"]");
            GgafOrder* pOrder_my_next = pOrder->_pOrder_next;
            GGAF_DELETE(pOrder);
            pOrder = pOrder_my_next;
        }
    }
    _TRACE2_("GgafFactory::clean ���_�� �H���|������");
    return;
}

void GgafFactory::removeOrder(GgafObject* prm_pReceiver) {
    GgafOrder* pOrder = GgafFactory::ROOT_ORDER;
    while (pOrder) {
        if (pOrder->_pReceiver == prm_pReceiver) {
            if (pOrder->_is_last_order_flg && pOrder->_is_first_order_flg) {
                //�Ō�̈��
                GGAF_DELETE(pOrder);
                GgafFactory::ROOT_ORDER = nullptr;
                GgafFactory::CREATING_ORDER = nullptr;
                break; //�I��
            } else {
                //�Ԃ̏ꍇ�A�|�C���^���q�������B
                GgafOrder* pOrder_t_next = pOrder->_pOrder_next;
                GgafOrder* pOrder_t_prev = pOrder->_pOrder_prev;
                pOrder_t_prev->_pOrder_next = pOrder_t_next;
                pOrder_t_next->_pOrder_prev = pOrder_t_prev;

                if (pOrder->_is_last_order_flg) {
                    pOrder_t_prev->_is_last_order_flg = true;
                }
                if (pOrder->_is_first_order_flg) {
                    GgafFactory::ROOT_ORDER = pOrder_t_next;
                    pOrder_t_next->_is_first_order_flg = true;
                }
                if (GgafFactory::CREATING_ORDER == pOrder) {
                    GgafFactory::CREATING_ORDER = pOrder_t_next;
                }
                _TRACE_("GgafFactory::removeOrder ���l("<<prm_pReceiver<<")���S�ׁ̈A�������폜���܂��B" << pOrder->getDebuginfo() << "");
                GGAF_DELETE(pOrder);
                pOrder = pOrder_t_next;
                continue;
            }
        } else {
            if (pOrder->_is_last_order_flg) {
                break; //�I��
            } else {
                pOrder = pOrder->_pOrder_next;
                continue;
            }
        }
    }
}

void GgafFactory::debuginfo() {
    _TRACE_("GgafFactory::debuginfo ���f�o�b�O��� ���݂̍H��̏��");
    try {
        GgafOrder* p = GgafFactory::ROOT_ORDER;
        if (p) {
            while(p) {
                _TRACE_("�E" << p->getDebuginfo() );
                p = p->_pOrder_next;
                if (p == GgafFactory::ROOT_ORDER) {
                    break;
                }
            }
        } else {
            _TRACE_("�E�I�[�_�[����܂���I");
        }
    } catch (...) {
        _TRACE_("GgafFactory::debuginfo �Ȃ�Ƃ������Ƃł��傤�B���݂̍H��̏�Ԃ̕\�����s�\�ł��B");
    }
    _TRACE_("GgafFactory::debuginfo �ȏ�");
}

unsigned __stdcall GgafFactory::work(void* prm_arg) {
    //_CrtSetBreakAlloc(65854);
    try {
        GgafObject* (*func)(void*, void*, void*) = nullptr;
        GgafObject* pObject = nullptr;
        Sleep(1000); //god �̃C���X�^���X����������܂łق�̂�����Ƒ҂K�v�����邩������Ȃ�

        //���i�����܂���H�ꃋ�[�v�I
        while (GgafFactory::_is_working_flg) {
            if (GgafFactory::_have_to_rest_flg) {
                GgafFactory::_is_resting_flg = true;
                Sleep(100);
                continue;
            } else {
                GgafFactory::_is_resting_flg = false;
            }

BEGIN_SYNCHRONIZED1; // ----->�r���J�n
            GgafOrder* pOrder_creating = GgafFactory::CREATING_ORDER;
            if (pOrder_creating) {
                if (pOrder_creating->_progress == 0) { //������Ȃ�܂����
                    _TRACE2_("GgafFactory::work ���H�꒷�� �悵�A����["<<pOrder_creating->_order_no<<"/"<<pOrder_creating->_pReceiver<<"]�͖�����(_progress == "<<pOrder_creating->_progress<<")���ȁB�䂦�ɍ�������܂��I");
                    pOrder_creating->_progress = 1; //�X�e�[�^�X�𐻑�����
                    pOrder_creating->_time_of_create_begin = timeGetTime();
                    func = pOrder_creating->_pFunc;
                    void* arg1 = pOrder_creating->_pArg1;
                    void* arg2 = pOrder_creating->_pArg2;
                    void* arg3 = pOrder_creating->_pArg3;
                    _TRACE2_("GgafFactory::work ���H�꒷�� �����J�n�I["<<pOrder_creating->_order_no<<"/"<<pOrder_creating->_pReceiver<<"]");
                    Sleep(2);
                    END_SYNCHRONIZED1; // <----- �r���I��

                    pObject = (*func)(arg1, arg2, arg3); //���i�̐����I

                    BEGIN_SYNCHRONIZED1; // ----->�r���J�n
                    Sleep(2);
                    _TRACE2_("GgafFactory::work ���H�꒷�� ���������I�i��["<<pOrder_creating->_order_no<<"/"<<pOrder_creating->_pReceiver<<"] (^_^)v");
                    if (GgafFactory::CREATING_ORDER == nullptr) {
                        //GgafFactory::CREATING_ORDER �������� nullptr �ɂȂ��Ă��܂��Ă���ꍇ�L�����Z���B
                        _TRACE2_("GgafFactory::work ���H�꒷�� �K�[���I�B��������������̂ɃL�����Z���������E�E�E�B�j�����܂��BpObject��delete!");
                        GGAF_DELETE(pObject);
END_SYNCHRONIZED1; // <----- �r���I��
                        continue;
                    } else if (GgafFactory::CREATING_ORDER == pOrder_creating) {
                        //����ȃP�[�X
                        pOrder_creating->_pObject_creation = pObject; //���i�o�^
                        pOrder_creating->_progress = 2; //�X�e�[�^�X�𐻑��ς݂�
                        pOrder_creating->_time_of_create_finish = timeGetTime();
                        _TRACE2_("GgafFactory::work ���H�꒷�� �������������̕i["<<pOrder_creating->_order_no<<"/"<<pOrder_creating->_pReceiver<<"]���A�I�ɒu���Ƃ��܂��B");
                    }  else if (GgafFactory::CREATING_ORDER != pOrder_creating) {
                        _TRACE2_("GgafFactory::work ���H�꒷�� �x���A�����̕i["<<pOrder_creating->_order_no<<"/"<<pOrder_creating->_pReceiver<<"]������Ă���ԂɁA"<<
                                 "CREATING_ORDER ���A�ʂ̒���["<<GgafFactory::CREATING_ORDER->_order_no<<"/"<<GgafFactory::CREATING_ORDER->_pReceiver<<"]���w���Ă��܂����I���Ă邩������܂���I�����I�Ɍ��ɖ߂��܂��I�v�����I");
                        GgafFactory::CREATING_ORDER = pOrder_creating; //�|�C���^�����߂�
                        pOrder_creating->_pObject_creation = pObject; //���i�o�^
                        pOrder_creating->_progress = 2; //�X�e�[�^�X�𐻑��ς݂�
                        pOrder_creating->_time_of_create_finish = timeGetTime();
                        _TRACE2_("GgafFactory::work ���H�꒷�� �������������̕i["<<pOrder_creating->_order_no<<"/"<<pOrder_creating->_pReceiver<<"]���A�I�ɒu���Ƃ��܂��E�E�E�B");
                    }
                } else {
                    _TRACE2_("GgafFactory::work ���H�꒷�� ����["<<pOrder_creating->_order_no<<"/"<<pOrder_creating->_pReceiver<<"]�́A��������ĒI�ɒu���Ă��邵�E�E�E(_progress == "<<pOrder_creating->_progress<<")�B");
                }
            }
            if (GgafFactory::ROOT_ORDER == nullptr) {
                //�������ҋ@
                _TRACE2_("GgafFactory::work ���H�꒷�� �H��ɂ͉��`�������܂���B�����Ȃ�ł��������������I�I�E�E�E�Ȃ��̂�H�B�i�ҋ@�j");
END_SYNCHRONIZED1; // <----- �r���I��
                if (GgafGod::_pGod->_fps >= PROPERTY::FPS_TO_CLEAN_GARBAGE_BOX) {
                    _TRACE2_("GgafFactory::work ���H�꒷�� ���قǖZ�����Ȃ��̂ŁA�S�~���̃S�~���o���Ƃ����B");
                    GgafGarbageBox::_pGarbageBox->clean(5); //�ɂȂ̂ŁA�S�~���|��
                    GgafGarbageBox::_cnt_cleaned = 0;
                }
            } else {
                if (GgafFactory::ROOT_ORDER != nullptr && GgafFactory::ROOT_ORDER->_pOrder_prev->_progress == 0) {
                    _TRACE2_("GgafFactory::work ���H�꒷�� �E�E�E�������̒���������C�z�B�ŏI�ڕW�̒�����["<<GgafFactory::ROOT_ORDER->_pOrder_prev->_order_no<<"/���l="<<GgafFactory::ROOT_ORDER->_pOrder_prev->_pReceiver<<"]�Ȃ̂��H�B");
                    GgafFactory::CREATING_ORDER = GgafFactory::CREATING_ORDER->_pOrder_next;
END_SYNCHRONIZED1; // <----- �r���I��
                } else {
                    _TRACE2_("GgafFactory::work ���H�꒷�� ���āA�����������͖����B�I�ɐ����ς̂񂪂��܂��Ă�̂𑁂���ɗ��������I�B�i�ҋ@�j");
END_SYNCHRONIZED1; // <----- �r���I��
                    if (GgafGod::_pGod->_fps >= PROPERTY::FPS_TO_CLEAN_GARBAGE_BOX) {
                        _TRACE2_("GgafFactory::work ���H�꒷�� ���قǖZ�����Ȃ��������Ȃ̂ŁA�S�~���̃S�~���o���Ƃ������B");
                        GgafGarbageBox::_pGarbageBox->clean(5); //�ɂȂ̂ŁA�S�~���|��
                        GgafGarbageBox::_cnt_cleaned = 0;
                    }
                }
            }
            Sleep(2);
        } // <-- while (GgafFactory::_is_working_flg)
        _TRACE2_("GgafFactory::work ���H�꒷�� �H��͂���ɂēX���܂��ł��B���悤�Ȃ�A�܂���܂��傤�B");
        GgafFactory::_was_finished_flg = true;
    } catch (GgafCriticalException& e) {
        GgafFactory::debuginfo();
        _TRACE_("���H���O�� ���Ƃ������Ƃ����݂܂���G"<<e.getMsg());
        GgafFactory::_is_working_flg = false;
        GgafFactory::_was_finished_flg = true;
        GgafGod::_pException_factory = NEW GgafCriticalException(e.getMsg());
        return 1;
    }
    return 0;
}

