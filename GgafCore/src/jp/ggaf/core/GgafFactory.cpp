#include "stdafx.h"

using namespace GgafCore;

//初期化
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

//注文
//このメソッドはメインスレッドが実行する。
void GgafFactory::order(UINT32 prm_id,
                        GgafObject* (*prm_pFunc)(void*, void*, void*),
                        GgafObject* prm_pOrderer,
                        void* prm_pArg1,
                        void* prm_pArg2,
                        void* prm_pArg3) {
    TRACE2("GgafFactory::order ＜客＞ 別スレッドの工場さん、[" << prm_id << "]を作っといて～。");
    //既に注文していないかチェック
    GgafOrder* pOrder = ROOT_ORDER;
    while (pOrder) {
        if (pOrder->_id == prm_id) {
            _TRACE_("＜警告＞ GgafFactory::order [" << prm_id << "]は、既に注文してるのでスルーします。意図していなければオカシイですよ！");
            return;
        }
        if (pOrder->_is_last_order_flg) {
            break;
        }
        pOrder = pOrder->_pOrder_next;
    }
    //既は未だであるようなのでストック
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
        TRACE2("GgafFactory::order ＜客＞ あぁ、工場は空っきしですね。注文、すぐできるよね？。");
        pOrder_new->_is_first_order_flg = true;
        pOrder_new->_is_last_order_flg = true;
        pOrder_new->_pOrder_next = pOrder_new;
        pOrder_new->_pOrder_prev = pOrder_new;
        ROOT_ORDER = pOrder_new;
        CREATING_ORDER = pOrder_new;
    } else {
        TRACE2("GgafFactory::order ＜客＞ 注文たまってますね、次々注文恐れ入ります。");
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
        //注文が無いよエラー発生！、エラーメッセージを作る。
        std::string name_org;
        if (prm_org->instanceOf(Obj_GgafScene)) {
            name_org = ((GgafScene*)prm_org)->getName();
        } else if (prm_org->instanceOf(Obj_GgafActor)) {
            name_org = ((GgafActor*)prm_org)->getName();
        }
        throwGgafCriticalException("GgafFactory::obtain("<<prm_id<<") Error! 注文リストはNULLで全て製造済みしています。\n"<<
                                   "orederとobtainの対応が取れていません。\n"<<
                                   "受取人(obtain呼び元)="<<name_org<<"("<<prm_org<<")");
    }

    //obtainメインループ
    while (_is_working_flg) {

        if (pOrder->_id == prm_id) {
            TRACE2("GgafFactory::obtain ＜客＞ こんにちは、["<<prm_id<<"]を取りに来ましたよっと。");
            while (_is_working_flg) {
                if (pOrder->_progress != 2) {
                    TRACE2("GgafFactory::obtain ＜客＞ 別スレッド工場さん、["<<prm_id<<"]の製造まだ～？、5ミリ秒だけ待ったげよう。pOrder->_progress="<<(pOrder->_progress));
#ifdef _DEBUG
                    //デバッグ時はタイムアウト無し
#else

                    if (waittime > 1000*600) { //約10分
                        //タイムアウトエラー発生！、エラーメッセージを作る。
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
                        throwGgafCriticalException("GgafFactory::obtain Error! ["<<prm_id<<"]の製造待ち時間タイムアウト、取得できません。\n"<<
                                                   "何らかの理由でメインスレッドが停止している可能性が大きいです。"<<
                                                   "発注者(order呼び元)="<<name_orderer<<"("<<pOrder->_pOrderer<<")／受取人(obtain呼び元)="<<name_org<<"("<<prm_org<<")");
                    } else {
                    }
#endif
                 ___EndSynchronized1; // <----- 排他終了
                    Sleep(5);
                 ___BeginSynchronized1; // ----->排他開始
                    waittime += 5;
                    if (pOrder->_progress == 1) {
                        //着手済み
                        _TEXT_("!");
                        continue; //待つ
                    } else {
                        //未着手？
                        pOrder = ROOT_ORDER; //もう一度最初から探させる。
                        _TEXT_(".");
                        break;
                    }
                } else {
                    TRACE2("GgafFactory::obtain ＜客＞ おぉ、["<<prm_id<<"]は製造済みですね、さすが！。あざーす！");
                    if (pOrder->_is_first_order_flg && pOrder->_is_last_order_flg) {
                        objectCreation = pOrder->_pObject_creation;
                        pOrder->_pObject_creation = NULL;
                        DELETE_IMPOSSIBLE_NULL(pOrder);
                        pOrder = NULL;
                        ROOT_ORDER = NULL;
                        CREATING_ORDER = NULL;
                        TRACE2("GgafFactory::obtain ＜客＞ 製品["<<prm_id<<"]頂きました。あ、もう工場は空ですね。暇になった？ねぇ？");
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
                //注文の形跡が無い、取得出来ないエラー発生！、エラーメッセージを作る。
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
                throwGgafCriticalException("GgafFactory::obtain Error! ＜工場長＞全部探しましたけど、そんな注文(prm_id="<<prm_id<<")は、ありません。\n "<<
                                           "oreder() と obtain() の対応が取れていません。oreder()漏れ、或いは同じ obtain() を２回以上してませんか？。\n"<<
                                           "発注者(order呼び元)="<<name_orderer<<"("<<pOrder->_pOrderer<<")／受取人(obtain呼び元)="<<name_org<<"("<<prm_org<<")");
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

//工場にため込んでいる全てのインスタンスを破棄
//神(GgafGod)がアプリ終了時等に実行する予定。
void GgafFactory::clean() {
    TRACE2("GgafFactory::clean ＜神＞ 工場を掃除開始");
    GgafOrder* pOrder = ROOT_ORDER;
    if (pOrder == NULL) {
        TRACE2("GgafFactory::clean ＜神＞ しかし工場に何も無い！！");
        return;
    }
    while (_is_working_flg || _was_finished_flg == false) {
        Sleep(10);
        _TRACE_("GgafFactory::clean ＜神＞ 工場がまだ動いています・・・");
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
            GgafOrder* pOrder_MyNext = pOrder->_pOrder_next;
            DELETE_IMPOSSIBLE_NULL(pOrder);
            pOrder = pOrder_MyNext;
        }
    }
    TRACE2("GgafFactory::clean ＜神＞ 工場を掃除完了");
    return;
}

unsigned __stdcall GgafFactory::work(void* prm_arg) {
    //_CrtSetBreakAlloc(95299);
    //_CrtSetBreakAlloc(65854);

    try {
        GgafObject* (*func)(void*, void*, void*) = NULL;
        GgafObject* pObject = NULL;
        GgafOrder* pOrder_InManufacturing_save = NULL;
        Sleep(1000); //god のインスタンスが完成するまでほんのちょっと待つ必要があるかもしれない
        while (_is_working_flg) {
            if (_have_to_rest_flg) {
                _is_resting_flg = true;
                Sleep(100);
                continue;
            } else {
                _is_resting_flg = false;
            }

         ___BeginSynchronized1; // ----->排他開始
            if (CREATING_ORDER) {
                if (CREATING_ORDER->_progress == 0) { //未着手ならまず作る
                    TRACE2("GgafFactory::work ＜工場長＞ よし、注文["<<CREATING_ORDER->_id<<"]は未着手(_progress == "<<CREATING_ORDER->_progress<<")だな。ゆえに今から作ります！");
                    CREATING_ORDER->_progress = 1; //ステータスを製造中へ
                    func = CREATING_ORDER->_pFunc;
                    pOrder_InManufacturing_save = CREATING_ORDER; //ポインタ一時退避
                    void* arg1 = CREATING_ORDER->_pArg1;
                    void* arg2 = CREATING_ORDER->_pArg2;
                    void* arg3 = CREATING_ORDER->_pArg3;
                    TRACE2("GgafFactory::work ＜工場長＞ 製造開始！["<<CREATING_ORDER->_id<<"] (σ ｀・ω・´)σ ");
                    Sleep(2);
                 ___EndSynchronized1; // <----- 排他終了
//#ifdef MY_DEBUG
//try {
//#endif
                    pObject = (*func)(arg1, arg2, arg3); //製品の製造！
//#ifdef MY_DEBUG
//} catch (GgafCriticalException& e) {
//    _TRACE_("＜工場例外＞ 製造中エラー；"<<e.getMsg());
//    std::string message = "\n・"+e.getMsg()+"  \n\nお心あたりが無いメッセージの場合、当方のバグの可能性があります。\n誠に申し訳ございません。\n";
//    std::string message_dialog = message + "(※「Shift + Ctrl + C」でメッセージはコピーできます。)";
//    MessageBox(NULL, message_dialog.c_str(),"下記のエラーが発生してしまいました", MB_OK|MB_ICONSTOP | MB_SETFOREGROUND);
//    _is_working_flg = false;
//    _was_finished_flg = true;
//    GgafGod::_pException_Factory = NEW GgafCriticalException(e.getMsg());
//    return 0;
//}
//#endif

                 ___BeginSynchronized1; // ----->排他開始
                    Sleep(2);
                    TRACE2("GgafFactory::work ＜工場長＞ 製造完了！品番["<<CREATING_ORDER->_id<<"] (^_^)v");
                    if (CREATING_ORDER == NULL) {
                        TRACE2("GgafFactory::work ＜工場長＞ ガーン！。せっかく作ったのにキャンセルっすか・・・。破棄します。pObjectをdelete!");
                        DELETE_IMPOSSIBLE_NULL(pObject);
                     ___EndSynchronized1; // <----- 排他終了
                        continue;
                    } else {
                        CREATING_ORDER = pOrder_InManufacturing_save; //ポインタ復帰
                        CREATING_ORDER->_pObject_creation = pObject; //製品登録
                        CREATING_ORDER->_progress = 2; //ステータスを製造済みへ
                        TRACE2("GgafFactory::work ＜工場長＞ 製造した注文の品["<<(CREATING_ORDER->_id)<<"]を、棚に置いときます。");
                    }
                } else {
                    TRACE2("GgafFactory::work ＜工場長＞ 注文["<<CREATING_ORDER->_id<<"]は既に棚に置いてある(_progress == "<<CREATING_ORDER->_progress<<")。ゆえに飛ばす");
                }
            }
            if (ROOT_ORDER == NULL) {
                //無条件待機
                TRACE2("GgafFactory::work ＜工場長＞ 工場には何～んもありません。さぁなんでも注文来い来い！！・・・ないのん？。（待機）");
             ___EndSynchronized1; // <----- 排他終了
                if (GgafGod::_pGod->_fps > GGAF_PROPERTY(FPS_TO_CLEAN_GARBAGE_BOX)) {
                    TRACE2("GgafFactory::work ＜工場長＞ FPSは高いよなぁ、その間を利用してゴミ箱掃除でもやっときます。1");
                    _pGarbageBox->clean(5); //暇なので、ゴミ箱掃除
                    _cnt_cleaned = 0;
                }
            } else {
                if (ROOT_ORDER != NULL && ROOT_ORDER->_pOrder_prev->_progress == 0) {
                    TRACE2("GgafFactory::work ＜工場長＞ ・・・未製造の注文がある気配。["<<ROOT_ORDER->_pOrder_prev->_id<<"]なのか？。");
                    CREATING_ORDER = CREATING_ORDER->_pOrder_next;
                 ___EndSynchronized1; // <----- 排他終了
                    continue;
                } else {
                    TRACE2("GgafFactory::work ＜工場長＞ さて、未製造注文は無し。あ～棚に製造済のがたまってるす、早く取に来やがれ！。（待機）");
                 ___EndSynchronized1; // <----- 排他終了
                    if (GgafGod::_pGod->_fps > GGAF_PROPERTY(FPS_TO_CLEAN_GARBAGE_BOX)) {
                        TRACE2("GgafFactory::work ＜工場長＞ FPSは高いなぁ、その間を利用してゴミ箱掃除でもやっときます。2");
                        _pGarbageBox->clean(5); //暇なので、ゴミ箱掃除
                        _cnt_cleaned = 0;
                    }
                }
            }
            Sleep(2);
        }
        TRACE2("GgafFactory::work ＜工場長＞ 工場はこれにて店じまいです。さようなら、また会いましょう。");
        _was_finished_flg = true;
    } catch (GgafCriticalException& e) {
        _TRACE_("＜工場例外＞ 私としたことがすみません；"<<e.getMsg());
        _is_working_flg = false;
        _was_finished_flg = true;
        GgafGod::_pException_Factory = NEW GgafCriticalException(e.getMsg());
        return 1;
    }
    return 0;
}

