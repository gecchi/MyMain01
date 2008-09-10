#include "stdafx.h"

//初期化
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
	TRACE("GgafSubcontractor::order 別スレッドさん、" << prm_id << "を作っといて。");
	GgafOrder* pOrder_New = NEW GgafOrder(prm_id);
	pOrder_New->_pObject_Creation=NULL;
	pOrder_New->_functionForBuild = prm_functionForBuild;
	pOrder_New->_argumentForBuild = prm_argumentForBuild;
	pOrder_New->_progress = 0;
	//::EnterCriticalSection(&(GgafGod::_cs1)); // -----> 排他開始
	if (_pOrder_First == NULL) {
		TRACE("GgafSubcontractor::order ["<<prm_id<<"] を、空っきしの工場へ注文してやんよ");
        pOrder_New -> _isFirstOrder = true;
        pOrder_New -> _isLastOrder = true;
        pOrder_New->_pOrder_Next = pOrder_New;
        pOrder_New->_pOrder_Prev = pOrder_New;
        _pOrder_First = pOrder_New;
        _pOrder_InManufacturing = pOrder_New;
        //::LeaveCriticalSection(&(GgafGod::_cs1)); // <----- 排他終了
	} else {
		TRACE("GgafSubcontractor::order ["<<prm_id<<"] をさらに追加注文");
        pOrder_New -> _isFirstOrder = false;
		pOrder_New -> _isLastOrder = true;
        GgafOrder* pOrder_Last = _pOrder_First->_pOrder_Prev;
        pOrder_Last -> _isLastOrder = false;
        pOrder_Last->_pOrder_Next = pOrder_New;
        pOrder_New->_pOrder_Prev = pOrder_Last;
        pOrder_New->_pOrder_Next = _pOrder_First;
        _pOrder_First->_pOrder_Prev = pOrder_New;
        //::LeaveCriticalSection(&(GgafGod::_cs1)); // <----- 排他終了
	}
}



void* GgafSubcontractor::obtain(string prm_id) {
	//::EnterCriticalSection(&(GgafGod::_cs1)); // -----> 排他開始
	TRACE("GgafSubcontractor::obtain "<<prm_id<<"/");
	GgafOrder* pOrder = _pOrder_First;
	GgafOrder* pOrder_MyNext;
	GgafOrder* pOrder_MyPrev;

	void* objectCreation;
	if (pOrder == NULL) {
		//::LeaveCriticalSection(&(GgafGod::_cs1)); // <----- 排他終了
		throw_GgafCriticalException("GgafSubcontractor::obtain Error! 注文はNULLです。orederとobtainの対応が取れていません)");
	}
	while(_isWorking) {
		if (pOrder->_id == prm_id) {
			TRACE("GgafSubcontractor::obtain ["<<prm_id<<"]の注文取りに来ました。");
			while(_isWorking) {
				if (pOrder->_progress != 2) {
					_TRACE_("GgafSubcontractor::obtain 別スレッドさん、["<<prm_id<<"]まだ～？、ちょこっと待ちます。pOrder->_progress "<<(pOrder->_progress)<<"だった");
					::LeaveCriticalSection(&(GgafGod::_cs1)); // <----- 排他終了
					Sleep(10);
					::EnterCriticalSection(&(GgafGod::_cs1)); // -----> 排他開始
					continue;
				} else {
					TRACE("GgafSubcontractor::obtain おぉ、製品["<<prm_id<<"]は製造完了ですね、あざーす！");
					if (pOrder->_isFirstOrder && pOrder->_isLastOrder) {
						objectCreation = pOrder->_pObject_Creation;
						pOrder->_pObject_Creation = NULL;
						delete pOrder;
						pOrder = NULL;
						_pOrder_First = NULL;
						_pOrder_InManufacturing = NULL;
						TRACE("GgafSubcontractor::obtain 製品["<<prm_id<<"]頂きました。工場は空ですね");
						//::LeaveCriticalSection(&(GgafGod::_cs1)); // <----- 排他終了
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

						//::LeaveCriticalSection(&(GgafGod::_cs1)); // <----- 排他終了
						return (void*)objectCreation;
					}
				}
			}
		} else {
			if (pOrder->_isLastOrder) {
				//::LeaveCriticalSection(&(GgafGod::_cs1)); // <----- 排他終了
				throw_GgafCriticalException("GgafSubcontractor::obtain Error! 全部探しましたけど、そんな注文(prm_id="<<prm_id<<")はありませんでした。orederとobtainの対応が取れていません");
			} else {
				pOrder = pOrder ->_pOrder_Next;
			}
		}
	}
	return NULL;
}


void GgafSubcontractor::clean() {
	TRACE("GgafSubcontractor::clean 工場を掃除開始");
	GgafOrder* pOrder = _pOrder_First;
	if (pOrder == NULL) {
		return;
	}
	while(true) {
		if (pOrder->_isLastOrder) {
			TRACE("GgafSubcontractor::clean 製品削除["<<pOrder->_id<<"]、最後のストック");
			delete pOrder;
			pOrder = NULL;
			_pOrder_First = NULL;
			_pOrder_InManufacturing = NULL;
			break;
		} else {
			TRACE("GgafSubcontractor::clean 製品削除["<<pOrder->_id<<"]");
			GgafOrder* pOrder_MyNext = pOrder -> _pOrder_Next;
			delete pOrder;
			pOrder = pOrder_MyNext;
		}
	}
	TRACE("GgafSubcontractor::clean 工場を掃除完了");
	return;
}


unsigned __stdcall GgafSubcontractor::work(void* prm_arg) {
	GgafObject* (*func)(void*);
	GgafObject* pObject;
	GgafOrder* pOrder_InManufacturing_save;
	while(_isWorking) {
		::EnterCriticalSection(&(GgafGod::_cs1)); // -----> 排他開始
		if (_pOrder_InManufacturing != NULL) {
			if (_pOrder_InManufacturing  -> _progress == 0) { //未着手ならまず作る
				TRACE2("GgafSubcontractor::work 注文["<<_pOrder_InManufacturing->_id<<"]は未着手(_progress == "<<_pOrder_InManufacturing  -> _progress<<")ゆえに作ります。");
				_pOrder_InManufacturing  -> _progress = 1;    //ステータスを製造中へ
				func = _pOrder_InManufacturing ->_functionForBuild;
				pOrder_InManufacturing_save = _pOrder_InManufacturing; //一時退避
				void* arg = _pOrder_InManufacturing ->_argumentForBuild;
				TRACE2("GgafSubcontractor::work 製造開始！["<<_pOrder_InManufacturing->_id<<"]");
				::LeaveCriticalSection(&(GgafGod::_cs1)); // <----- 排他終了
				Sleep(5);
				pObject = (*func)(arg); //製品の製造！
				Sleep(5);
				::EnterCriticalSection(&(GgafGod::_cs1)); // -----> 排他開始
				_pOrder_InManufacturing = pOrder_InManufacturing_save;//復帰
				TRACE2("GgafSubcontractor::work 製造完了！["<<_pOrder_InManufacturing->_id<<"]");
				if (_pOrder_InManufacturing == NULL) {
					TRACE2("GgafSubcontractor::work せっかく作ったのに遅かったようだ(T_T)!無かった事にします。pObjectの削除");
					delete ((GgafActor*)pObject);
					::LeaveCriticalSection(&(GgafGod::_cs1)); // <----- 排他終了
					Sleep(10);
					continue;
				} else {
					_pOrder_InManufacturing -> _pObject_Creation = pObject;
					_pOrder_InManufacturing -> _progress = 2; //ステータスを製造済みへ
					TRACE2("GgafSubcontractor::work 注文の品["<<(_pOrder_InManufacturing->_id)<<"]が、でけました！");
				}
			} else {
				TRACE2("GgafSubcontractor::work 注文["<<_pOrder_InManufacturing->_id<<"]は着手済み(_progress == "<<_pOrder_InManufacturing  -> _progress<<")ゆえにとばす");
			}
		}
		if (_pOrder_First == NULL) {
			//無条件待機
			TRACE2("GgafSubcontractor::work 工場には何もありません。さぁなんでも注文来やがれ！（待機）");
			::LeaveCriticalSection(&(GgafGod::_cs1)); // <----- 排他終了
		} else {
			if (_pOrder_First != NULL && _pOrder_First -> _pOrder_Prev -> _progress == 0) {
				TRACE2("GgafSubcontractor::work ･･･む、次に未製造の注文["<<_pOrder_InManufacturing->_pOrder_Next->_id<<"]がありんす");
				_pOrder_InManufacturing = _pOrder_InManufacturing -> _pOrder_Next;
				::LeaveCriticalSection(&(GgafGod::_cs1)); // <----- 排他終了
				Sleep(10);
				continue;
			} else {
				TRACE2("GgafSubcontractor::work 製造済の注文はあるが、未製造注文は無し。ってかよゆ～ｗ（待機）");
				::LeaveCriticalSection(&(GgafGod::_cs1)); // <----- 排他終了
			}
		}

		Sleep(10);

	}
	TRACE2("GgafSubcontractor::work 工場はこれにて店じまいです。では、また会いましょう。");
	return 0;
}

