#include "jp/ggaf/core/GgafFactory.h"

#include "jp/ggaf/core/GgafGod.h"
#include "jp/ggaf/core/GgafOrder.h"
#include "jp/ggaf/core/GgafGarbageBox.h"
#include "jp/ggaf/core/actor/GgafActor.h"
#include "jp/ggaf/core/scene/GgafScene.h"
#include "jp/ggaf/core/GgafProperties.h"


using namespace GgafCore;

//初期化
GgafOrder* GgafFactory::ROOT_ORDER = nullptr;
GgafOrder* GgafFactory::CREATING_ORDER = nullptr;
volatile bool GgafFactory::_is_working_flg = true;
volatile bool GgafFactory::_have_to_rest_flg = false;
volatile bool GgafFactory::_is_resting_flg = false;
volatile bool GgafFactory::_was_finished_flg = false;

GgafMainActor* GgafFactory::obtainActor(uint64_t prm_order_id, GgafObject* prm_org) {
    return (GgafMainActor*)GgafFactory::obtain(prm_order_id, prm_org);
}

GgafMainScene* GgafFactory::obtainScene(uint64_t prm_order_id, GgafObject* prm_org) {
    return (GgafMainScene*)GgafFactory::obtain(prm_order_id, prm_org);
}

//注文
//このメソッドはメインスレッドが実行する。
void GgafFactory::order(uint64_t prm_order_id,
                        GgafObject* (*prm_pFunc)(void*, void*, void*),
                        GgafObject* prm_pOrderer,
                        void* prm_pArg1,
                        void* prm_pArg2,
                        void* prm_pArg3) {
    _TRACE2_("GgafFactory::order ＜客＞ 別スレッドの工場さん、[" << prm_id << "]を作っといて～。");
    //既に注文していないかチェック
    GgafOrder* pOrder = GgafFactory::ROOT_ORDER;
    while (pOrder) {
        if (pOrder->_order_id == prm_order_id) {
            _TRACE_("＜警告＞ GgafFactory::order [" << prm_order_id << "]は、既に注文してるのでスルーします。意図していなければオカシイですよ！");
            return;
        }
        if (pOrder->_is_last_order_flg) {
            break;
        }
        pOrder = pOrder->_pOrder_next;
    }
    //既は未だであるようなので先頭にストック
    GgafOrder* pOrder_new;
    pOrder_new = NEW GgafOrder(prm_order_id);
    pOrder_new->_pObject_creation=nullptr;
    pOrder_new->_pFunc = prm_pFunc;
    pOrder_new->_pOrderer = prm_pOrderer;
    pOrder_new->_pArg1 = prm_pArg1;
    pOrder_new->_pArg2 = prm_pArg2;
    pOrder_new->_pArg3 = prm_pArg3;
    pOrder_new->_progress = 0;
    if (GgafFactory::ROOT_ORDER == nullptr) {
        _TRACE2_("GgafFactory::order ＜客＞ あぁ、工場は空っきしですね。注文、すぐできるよね？。");
        pOrder_new->_is_first_order_flg = true;
        pOrder_new->_is_last_order_flg = true;
        pOrder_new->_pOrder_next = pOrder_new;
        pOrder_new->_pOrder_prev = pOrder_new;
        GgafFactory::ROOT_ORDER = pOrder_new;
        GgafFactory::CREATING_ORDER = pOrder_new;
    } else {
        _TRACE2_("GgafFactory::order ＜客＞ 注文たまってますね、次々注文恐れ入ります。");
        pOrder_new->_is_first_order_flg = false;
        pOrder_new->_is_last_order_flg = true;
        GgafOrder* pOrder_last;
        pOrder_last = GgafFactory::ROOT_ORDER->_pOrder_prev;
        pOrder_last->_is_last_order_flg = false;
        pOrder_last->_pOrder_next = pOrder_new;
        pOrder_new->_pOrder_prev = pOrder_last;
        pOrder_new->_pOrder_next = GgafFactory::ROOT_ORDER;
        GgafFactory::ROOT_ORDER->_pOrder_prev = pOrder_new;
    }
}

int GgafFactory::chkProgress(uint64_t prm_order_id) {
    GgafOrder* pOrder;
    pOrder = GgafFactory::ROOT_ORDER;
    if (pOrder == nullptr) {
        return -1;
    }
    while (GgafFactory::_is_working_flg) {
        if (pOrder->_order_id == prm_order_id) {
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

void* GgafFactory::obtain(uint64_t prm_order_id, GgafObject* prm_org) {
    GgafOrder* pOrder;
    GgafOrder* pOrder_my_next;
    GgafOrder* pOrder_my_prev;
    DWORD waittime = 0;
    pOrder = GgafFactory::ROOT_ORDER;
    void* objectCreation;


    if (pOrder == nullptr) {
        //注文が無いよエラー発生！、エラーメッセージを作る。
        _TRACE_("GgafFactory::obtain 注文が無いよエラー発生！");
        GgafFactory::debuginfo();
        std::string name_org;
        if (prm_org->instanceOf(Obj_GgafScene)) {
            name_org = ((GgafScene*)prm_org)->getName();
        } else if (prm_org->instanceOf(Obj_GgafActor)) {
            name_org = ((GgafActor*)prm_org)->getName();
        }
        throwGgafCriticalException("GgafFactory::obtain("<<prm_order_id<<") Error! 注文リストはnullptrで全て製造済みしています。\n"<<
                                   "orederとobtainの対応が取れていません。\n"<<
                                   "受取人(obtain呼び元)="<<name_org<<"("<<prm_org<<")");
    }

    //obtainメインループ
    while (GgafFactory::_is_working_flg) {

        if (pOrder->_order_id == prm_order_id) {
            _TRACE2_("GgafFactory::obtain ＜客＞ こんにちは、["<<prm_order_id<<"]を取りに来ましたよっと。");
            while (GgafFactory::_is_working_flg) {
                if (pOrder->_progress != 2) {
                    _TRACE2_("GgafFactory::obtain ＜客＞ 別スレッド工場さん、["<<prm_order_id<<"]の製造まだ～？、5ミリ秒だけ待ったげよう。pOrder->_progress="<<(pOrder->_progress));
#ifdef _DEBUG
                    //デバッグ時はタイムアウト無し
#else

                    if (waittime > 1000*600) { //約10分
                        _TRACE_("GgafFactory::obtain タイムアウトエラー発生！");
                        GgafFactory::debuginfo();
                        //タイムアウトエラー発生！、エラーメッセージを作る。
                        std::string name_org;
                        if (prm_org->instanceOf(Obj_GgafScene)) {
                            name_org = ((GgafScene*)prm_org)->getName();
                        } else if (prm_org->instanceOf(Obj_GgafActor)) {
                            name_org = ((GgafActor*)prm_org)->getName();
                        }
                        throwGgafCriticalException("GgafFactory::obtain Error! ["<<prm_order_id<<"]の製造待ち時間タイムアウト、取得できません。\n"<<
                                                   "何らかの理由でメインスレッドが停止している可能性が大きいです。"<<
                                                   "発注者(order呼び元)=("<<pOrder->_pOrderer<<")／受取人(obtain呼び元)="<<name_org<<"("<<prm_org<<")");
                    } else {
                    }
#endif
                    END_SYNCHRONIZED1; // <----- 排他終了
                    Sleep(5);
                    BEGIN_SYNCHRONIZED1; // ----->排他開始
                    waittime += 5;
                    if (pOrder->_progress == 1) {
                        //着手済み
                        _TRACE_N_("Soon ");
                        continue; //待つ
                    } else if (pOrder->_progress == 0) {
                        //未着手？
                        pOrder = GgafFactory::ROOT_ORDER; //もう一度最初から探させる。
                        _TRACE_N_("Wait ");
                        break;
                    } else if (pOrder->_progress == 2) {
                        //完成
                        pOrder = GgafFactory::ROOT_ORDER; //もう一度最初から探させる。
                        _TRACE_N_("Okey-doke ");
                        break;
                    }
                } else {
                    _TRACE2_("GgafFactory::obtain ＜客＞ おぉ、["<<prm_id<<"]は製造済みですね、さすが！。あざーす！");
#ifdef MY_DEBUG
                    if (waittime > 0) {
                        _TRACE_N_("...Finish!! ");
                    }
#endif
                    if (pOrder->_is_first_order_flg && pOrder->_is_last_order_flg) {
                        objectCreation = pOrder->_pObject_creation;
                        pOrder->_pObject_creation = nullptr;
                        GGAF_DELETE(pOrder);
                        pOrder = nullptr;
                        GgafFactory::ROOT_ORDER = nullptr;
                        GgafFactory::CREATING_ORDER = nullptr;
                        _TRACE2_("GgafFactory::obtain ＜客＞ 製品["<<prm_id<<"]頂きました。あ、もう工場は空ですね。暇になった？ねぇ？");
                        return (void*)objectCreation;
                    } else {
                        pOrder_my_next = pOrder->_pOrder_next;
                        pOrder_my_prev = pOrder->_pOrder_prev;
                        pOrder_my_prev->_pOrder_next = pOrder_my_next;
                        pOrder_my_next->_pOrder_prev = pOrder_my_prev;
                        if (pOrder->_is_first_order_flg == false && pOrder->_is_last_order_flg) {
                            pOrder_my_prev->_is_last_order_flg = true;
//                            GgafFactory::CREATING_ORDER = pOrder_my_prev;
                        } else if (pOrder->_is_first_order_flg && pOrder->_is_last_order_flg == false) {
                            pOrder_my_next->_is_first_order_flg = true;
                            GgafFactory::ROOT_ORDER = pOrder_my_next;
//                            GgafFactory::CREATING_ORDER = pOrder_my_next;
                        } else if (pOrder->_is_first_order_flg == false && pOrder->_is_last_order_flg == false) {

                            //GgafFactory::CREATING_ORDER = pOrder_my_prev;
                        }
                        if (GgafFactory::CREATING_ORDER == pOrder) {
                            GgafFactory::CREATING_ORDER = pOrder_my_prev;
                        }
                        objectCreation = pOrder->_pObject_creation;
                        pOrder->_pObject_creation = nullptr;
                        GGAF_DELETE(pOrder);
                        pOrder = nullptr;

                        return (void*)objectCreation;
                    }
                }
            }
        } else {
            if (pOrder->_is_last_order_flg) {
                _TRACE_("GgafFactory::obtain 注文の形跡が無い、取得出来ないエラー発生！");
                GgafFactory::debuginfo();
                //注文の形跡が無い、取得出来ないエラー発生！、エラーメッセージを作る。
                std::string name_org;
                if (prm_org->instanceOf(Obj_GgafScene)) {
                    name_org = ((GgafScene*)prm_org)->getName();
                } else if (prm_org->instanceOf(Obj_GgafActor)) {
                    name_org = ((GgafActor*)prm_org)->getName();
                }
                throwGgafCriticalException("GgafFactory::obtain Error! ＜工場長＞全部探しましたけど、そんな注文(prm_order_id="<<prm_order_id<<")は、ありません。\n "<<
                                           "oreder() と GgafFactory::obtain() の対応が取れていません。oreder()漏れ、或いは同じ GgafFactory::obtain() を２回以上してませんか？。\n"<<
                                           "情報：受取人(obtain呼び元)="<<name_org<<"("<<prm_org<<") でした。\n" <<
                                           "（※ちなみに、現在工場の最終オーダーは、注文番号(_order_id="<<pOrder->_order_id<<")で、発注者(order呼び元)=("<<pOrder->_pOrderer<<") でした）");
            } else {
                pOrder = pOrder->_pOrder_next;
            }
        }
    }
    if (GgafGod::_pException_factory) {
        throw *(GgafGod::_pException_factory);
    }
    return nullptr;
}

void GgafFactory::beginRest() {
    _TRACE_("GgafFactory::beginRest() ＜神＞工場、休憩しなさい");
    GgafFactory::_have_to_rest_flg = true;
}

bool GgafFactory::isResting() {
    if (GgafFactory::_is_resting_flg) {
        _TRACE_("GgafFactory::isResting() 工場休止状態");
    } else {
        _TRACE_("GgafFactory::isResting() 工場稼働状態");
    }
    return GgafFactory::_is_resting_flg;
}

void GgafFactory::finishRest() {
    _TRACE_("GgafFactory::beginRest() ＜神＞工場、休憩はおしまい。さあ動け！");
    GgafFactory::_have_to_rest_flg = false;
}

//工場にため込んでいる全てのインスタンスを破棄
//神(GgafGod)がアプリ終了時等に実行する予定。
void GgafFactory::clean() {
    _TRACE2_("GgafFactory::clean ＜神＞ 工場を掃除開始");
    GgafOrder* pOrder = GgafFactory::ROOT_ORDER;
    if (pOrder == nullptr) {
        _TRACE2_("GgafFactory::clean ＜神＞ しかし工場に何も無い！！");
        return;
    }
    while (GgafFactory::_is_working_flg || GgafFactory::_was_finished_flg == false) {
        Sleep(10);
        _TRACE_("GgafFactory::clean ＜神＞ 工場がまだ動いています・・・");
    }

    GgafFactory::debuginfo();

    while (true) {
        if (pOrder->_is_last_order_flg) {
            _TRACE2_("GgafFactory::clean ＜神＞ 製品削除["<<pOrder->_id<<"]、最後のストック");
            GGAF_DELETE(pOrder);
            pOrder = nullptr;
            GgafFactory::ROOT_ORDER = nullptr;
            GgafFactory::CREATING_ORDER = nullptr;
            break;
        } else {
            _TRACE2_("GgafFactory::clean ＜神＞ 製品削除["<<pOrder->_id<<"]");
            GgafOrder* pOrder_my_next = pOrder->_pOrder_next;
            GGAF_DELETE(pOrder);
            pOrder = pOrder_my_next;
        }
    }
    _TRACE2_("GgafFactory::clean ＜神＞ 工場を掃除完了");
    return;
}

void GgafFactory::debuginfo() {
    _TRACE_("GgafFactory::debuginfo ＜デバッグ情報＞ 現在の工場の状態");
    try {
        GgafOrder* p = GgafFactory::ROOT_ORDER;
        if (p) {
            while(p) {

                if (p->_pObject_creation) {

                    std::string name_creation;
                    if (p->_pObject_creation->instanceOf(Obj_GgafScene)) {
                        name_creation = ((GgafScene*)p->_pObject_creation)->getName();
                    } else if (p->_pObject_creation->instanceOf(Obj_GgafActor)) {
                        name_creation = ((GgafActor*)p->_pObject_creation)->getName();
                    }


                    _TRACE_("・注文ID="<<p->_order_id<<", "<<
                            "進捗="<<p->_progress<<", "<<
                            "商品="<<name_creation<<"("<<p->_pObject_creation<<")"<<", "<<
                            "発注者=("<<p->_pOrderer<<")"
                    );
                } else {
                    _TRACE_("・注文ID="<<p->_order_id<<", "<<
                            "進捗="<<p->_progress<<", "<<
                            "商品=nullptr, "<<
                            "発注者=("<<p->_pOrderer<<")"
                    );
                }
                p = p->_pOrder_next;
                if (p == GgafFactory::ROOT_ORDER) {
                    break;
                }
            }
        } else {
            _TRACE_("・オーダーありません！");
        }
    } catch (...) {
        _TRACE_("GgafFactory::debuginfo なんということでしょう。現在の工場の状態の表示が不可能です。");
    }
    _TRACE_("GgafFactory::debuginfo 以上");
}





unsigned __stdcall GgafFactory::work(void* prm_arg) {
    //_CrtSetBreakAlloc(95299);
    //_CrtSetBreakAlloc(65854);

    try {
        GgafObject* (*func)(void*, void*, void*) = nullptr;
        GgafObject* pObject = nullptr;
        GgafOrder* pOrder_in_manufacturing_save = nullptr;
        Sleep(1000); //god のインスタンスが完成するまでほんのちょっと待つ必要があるかもしれない
        while (GgafFactory::_is_working_flg) {
            if (GgafFactory::_have_to_rest_flg) {
                GgafFactory::_is_resting_flg = true;
                Sleep(100);
                continue;
            } else {
                GgafFactory::_is_resting_flg = false;
            }

            BEGIN_SYNCHRONIZED1; // ----->排他開始
            if (GgafFactory::CREATING_ORDER) {
                if (GgafFactory::CREATING_ORDER->_progress == 0) { //未着手ならまず作る
                    _TRACE2_("GgafFactory::work ＜工場長＞ よし、注文["<<GgafFactory::CREATING_ORDER->_id<<"]は未着手(_progress == "<<GgafFactory::CREATING_ORDER->_progress<<")だな。ゆえに今から作ります！");
                    GgafFactory::CREATING_ORDER->_progress = 1; //ステータスを製造中へ
                    func = GgafFactory::CREATING_ORDER->_pFunc;
                    pOrder_in_manufacturing_save = GgafFactory::CREATING_ORDER; //ポインタ一時退避
                    void* arg1 = GgafFactory::CREATING_ORDER->_pArg1;
                    void* arg2 = GgafFactory::CREATING_ORDER->_pArg2;
                    void* arg3 = GgafFactory::CREATING_ORDER->_pArg3;
                    _TRACE2_("GgafFactory::work ＜工場長＞ 製造開始！["<<GgafFactory::CREATING_ORDER->_id<<"] (σ ｀・ω・´)σ ");
                    Sleep(2);
                    END_SYNCHRONIZED1; // <----- 排他終了
//#ifdef MY_DEBUG
//try {
//#endif
                    pObject = (*func)(arg1, arg2, arg3); //製品の製造！
//#ifdef MY_DEBUG
//} catch (GgafCriticalException& e) {
//    _TRACE_("＜工場例外＞ 製造中エラー；"<<e.getMsg());
//    std::string message = "\n・"+e.getMsg()+"  \n\nお心あたりが無いメッセージの場合、当方のバグの可能性があります。\n誠に申し訳ございません。\n";
//    std::string message_dialog = message + "(※「Shift + Ctrl + C」でメッセージはコピーできます。)";
//    MessageBox(nullptr, message_dialog.c_str(),"下記のエラーが発生してしまいました", MB_OK|MB_ICONSTOP | MB_SETFOREGROUND|MB_TOPMOST);
//    GgafFactory::_is_working_flg = false;
//    GgafFactory::_was_finished_flg = true;
//    GgafGod::_pException_factory = NEW GgafCriticalException(e.getMsg());
//    return 0;
//}
//#endif

                    BEGIN_SYNCHRONIZED1; // ----->排他開始
                    Sleep(2);
                    _TRACE2_("GgafFactory::work ＜工場長＞ 製造完了！品番["<<GgafFactory::CREATING_ORDER->_id<<"] (^_^)v");
                    if (GgafFactory::CREATING_ORDER == nullptr) {
                        _TRACE2_("GgafFactory::work ＜工場長＞ ガーン！。せっかく作ったのにキャンセルっすか・・・。破棄します。pObjectをdelete!");
                        GGAF_DELETE(pObject);
                        END_SYNCHRONIZED1; // <----- 排他終了
                        continue;
                    } else {
                        GgafFactory::CREATING_ORDER = pOrder_in_manufacturing_save; //ポインタ復帰
                        GgafFactory::CREATING_ORDER->_pObject_creation = pObject; //製品登録
                        GgafFactory::CREATING_ORDER->_progress = 2; //ステータスを製造済みへ
                        _TRACE2_("GgafFactory::work ＜工場長＞ 製造した注文の品["<<(GgafFactory::CREATING_ORDER->_id)<<"]を、棚に置いときます。");
                    }
                } else {
                    _TRACE2_("GgafFactory::work ＜工場長＞ 注文["<<GgafFactory::CREATING_ORDER->_id<<"]は既に棚に置いてある(_progress == "<<GgafFactory::CREATING_ORDER->_progress<<")。ゆえに飛ばす");
                }
            }
            if (GgafFactory::ROOT_ORDER == nullptr) {
                //無条件待機
                _TRACE2_("GgafFactory::work ＜工場長＞ 工場には何～んもありません。さぁなんでも注文来い来い！！・・・ないのん？。（待機）");
                END_SYNCHRONIZED1; // <----- 排他終了
                if (GgafGod::_pGod->_fps >= PROPERTY::FPS_TO_CLEAN_GARBAGE_BOX) {
                    _TRACE2_("GgafFactory::work ＜工場長＞ FPSは高いよなぁ、その間を利用してゴミ箱掃除でもやっときます。1");
                    GgafGarbageBox::_pGarbageBox->clean(5); //暇なので、ゴミ箱掃除
                    GgafGarbageBox::_cnt_cleaned = 0;
                }
            } else {
                if (GgafFactory::ROOT_ORDER != nullptr && GgafFactory::ROOT_ORDER->_pOrder_prev->_progress == 0) {
                    _TRACE2_("GgafFactory::work ＜工場長＞ ・・・未製造の注文がある気配。["<<GgafFactory::ROOT_ORDER->_pOrder_prev->_id<<"]なのか？。");
                    GgafFactory::CREATING_ORDER = GgafFactory::CREATING_ORDER->_pOrder_next;
                    END_SYNCHRONIZED1; // <----- 排他終了
                    continue;
                } else {
                    _TRACE2_("GgafFactory::work ＜工場長＞ さて、未製造注文は無し。あ～棚に製造済のがたまってるす、早く取に来やがれ！。（待機）");
                    END_SYNCHRONIZED1; // <----- 排他終了
                    if (GgafGod::_pGod->_fps >= PROPERTY::FPS_TO_CLEAN_GARBAGE_BOX) {
                        _TRACE2_("GgafFactory::work ＜工場長＞ FPSは高いなぁ、その間を利用してゴミ箱掃除でもやっときます。2");
                        GgafGarbageBox::_pGarbageBox->clean(5); //暇なので、ゴミ箱掃除
                        GgafGarbageBox::_cnt_cleaned = 0;
                    }
                }
            }
            Sleep(2);
        }
        _TRACE2_("GgafFactory::work ＜工場長＞ 工場はこれにて店じまいです。さようなら、また会いましょう。");
        GgafFactory::_was_finished_flg = true;
    } catch (GgafCriticalException& e) {
        GgafFactory::debuginfo();
        _TRACE_("＜工場例外＞ 私としたことがすみません；"<<e.getMsg());
        GgafFactory::_is_working_flg = false;
        GgafFactory::_was_finished_flg = true;
        GgafGod::_pException_factory = NEW GgafCriticalException(e.getMsg());
        return 1;
    }
    return 0;
}

