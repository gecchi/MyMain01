#include "stdafx.h"

//初期化
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
	TRACE2("GgafFactory::order ＜客＞ 別スレッド工場さん、[" << prm_id << "]を作っといて～。");
	GgafOrder* pOrder_New = NEW GgafOrder(prm_id);
	pOrder_New->_pObject_Creation=NULL;
	pOrder_New->_pFunc = prm_pFunc;
	pOrder_New->_pArg1 = prm_pArg1;
	pOrder_New->_pArg2 = prm_pArg2;
	pOrder_New->_progress = 0;
	//::EnterCriticalSection(&(GgafGod::CS1)); // -----> 排他開始
	if (ROOT_ORDER == NULL) {
		TRACE2("GgafFactory::order ＜客＞ 空っきしの工場へ注文してやんよ。すぐできるよね？。");
        pOrder_New -> _isFirstOrder = true;
        pOrder_New -> _isLastOrder = true;
        pOrder_New->_pOrder_Next = pOrder_New;
        pOrder_New->_pOrder_Prev = pOrder_New;
        ROOT_ORDER = pOrder_New;
        CREATING_ORDER = pOrder_New;
        //::LeaveCriticalSection(&(GgafGod::CS1)); // <----- 排他終了
	} else {
		TRACE2("GgafFactory::order ＜客＞ 次々にすまんのぉ");
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



void* GgafFactory::obtain(string prm_id) {
	//::EnterCriticalSection(&(GgafGod::CS1)); // -----> 排他開始
	TRACE("GgafFactory::obtain "<<prm_id<<"/");
	GgafOrder* pOrder = ROOT_ORDER;
	GgafOrder* pOrder_MyNext;
	GgafOrder* pOrder_MyPrev;

	void* objectCreation;
	if (pOrder == NULL) {
		//::LeaveCriticalSection(&(GgafGod::CS1)); // <----- 排他終了
		throw_GgafCriticalException("GgafFactory::obtain Error! 注文はNULLです。orederとobtainの対応が取れていません)");
	}
	while(_isWorking) {
		if (pOrder->_id == prm_id) {
			TRACE2("GgafFactory::obtain ＜客＞ こんにちは、["<<prm_id<<"]を取りに来ましたよっと。");
			while(_isWorking) {
				if (pOrder->_progress != 2) {
					_TRACE_("GgafFactory::obtain ＜客＞ 別スレッド工場さん、["<<prm_id<<"]まだ～？、2ミリ秒待ったげよう。pOrder->_progress="<<(pOrder->_progress));
					::LeaveCriticalSection(&(GgafGod::CS1)); // <----- 排他終了
					Sleep(2);
					::EnterCriticalSection(&(GgafGod::CS1)); // -----> 排他開始
					continue;
				} else {
					TRACE2("GgafFactory::obtain ＜客＞ おぉ、["<<prm_id<<"]は製造済みですね、あざーす！");
					if (pOrder->_isFirstOrder && pOrder->_isLastOrder) {
						objectCreation = pOrder->_pObject_Creation;
						pOrder->_pObject_Creation = NULL;
						DELETE_IMPOSSIBLE_NULL(pOrder);
						pOrder = NULL;
						ROOT_ORDER = NULL;
						CREATING_ORDER = NULL;
						TRACE2("GgafFactory::obtain ＜客＞ 製品["<<prm_id<<"]頂きました。あ、工場は空ですね。暇なの？");
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
						DELETE_IMPOSSIBLE_NULL(pOrder);
						pOrder = NULL;

						//::LeaveCriticalSection(&(GgafGod::CS1)); // <----- 排他終了
						return (void*)objectCreation;
					}
				}
			}
		} else {
			if (pOrder->_isLastOrder) {
				//::LeaveCriticalSection(&(GgafGod::CS1)); // <----- 排他終了
				throw_GgafCriticalException("GgafFactory::obtain Error! 全部探しましたけど、そんな注文(prm_id="<<prm_id<<")は、ありゃしまへん。orederとobtainの対応が取れていません");
			} else {
				pOrder = pOrder ->_pOrder_Next;
			}
		}
	}
	return NULL;
}


void GgafFactory::clean() {
	TRACE("GgafFactory::clean ＜神＞ 工場を掃除開始");
	GgafOrder* pOrder = ROOT_ORDER;
	if (pOrder == NULL) {
		return;
	}
	while(true) {
		if (pOrder->_isLastOrder) {
			TRACE2("GgafFactory::clean ＜神＞ 製品削除["<<pOrder->_id<<"]、最後のストック");
			DELETE_IMPOSSIBLE_NULL(pOrder);
			pOrder = NULL;
			ROOT_ORDER = NULL;
			CREATING_ORDER = NULL;
			break;
		} else {
			TRACE2("GgafFactory::clean ＜神＞ 製品削除["<<pOrder->_id<<"]");
			GgafOrder* pOrder_MyNext = pOrder -> _pOrder_Next;
			DELETE_IMPOSSIBLE_NULL(pOrder);
			pOrder = pOrder_MyNext;
		}
	}
	TRACE2("GgafFactory::clean ＜神＞ 工場を掃除完了");
	return;
}


unsigned __stdcall GgafFactory::work(void* prm_arg) {
	try {
		GgafObject* (*func)(void*, void*);
		GgafObject* pObject;
		GgafOrder* pOrder_InManufacturing_save;
		while(_isWorking) {

			::EnterCriticalSection(&(GgafGod::CS1)); // -----> 排他開始
			if (CREATING_ORDER != NULL) {
				if (CREATING_ORDER  -> _progress == 0) { //未着手ならまず作る
					TRACE2("GgafFactory::work ＜工場＞ 注文["<<CREATING_ORDER->_id<<"]は未着手(_progress == "<<CREATING_ORDER -> _progress<<")。ゆえに作ります！");
					CREATING_ORDER  -> _progress = 1;    //ステータスを製造中へ
					func = CREATING_ORDER ->_pFunc;
					pOrder_InManufacturing_save = CREATING_ORDER; //ポインタ一時退避
					void* arg1 = CREATING_ORDER ->_pArg1;
					void* arg2 = CREATING_ORDER ->_pArg2;
					TRACE2("GgafFactory::work ＜工場＞ 製造開始！["<<CREATING_ORDER->_id<<"]");
					::LeaveCriticalSection(&(GgafGod::CS1)); // <----- 排他終了
					Sleep(2);
					pObject = (*func)(arg1, arg2); //製品の製造！！！！
					Sleep(2);
					::EnterCriticalSection(&(GgafGod::CS1)); // -----> 排他開始
					TRACE2("GgafFactory::work ＜工場＞ 製造完了！["<<CREATING_ORDER->_id<<"] (^_^)v");
					if (CREATING_ORDER == NULL) {
						TRACE2("GgafFactory::work ＜工場＞ ガーン！。せっかく作ったのにキャンセルっすか(T_T)。破棄します。pObjectをdelete!");
						DELETE_IMPOSSIBLE_NULL(pObject);
						::LeaveCriticalSection(&(GgafGod::CS1)); // <----- 排他終了
						Sleep(20);
						continue;
					} else {
						CREATING_ORDER = pOrder_InManufacturing_save;  //ポインタ復帰
						CREATING_ORDER -> _pObject_Creation = pObject; //製品登録
						CREATING_ORDER -> _progress = 2;               //ステータスを製造済みへ
						TRACE2("GgafFactory::work ＜工場＞ 製造した注文の品["<<(CREATING_ORDER->_id)<<"]を、棚に置いときます。");
					}
				} else {
					TRACE2("GgafFactory::work ＜工場＞ 注文["<<CREATING_ORDER->_id<<"]は既に棚に置いてある(_progress == "<<CREATING_ORDER  -> _progress<<")。ゆえに飛ばす");
				}
			}
			if (ROOT_ORDER == NULL) {
				//無条件待機
				TRACE2("GgafFactory::work ＜工場＞ 工場には何～んもありません。さぁなんでも注文来い来い！。暇なのでゴミ箱掃除でもやっときます。（待機）");
				::LeaveCriticalSection(&(GgafGod::CS1)); // <----- 排他終了
				if (_pGod->_fFps > 52) {
					Sleep(5);
					TRACE2("GgafFactory::work ＜工場＞ 神さんも余裕あるし、暇なのでゴミ箱掃除でもやっときます。");
					_pTrashBox->cleane(1); //暇なので、ゴミ箱掃除
					_s_iCountCleanedNode = 0;
				}
			} else {
				if (ROOT_ORDER != NULL && ROOT_ORDER -> _pOrder_Prev -> _progress == 0) {
					TRACE2("GgafFactory::work ＜工場＞ ･･･む、次に未製造の注文["<<CREATING_ORDER->_pOrder_Next->_id<<"]がありんす");
					CREATING_ORDER = CREATING_ORDER -> _pOrder_Next;
					::LeaveCriticalSection(&(GgafGod::CS1)); // <----- 排他終了
					Sleep(10);
					continue;
				} else {
					TRACE2("GgafFactory::work ＜工場＞ よし、未製造注文は無し。あ～棚に製造済のがたまってるす、早く取に来やがれ！。（待機）");
					::LeaveCriticalSection(&(GgafGod::CS1)); // <----- 排他終了
					if (_pGod->_fFps > 52) {
						TRACE2("GgafFactory::work ＜工場＞ 神さんも余裕あるし、暇なのでゴミ箱掃除でもやっときます。");
						Sleep(5);
						_pTrashBox->cleane(1); //暇なので、ゴミ箱掃除
						_s_iCountCleanedNode = 0;
					}
				}
			}
			Sleep(20);
		}
		TRACE2("GgafFactory::work ＜工場＞ 工場はこれにて店じまいです。さようなら、また会いましょう。");
		_isFinish = true;
		return 0;
	} catch (GgafCriticalException& e) {
		_TRACE_("＜工場例外＞ 私としたことがすみません；"<<e.getMsg());
		_isWorking = false;
		_isFinish = true;
		GgafGod::_pException_Factory = NEW GgafCriticalException(e.getMsg());
		return 0;
	}
}

