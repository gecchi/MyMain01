#include "stdafx.h"

//������
GgafGod* GgafFactory::_pGod = NULL;
GgafOrder* GgafFactory::ROOT_ORDER = NULL;
GgafOrder* GgafFactory::CREATING_ORDER = NULL;
bool       GgafFactory::_isWorking = true;
bool       GgafFactory::_isFinish  = false;
int GgafFactory::_s_iCountCleanedNode = 0;
GgafTrashBox* GgafFactory::_pTrashBox = NULL;

GgafMainActor* GgafFactory::obtainActor(string prm_id) {
	return (GgafMainActor*)obtain(prm_id);
}

GgafMainScene* GgafFactory::obtainScene(string prm_id) {
	return (GgafMainScene*)obtain(prm_id);
}

void GgafFactory::order(string prm_id, GgafObject* (*prm_pFunc)(void*, void*), void* prm_pArg1, void* prm_pArg2) {
	TRACE2("GgafFactory::order ���q�� �ʃX���b�h�H�ꂳ��A[" << prm_id << "]������Ƃ��ā`�B");
	GgafOrder* pOrder_New = NEW GgafOrder(prm_id);
	pOrder_New->_pObject_Creation=NULL;
	pOrder_New->_pFunc = prm_pFunc;
	pOrder_New->_pArg1 = prm_pArg1;
	pOrder_New->_pArg2 = prm_pArg2;
	pOrder_New->_progress = 0;
	//::EnterCriticalSection(&(GgafGod::CS1)); // -----> �r���J�n
	if (ROOT_ORDER == NULL) {
		TRACE2("GgafFactory::order ���q�� ��������̍H��֒������Ă���B�����ł����ˁH�B");
        pOrder_New -> _isFirstOrder = true;
        pOrder_New -> _isLastOrder = true;
        pOrder_New->_pOrder_Next = pOrder_New;
        pOrder_New->_pOrder_Prev = pOrder_New;
        ROOT_ORDER = pOrder_New;
        CREATING_ORDER = pOrder_New;
        //::LeaveCriticalSection(&(GgafGod::CS1)); // <----- �r���I��
	} else {
		TRACE2("GgafFactory::order ���q�� ���X�ɂ��܂�̂�");
        pOrder_New -> _isFirstOrder = false;
		pOrder_New -> _isLastOrder = true;
        GgafOrder* pOrder_Last = ROOT_ORDER->_pOrder_Prev;
        pOrder_Last -> _isLastOrder = false;
        pOrder_Last->_pOrder_Next = pOrder_New;
        pOrder_New->_pOrder_Prev = pOrder_Last;
        pOrder_New->_pOrder_Next = ROOT_ORDER;
        ROOT_ORDER->_pOrder_Prev = pOrder_New;
        //::LeaveCriticalSection(&(GgafGod::CS1)); // <----- �r���I��
	}
}



void* GgafFactory::obtain(string prm_id) {
	//::EnterCriticalSection(&(GgafGod::CS1)); // -----> �r���J�n
	TRACE("GgafFactory::obtain "<<prm_id<<"/");
	GgafOrder* pOrder = ROOT_ORDER;
	GgafOrder* pOrder_MyNext;
	GgafOrder* pOrder_MyPrev;

	void* objectCreation;
	if (pOrder == NULL) {
		//::LeaveCriticalSection(&(GgafGod::CS1)); // <----- �r���I��
		throw_GgafCriticalException("GgafFactory::obtain Error! ������NULL�ł��Boreder��obtain�̑Ή������Ă��܂���)");
	}
	while(_isWorking) {
		if (pOrder->_id == prm_id) {
			TRACE2("GgafFactory::obtain ���q�� ����ɂ��́A["<<prm_id<<"]�����ɗ��܂�������ƁB");
			while(_isWorking) {
				if (pOrder->_progress != 2) {
					_TRACE_("GgafFactory::obtain ���q�� �ʃX���b�h�H�ꂳ��A["<<prm_id<<"]�܂��`�H�A2�~���b�҂������悤�BpOrder->_progress="<<(pOrder->_progress));
					::LeaveCriticalSection(&(GgafGod::CS1)); // <----- �r���I��
					Sleep(2);
					::EnterCriticalSection(&(GgafGod::CS1)); // -----> �r���J�n
					continue;
				} else {
					TRACE2("GgafFactory::obtain ���q�� �����A["<<prm_id<<"]�͐����ς݂ł��ˁA�����[���I");
					if (pOrder->_isFirstOrder && pOrder->_isLastOrder) {
						objectCreation = pOrder->_pObject_Creation;
						pOrder->_pObject_Creation = NULL;
						DELETE_IMPOSSIBLE_NULL(pOrder);
						pOrder = NULL;
						ROOT_ORDER = NULL;
						CREATING_ORDER = NULL;
						TRACE2("GgafFactory::obtain ���q�� ���i["<<prm_id<<"]�����܂����B���A�H��͋�ł��ˁB�ɂȂ́H");
						//::LeaveCriticalSection(&(GgafGod::CS1)); // <----- �r���I��
						return (void*)objectCreation;
					} else {
						pOrder_MyNext = pOrder -> _pOrder_Next;
						pOrder_MyPrev = pOrder -> _pOrder_Prev;
						pOrder_MyPrev -> _pOrder_Next = pOrder_MyNext;
						pOrder_MyNext -> _pOrder_Prev = pOrder_MyPrev;
						if (pOrder->_isLastOrder) {
							pOrder_MyPrev->_isLastOrder = true;
							CREATING_ORDER = pOrder_MyPrev;
						}
						if (pOrder->_isFirstOrder) {
							pOrder_MyNext->_isFirstOrder = true;
							ROOT_ORDER = pOrder_MyNext;
							CREATING_ORDER = pOrder_MyNext;
						}
						objectCreation = pOrder->_pObject_Creation;
						pOrder->_pObject_Creation = NULL;
						DELETE_IMPOSSIBLE_NULL(pOrder);
						pOrder = NULL;

						//::LeaveCriticalSection(&(GgafGod::CS1)); // <----- �r���I��
						return (void*)objectCreation;
					}
				}
			}
		} else {
			if (pOrder->_isLastOrder) {
				//::LeaveCriticalSection(&(GgafGod::CS1)); // <----- �r���I��
				throw_GgafCriticalException("GgafFactory::obtain Error! �S���T���܂������ǁA����Ȓ���(prm_id="<<prm_id<<")�́A����Ⴕ�܂ւ�Boreder��obtain�̑Ή������Ă��܂���");
			} else {
				pOrder = pOrder ->_pOrder_Next;
			}
		}
	}
	return NULL;
}


void GgafFactory::clean() {
	TRACE("GgafFactory::clean ���_�� �H���|���J�n");
	GgafOrder* pOrder = ROOT_ORDER;
	if (pOrder == NULL) {
		return;
	}
	while(true) {
		if (pOrder->_isLastOrder) {
			TRACE2("GgafFactory::clean ���_�� ���i�폜["<<pOrder->_id<<"]�A�Ō�̃X�g�b�N");
			DELETE_IMPOSSIBLE_NULL(pOrder);
			pOrder = NULL;
			ROOT_ORDER = NULL;
			CREATING_ORDER = NULL;
			break;
		} else {
			TRACE2("GgafFactory::clean ���_�� ���i�폜["<<pOrder->_id<<"]");
			GgafOrder* pOrder_MyNext = pOrder -> _pOrder_Next;
			DELETE_IMPOSSIBLE_NULL(pOrder);
			pOrder = pOrder_MyNext;
		}
	}
	TRACE2("GgafFactory::clean ���_�� �H���|������");
	return;
}


unsigned __stdcall GgafFactory::work(void* prm_arg) {
	try {
		GgafObject* (*func)(void*, void*);
		GgafObject* pObject;
		GgafOrder* pOrder_InManufacturing_save;
		while(_isWorking) {

			::EnterCriticalSection(&(GgafGod::CS1)); // -----> �r���J�n
			if (CREATING_ORDER != NULL) {
				if (CREATING_ORDER  -> _progress == 0) { //������Ȃ�܂����
					TRACE2("GgafFactory::work ���H�ꁄ ����["<<CREATING_ORDER->_id<<"]�͖�����(_progress == "<<CREATING_ORDER -> _progress<<")�B�䂦�ɍ��܂��I");
					CREATING_ORDER  -> _progress = 1;    //�X�e�[�^�X�𐻑�����
					func = CREATING_ORDER ->_pFunc;
					pOrder_InManufacturing_save = CREATING_ORDER; //�|�C���^�ꎞ�ޔ�
					void* arg1 = CREATING_ORDER ->_pArg1;
					void* arg2 = CREATING_ORDER ->_pArg2;
					TRACE2("GgafFactory::work ���H�ꁄ �����J�n�I["<<CREATING_ORDER->_id<<"]");
					::LeaveCriticalSection(&(GgafGod::CS1)); // <----- �r���I��
					Sleep(2);
					pObject = (*func)(arg1, arg2); //���i�̐����I�I�I�I
					Sleep(2);
					::EnterCriticalSection(&(GgafGod::CS1)); // -----> �r���J�n
					TRACE2("GgafFactory::work ���H�ꁄ ���������I["<<CREATING_ORDER->_id<<"] (^_^)v");
					if (CREATING_ORDER == NULL) {
						TRACE2("GgafFactory::work ���H�ꁄ �K�[���I�B��������������̂ɃL�����Z��������(T_T)�B�j�����܂��BpObject��delete!");
						DELETE_IMPOSSIBLE_NULL(pObject);
						::LeaveCriticalSection(&(GgafGod::CS1)); // <----- �r���I��
						Sleep(20);
						continue;
					} else {
						CREATING_ORDER = pOrder_InManufacturing_save;  //�|�C���^���A
						CREATING_ORDER -> _pObject_Creation = pObject; //���i�o�^
						CREATING_ORDER -> _progress = 2;               //�X�e�[�^�X�𐻑��ς݂�
						TRACE2("GgafFactory::work ���H�ꁄ �������������̕i["<<(CREATING_ORDER->_id)<<"]���A�I�ɒu���Ƃ��܂��B");
					}
				} else {
					TRACE2("GgafFactory::work ���H�ꁄ ����["<<CREATING_ORDER->_id<<"]�͊��ɒI�ɒu���Ă���(_progress == "<<CREATING_ORDER  -> _progress<<")�B�䂦�ɔ�΂�");
				}
			}
			if (ROOT_ORDER == NULL) {
				//�������ҋ@
				TRACE2("GgafFactory::work ���H�ꁄ �H��ɂ͉��`�������܂���B�����Ȃ�ł��������������I�B�ɂȂ̂ŃS�~���|���ł�����Ƃ��܂��B�i�ҋ@�j");
				::LeaveCriticalSection(&(GgafGod::CS1)); // <----- �r���I��
				if (_pGod->_fFps > 52) {
					Sleep(5);
					TRACE2("GgafFactory::work ���H�ꁄ �_������]�T���邵�A�ɂȂ̂ŃS�~���|���ł�����Ƃ��܂��B");
					_pTrashBox->cleane(1); //�ɂȂ̂ŁA�S�~���|��
					_s_iCountCleanedNode = 0;
				}
			} else {
				if (ROOT_ORDER != NULL && ROOT_ORDER -> _pOrder_Prev -> _progress == 0) {
					TRACE2("GgafFactory::work ���H�ꁄ ����ށA���ɖ������̒���["<<CREATING_ORDER->_pOrder_Next->_id<<"]�������");
					CREATING_ORDER = CREATING_ORDER -> _pOrder_Next;
					::LeaveCriticalSection(&(GgafGod::CS1)); // <----- �r���I��
					Sleep(10);
					continue;
				} else {
					TRACE2("GgafFactory::work ���H�ꁄ �悵�A�����������͖����B���`�I�ɐ����ς̂����܂��Ă邷�A������ɗ��₪��I�B�i�ҋ@�j");
					::LeaveCriticalSection(&(GgafGod::CS1)); // <----- �r���I��
					if (_pGod->_fFps > 52) {
						TRACE2("GgafFactory::work ���H�ꁄ �_������]�T���邵�A�ɂȂ̂ŃS�~���|���ł�����Ƃ��܂��B");
						Sleep(5);
						_pTrashBox->cleane(1); //�ɂȂ̂ŁA�S�~���|��
						_s_iCountCleanedNode = 0;
					}
				}
			}
			Sleep(20);
		}
		TRACE2("GgafFactory::work ���H�ꁄ �H��͂���ɂēX���܂��ł��B���悤�Ȃ�A�܂���܂��傤�B");
		_isFinish = true;
		return 0;
	} catch (GgafCriticalException& e) {
		_TRACE_("���H���O�� ���Ƃ������Ƃ����݂܂���G"<<e.getMsg());
		_isWorking = false;
		_isFinish = true;
		GgafGod::_pException_Factory = NEW GgafCriticalException(e.getMsg());
		return 0;
	}
}

