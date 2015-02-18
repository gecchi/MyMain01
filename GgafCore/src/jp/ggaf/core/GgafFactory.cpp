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
volatile bool GgafFactory::_is_working_flg = true;
volatile bool GgafFactory::_have_to_rest_flg = false;
volatile bool GgafFactory::_is_resting_flg = false;
volatile bool GgafFactory::_was_finished_flg = false;

GgafMainActor* GgafFactory::obtainActor(uint64_t prm_order_id, GgafObject* prm_org) {
    return (GgafMainActor*)GgafFactory::obtain(prm_order_id, prm_org);
}

GgafMainScene* GgafFactory::obtainScene(uint64_t prm_order_id, GgafObject* prm_org) {
    return (GgafMainScene*)GgafFactory::obtain(prm_order_id, prm_org);
}

//����
//���̃��\�b�h�̓��C���X���b�h�����s����B
void GgafFactory::order(uint64_t prm_order_id,
                        GgafObject* (*prm_pFunc)(void*, void*, void*),
                        GgafObject* prm_pOrderer,
                        void* prm_pArg1,
                        void* prm_pArg2,
                        void* prm_pArg3) {
    _TRACE2_("GgafFactory::order ���q�� �ʃX���b�h�̍H�ꂳ��A[" << prm_id << "]������Ƃ��ā`�B");
    //���ɒ������Ă��Ȃ����`�F�b�N
    GgafOrder* pOrder = GgafFactory::ROOT_ORDER;
    while (pOrder) {
        if (pOrder->_order_id == prm_order_id) {
            _TRACE_("���x���� GgafFactory::order [" << prm_order_id << "]�́A���ɒ������Ă�̂ŃX���[���܂��B�Ӑ}���Ă��Ȃ���΃I�J�V�C�ł���I");
            return;
        }
        if (pOrder->_is_last_order_flg) {
            break;
        }
        pOrder = pOrder->_pOrder_next;
    }
    //���͖����ł���悤�Ȃ̂Ő擪�ɃX�g�b�N
    GgafOrder* pOrder_new;
    pOrder_new = NEW GgafOrder(prm_order_id);
    pOrder_new->_pObject_creation=nullptr;
    pOrder_new->_pFunc = prm_pFunc;
    pOrder_new->_pOrderer = prm_pOrderer;
    pOrder_new->_pArg1 = prm_pArg1;
    pOrder_new->_pArg2 = prm_pArg2;
    pOrder_new->_pArg3 = prm_pArg3;
    pOrder_new->_progress = 0;
    if (GgafFactory::ROOT_ORDER == nullptr) {
        _TRACE2_("GgafFactory::order ���q�� �����A�H��͋�������ł��ˁB�����A�����ł����ˁH�B");
        pOrder_new->_is_first_order_flg = true;
        pOrder_new->_is_last_order_flg = true;
        pOrder_new->_pOrder_next = pOrder_new;
        pOrder_new->_pOrder_prev = pOrder_new;
        GgafFactory::ROOT_ORDER = pOrder_new;
        GgafFactory::CREATING_ORDER = pOrder_new;
    } else {
        _TRACE2_("GgafFactory::order ���q�� �������܂��Ă܂��ˁA���X�����������܂��B");
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

int GgafFactory::chkProgress(uint64_t prm_order_id) {
    GgafOrder* pOrder;
    pOrder = GgafFactory::ROOT_ORDER;
    if (pOrder == nullptr) {
        return -1;
    }
    while (GgafFactory::_is_working_flg) {
        if (pOrder->_order_id == prm_order_id) {
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

void* GgafFactory::obtain(uint64_t prm_order_id, GgafObject* prm_org) {
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
        std::string name_org;
        if (prm_org->instanceOf(Obj_GgafScene)) {
            name_org = ((GgafScene*)prm_org)->getName();
        } else if (prm_org->instanceOf(Obj_GgafActor)) {
            name_org = ((GgafActor*)prm_org)->getName();
        }
        throwGgafCriticalException("GgafFactory::obtain("<<prm_order_id<<") Error! �������X�g��nullptr�őS�Đ����ς݂��Ă��܂��B\n"<<
                                   "oreder��obtain�̑Ή������Ă��܂���B\n"<<
                                   "���l(obtain�Ăь�)="<<name_org<<"("<<prm_org<<")");
    }

    //obtain���C�����[�v
    while (GgafFactory::_is_working_flg) {

        if (pOrder->_order_id == prm_order_id) {
            _TRACE2_("GgafFactory::obtain ���q�� ����ɂ��́A["<<prm_order_id<<"]�����ɗ��܂�������ƁB");
            while (GgafFactory::_is_working_flg) {
                if (pOrder->_progress != 2) {
                    _TRACE2_("GgafFactory::obtain ���q�� �ʃX���b�h�H�ꂳ��A["<<prm_order_id<<"]�̐����܂��`�H�A5�~���b�����҂������悤�BpOrder->_progress="<<(pOrder->_progress));
#ifdef _DEBUG
                    //�f�o�b�O���̓^�C���A�E�g����
#else

                    if (waittime > 1000*600) { //��10��
                        _TRACE_("GgafFactory::obtain �^�C���A�E�g�G���[�����I");
                        GgafFactory::debuginfo();
                        //�^�C���A�E�g�G���[�����I�A�G���[���b�Z�[�W�����B
                        std::string name_org;
                        if (prm_org->instanceOf(Obj_GgafScene)) {
                            name_org = ((GgafScene*)prm_org)->getName();
                        } else if (prm_org->instanceOf(Obj_GgafActor)) {
                            name_org = ((GgafActor*)prm_org)->getName();
                        }
                        throwGgafCriticalException("GgafFactory::obtain Error! ["<<prm_order_id<<"]�̐����҂����ԃ^�C���A�E�g�A�擾�ł��܂���B\n"<<
                                                   "���炩�̗��R�Ń��C���X���b�h����~���Ă���\�����傫���ł��B"<<
                                                   "������(order�Ăь�)=("<<pOrder->_pOrderer<<")�^���l(obtain�Ăь�)="<<name_org<<"("<<prm_org<<")");
                    } else {
                    }
#endif
                    END_SYNCHRONIZED1; // <----- �r���I��
                    Sleep(5);
                    BEGIN_SYNCHRONIZED1; // ----->�r���J�n
                    waittime += 5;
                    if (pOrder->_progress == 1) {
                        //����ς�
                        _TRACE_N_("Soon ");
                        continue; //�҂�
                    } else if (pOrder->_progress == 0) {
                        //������H
                        pOrder = GgafFactory::ROOT_ORDER; //������x�ŏ�����T������B
                        _TRACE_N_("Wait ");
                        break;
                    } else if (pOrder->_progress == 2) {
                        //����
                        pOrder = GgafFactory::ROOT_ORDER; //������x�ŏ�����T������B
                        _TRACE_N_("Okey-doke ");
                        break;
                    }
                } else {
                    _TRACE2_("GgafFactory::obtain ���q�� �����A["<<prm_id<<"]�͐����ς݂ł��ˁA�������I�B�����[���I");
#ifdef MY_DEBUG
                    if (waittime > 0) {
                        _TRACE_N_("...Finish!! ");
                    }
#endif
                    if (pOrder->_is_first_order_flg && pOrder->_is_last_order_flg) {
                        objectCreation = pOrder->_pObject_creation;
                        pOrder->_pObject_creation = nullptr;
                        GGAF_DELETE(pOrder);
                        pOrder = nullptr;
                        GgafFactory::ROOT_ORDER = nullptr;
                        GgafFactory::CREATING_ORDER = nullptr;
                        _TRACE2_("GgafFactory::obtain ���q�� ���i["<<prm_id<<"]�����܂����B���A�����H��͋�ł��ˁB�ɂɂȂ����H�˂��H");
                        return (void*)objectCreation;
                    } else {
                        pOrder_my_next = pOrder->_pOrder_next;
                        pOrder_my_prev = pOrder->_pOrder_prev;
                        pOrder_my_prev->_pOrder_next = pOrder_my_next;
                        pOrder_my_next->_pOrder_prev = pOrder_my_prev;
                        if (pOrder->_is_first_order_flg == false && pOrder->_is_last_order_flg) {
                            pOrder_my_prev->_is_last_order_flg = true;
//                            GgafFactory::CREATING_ORDER = pOrder_my_prev;
                        } else if (pOrder->_is_first_order_flg && pOrder->_is_last_order_flg == false) {
                            pOrder_my_next->_is_first_order_flg = true;
                            GgafFactory::ROOT_ORDER = pOrder_my_next;
//                            GgafFactory::CREATING_ORDER = pOrder_my_next;
                        } else if (pOrder->_is_first_order_flg == false && pOrder->_is_last_order_flg == false) {

                            //GgafFactory::CREATING_ORDER = pOrder_my_prev;
                        }
                        if (GgafFactory::CREATING_ORDER == pOrder) {
                            GgafFactory::CREATING_ORDER = pOrder_my_prev;
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
                std::string name_org;
                if (prm_org->instanceOf(Obj_GgafScene)) {
                    name_org = ((GgafScene*)prm_org)->getName();
                } else if (prm_org->instanceOf(Obj_GgafActor)) {
                    name_org = ((GgafActor*)prm_org)->getName();
                }
                throwGgafCriticalException("GgafFactory::obtain Error! ���H�꒷���S���T���܂������ǁA����Ȓ���(prm_order_id="<<prm_order_id<<")�́A����܂���B\n "<<
                                           "oreder() �� GgafFactory::obtain() �̑Ή������Ă��܂���Boreder()�R��A�����͓��� GgafFactory::obtain() ���Q��ȏサ�Ă܂��񂩁H�B\n"<<
                                           "���F���l(obtain�Ăь�)="<<name_org<<"("<<prm_org<<") �ł����B\n" <<
                                           "�i�����Ȃ݂ɁA���ݍH��̍ŏI�I�[�_�[�́A�����ԍ�(_order_id="<<pOrder->_order_id<<")�ŁA������(order�Ăь�)=("<<pOrder->_pOrderer<<") �ł����j");
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
            _TRACE2_("GgafFactory::clean ���_�� ���i�폜["<<pOrder->_id<<"]�A�Ō�̃X�g�b�N");
            GGAF_DELETE(pOrder);
            pOrder = nullptr;
            GgafFactory::ROOT_ORDER = nullptr;
            GgafFactory::CREATING_ORDER = nullptr;
            break;
        } else {
            _TRACE2_("GgafFactory::clean ���_�� ���i�폜["<<pOrder->_id<<"]");
            GgafOrder* pOrder_my_next = pOrder->_pOrder_next;
            GGAF_DELETE(pOrder);
            pOrder = pOrder_my_next;
        }
    }
    _TRACE2_("GgafFactory::clean ���_�� �H���|������");
    return;
}

void GgafFactory::debuginfo() {
    _TRACE_("GgafFactory::debuginfo ���f�o�b�O��� ���݂̍H��̏��");
    try {
        GgafOrder* p = GgafFactory::ROOT_ORDER;
        if (p) {
            while(p) {

                if (p->_pObject_creation) {

                    std::string name_creation;
                    if (p->_pObject_creation->instanceOf(Obj_GgafScene)) {
                        name_creation = ((GgafScene*)p->_pObject_creation)->getName();
                    } else if (p->_pObject_creation->instanceOf(Obj_GgafActor)) {
                        name_creation = ((GgafActor*)p->_pObject_creation)->getName();
                    }


                    _TRACE_("�E����ID="<<p->_order_id<<", "<<
                            "�i��="<<p->_progress<<", "<<
                            "���i="<<name_creation<<"("<<p->_pObject_creation<<")"<<", "<<
                            "������=("<<p->_pOrderer<<")"
                    );
                } else {
                    _TRACE_("�E����ID="<<p->_order_id<<", "<<
                            "�i��="<<p->_progress<<", "<<
                            "���i=nullptr, "<<
                            "������=("<<p->_pOrderer<<")"
                    );
                }
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
    //_CrtSetBreakAlloc(95299);
    //_CrtSetBreakAlloc(65854);

    try {
        GgafObject* (*func)(void*, void*, void*) = nullptr;
        GgafObject* pObject = nullptr;
        GgafOrder* pOrder_in_manufacturing_save = nullptr;
        Sleep(1000); //god �̃C���X�^���X����������܂łق�̂�����Ƒ҂K�v�����邩������Ȃ�
        while (GgafFactory::_is_working_flg) {
            if (GgafFactory::_have_to_rest_flg) {
                GgafFactory::_is_resting_flg = true;
                Sleep(100);
                continue;
            } else {
                GgafFactory::_is_resting_flg = false;
            }

            BEGIN_SYNCHRONIZED1; // ----->�r���J�n
            if (GgafFactory::CREATING_ORDER) {
                if (GgafFactory::CREATING_ORDER->_progress == 0) { //������Ȃ�܂����
                    _TRACE2_("GgafFactory::work ���H�꒷�� �悵�A����["<<GgafFactory::CREATING_ORDER->_id<<"]�͖�����(_progress == "<<GgafFactory::CREATING_ORDER->_progress<<")���ȁB�䂦�ɍ�������܂��I");
                    GgafFactory::CREATING_ORDER->_progress = 1; //�X�e�[�^�X�𐻑�����
                    func = GgafFactory::CREATING_ORDER->_pFunc;
                    pOrder_in_manufacturing_save = GgafFactory::CREATING_ORDER; //�|�C���^�ꎞ�ޔ�
                    void* arg1 = GgafFactory::CREATING_ORDER->_pArg1;
                    void* arg2 = GgafFactory::CREATING_ORDER->_pArg2;
                    void* arg3 = GgafFactory::CREATING_ORDER->_pArg3;
                    _TRACE2_("GgafFactory::work ���H�꒷�� �����J�n�I["<<GgafFactory::CREATING_ORDER->_id<<"] (�� �M�E�ցE�L)�� ");
                    Sleep(2);
                    END_SYNCHRONIZED1; // <----- �r���I��
//#ifdef MY_DEBUG
//try {
//#endif
                    pObject = (*func)(arg1, arg2, arg3); //���i�̐����I
//#ifdef MY_DEBUG
//} catch (GgafCriticalException& e) {
//    _TRACE_("���H���O�� �������G���[�G"<<e.getMsg());
//    std::string message = "\n�E"+e.getMsg()+"  \n\n���S�����肪�������b�Z�[�W�̏ꍇ�A�����̃o�O�̉\��������܂��B\n���ɐ\���󂲂����܂���B\n";
//    std::string message_dialog = message + "(���uShift + Ctrl + C�v�Ń��b�Z�[�W�̓R�s�[�ł��܂��B)";
//    MessageBox(nullptr, message_dialog.c_str(),"���L�̃G���[���������Ă��܂��܂���", MB_OK|MB_ICONSTOP | MB_SETFOREGROUND|MB_TOPMOST);
//    GgafFactory::_is_working_flg = false;
//    GgafFactory::_was_finished_flg = true;
//    GgafGod::_pException_factory = NEW GgafCriticalException(e.getMsg());
//    return 0;
//}
//#endif

                    BEGIN_SYNCHRONIZED1; // ----->�r���J�n
                    Sleep(2);
                    _TRACE2_("GgafFactory::work ���H�꒷�� ���������I�i��["<<GgafFactory::CREATING_ORDER->_id<<"] (^_^)v");
                    if (GgafFactory::CREATING_ORDER == nullptr) {
                        _TRACE2_("GgafFactory::work ���H�꒷�� �K�[���I�B��������������̂ɃL�����Z���������E�E�E�B�j�����܂��BpObject��delete!");
                        GGAF_DELETE(pObject);
                        END_SYNCHRONIZED1; // <----- �r���I��
                        continue;
                    } else {
                        GgafFactory::CREATING_ORDER = pOrder_in_manufacturing_save; //�|�C���^���A
                        GgafFactory::CREATING_ORDER->_pObject_creation = pObject; //���i�o�^
                        GgafFactory::CREATING_ORDER->_progress = 2; //�X�e�[�^�X�𐻑��ς݂�
                        _TRACE2_("GgafFactory::work ���H�꒷�� �������������̕i["<<(GgafFactory::CREATING_ORDER->_id)<<"]���A�I�ɒu���Ƃ��܂��B");
                    }
                } else {
                    _TRACE2_("GgafFactory::work ���H�꒷�� ����["<<GgafFactory::CREATING_ORDER->_id<<"]�͊��ɒI�ɒu���Ă���(_progress == "<<GgafFactory::CREATING_ORDER->_progress<<")�B�䂦�ɔ�΂�");
                }
            }
            if (GgafFactory::ROOT_ORDER == nullptr) {
                //�������ҋ@
                _TRACE2_("GgafFactory::work ���H�꒷�� �H��ɂ͉��`�������܂���B�����Ȃ�ł��������������I�I�E�E�E�Ȃ��̂�H�B�i�ҋ@�j");
                END_SYNCHRONIZED1; // <----- �r���I��
                if (GgafGod::_pGod->_fps >= PROPERTY::FPS_TO_CLEAN_GARBAGE_BOX) {
                    _TRACE2_("GgafFactory::work ���H�꒷�� FPS�͍�����Ȃ��A���̊Ԃ𗘗p���ăS�~���|���ł�����Ƃ��܂��B1");
                    GgafGarbageBox::_pGarbageBox->clean(5); //�ɂȂ̂ŁA�S�~���|��
                    GgafGarbageBox::_cnt_cleaned = 0;
                }
            } else {
                if (GgafFactory::ROOT_ORDER != nullptr && GgafFactory::ROOT_ORDER->_pOrder_prev->_progress == 0) {
                    _TRACE2_("GgafFactory::work ���H�꒷�� �E�E�E�������̒���������C�z�B["<<GgafFactory::ROOT_ORDER->_pOrder_prev->_id<<"]�Ȃ̂��H�B");
                    GgafFactory::CREATING_ORDER = GgafFactory::CREATING_ORDER->_pOrder_next;
                    END_SYNCHRONIZED1; // <----- �r���I��
                    continue;
                } else {
                    _TRACE2_("GgafFactory::work ���H�꒷�� ���āA�����������͖����B���`�I�ɐ����ς̂����܂��Ă邷�A������ɗ��₪��I�B�i�ҋ@�j");
                    END_SYNCHRONIZED1; // <----- �r���I��
                    if (GgafGod::_pGod->_fps >= PROPERTY::FPS_TO_CLEAN_GARBAGE_BOX) {
                        _TRACE2_("GgafFactory::work ���H�꒷�� FPS�͍����Ȃ��A���̊Ԃ𗘗p���ăS�~���|���ł�����Ƃ��܂��B2");
                        GgafGarbageBox::_pGarbageBox->clean(5); //�ɂȂ̂ŁA�S�~���|��
                        GgafGarbageBox::_cnt_cleaned = 0;
                    }
                }
            }
            Sleep(2);
        }
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

