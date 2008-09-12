#include "stdafx.h"

//初期化
GgafGod* GgafSubcontractor::_pGod = NULL;
GgafOrder* GgafSubcontractor::ROOT_ORDER = NULL;
GgafOrder* GgafSubcontractor::CREATING_ORDER = NULL;
bool       GgafSubcontractor::_isWorking = true;
bool       GgafSubcontractor::_isFinish  = false;

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
	//::EnterCriticalSection(&(GgafGod::CS1)); // -----> 排他開始
	if (ROOT_ORDER == NULL) {
		TRACE("GgafSubcontractor::order ["<<prm_id<<"] を、空っきしの工場へ注文してやんよ");
        pOrder_New -> _isFirstOrder = true;
        pOrder_New -> _isLastOrder = true;
        pOrder_New->_pOrder_Next = pOrder_New;
        pOrder_New->_pOrder_Prev = pOrder_New;
        ROOT_ORDER = pOrder_New;
        CREATING_ORDER = pOrder_New;
        //::LeaveCriticalSection(&(GgafGod::CS1)); // <----- 排他終了
	} else {
		TRACE("GgafSubcontractor::order ["<<prm_id<<"] をさらに追加注文");
        pOrder_New -> _isFirstOrder = false;
		pOrder_New -> _isLastOrder = true;
        GgafOrder* pOrder_Last = ROOT_ORDER->_pOrder_Prev;
        pOrder_Last -> _isLastOrder = false;
        pOrder_Last->_pOrder_Next = pOrder_New;
        pOrder_New->_pOrder_Prev = pOrder_Last;
        pOrder_New->_pOrder_Next = ROOT_ORDER;
        ROOT_ORDER->_pOrder_Prev = pOrder_New;
        //::LeaveCriticalSection(&(GgafGod::CS1)); // <----- 排他終了
	}
}



void* GgafSubcontractor::obtain(string prm_id) {
	//::EnterCriticalSection(&(GgafGod::CS1)); // -----> 排他開始
	TRACE("GgafSubcontractor::obtain "<<prm_id<<"/");
	GgafOrder* pOrder = ROOT_ORDER;
	GgafOrder* pOrder_MyNext;
	GgafOrder* pOrder_MyPrev;

	void* objectCreation;
	if (pOrder == NULL) {
		//::LeaveCriticalSection(&(GgafGod::CS1)); // <----- 排他終了
		throw_GgafCriticalException("GgafSubcontractor::obtain Error! 注文はNULLです。orederとobtainの対応が取れていません)");
	}
	while(_isWorking) {
		if (pOrder->_id == prm_id) {
			TRACE("GgafSubcontractor::obtain ["<<prm_id<<"]の注文取りに来ました。");
			while(_isWorking) {
				if (pOrder->_progress != 2) {
					_TRACE_("GgafSubcontractor::obtain 別スレッドさん、["<<prm_id<<"]まだ～？、ちょこっと待ちます。pOrder->_progress "<<(pOrder->_progress)<<"だった");
					::LeaveCriticalSection(&(GgafGod::CS1)); // <----- 排他終了
					Sleep(10);
					::EnterCriticalSection(&(GgafGod::CS1)); // -----> 排他開始
					continue;
				} else {
					TRACE("GgafSubcontractor::obtain おぉ、製品["<<prm_id<<"]は製造完了ですね、あざーす！");
					if (pOrder->_isFirstOrder && pOrder->_isLastOrder) {
						objectCreation = pOrder->_pObject_Creation;
						pOrder->_pObject_Creation = NULL;
						delete pOrder;
						pOrder = NULL;
						ROOT_ORDER = NULL;
						CREATING_ORDER = NULL;
						TRACE("GgafSubcontractor::obtain 製品["<<prm_id<<"]頂きました。工場は空ですね");
						//::LeaveCriticalSection(&(GgafGod::CS1)); // <----- 排他終了
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

						//::LeaveCriticalSection(&(GgafGod::CS1)); // <----- 排他終了
						return (void*)objectCreation;
					}
				}
			}
		} else {
			if (pOrder->_isLastOrder) {
				//::LeaveCriticalSection(&(GgafGod::CS1)); // <----- 排他終了
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
	GgafOrder* pOrder = ROOT_ORDER;
	if (pOrder == NULL) {
		return;
	}
	while(true) {
		if (pOrder->_isLastOrder) {
			TRACE("GgafSubcontractor::clean 製品削除["<<pOrder->_id<<"]、最後のストック");
			delete pOrder;
			pOrder = NULL;
			ROOT_ORDER = NULL;
			CREATING_ORDER = NULL;
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
		::EnterCriticalSection(&(GgafGod::CS1)); // -----> 排他開始
		if (CREATING_ORDER != NULL) {
			if (CREATING_ORDER  -> _progress == 0) { //未着手ならまず作る
				TRACE2("GgafSubcontractor::work 注文["<<CREATING_ORDER->_id<<"]は未着手(_progress == "<<CREATING_ORDER  -> _progress<<")ゆえに作ります。");
				CREATING_ORDER  -> _progress = 1;    //ステータスを製造中へ
				func = CREATING_ORDER ->_functionForBuild;
				pOrder_InManufacturing_save = CREATING_ORDER; //ポインタ一時退避
				void* arg = CREATING_ORDER ->_argumentForBuild;
				TRACE2("GgafSubcontractor::work 製造開始！["<<CREATING_ORDER->_id<<"]");
				::LeaveCriticalSection(&(GgafGod::CS1)); // <----- 排他終了
				Sleep(2);
				pObject = (*func)(arg); //製品の製造！
				Sleep(2);
				::EnterCriticalSection(&(GgafGod::CS1)); // -----> 排他開始
				TRACE2("GgafSubcontractor::work 製造完了！["<<CREATING_ORDER->_id<<"]");
				if (CREATING_ORDER == NULL) {
					TRACE2("GgafSubcontractor::work せっかく作ったのに遅かったようだ(T_T)!無かった事にします。pObjectの削除");
					delete ((GgafActor*)pObject);
					::LeaveCriticalSection(&(GgafGod::CS1)); // <----- 排他終了
					Sleep(10);
					continue;
				} else {
					CREATING_ORDER = pOrder_InManufacturing_save;  //ポインタ復帰
					CREATING_ORDER -> _pObject_Creation = pObject; //製品登録
					CREATING_ORDER -> _progress = 2;               //ステータスを製造済みへ
					TRACE2("GgafSubcontractor::work 注文の品["<<(CREATING_ORDER->_id)<<"]が、でけました！");
				}
			} else {
				TRACE2("GgafSubcontractor::work 注文["<<CREATING_ORDER->_id<<"]は製造済みッス(_progress == "<<CREATING_ORDER  -> _progress<<")ゆえにとばす");
			}
		}
		if (ROOT_ORDER == NULL) {
			//無条件待機
			TRACE2("GgafSubcontractor::work 工場には何もありません。さぁなんでも注文来やがれ！（待機）");
			::LeaveCriticalSection(&(GgafGod::CS1)); // <----- 排他終了
		} else {
			if (ROOT_ORDER != NULL && ROOT_ORDER -> _pOrder_Prev -> _progress == 0) {
				TRACE2("GgafSubcontractor::work ･･･む、次に未製造の注文["<<CREATING_ORDER->_pOrder_Next->_id<<"]がありんす");
				CREATING_ORDER = CREATING_ORDER -> _pOrder_Next;
				::LeaveCriticalSection(&(GgafGod::CS1)); // <----- 排他終了
				Sleep(10);
				continue;
			} else {
				TRACE2("GgafSubcontractor::work 製造済の注文はあるが、未製造注文は無し。ってかよゆ～ｗ（待機）");
				::LeaveCriticalSection(&(GgafGod::CS1)); // <----- 排他終了
			}
		}
		Sleep(10);
	}
	TRACE2("GgafSubcontractor::work 工場はこれにて店じまいです。では、また会いましょう。");
	_isFinish = true;
	return 0;
}

