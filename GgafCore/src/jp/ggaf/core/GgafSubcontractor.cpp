#include "stdafx.h"

//������
GgafGod* GgafSubcontractor::_pGod = NULL;
GgafOrder* GgafSubcontractor::_pOrder_First = NULL;
GgafOrder* GgafSubcontractor::_pOrder_InManufacturing = NULL;
bool       GgafSubcontractor::_isWorking = true;

void GgafSubcontractor::orderActor(string prm_id, GgafMainActor* (*prm_functionForBuild)(void*), void* prm_argumentForBuild) {
	order(prm_id, (GgafObject* (*)(void*))prm_functionForBuild, prm_argumentForBuild);
}

void GgafSubcontractor::orderScene(string prm_id, GgafMainScene* (*prm_functionForBuild)(void*), void* prm_argumentForBuild) {
	order(prm_id, (GgafObject* (*)(void*))prm_functionForBuild, prm_argumentForBuild);
}

GgafMainActor* GgafSubcontractor::obtainActor(string prm_id) {
	return (GgafMainActor*)obtain(prm_id);
}

GgafMainScene* GgafSubcontractor::obtainScene(string prm_id) {
	return (GgafMainScene*)obtain(prm_id);
}

void GgafSubcontractor::order(string prm_id, GgafObject* (*prm_functionForBuild)(void*), void* prm_argumentForBuild) {
	TRACE("GgafSubcontractor::order �ʃX���b�h����A" << prm_id << "������Ƃ��āB");
	GgafOrder* pOrder_New = NEW GgafOrder(prm_id);
	pOrder_New->_pObject_Creation=NULL;
	pOrder_New->_functionForBuild = prm_functionForBuild;
	pOrder_New->_argumentForBuild = prm_argumentForBuild;
	pOrder_New->_progress = 0;
	//::EnterCriticalSection(&(GgafGod::_cs1)); // -----> �r���J�n
	if (_pOrder_First == NULL) {
		TRACE("GgafSubcontractor::order ["<<prm_id<<"] ���A��������̍H��֒������Ă���");
        pOrder_New -> _isFirstOrder = true;
        pOrder_New -> _isLastOrder = true;
        pOrder_New->_pOrder_Next = pOrder_New;
        pOrder_New->_pOrder_Prev = pOrder_New;
        _pOrder_First = pOrder_New;
        _pOrder_InManufacturing = pOrder_New;
        //::LeaveCriticalSection(&(GgafGod::_cs1)); // <----- �r���I��
	} else {
		TRACE("GgafSubcontractor::order ["<<prm_id<<"] ������ɒǉ�����");
        pOrder_New -> _isFirstOrder = false;
		pOrder_New -> _isLastOrder = true;
        GgafOrder* pOrder_Last = _pOrder_First->_pOrder_Prev;
        pOrder_Last -> _isLastOrder = false;
        pOrder_Last->_pOrder_Next = pOrder_New;
        pOrder_New->_pOrder_Prev = pOrder_Last;
        pOrder_New->_pOrder_Next = _pOrder_First;
        _pOrder_First->_pOrder_Prev = pOrder_New;
        //::LeaveCriticalSection(&(GgafGod::_cs1)); // <----- �r���I��
	}
}



void* GgafSubcontractor::obtain(string prm_id) {
	//::EnterCriticalSection(&(GgafGod::_cs1)); // -----> �r���J�n
	TRACE("GgafSubcontractor::obtain "<<prm_id<<"/");
	GgafOrder* pOrder = _pOrder_First;
	GgafOrder* pOrder_MyNext;
	GgafOrder* pOrder_MyPrev;

	void* objectCreation;
	if (pOrder == NULL) {
		//::LeaveCriticalSection(&(GgafGod::_cs1)); // <----- �r���I��
		throw_GgafCriticalException("GgafSubcontractor::obtain Error! ������NULL�ł��Boreder��obtain�̑Ή������Ă��܂���)");
	}
	while(_isWorking) {
		if (pOrder->_id == prm_id) {
			TRACE("GgafSubcontractor::obtain ["<<prm_id<<"]�̒������ɗ��܂����B");
			while(_isWorking) {
				if (pOrder->_progress != 2) {
					_TRACE_("GgafSubcontractor::obtain �ʃX���b�h����A["<<prm_id<<"]�܂��`�H�A���傱���Ƒ҂��܂��BpOrder->_progress "<<(pOrder->_progress)<<"������");
					::LeaveCriticalSection(&(GgafGod::_cs1)); // <----- �r���I��
					Sleep(10);
					::EnterCriticalSection(&(GgafGod::_cs1)); // -----> �r���J�n
					continue;
				} else {
					TRACE("GgafSubcontractor::obtain �����A���i["<<prm_id<<"]�͐��������ł��ˁA�����[���I");
					if (pOrder->_isFirstOrder && pOrder->_isLastOrder) {
						objectCreation = pOrder->_pObject_Creation;
						pOrder->_pObject_Creation = NULL;
						delete pOrder;
						pOrder = NULL;
						_pOrder_First = NULL;
						_pOrder_InManufacturing = NULL;
						TRACE("GgafSubcontractor::obtain ���i["<<prm_id<<"]�����܂����B�H��͋�ł���");
						//::LeaveCriticalSection(&(GgafGod::_cs1)); // <----- �r���I��
						return (void*)objectCreation;
					} else {
						pOrder_MyNext = pOrder -> _pOrder_Next;
						pOrder_MyPrev = pOrder -> _pOrder_Prev;
						pOrder_MyPrev -> _pOrder_Next = pOrder_MyNext;
						pOrder_MyNext -> _pOrder_Prev = pOrder_MyPrev;
						if (pOrder->_isLastOrder) {
							pOrder_MyPrev->_isLastOrder = true;
							_pOrder_InManufacturing = pOrder_MyPrev;
						}
						if (pOrder->_isFirstOrder) {
							pOrder_MyNext->_isFirstOrder = true;
							_pOrder_First = pOrder_MyNext;
							_pOrder_InManufacturing = pOrder_MyNext;
						}
						objectCreation = pOrder->_pObject_Creation;
						pOrder->_pObject_Creation = NULL;
						delete pOrder;
						pOrder = NULL;

						//::LeaveCriticalSection(&(GgafGod::_cs1)); // <----- �r���I��
						return (void*)objectCreation;
					}
				}
			}
		} else {
			if (pOrder->_isLastOrder) {
				//::LeaveCriticalSection(&(GgafGod::_cs1)); // <----- �r���I��
				throw_GgafCriticalException("GgafSubcontractor::obtain Error! �S���T���܂������ǁA����Ȓ���(prm_id="<<prm_id<<")�͂���܂���ł����Boreder��obtain�̑Ή������Ă��܂���");
			} else {
				pOrder = pOrder ->_pOrder_Next;
			}
		}
	}
	return NULL;
}


void GgafSubcontractor::clean() {
	TRACE("GgafSubcontractor::clean �H���|���J�n");
	GgafOrder* pOrder = _pOrder_First;
	if (pOrder == NULL) {
		return;
	}
	while(true) {
		if (pOrder->_isLastOrder) {
			TRACE("GgafSubcontractor::clean ���i�폜["<<pOrder->_id<<"]�A�Ō�̃X�g�b�N");
			delete pOrder;
			pOrder = NULL;
			_pOrder_First = NULL;
			_pOrder_InManufacturing = NULL;
			break;
		} else {
			TRACE("GgafSubcontractor::clean ���i�폜["<<pOrder->_id<<"]");
			GgafOrder* pOrder_MyNext = pOrder -> _pOrder_Next;
			delete pOrder;
			pOrder = pOrder_MyNext;
		}
	}
	TRACE("GgafSubcontractor::clean �H���|������");
	return;
}


unsigned __stdcall GgafSubcontractor::work(void* prm_arg) {
	GgafObject* (*func)(void*);
	GgafObject* pObject;
	GgafOrder* pOrder_InManufacturing_save;
	while(_isWorking) {
		::EnterCriticalSection(&(GgafGod::_cs1)); // -----> �r���J�n
		if (_pOrder_InManufacturing != NULL) {
			if (_pOrder_InManufacturing  -> _progress == 0) { //������Ȃ�܂����
				TRACE2("GgafSubcontractor::work ����["<<_pOrder_InManufacturing->_id<<"]�͖�����(_progress == "<<_pOrder_InManufacturing  -> _progress<<")�䂦�ɍ��܂��B");
				_pOrder_InManufacturing  -> _progress = 1;    //�X�e�[�^�X�𐻑�����
				func = _pOrder_InManufacturing ->_functionForBuild;
				pOrder_InManufacturing_save = _pOrder_InManufacturing; //�ꎞ�ޔ�
				void* arg = _pOrder_InManufacturing ->_argumentForBuild;
				TRACE2("GgafSubcontractor::work �����J�n�I["<<_pOrder_InManufacturing->_id<<"]");
				::LeaveCriticalSection(&(GgafGod::_cs1)); // <----- �r���I��
				Sleep(5);
				pObject = (*func)(arg); //���i�̐����I
				Sleep(5);
				::EnterCriticalSection(&(GgafGod::_cs1)); // -----> �r���J�n
				_pOrder_InManufacturing = pOrder_InManufacturing_save;//���A
				TRACE2("GgafSubcontractor::work ���������I["<<_pOrder_InManufacturing->_id<<"]");
				if (_pOrder_InManufacturing == NULL) {
					TRACE2("GgafSubcontractor::work ��������������̂ɒx�������悤��(T_T)!�����������ɂ��܂��BpObject�̍폜");
					delete ((GgafActor*)pObject);
					::LeaveCriticalSection(&(GgafGod::_cs1)); // <----- �r���I��
					Sleep(10);
					continue;
				} else {
					_pOrder_InManufacturing -> _pObject_Creation = pObject;
					_pOrder_InManufacturing -> _progress = 2; //�X�e�[�^�X�𐻑��ς݂�
					TRACE2("GgafSubcontractor::work �����̕i["<<(_pOrder_InManufacturing->_id)<<"]���A�ł��܂����I");
				}
			} else {
				TRACE2("GgafSubcontractor::work ����["<<_pOrder_InManufacturing->_id<<"]�͒���ς�(_progress == "<<_pOrder_InManufacturing  -> _progress<<")�䂦�ɂƂ΂�");
			}
		}
		if (_pOrder_First == NULL) {
			//�������ҋ@
			TRACE2("GgafSubcontractor::work �H��ɂ͉�������܂���B�����Ȃ�ł��������₪��I�i�ҋ@�j");
			::LeaveCriticalSection(&(GgafGod::_cs1)); // <----- �r���I��
		} else {
			if (_pOrder_First != NULL && _pOrder_First -> _pOrder_Prev -> _progress == 0) {
				TRACE2("GgafSubcontractor::work ����ށA���ɖ������̒���["<<_pOrder_InManufacturing->_pOrder_Next->_id<<"]�������");
				_pOrder_InManufacturing = _pOrder_InManufacturing -> _pOrder_Next;
				::LeaveCriticalSection(&(GgafGod::_cs1)); // <----- �r���I��
				Sleep(10);
				continue;
			} else {
				TRACE2("GgafSubcontractor::work �����ς̒����͂��邪�A�����������͖����B���Ă����`���i�ҋ@�j");
				::LeaveCriticalSection(&(GgafGod::_cs1)); // <----- �r���I��
			}
		}

		Sleep(10);

	}
	TRACE2("GgafSubcontractor::work �H��͂���ɂēX���܂��ł��B�ł́A�܂���܂��傤�B");
	return 0;
}

