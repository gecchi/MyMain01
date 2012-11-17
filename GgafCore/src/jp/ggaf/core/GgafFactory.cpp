#include "stdafx.h"

using namespace GgafCore;

//������
GgafOrder* GgafFactory::ROOT_ORDER = NULL;
GgafOrder* GgafFactory::CREATING_ORDER = NULL;
volatile bool GgafFactory::_is_working_flg = true;
volatile bool GgafFactory::_have_to_rest_flg = false;
volatile bool GgafFactory::_is_resting_flg = false;


volatile bool GgafFactory::_was_finished_flg = false;
int GgafFactory::_cnt_cleaned = 0;
GgafGarbageBox* GgafFactory::_pGarbageBox = NULL;



GgafMainActor* GgafFactory::obtainActor(UINT32 prm_id, GgafObject* prm_org) {
    return (GgafMainActor*)obtain(prm_id, prm_org);
}

GgafMainScene* GgafFactory::obtainScene(UINT32 prm_id, GgafObject* prm_org) {
    return (GgafMainScene*)obtain(prm_id, prm_org);
}

//����
//���̃��\�b�h�̓��C���X���b�h�����s����B
void GgafFactory::order(UINT32 prm_id,
                        GgafObject* (*prm_pFunc)(void*, void*, void*),
                        GgafObject* prm_pOrderer,
                        void* prm_pArg1,
                        void* prm_pArg2,
                        void* prm_pArg3) {
    TRACE2("GgafFactory::order ���q�� �ʃX���b�h�̍H�ꂳ��A[" << prm_id << "]������Ƃ��ā`�B");
    //���ɒ������Ă��Ȃ����`�F�b�N
    GgafOrder* pOrder = ROOT_ORDER;
    while (pOrder) {
        if (pOrder->_id == prm_id) {
            _TRACE_("���x���� GgafFactory::order [" << prm_id << "]�́A���ɒ������Ă�̂ŃX���[���܂��B�Ӑ}���Ă��Ȃ���΃I�J�V�C�ł���I");
            return;
        }
        if (pOrder->_is_last_order_flg) {
            break;
        }
        pOrder = pOrder->_pOrder_next;
    }
    //���͖����ł���悤�Ȃ̂ŃX�g�b�N
    GgafOrder* pOrder_new;
    pOrder_new = NEW GgafOrder(prm_id);
    pOrder_new->_pObject_creation=NULL;
    pOrder_new->_pFunc = prm_pFunc;
    pOrder_new->_pOrderer = prm_pOrderer;
    pOrder_new->_pArg1 = prm_pArg1;
    pOrder_new->_pArg2 = prm_pArg2;
    pOrder_new->_pArg3 = prm_pArg3;
    pOrder_new->_progress = 0;
    if (ROOT_ORDER == NULL) {
        TRACE2("GgafFactory::order ���q�� �����A�H��͋�������ł��ˁB�����A�����ł����ˁH�B");
        pOrder_new->_is_first_order_flg = true;
        pOrder_new->_is_last_order_flg = true;
        pOrder_new->_pOrder_next = pOrder_new;
        pOrder_new->_pOrder_prev = pOrder_new;
        ROOT_ORDER = pOrder_new;
        CREATING_ORDER = pOrder_new;
    } else {
        TRACE2("GgafFactory::order ���q�� �������܂��Ă܂��ˁA���X�����������܂��B");
        pOrder_new->_is_first_order_flg = false;
        pOrder_new->_is_last_order_flg = true;
        GgafOrder* pOrder_last;
        pOrder_last = ROOT_ORDER->_pOrder_prev;
        pOrder_last->_is_last_order_flg = false;
        pOrder_last->_pOrder_next = pOrder_new;
        pOrder_new->_pOrder_prev = pOrder_last;
        pOrder_new->_pOrder_next = ROOT_ORDER;
        ROOT_ORDER->_pOrder_prev = pOrder_new;
    }
}

int GgafFactory::chkProgress(UINT32 prm_id) {
    GgafOrder* pOrder;
    pOrder = ROOT_ORDER;
    if (pOrder == NULL) {
        return -1;
    }
    while (_is_working_flg) {
        if (pOrder->_id == prm_id) {
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

void* GgafFactory::obtain(UINT32 prm_id, GgafObject* prm_org) {
    TRACE("GgafFactory::obtain "<<prm_id<<"/");
    GgafOrder* pOrder;
    GgafOrder* pOrder_MyNext;
    GgafOrder* pOrder_MyPrev;
    DWORD waittime = 0;
    pOrder = ROOT_ORDER;
    void* objectCreation;


    if (pOrder == NULL) {
        //������������G���[�����I�A�G���[���b�Z�[�W�����B
        std::string name_org;
        if (prm_org->instanceOf(Obj_GgafScene)) {
            name_org = ((GgafScene*)prm_org)->getName();
        } else if (prm_org->instanceOf(Obj_GgafActor)) {
            name_org = ((GgafActor*)prm_org)->getName();
        }
        throwGgafCriticalException("GgafFactory::obtain("<<prm_id<<") Error! �������X�g��NULL�őS�Đ����ς݂��Ă��܂��B\n"<<
                                   "oreder��obtain�̑Ή������Ă��܂���B\n"<<
                                   "���l(obtain�Ăь�)="<<name_org<<"("<<prm_org<<")");
    }

    //obtain���C�����[�v
    while (_is_working_flg) {

        if (pOrder->_id == prm_id) {
            TRACE2("GgafFactory::obtain ���q�� ����ɂ��́A["<<prm_id<<"]�����ɗ��܂�������ƁB");
            while (_is_working_flg) {
                if (pOrder->_progress != 2) {
                    TRACE2("GgafFactory::obtain ���q�� �ʃX���b�h�H�ꂳ��A["<<prm_id<<"]�̐����܂��`�H�A5�~���b�����҂������悤�BpOrder->_progress="<<(pOrder->_progress));
#ifdef _DEBUG
                    //�f�o�b�O���̓^�C���A�E�g����
#else

                    if (waittime > 1000*600) { //��10��
                        //�^�C���A�E�g�G���[�����I�A�G���[���b�Z�[�W�����B
                        std::string name_org;
                        if (prm_org->instanceOf(Obj_GgafScene)) {
                            name_org = ((GgafScene*)prm_org)->getName();
                        } else if (prm_org->instanceOf(Obj_GgafActor)) {
                            name_org = ((GgafActor*)prm_org)->getName();
                        }
                        std::string name_orderer;
                        if (pOrder->_pOrderer->instanceOf(Obj_GgafScene)) {
                            name_orderer = ((GgafScene*)pOrder->_pOrderer)->getName();
                        } else if (pOrder->_pOrderer->instanceOf(Obj_GgafActor)) {
                            name_orderer = ((GgafActor*)pOrder->_pOrderer)->getName();
                        }
                        throwGgafCriticalException("GgafFactory::obtain Error! ["<<prm_id<<"]�̐����҂����ԃ^�C���A�E�g�A�擾�ł��܂���B\n"<<
                                                   "���炩�̗��R�Ń��C���X���b�h����~���Ă���\�����傫���ł��B"<<
                                                   "������(order�Ăь�)="<<name_orderer<<"("<<pOrder->_pOrderer<<")�^���l(obtain�Ăь�)="<<name_org<<"("<<prm_org<<")");
                    } else {
                    }
#endif
                 ___EndSynchronized1; // <----- �r���I��
                    Sleep(5);
                 ___BeginSynchronized1; // ----->�r���J�n
                    waittime += 5;
                    if (pOrder->_progress == 1) {
                        //����ς�
                        _TEXT_("!");
                        continue; //�҂�
                    } else {
                        //������H
                        pOrder = ROOT_ORDER; //������x�ŏ�����T������B
                        _TEXT_(".");
                        break;
                    }
                } else {
                    TRACE2("GgafFactory::obtain ���q�� �����A["<<prm_id<<"]�͐����ς݂ł��ˁA�������I�B�����[���I");
                    if (pOrder->_is_first_order_flg && pOrder->_is_last_order_flg) {
                        objectCreation = pOrder->_pObject_creation;
                        pOrder->_pObject_creation = NULL;
                        DELETE_IMPOSSIBLE_NULL(pOrder);
                        pOrder = NULL;
                        ROOT_ORDER = NULL;
                        CREATING_ORDER = NULL;
                        TRACE2("GgafFactory::obtain ���q�� ���i["<<prm_id<<"]�����܂����B���A�����H��͋�ł��ˁB�ɂɂȂ����H�˂��H");
                        return (void*)objectCreation;
                    } else {
                        pOrder_MyNext = pOrder->_pOrder_next;
                        pOrder_MyPrev = pOrder->_pOrder_prev;
                        pOrder_MyPrev->_pOrder_next = pOrder_MyNext;
                        pOrder_MyNext->_pOrder_prev = pOrder_MyPrev;
                        if (pOrder->_is_first_order_flg == false && pOrder->_is_last_order_flg) {
                            pOrder_MyPrev->_is_last_order_flg = true;
//                            CREATING_ORDER = pOrder_MyPrev;
                        } else if (pOrder->_is_first_order_flg && pOrder->_is_last_order_flg == false) {
                            pOrder_MyNext->_is_first_order_flg = true;
                            ROOT_ORDER = pOrder_MyNext;
//                            CREATING_ORDER = pOrder_MyNext;
                        } else if (pOrder->_is_first_order_flg == false && pOrder->_is_last_order_flg == false) {

                            //CREATING_ORDER = pOrder_MyPrev;
                        }
                        if (CREATING_ORDER == pOrder) {
                            CREATING_ORDER = pOrder_MyPrev;
                        }
                        objectCreation = pOrder->_pObject_creation;
                        pOrder->_pObject_creation = NULL;
                        DELETE_IMPOSSIBLE_NULL(pOrder);
                        pOrder = NULL;

                        return (void*)objectCreation;
                    }
                }
            }
        } else {
            if (pOrder->_is_last_order_flg) {
                //�����̌`�Ղ������A�擾�o���Ȃ��G���[�����I�A�G���[���b�Z�[�W�����B
                std::string name_orderer;
                if (pOrder->_pOrderer->instanceOf(Obj_GgafScene)) {
                    name_orderer = ((GgafScene*)pOrder->_pOrderer)->getName();
                } else if (pOrder->_pOrderer->instanceOf(Obj_GgafActor)) {
                    name_orderer = ((GgafActor*)pOrder->_pOrderer)->getName();
                }
                std::string name_org;
                if (prm_org->instanceOf(Obj_GgafScene)) {
                    name_org = ((GgafScene*)prm_org)->getName();
                } else if (prm_org->instanceOf(Obj_GgafActor)) {
                    name_org = ((GgafActor*)prm_org)->getName();
                }
                throwGgafCriticalException("GgafFactory::obtain Error! ���H�꒷���S���T���܂������ǁA����Ȓ���(prm_id="<<prm_id<<")�́A����܂���B\n "<<
                                           "oreder() �� obtain() �̑Ή������Ă��܂���Boreder()�R��A�����͓��� obtain() ���Q��ȏサ�Ă܂��񂩁H�B\n"<<
                                           "������(order�Ăь�)="<<name_orderer<<"("<<pOrder->_pOrderer<<")�^���l(obtain�Ăь�)="<<name_org<<"("<<prm_org<<")");
            } else {
                pOrder = pOrder->_pOrder_next;
            }
        }
    }
    if (GgafGod::_pException_Factory) {
        throw *(GgafGod::_pException_Factory);
    }
    return NULL;
}

//�H��ɂ��ߍ���ł���S�ẴC���X�^���X��j��
//�_(GgafGod)���A�v���I�������Ɏ��s����\��B
void GgafFactory::clean() {
    TRACE2("GgafFactory::clean ���_�� �H���|���J�n");
    GgafOrder* pOrder = ROOT_ORDER;
    if (pOrder == NULL) {
        TRACE2("GgafFactory::clean ���_�� �������H��ɉ��������I�I");
        return;
    }
    while (_is_working_flg || _was_finished_flg == false) {
        Sleep(10);
        _TRACE_("GgafFactory::clean ���_�� �H�ꂪ�܂������Ă��܂��E�E�E");
    }

    while (true) {
        if (pOrder->_is_last_order_flg) {
            TRACE2("GgafFactory::clean ���_�� ���i�폜["<<pOrder->_id<<"]�A�Ō�̃X�g�b�N");
            DELETE_IMPOSSIBLE_NULL(pOrder);
            pOrder = NULL;
            ROOT_ORDER = NULL;
            CREATING_ORDER = NULL;
            break;
        } else {
            TRACE2("GgafFactory::clean ���_�� ���i�폜["<<pOrder->_id<<"]");
            GgafOrder* pOrder_MyNext = pOrder->_pOrder_next;
            DELETE_IMPOSSIBLE_NULL(pOrder);
            pOrder = pOrder_MyNext;
        }
    }
    TRACE2("GgafFactory::clean ���_�� �H���|������");
    return;
}

unsigned __stdcall GgafFactory::work(void* prm_arg) {
    //_CrtSetBreakAlloc(95299);
    //_CrtSetBreakAlloc(65854);

    try {
        GgafObject* (*func)(void*, void*, void*) = NULL;
        GgafObject* pObject = NULL;
        GgafOrder* pOrder_InManufacturing_save = NULL;
        Sleep(1000); //god �̃C���X�^���X����������܂łق�̂�����Ƒ҂K�v�����邩������Ȃ�
        while (_is_working_flg) {
            if (_have_to_rest_flg) {
                _is_resting_flg = true;
                Sleep(100);
                continue;
            } else {
                _is_resting_flg = false;
            }

         ___BeginSynchronized1; // ----->�r���J�n
            if (CREATING_ORDER) {
                if (CREATING_ORDER->_progress == 0) { //������Ȃ�܂����
                    TRACE2("GgafFactory::work ���H�꒷�� �悵�A����["<<CREATING_ORDER->_id<<"]�͖�����(_progress == "<<CREATING_ORDER->_progress<<")���ȁB�䂦�ɍ�������܂��I");
                    CREATING_ORDER->_progress = 1; //�X�e�[�^�X�𐻑�����
                    func = CREATING_ORDER->_pFunc;
                    pOrder_InManufacturing_save = CREATING_ORDER; //�|�C���^�ꎞ�ޔ�
                    void* arg1 = CREATING_ORDER->_pArg1;
                    void* arg2 = CREATING_ORDER->_pArg2;
                    void* arg3 = CREATING_ORDER->_pArg3;
                    TRACE2("GgafFactory::work ���H�꒷�� �����J�n�I["<<CREATING_ORDER->_id<<"] (�� �M�E�ցE�L)�� ");
                    Sleep(2);
                 ___EndSynchronized1; // <----- �r���I��
//#ifdef MY_DEBUG
//try {
//#endif
                    pObject = (*func)(arg1, arg2, arg3); //���i�̐����I
//#ifdef MY_DEBUG
//} catch (GgafCriticalException& e) {
//    _TRACE_("���H���O�� �������G���[�G"<<e.getMsg());
//    std::string message = "\n�E"+e.getMsg()+"  \n\n���S�����肪�������b�Z�[�W�̏ꍇ�A�����̃o�O�̉\��������܂��B\n���ɐ\���󂲂����܂���B\n";
//    std::string message_dialog = message + "(���uShift + Ctrl + C�v�Ń��b�Z�[�W�̓R�s�[�ł��܂��B)";
//    MessageBox(NULL, message_dialog.c_str(),"���L�̃G���[���������Ă��܂��܂���", MB_OK|MB_ICONSTOP | MB_SETFOREGROUND);
//    _is_working_flg = false;
//    _was_finished_flg = true;
//    GgafGod::_pException_Factory = NEW GgafCriticalException(e.getMsg());
//    return 0;
//}
//#endif

                 ___BeginSynchronized1; // ----->�r���J�n
                    Sleep(2);
                    TRACE2("GgafFactory::work ���H�꒷�� ���������I�i��["<<CREATING_ORDER->_id<<"] (^_^)v");
                    if (CREATING_ORDER == NULL) {
                        TRACE2("GgafFactory::work ���H�꒷�� �K�[���I�B��������������̂ɃL�����Z���������E�E�E�B�j�����܂��BpObject��delete!");
                        DELETE_IMPOSSIBLE_NULL(pObject);
                     ___EndSynchronized1; // <----- �r���I��
                        continue;
                    } else {
                        CREATING_ORDER = pOrder_InManufacturing_save; //�|�C���^���A
                        CREATING_ORDER->_pObject_creation = pObject; //���i�o�^
                        CREATING_ORDER->_progress = 2; //�X�e�[�^�X�𐻑��ς݂�
                        TRACE2("GgafFactory::work ���H�꒷�� �������������̕i["<<(CREATING_ORDER->_id)<<"]���A�I�ɒu���Ƃ��܂��B");
                    }
                } else {
                    TRACE2("GgafFactory::work ���H�꒷�� ����["<<CREATING_ORDER->_id<<"]�͊��ɒI�ɒu���Ă���(_progress == "<<CREATING_ORDER->_progress<<")�B�䂦�ɔ�΂�");
                }
            }
            if (ROOT_ORDER == NULL) {
                //�������ҋ@
                TRACE2("GgafFactory::work ���H�꒷�� �H��ɂ͉��`�������܂���B�����Ȃ�ł��������������I�I�E�E�E�Ȃ��̂�H�B�i�ҋ@�j");
             ___EndSynchronized1; // <----- �r���I��
                if (GgafGod::_pGod->_fps > GGAF_PROPERTY(FPS_TO_CLEAN_GARBAGE_BOX)) {
                    TRACE2("GgafFactory::work ���H�꒷�� FPS�͍�����Ȃ��A���̊Ԃ𗘗p���ăS�~���|���ł�����Ƃ��܂��B1");
                    _pGarbageBox->clean(5); //�ɂȂ̂ŁA�S�~���|��
                    _cnt_cleaned = 0;
                }
            } else {
                if (ROOT_ORDER != NULL && ROOT_ORDER->_pOrder_prev->_progress == 0) {
                    TRACE2("GgafFactory::work ���H�꒷�� �E�E�E�������̒���������C�z�B["<<ROOT_ORDER->_pOrder_prev->_id<<"]�Ȃ̂��H�B");
                    CREATING_ORDER = CREATING_ORDER->_pOrder_next;
                 ___EndSynchronized1; // <----- �r���I��
                    continue;
                } else {
                    TRACE2("GgafFactory::work ���H�꒷�� ���āA�����������͖����B���`�I�ɐ����ς̂����܂��Ă邷�A������ɗ��₪��I�B�i�ҋ@�j");
                 ___EndSynchronized1; // <----- �r���I��
                    if (GgafGod::_pGod->_fps > GGAF_PROPERTY(FPS_TO_CLEAN_GARBAGE_BOX)) {
                        TRACE2("GgafFactory::work ���H�꒷�� FPS�͍����Ȃ��A���̊Ԃ𗘗p���ăS�~���|���ł�����Ƃ��܂��B2");
                        _pGarbageBox->clean(5); //�ɂȂ̂ŁA�S�~���|��
                        _cnt_cleaned = 0;
                    }
                }
            }
            Sleep(2);
        }
        TRACE2("GgafFactory::work ���H�꒷�� �H��͂���ɂēX���܂��ł��B���悤�Ȃ�A�܂���܂��傤�B");
        _was_finished_flg = true;
    } catch (GgafCriticalException& e) {
        _TRACE_("���H���O�� ���Ƃ������Ƃ����݂܂���G"<<e.getMsg());
        _is_working_flg = false;
        _was_finished_flg = true;
        GgafGod::_pException_Factory = NEW GgafCriticalException(e.getMsg());
        return 1;
    }
    return 0;
}

