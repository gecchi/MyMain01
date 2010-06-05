#include "stdafx.h"
using namespace std;

using namespace GgafCore;

//初期化
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

//注文
//このメソッドはメインスレッドが実行する。
void GgafFactory::order(unsigned long prm_id,
                        GgafObject* (*prm_pFunc)(void*, void*, void*),
                        void* prm_pArg1,
                        void* prm_pArg2,
                        void* prm_pArg3) {
    TRACE2("GgafFactory::order ＜客＞ 別スレッドの工場さん、[" << prm_id << "]を作っといて～。");
    static GgafOrder* pOrder_New;
    pOrder_New = NEW GgafOrder(prm_id);
    pOrder_New->_pObject_Creation=NULL;
    pOrder_New->_pFunc = prm_pFunc;
    pOrder_New->_pArg1 = prm_pArg1;
    pOrder_New->_pArg2 = prm_pArg2;
    pOrder_New->_pArg3 = prm_pArg3;
    pOrder_New->_progress = 0;
    if (ROOT_ORDER == NULL) {
        TRACE2("GgafFactory::order ＜客＞ あぁ、工場は空っきしですね。注文、すぐできるよね？。");
        pOrder_New->_is_first_order_flg = true;
        pOrder_New->_is_last_order_flg = true;
        pOrder_New->_pOrder_Next = pOrder_New;
        pOrder_New->_pOrder_Prev = pOrder_New;
        ROOT_ORDER = pOrder_New;
        CREATING_ORDER = pOrder_New;
    } else {
        TRACE2("GgafFactory::order ＜客＞ 注文たまってますね、次々注文恐れ入ります。");
        pOrder_New->_is_first_order_flg = false;
        pOrder_New->_is_last_order_flg = true;
        static GgafOrder* pOrder_Last;
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
    DWORD waittime = 0;
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
        throwGgafCriticalException("GgafFactory::obtain Error! 注文はNULLです。orederとobtainの対応が取れていません。");
    }
    while (_is_working_flg) {

        if (pOrder->_id == prm_id) {
            TRACE2("GgafFactory::obtain ＜客＞ こんにちは、["<<prm_id<<"]を取りに来ましたよっと。");
            while (_is_working_flg) {
                if (pOrder->_progress != 2) {
                    TRACE2("GgafFactory::obtain ＜客＞ 別スレッド工場さん、["<<prm_id<<"]の製造まだ～？、5ミリ秒だけ待ったげよう。pOrder->_progress="<<(pOrder->_progress));
                    if (waittime > 1000*60) { //約60秒
                        throwGgafCriticalException("GgafFactory::obtain Error! ["<<prm_id<<"]の製造待ち時間、タイムアウト。\n何らかの理由でメインスレッドが停止している可能性が大きいです。");
                    } else {
                        _TEXT_("…");
                    }

                 ___EndSynchronized; // <----- 排他終了
                    Sleep(5);
                 ___BeginSynchronized; // ----->排他開始
                    waittime += 5;
                    continue;
                } else {
                    TRACE2("GgafFactory::obtain ＜客＞ おぉ、["<<prm_id<<"]は製造済みですね、さすが！。あざーす！");
                    if (pOrder->_is_first_order_flg && pOrder->_is_last_order_flg) {
                        objectCreation = pOrder->_pObject_Creation;
                        pOrder->_pObject_Creation = NULL;
                        DELETE_IMPOSSIBLE_NULL(pOrder);
                        pOrder = NULL;
                        ROOT_ORDER = NULL;
                        CREATING_ORDER = NULL;
                        TRACE2("GgafFactory::obtain ＜客＞ 製品["<<prm_id<<"]頂きました。あ、もう工場は空ですね。暇になった？ねぇ？");
                        return (void*)objectCreation;
                    } else {
                        pOrder_MyNext = pOrder->_pOrder_Next;
                        pOrder_MyPrev = pOrder->_pOrder_Prev;
                        pOrder_MyPrev->_pOrder_Next = pOrder_MyNext;
                        pOrder_MyNext->_pOrder_Prev = pOrder_MyPrev;
                        if (pOrder->_is_last_order_flg) {
                            pOrder_MyPrev->_is_last_order_flg = true;
                            CREATING_ORDER = pOrder_MyPrev;
                        }
                        if (pOrder->_is_first_order_flg) {
                            pOrder_MyNext->_is_first_order_flg = true;
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
            if (pOrder->_is_last_order_flg) {
                throwGgafCriticalException("GgafFactory::obtain Error! ＜工場＞全部探しましたけど、そんな注文(prm_id="<<prm_id<<")は、ありません。\n oreder() と obtain() の対応が取れていません。ありえない、おかしいな～");
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

//工場にため込んでいる全てのインスタンスを破棄
//神(GgafGod)がアプリ終了時等に実行する予定。
void GgafFactory::clean() {
    TRACE2("GgafFactory::clean ＜神＞ 工場を掃除開始");
    GgafOrder* pOrder = ROOT_ORDER;
    if (pOrder == NULL) {
        TRACE2("GgafFactory::clean ＜神＞ しかし工場に何も無い！！");
        return;
    }
    while (true) {
        if (pOrder->_is_last_order_flg) {
            TRACE2("GgafFactory::clean ＜神＞ 製品削除["<<pOrder->_id<<"]、最後のストック");
            DELETE_IMPOSSIBLE_NULL(pOrder);
            pOrder = NULL;
            ROOT_ORDER = NULL;
            CREATING_ORDER = NULL;
            break;
        } else {
            TRACE2("GgafFactory::clean ＜神＞ 製品削除["<<pOrder->_id<<"]");
            GgafOrder* pOrder_MyNext = pOrder->_pOrder_Next;
            DELETE_IMPOSSIBLE_NULL(pOrder);
            pOrder = pOrder_MyNext;
        }
    }
    TRACE2("GgafFactory::clean ＜神＞ 工場を掃除完了");
    return;
}

unsigned __stdcall GgafFactory::work(void* prm_arg) {
    //_CrtSetBreakAlloc(95299);

    try {
        static GgafObject* (*func)(void*, void*, void*);
        static GgafObject* pObject;
        static GgafOrder* pOrder_InManufacturing_save;
        Sleep(1000); //god のインスタンスが完成するまでほんのちょっと待つ必要があるかもしれない
        while (_is_working_flg) {
            if (_have_to_rest_flg) {
                _is_resting_flg = true;
                Sleep(20);
                continue;
            } else {
                _is_resting_flg = false;
            }

         ___BeginSynchronized; // ----->排他開始
            if (CREATING_ORDER != NULL) {
                if (CREATING_ORDER->_progress == 0) { //未着手ならまず作る
                    TRACE2("GgafFactory::work ＜工場＞ よし、注文["<<CREATING_ORDER->_id<<"]は未着手(_progress == "<<CREATING_ORDER->_progress<<")だな。ゆえに今から作ります！");
                    CREATING_ORDER->_progress = 1; //ステータスを製造中へ
                    func = CREATING_ORDER->_pFunc;
                    pOrder_InManufacturing_save = CREATING_ORDER; //ポインタ一時退避
                    void* arg1 = CREATING_ORDER->_pArg1;
                    void* arg2 = CREATING_ORDER->_pArg2;
                    void* arg3 = CREATING_ORDER->_pArg3;
                    TRACE2("GgafFactory::work ＜工場＞ 製造開始！["<<CREATING_ORDER->_id<<"] (σ ｀・ω・´)σ ");
                 ___EndSynchronized; // <----- 排他終了
//#ifdef MY_DEBUG
//try {
//#endif
                    pObject = (*func)(arg1, arg2, arg3); //製品の製造！
//#ifdef MY_DEBUG
//} catch (GgafCriticalException& e) {
//    _TRACE_("＜工場例外＞ 製造中エラー；"<<e.getMsg());
//    string message = "\n・"+e.getMsg()+"  \n\nお心あたりが無いメッセージの場合、当方のバグの可能性があります。\n誠に申し訳ございません。\n";
//    string message_dialog = message + "(※「Shift + Ctrl + C」でメッセージはコピーできます。)";
//    MessageBox(NULL, message_dialog.c_str(),"下記のエラーが発生してしまいました", MB_OK|MB_ICONSTOP);
//    _is_working_flg = false;
//    _was_finished_flg = true;
//    GgafGod::_pException_Factory = NEW GgafCriticalException(e.getMsg());
//    return 0;
//}
//#endif

                 ___BeginSynchronized; // ----->排他開始
                    TRACE2("GgafFactory::work ＜工場＞ 製造完了！品番["<<CREATING_ORDER->_id<<"] (^_^)v");
                    if (CREATING_ORDER == NULL) {
                        TRACE2("GgafFactory::work ＜工場＞ ガーン！。せっかく作ったのにキャンセルっすか・・・。破棄します。pObjectをdelete!");
                        DELETE_IMPOSSIBLE_NULL(pObject);
                     ___EndSynchronized; // <----- 排他終了
                        continue;
                    } else {
                        CREATING_ORDER = pOrder_InManufacturing_save; //ポインタ復帰
                        CREATING_ORDER->_pObject_Creation = pObject; //製品登録
                        CREATING_ORDER->_progress = 2; //ステータスを製造済みへ
                        TRACE2("GgafFactory::work ＜工場＞ 製造した注文の品["<<(CREATING_ORDER->_id)<<"]を、棚に置いときます。");
                    }
                } else {
                    TRACE2("GgafFactory::work ＜工場＞ 注文["<<CREATING_ORDER->_id<<"]は既に棚に置いてある(_progress == "<<CREATING_ORDER->_progress<<")。ゆえに飛ばす");
                }
            }
            if (ROOT_ORDER == NULL) {
                //無条件待機
                TRACE2("GgafFactory::work ＜工場＞ 工場には何～んもありません。さぁなんでも注文来い来い！！・・・ないのん？。暇なのでゴミ箱掃除でもやっときます。（待機）");
             ___EndSynchronized; // <----- 排他終了
                if (GgafGod::_pGod->_fps > 55.0f) {
                    TRACE2("GgafFactory::work ＜工場＞ 神さんも余裕あるしFPSは高いよなぁ、その間を利用してゴミ箱掃除でもやっときます。1");
                    _pGarbageBox->clean(20); //暇なので、ゴミ箱掃除
                    _cnt_cleaned = 0;
                }
            } else {
                if (ROOT_ORDER != NULL && ROOT_ORDER->_pOrder_Prev->_progress == 0) {
                    TRACE2("GgafFactory::work ＜工場＞ ・・・む、既に次に未製造の注文["<<CREATING_ORDER->_pOrder_Next->_id<<"]がありんす。急いで作らねば。");
                    CREATING_ORDER = CREATING_ORDER->_pOrder_Next;
                 ___EndSynchronized; // <----- 排他終了
                    continue;
                } else {
                    TRACE2("GgafFactory::work ＜工場＞ さて、未製造注文は無し。あ～棚に製造済のがたまってるす、早く取に来やがれ！。（待機）");
                 ___EndSynchronized; // <----- 排他終了
                    if (GgafGod::_pGod->_fps > 55.0f) {
                        TRACE2("GgafFactory::work ＜工場＞ 神さんも余裕あるしFPSは高いなぁ、その間を利用してゴミ箱掃除でもやっときます。2");
                        _pGarbageBox->clean(20); //暇なので、ゴミ箱掃除
                        _cnt_cleaned = 0;
                    }
                }
            }
            Sleep(1);
        }
        TRACE2("GgafFactory::work ＜工場＞ 工場はこれにて店じまいです。さようなら、また会いましょう。");
        _was_finished_flg = true;
        return 0;
    } catch (GgafCriticalException& e) {
        _TRACE_("＜工場例外＞ 私としたことがすみません；"<<e.getMsg());
        _is_working_flg = false;
        _was_finished_flg = true;
        GgafGod::_pException_Factory = NEW GgafCriticalException(e.getMsg());
        return 0;
    }
}

