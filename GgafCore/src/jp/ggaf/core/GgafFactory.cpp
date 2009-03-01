#include "stdafx.h"
using namespace std;

using namespace GgafCore;

//������
GgafGod* GgafFactory::_pGod = NULL;
GgafOrder* GgafFactory::ROOT_ORDER = NULL;
GgafOrder* GgafFactory::CREATING_ORDER = NULL;
bool GgafFactory::_isWorkingFlg = true;
bool GgafFactory::_isRestFlg = false;
bool GgafFactory::_isRestingFlg = false;

bool GgafFactory::_isFinishFlg = false;
int GgafFactory::_cnt_cleaned = 0;
GgafGarbageBox* GgafFactory::_pGarbageBox = NULL;

GgafMainActor* GgafFactory::obtainActor(unsigned long prm_id) {
    return (GgafMainActor*)obtain(prm_id);
}

GgafMainScene* GgafFactory::obtainScene(unsigned long prm_id) {
    return (GgafMainScene*)obtain(prm_id);
}

void GgafFactory::order(unsigned long prm_id,
                        GgafObject* (*prm_pFunc)(void*, void*, void*),
                        void* prm_pArg1,
                        void* prm_pArg2,
                        void* prm_pArg3) {
    TRACE2("GgafFactory::order ���q�� �ʃX���b�h�H�ꂳ��A[" << prm_id << "]������Ƃ��ā`�B");
    static GgafOrder* pOrder_New;
    pOrder_New = NEW GgafOrder(prm_id);
    pOrder_New->_pObject_Creation=NULL;
    pOrder_New->_pFunc = prm_pFunc;
    pOrder_New->_pArg1 = prm_pArg1;
    pOrder_New->_pArg2 = prm_pArg2;
    pOrder_New->_pArg3 = prm_pArg3;
    pOrder_New->_progress = 0;
    if (ROOT_ORDER == NULL) {
        TRACE2("GgafFactory::order ���q�� ��������̍H��֒������Ă���B�����ł����ˁH�B");
        pOrder_New->_isFirstOrderFlg = true;
        pOrder_New->_isLastOrderFlg = true;
        pOrder_New->_pOrder_Next = pOrder_New;
        pOrder_New->_pOrder_Prev = pOrder_New;
        ROOT_ORDER = pOrder_New;
        CREATING_ORDER = pOrder_New;
    } else {
        TRACE2("GgafFactory::order ���q�� ���X�ɂ��܂�̂�");
        pOrder_New->_isFirstOrderFlg = false;
        pOrder_New->_isLastOrderFlg = true;
        static GgafOrder* pOrder_Last;
        pOrder_Last = ROOT_ORDER->_pOrder_Prev;
        pOrder_Last->_isLastOrderFlg = false;
        pOrder_Last->_pOrder_Next = pOrder_New;
        pOrder_New->_pOrder_Prev = pOrder_Last;
        pOrder_New->_pOrder_Next = ROOT_ORDER;
        ROOT_ORDER->_pOrder_Prev = pOrder_New;
    }
}

void* GgafFactory::obtain(unsigned long prm_id) {
    TRACE("GgafFactory::obtain "<<prm_id<<"/");
    static GgafOrder* pOrder;
    static GgafOrder* pOrder_MyNext;
    static GgafOrder* pOrder_MyPrev;
    pOrder = ROOT_ORDER;
    void* objectCreation;
    if (pOrder == NULL) {
        throwGgafCriticalException("GgafFactory::obtain Error! ������NULL�ł��Boreder��obtain�̑Ή������Ă��܂���)");
    }
    while (_isWorkingFlg) {

        if (pOrder->_id == prm_id) {
            TRACE2("GgafFactory::obtain ���q�� ����ɂ��́A["<<prm_id<<"]�����ɗ��܂�������ƁB");
            while (_isWorkingFlg) {
                if (pOrder->_progress != 2) {
                    TRACE2("GgafFactory::obtain ���q�� �ʃX���b�h�H�ꂳ��A["<<prm_id<<"]�܂��`�H�A2�~���b�҂������悤�BpOrder->_progress="<<(pOrder->_progress));
                 ___EndSynchronized; // <----- �r���I��
                    Sleep(2);
                 ___BeginSynchronized; // ----->�r���J�n
                    continue;
                } else {
                    TRACE2("GgafFactory::obtain ���q�� �����A["<<prm_id<<"]�͐����ς݂ł��ˁA�����[���I");
                    if (pOrder->_isFirstOrderFlg && pOrder->_isLastOrderFlg) {
                        objectCreation = pOrder->_pObject_Creation;
                        pOrder->_pObject_Creation = NULL;
                        DELETE_IMPOSSIBLE_NULL(pOrder);
                        pOrder = NULL;
                        ROOT_ORDER = NULL;
                        CREATING_ORDER = NULL;
                        TRACE2("GgafFactory::obtain ���q�� ���i["<<prm_id<<"]�����܂����B���A�H��͋�ł��ˁB�ɂȂ́H");
                        return (void*)objectCreation;
                    } else {
                        pOrder_MyNext = pOrder->_pOrder_Next;
                        pOrder_MyPrev = pOrder->_pOrder_Prev;
                        pOrder_MyPrev->_pOrder_Next = pOrder_MyNext;
                        pOrder_MyNext->_pOrder_Prev = pOrder_MyPrev;
                        if (pOrder->_isLastOrderFlg) {
                            pOrder_MyPrev->_isLastOrderFlg = true;
                            CREATING_ORDER = pOrder_MyPrev;
                        }
                        if (pOrder->_isFirstOrderFlg) {
                            pOrder_MyNext->_isFirstOrderFlg = true;
                            ROOT_ORDER = pOrder_MyNext;
                            CREATING_ORDER = pOrder_MyNext;
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
            if (pOrder->_isLastOrderFlg) {
                throwGgafCriticalException("GgafFactory::obtain Error! �S���T���܂������ǁA����Ȓ���(prm_id="<<prm_id<<")�́A����Ⴕ�܂ւ�Boreder��obtain�̑Ή������Ă��܂���");
            } else {
                pOrder = pOrder->_pOrder_Next;
            }
        }
    }
    if (GgafGod::_pException_Factory != NULL) {
        throw *(GgafGod::_pException_Factory);
    }
    return NULL;
}

void GgafFactory::clean() {
    TRACE("GgafFactory::clean ���_�� �H���|���J�n");
    GgafOrder* pOrder = ROOT_ORDER;
    if (pOrder == NULL) {
        return;
    }
    while (true) {
        if (pOrder->_isLastOrderFlg) {
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
    try {
        static GgafObject* (*func)(void*, void*, void*);
        static GgafObject* pObject;
        static GgafOrder* pOrder_InManufacturing_save;
        Sleep(1000); //god �̃C���X�^���X����������܂łق�̂�����Ƒ҂K�v�����邩������Ȃ�
        while (_isWorkingFlg) {
            if (_isRestFlg) {
                _isRestingFlg = true;
                Sleep(20);
                continue;
            } else {
                _isRestingFlg = false;
            }

         ___BeginSynchronized; // ----->�r���J�n
            if (CREATING_ORDER != NULL) {
                if (CREATING_ORDER->_progress == 0) { //������Ȃ�܂����
                    TRACE2("GgafFactory::work ���H�ꁄ ����["<<CREATING_ORDER->_id<<"]�͖�����(_progress == "<<CREATING_ORDER->_progress<<")�B�䂦�ɍ��܂��I");
                    CREATING_ORDER->_progress = 1; //�X�e�[�^�X�𐻑�����
                    func = CREATING_ORDER->_pFunc;
                    pOrder_InManufacturing_save = CREATING_ORDER; //�|�C���^�ꎞ�ޔ�
                    void* arg1 = CREATING_ORDER->_pArg1;
                    void* arg2 = CREATING_ORDER->_pArg2;
                    void* arg3 = CREATING_ORDER->_pArg3;
                    TRACE2("GgafFactory::work ���H�ꁄ �����J�n�I["<<CREATING_ORDER->_id<<"]");
                 ___EndSynchronized; // <----- �r���I��
                    Sleep(2);
                    pObject = (*func)(arg1, arg2, arg3); //���i�̐����I�I�I�I
                    Sleep(2);
                 ___BeginSynchronized; // ----->�r���J�n
                    TRACE2("GgafFactory::work ���H�ꁄ ���������I["<<CREATING_ORDER->_id<<"] (^_^)v");
                    if (CREATING_ORDER == NULL) {
                        TRACE2("GgafFactory::work ���H�ꁄ �K�[���I�B��������������̂ɃL�����Z��������(T_T)�B�j�����܂��BpObject��delete!");
                        DELETE_IMPOSSIBLE_NULL(pObject);
                     ___EndSynchronized; // <----- �r���I��
                        Sleep(20);
                        continue;
                    } else {
                        CREATING_ORDER = pOrder_InManufacturing_save; //�|�C���^���A
                        CREATING_ORDER->_pObject_Creation = pObject; //���i�o�^
                        CREATING_ORDER->_progress = 2; //�X�e�[�^�X�𐻑��ς݂�
                        TRACE2("GgafFactory::work ���H�ꁄ �������������̕i["<<(CREATING_ORDER->_id)<<"]���A�I�ɒu���Ƃ��܂��B");
                    }
                } else {
                    TRACE2("GgafFactory::work ���H�ꁄ ����["<<CREATING_ORDER->_id<<"]�͊��ɒI�ɒu���Ă���(_progress == "<<CREATING_ORDER->_progress<<")�B�䂦�ɔ�΂�");
                }
            }
            if (ROOT_ORDER == NULL) {
                //�������ҋ@
                TRACE2("GgafFactory::work ���H�ꁄ �H��ɂ͉��`�������܂���B�����Ȃ�ł��������������I�B�ɂȂ̂ŃS�~���|���ł�����Ƃ��܂��B�i�ҋ@�j");
             ___EndSynchronized; // <----- �r���I��
                if (_pGod->_fFps > 52) {
                    Sleep(5);
                    TRACE2("GgafFactory::work ���H�ꁄ �_������]�T���邵�A�ɂȂ̂ŃS�~���|���ł�����Ƃ��܂��B");
                    _pGarbageBox->cleane(1); //�ɂȂ̂ŁA�S�~���|��
                    _cnt_cleaned = 0;
                }
            } else {
                if (ROOT_ORDER != NULL && ROOT_ORDER->_pOrder_Prev->_progress == 0) {
                    TRACE2("GgafFactory::work ���H�ꁄ ����ށA���ɖ������̒���["<<CREATING_ORDER->_pOrder_Next->_id<<"]�������");
                    CREATING_ORDER = CREATING_ORDER->_pOrder_Next;
                 ___EndSynchronized; // <----- �r���I��
                    Sleep(10);
                    continue;
                } else {
                    TRACE2("GgafFactory::work ���H�ꁄ �悵�A�����������͖����B���`�I�ɐ����ς̂����܂��Ă邷�A������ɗ��₪��I�B�i�ҋ@�j");
                 ___EndSynchronized; // <----- �r���I��
                    if (_pGod->_fFps > 52) {
                        TRACE2("GgafFactory::work ���H�ꁄ �_������]�T���邵�A�ɂȂ̂ŃS�~���|���ł�����Ƃ��܂��B");
                        Sleep(5);
                        _pGarbageBox->cleane(1); //�ɂȂ̂ŁA�S�~���|��
                        _cnt_cleaned = 0;
                    }
                }
            }
            Sleep(20);
        }
        TRACE2("GgafFactory::work ���H�ꁄ �H��͂���ɂēX���܂��ł��B���悤�Ȃ�A�܂���܂��傤�B");
        _isFinishFlg = true;
        return 0;
    } catch (GgafCriticalException& e) {
        _TRACE_("���H���O�� ���Ƃ������Ƃ����݂܂���G"<<e.getMsg());
        _isWorkingFlg = false;
        _isFinishFlg = true;
        GgafGod::_pException_Factory = NEW GgafCriticalException(e.getMsg());
        return 0;
    }
}

