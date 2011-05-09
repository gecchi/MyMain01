#include "stdafx.h"
using namespace std;

using namespace GgafCore;

//������
GgafOrder* GgafFactory::ROOT_ORDER = NULL;
GgafOrder* GgafFactory::CREATING_ORDER = NULL;
bool GgafFactory::_is_working_flg = true;
bool GgafFactory::_have_to_rest_flg = false;
bool GgafFactory::_is_resting_flg = false;

bool GgafFactory::_was_finished_flg = false;
int GgafFactory::_cnt_cleaned = 0;
GgafGarbageBox* GgafFactory::_pGarbageBox = NULL;

GgafMainActor* GgafFactory::obtainActor(unsigned long prm_id) {
    return (GgafMainActor*)obtain(prm_id);
}

GgafMainScene* GgafFactory::obtainScene(unsigned long prm_id) {
    return (GgafMainScene*)obtain(prm_id);
}

//����
//���̃��\�b�h�̓��C���X���b�h�����s����B
void GgafFactory::order(unsigned long prm_id,
                        GgafObject* (*prm_pFunc)(void*, void*, void*),
                        void* prm_pArg1,
                        void* prm_pArg2,
                        void* prm_pArg3) {
    TRACE2("GgafFactory::order ���q�� �ʃX���b�h�̍H�ꂳ��A[" << prm_id << "]������Ƃ��ā`�B");
    //���ɒ������Ă��Ȃ����`�F�b�N
    GgafOrder* pOrder;
    pOrder = ROOT_ORDER;
    while (pOrder) {
        if (pOrder->_id == prm_id) {
            _TRACE_("���x���� GgafFactory::order [" << prm_id << "]�́A���ɒ������Ă�̂ŃX���[���܂��B�Ӑ}���Ă��Ȃ���΃I�J�V�C�ł���I");
            return;
        }
        if (pOrder->_is_last_order_flg) {
            break;
        }
        pOrder = pOrder->_pOrder_Next;
    }
    //���͖����ł���悤�Ȃ̂ŃX�g�b�N
    GgafOrder* pOrder_New;
    pOrder_New = NEW GgafOrder(prm_id);
    pOrder_New->_pObject_Creation=NULL;
    pOrder_New->_pFunc = prm_pFunc;
    pOrder_New->_pArg1 = prm_pArg1;
    pOrder_New->_pArg2 = prm_pArg2;
    pOrder_New->_pArg3 = prm_pArg3;
    pOrder_New->_progress = 0;
    if (ROOT_ORDER == NULL) {
        TRACE2("GgafFactory::order ���q�� �����A�H��͋�������ł��ˁB�����A�����ł����ˁH�B");
        pOrder_New->_is_first_order_flg = true;
        pOrder_New->_is_last_order_flg = true;
        pOrder_New->_pOrder_Next = pOrder_New;
        pOrder_New->_pOrder_Prev = pOrder_New;
        ROOT_ORDER = pOrder_New;
        CREATING_ORDER = pOrder_New;
    } else {
        TRACE2("GgafFactory::order ���q�� �������܂��Ă܂��ˁA���X�����������܂��B");
        pOrder_New->_is_first_order_flg = false;
        pOrder_New->_is_last_order_flg = true;
        GgafOrder* pOrder_Last;
        pOrder_Last = ROOT_ORDER->_pOrder_Prev;
        pOrder_Last->_is_last_order_flg = false;
        pOrder_Last->_pOrder_Next = pOrder_New;
        pOrder_New->_pOrder_Prev = pOrder_Last;
        pOrder_New->_pOrder_Next = ROOT_ORDER;
        ROOT_ORDER->_pOrder_Prev = pOrder_New;
    }
}

int GgafFactory::chkProgress(unsigned long prm_id) {
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
                pOrder = pOrder->_pOrder_Next;
            }
        }
    }
    return -2;
}

void* GgafFactory::obtain(unsigned long prm_id) {
    TRACE("GgafFactory::obtain "<<prm_id<<"/");
    GgafOrder* pOrder;
    GgafOrder* pOrder_MyNext;
    GgafOrder* pOrder_MyPrev;
    DWORD waittime = 0;
    pOrder = ROOT_ORDER;
    void* objectCreation;
    if (pOrder == NULL) {
        throwGgafCriticalException("GgafFactory::obtain("<<prm_id<<") Error! ������NULL�ł��Boreder��obtain�̑Ή������Ă��܂���B");
    }
    while (_is_working_flg) {

        if (pOrder->_id == prm_id) {
            TRACE2("GgafFactory::obtain ���q�� ����ɂ��́A["<<prm_id<<"]�����ɗ��܂�������ƁB");
            while (_is_working_flg) {
                if (pOrder->_progress != 2) {
                    TRACE2("GgafFactory::obtain ���q�� �ʃX���b�h�H�ꂳ��A["<<prm_id<<"]�̐����܂��`�H�A5�~���b�����҂������悤�BpOrder->_progress="<<(pOrder->_progress));
                    if (waittime > 1000*60) { //��60�b
                        throwGgafCriticalException("GgafFactory::obtain Error! ["<<prm_id<<"]�̐����҂����ԁA�^�C���A�E�g�B\n���炩�̗��R�Ń��C���X���b�h����~���Ă���\�����傫���ł��B");
                    } else {
                        _TEXT_("�c");
                    }

                 ___EndSynchronized; // <----- �r���I��
                    Sleep(5);
                 ___BeginSynchronized; // ----->�r���J�n
                    waittime += 5;
                    continue;
                } else {
                    TRACE2("GgafFactory::obtain ���q�� �����A["<<prm_id<<"]�͐����ς݂ł��ˁA�������I�B�����[���I");
                    if (pOrder->_is_first_order_flg && pOrder->_is_last_order_flg) {
                        objectCreation = pOrder->_pObject_Creation;
                        pOrder->_pObject_Creation = NULL;
                        DELETE_IMPOSSIBLE_NULL(pOrder);
                        pOrder = NULL;
                        ROOT_ORDER = NULL;
                        CREATING_ORDER = NULL;
                        TRACE2("GgafFactory::obtain ���q�� ���i["<<prm_id<<"]�����܂����B���A�����H��͋�ł��ˁB�ɂɂȂ����H�˂��H");
                        return (void*)objectCreation;
                    } else {
                        pOrder_MyNext = pOrder->_pOrder_Next;
                        pOrder_MyPrev = pOrder->_pOrder_Prev;
                        pOrder_MyPrev->_pOrder_Next = pOrder_MyNext;
                        pOrder_MyNext->_pOrder_Prev = pOrder_MyPrev;
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
                        objectCreation = pOrder->_pObject_Creation;
                        pOrder->_pObject_Creation = NULL;
                        DELETE_IMPOSSIBLE_NULL(pOrder);
                        pOrder = NULL;

                        return (void*)objectCreation;
                    }
                }
            }
        } else {
            if (pOrder->_is_last_order_flg) {
                throwGgafCriticalException("GgafFactory::obtain Error! ���H�꒷���S���T���܂������ǁA����Ȓ���(prm_id="<<prm_id<<")�́A����܂���B\n oreder() �� obtain() �̑Ή������Ă��܂���B���� obtain() ���Q��ȏサ�Ă܂��񂩁H�B���ĂȂ��H�A���������ȁ`");
            } else {
                pOrder = pOrder->_pOrder_Next;
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
            GgafOrder* pOrder_MyNext = pOrder->_pOrder_Next;
            DELETE_IMPOSSIBLE_NULL(pOrder);
            pOrder = pOrder_MyNext;
        }
    }
    TRACE2("GgafFactory::clean ���_�� �H���|������");
    return;
}

unsigned __stdcall GgafFactory::work(void* prm_arg) {
    //_CrtSetBreakAlloc(95299);

    try {
        GgafObject* (*func)(void*, void*, void*) = NULL;
        GgafObject* pObject = NULL;
        GgafOrder* pOrder_InManufacturing_save = NULL;
        Sleep(1000); //god �̃C���X�^���X����������܂łق�̂�����Ƒ҂K�v�����邩������Ȃ�
        while (_is_working_flg) {
            if (_have_to_rest_flg) {
                _is_resting_flg = true;
                Sleep(20);
                continue;
            } else {
                _is_resting_flg = false;
            }

         ___BeginSynchronized; // ----->�r���J�n
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
                 ___EndSynchronized; // <----- �r���I��
//#ifdef MY_DEBUG
//try {
//#endif
                    pObject = (*func)(arg1, arg2, arg3); //���i�̐����I
//#ifdef MY_DEBUG
//} catch (GgafCriticalException& e) {
//    _TRACE_("���H���O�� �������G���[�G"<<e.getMsg());
//    string message = "\n�E"+e.getMsg()+"  \n\n���S�����肪�������b�Z�[�W�̏ꍇ�A�����̃o�O�̉\��������܂��B\n���ɐ\���󂲂����܂���B\n";
//    string message_dialog = message + "(���uShift + Ctrl + C�v�Ń��b�Z�[�W�̓R�s�[�ł��܂��B)";
//    MessageBox(NULL, message_dialog.c_str(),"���L�̃G���[���������Ă��܂��܂���", MB_OK|MB_ICONSTOP);
//    _is_working_flg = false;
//    _was_finished_flg = true;
//    GgafGod::_pException_Factory = NEW GgafCriticalException(e.getMsg());
//    return 0;
//}
//#endif

                 ___BeginSynchronized; // ----->�r���J�n
                    Sleep(2);
                    TRACE2("GgafFactory::work ���H�꒷�� ���������I�i��["<<CREATING_ORDER->_id<<"] (^_^)v");
                    if (CREATING_ORDER == NULL) {
                        TRACE2("GgafFactory::work ���H�꒷�� �K�[���I�B��������������̂ɃL�����Z���������E�E�E�B�j�����܂��BpObject��delete!");
                        DELETE_IMPOSSIBLE_NULL(pObject);
                     ___EndSynchronized; // <----- �r���I��
                        continue;
                    } else {
                        CREATING_ORDER = pOrder_InManufacturing_save; //�|�C���^���A
                        CREATING_ORDER->_pObject_Creation = pObject; //���i�o�^
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
             ___EndSynchronized; // <----- �r���I��
                if (GgafGod::_pGod->_fps > PROPERTY(FPS_TO_CLEAN_GARBAGE_BOX)) {
                    TRACE2("GgafFactory::work ���H�꒷�� FPS�͍�����Ȃ��A���̊Ԃ𗘗p���ăS�~���|���ł�����Ƃ��܂��B1");
                    _pGarbageBox->clean(10); //�ɂȂ̂ŁA�S�~���|��
                    _cnt_cleaned = 0;
                }
            } else {
                if (ROOT_ORDER != NULL && ROOT_ORDER->_pOrder_Prev->_progress == 0) {
                    TRACE2("GgafFactory::work ���H�꒷�� �E�E�E�������̒���������C�z�B["<<ROOT_ORDER->_pOrder_Prev->_id<<"]�Ȃ̂��H�B");
                    CREATING_ORDER = CREATING_ORDER->_pOrder_Next;
                 ___EndSynchronized; // <----- �r���I��
                    continue;
                } else {
                    TRACE2("GgafFactory::work ���H�꒷�� ���āA�����������͖����B���`�I�ɐ����ς̂����܂��Ă邷�A������ɗ��₪��I�B�i�ҋ@�j");
                 ___EndSynchronized; // <----- �r���I��
                    if (GgafGod::_pGod->_fps > PROPERTY(FPS_TO_CLEAN_GARBAGE_BOX)) {
                        TRACE2("GgafFactory::work ���H�꒷�� FPS�͍����Ȃ��A���̊Ԃ𗘗p���ăS�~���|���ł�����Ƃ��܂��B2");
                        _pGarbageBox->clean(10); //�ɂȂ̂ŁA�S�~���|��
                        _cnt_cleaned = 0;
                    }
                }
            }
            Sleep(10);
        }
        TRACE2("GgafFactory::work ���H�꒷�� �H��͂���ɂēX���܂��ł��B���悤�Ȃ�A�܂���܂��傤�B");
        _was_finished_flg = true;
        return 0;
    } catch (GgafCriticalException& e) {
        _TRACE_("���H���O�� ���Ƃ������Ƃ����݂܂���G"<<e.getMsg());
        _is_working_flg = false;
        _was_finished_flg = true;
        GgafGod::_pException_Factory = NEW GgafCriticalException(e.getMsg());
        return 0;
    }
}

