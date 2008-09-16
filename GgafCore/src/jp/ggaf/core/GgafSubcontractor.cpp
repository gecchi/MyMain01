#include "stdafx.h"

//������
GgafGod* GgafFactory::_pGod = NULL;
GgafOrder* GgafFactory::ROOT_ORDER = NULL;
GgafOrder* GgafFactory::CREATING_ORDER = NULL;
bool       GgafFactory::_isWorking = true;
bool       GgafFactory::_isFinish  = false;

void GgafFactory::orderActor(string prm_id, GgafMainActor* (*prm_functionForBuild)(void*), void* prm_argumentForBuild) {
	order(prm_id, (GgafObject* (*)(void*))prm_functionForBuild, prm_argumentForBuild);
}

void GgafFactory::orderScene(string prm_id, GgafMainScene* (*prm_functionForBuild)(void*), void* prm_argumentForBuild) {
	order(prm_id, (GgafObject* (*)(void*))prm_functionForBuild, prm_argumentForBuild);
}

GgafMainActor* GgafFactory::obtainActor(string prm_id) {
	return (GgafMainActor*)obtain(prm_id);
}

GgafMainScene* GgafFactory::obtainScene(string prm_id) {
	return (GgafMainScene*)obtain(prm_id);
}

void GgafFactory::order(string prm_id, GgafObject* (*prm_functionForBuild)(void*), void* prm_argumentForBuild) {
	TRACE("GgafFactory::order �ʃX���b�h����A" << prm_id << "������Ƃ��āB");
	GgafOrder* pOrder_New = NEW GgafOrder(prm_id);
	pOrder_New->_pObject_Creation=NULL;
	pOrder_New->_functionForBuild = prm_functionForBuild;
	pOrder_New->_argumentForBuild = prm_argumentForBuild;
	pOrder_New->_progress = 0;
	//::EnterCriticalSection(&(GgafGod::CS1)); // -----> �r���J�n
	if (ROOT_ORDER == NULL) {
		TRACE("GgafFactory::order ["<<prm_id<<"] ���A��������̍H��֒������Ă���");
        pOrder_New -> _isFirstOrder = true;
        pOrder_New -> _isLastOrder = true;
        pOrder_New->_pOrder_Next = pOrder_New;
        pOrder_New->_pOrder_Prev = pOrder_New;
        ROOT_ORDER = pOrder_New;
        CREATING_ORDER = pOrder_New;
        //::LeaveCriticalSection(&(GgafGod::CS1)); // <----- �r���I��
	} else {
		TRACE("GgafFactory::order ["<<prm_id<<"] ������ɒǉ�����");
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
			TRACE("GgafFactory::obtain ["<<prm_id<<"]�̒������ɗ��܂����B");
			while(_isWorking) {
				if (pOrder->_progress != 2) {
					_TRACE_("GgafFactory::obtain �ʃX���b�h����A["<<prm_id<<"]�܂��`�H�A���傱���Ƒ҂��܂��BpOrder->_progress "<<(pOrder->_progress)<<"������");
					::LeaveCriticalSection(&(GgafGod::CS1)); // <----- �r���I��
					Sleep(10);
					::EnterCriticalSection(&(GgafGod::CS1)); // -----> �r���J�n
					continue;
				} else {
					TRACE("GgafFactory::obtain �����A���i["<<prm_id<<"]�͐��������ł��ˁA�����[���I");
					if (pOrder->_isFirstOrder && pOrder->_isLastOrder) {
						objectCreation = pOrder->_pObject_Creation;
						pOrder->_pObject_Creation = NULL;
						delete pOrder;
						pOrder = NULL;
						ROOT_ORDER = NULL;
						CREATING_ORDER = NULL;
						TRACE("GgafFactory::obtain ���i["<<prm_id<<"]�����܂����B�H��͋�ł���");
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
						delete pOrder;
						pOrder = NULL;

						//::LeaveCriticalSection(&(GgafGod::CS1)); // <----- �r���I��
						return (void*)objectCreation;
					}
				}
			}
		} else {
			if (pOrder->_isLastOrder) {
				//::LeaveCriticalSection(&(GgafGod::CS1)); // <----- �r���I��
				throw_GgafCriticalException("GgafFactory::obtain Error! �S���T���܂������ǁA����Ȓ���(prm_id="<<prm_id<<")�͂���܂���ł����Boreder��obtain�̑Ή������Ă��܂���");
			} else {
				pOrder = pOrder ->_pOrder_Next;
			}
		}
	}
	return NULL;
}


void GgafFactory::clean() {
	TRACE("GgafFactory::clean �H���|���J�n");
	GgafOrder* pOrder = ROOT_ORDER;
	if (pOrder == NULL) {
		return;
	}
	while(true) {
		if (pOrder->_isLastOrder) {
			TRACE("GgafFactory::clean ���i�폜["<<pOrder->_id<<"]�A�Ō�̃X�g�b�N");
			delete pOrder;
			pOrder = NULL;
			ROOT_ORDER = NULL;
			CREATING_ORDER = NULL;
			break;
		} else {
			TRACE("GgafFactory::clean ���i�폜["<<pOrder->_id<<"]");
			GgafOrder* pOrder_MyNext = pOrder -> _pOrder_Next;
			delete pOrder;
			pOrder = pOrder_MyNext;
		}
	}
	TRACE("GgafFactory::clean �H���|������");
	return;
}


unsigned __stdcall GgafFactory::work(void* prm_arg) {
	GgafObject* (*func)(void*);
	GgafObject* pObject;
	GgafOrder* pOrder_InManufacturing_save;
	while(_isWorking) {
		::EnterCriticalSection(&(GgafGod::CS1)); // -----> �r���J�n
		if (CREATING_ORDER != NULL) {
			if (CREATING_ORDER  -> _progress == 0) { //������Ȃ�܂����
				TRACE2("GgafFactory::work ����["<<CREATING_ORDER->_id<<"]�͖�����(_progress == "<<CREATING_ORDER  -> _progress<<")�䂦�ɍ��܂��B");
				CREATING_ORDER  -> _progress = 1;    //�X�e�[�^�X�𐻑�����
				func = CREATING_ORDER ->_functionForBuild;
				pOrder_InManufacturing_save = CREATING_ORDER; //�|�C���^�ꎞ�ޔ�
				void* arg = CREATING_ORDER ->_argumentForBuild;
				TRACE2("GgafFactory::work �����J�n�I["<<CREATING_ORDER->_id<<"]");
				::LeaveCriticalSection(&(GgafGod::CS1)); // <----- �r���I��
				Sleep(2);
				pObject = (*func)(arg); //���i�̐����I
				Sleep(2);
				::EnterCriticalSection(&(GgafGod::CS1)); // -----> �r���J�n
				TRACE2("GgafFactory::work ���������I["<<CREATING_ORDER->_id<<"]");
				if (CREATING_ORDER == NULL) {
					TRACE2("GgafFactory::work ��������������̂ɒx�������悤��(T_T)!�����������ɂ��܂��BpObject�̍폜");
					delete ((GgafActor*)pObject);
					::LeaveCriticalSection(&(GgafGod::CS1)); // <----- �r���I��
					Sleep(10);
					continue;
				} else {
					CREATING_ORDER = pOrder_InManufacturing_save;  //�|�C���^���A
					CREATING_ORDER -> _pObject_Creation = pObject; //���i�o�^
					CREATING_ORDER -> _progress = 2;               //�X�e�[�^�X�𐻑��ς݂�
					TRACE2("GgafFactory::work �����̕i["<<(CREATING_ORDER->_id)<<"]���A�ł��܂����I");
				}
			} else {
				TRACE2("GgafFactory::work ����["<<CREATING_ORDER->_id<<"]�͐����ς݃b�X(_progress == "<<CREATING_ORDER  -> _progress<<")�䂦�ɂƂ΂�");
			}
		}
		if (ROOT_ORDER == NULL) {
			//�������ҋ@
			TRACE2("GgafFactory::work �H��ɂ͉�������܂���B�����Ȃ�ł��������₪��I�i�ҋ@�j");
			::LeaveCriticalSection(&(GgafGod::CS1)); // <----- �r���I��
		} else {
			if (ROOT_ORDER != NULL && ROOT_ORDER -> _pOrder_Prev -> _progress == 0) {
				TRACE2("GgafFactory::work ����ށA���ɖ������̒���["<<CREATING_ORDER->_pOrder_Next->_id<<"]�������");
				CREATING_ORDER = CREATING_ORDER -> _pOrder_Next;
				::LeaveCriticalSection(&(GgafGod::CS1)); // <----- �r���I��
				Sleep(10);
				continue;
			} else {
				TRACE2("GgafFactory::work �����ς̒����͂��邪�A�����������͖����B���Ă����`���i�ҋ@�j");
				::LeaveCriticalSection(&(GgafGod::CS1)); // <----- �r���I��
			}
		}
		Sleep(10);
	}
	TRACE2("GgafFactory::work �H��͂���ɂēX���܂��ł��B�ł́A�܂���܂��傤�B");
	_isFinish = true;
	return 0;
}

