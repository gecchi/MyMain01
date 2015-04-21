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
#ifdef _MSC_VER
volatile bool GgafFactory::_is_working_flg   = true;
volatile bool GgafFactory::_have_to_rest_flg = false;
volatile bool GgafFactory::_is_resting_flg   = false;
volatile bool GgafFactory::_was_finished_flg = false;
#else
volatile std::atomic<bool> GgafFactory::_is_working_flg(true);
volatile std::atomic<bool> GgafFactory::_have_to_rest_flg(false);
volatile std::atomic<bool> GgafFactory::_is_resting_flg(false);
volatile std::atomic<bool> GgafFactory::_was_finished_flg(false);
#endif

GgafMainActor* GgafFactory::obtainActor(uint64_t prm_order_no, GgafObject* prm_pReceiver) {
    return (GgafMainActor*)GgafFactory::obtain(prm_order_no, prm_pReceiver);
}

GgafMainScene* GgafFactory::obtainScene(uint64_t prm_order_no, GgafObject* prm_pReceiver) {
    return (GgafMainScene*)GgafFactory::obtain(prm_order_no, prm_pReceiver);
}


//このメソッドはメインスレッドが実行する。
void GgafFactory::order(uint64_t prm_order_no,
                        GgafObject* (*prm_pFunc)(void*, void*, void*),
                        GgafObject* prm_pOrderer,
                        GgafObject* prm_pReceiver,
                        void* prm_pArg1,
                        void* prm_pArg2,
                        void* prm_pArg3) {

    _TRACE2_("GgafFactory::order ＜客:("<<prm_pOrderer<<")＞ 別スレッドの工場さん、 [" << prm_order_no << "/"<<prm_pReceiver<<"]を作っといてや～。");
    //既に注文していないかチェック
    GgafOrder* pOrder = GgafFactory::ROOT_ORDER;
    while (pOrder) {
        if (pOrder->_order_no == prm_order_no &&  pOrder->_pReceiver == prm_pReceiver) {
            _TRACE_("＜警告＞ GgafFactory::order ちょっと、[" << prm_order_no << "/"<<prm_pReceiver<<"]は、２重注文していますよ！、無視します。意図していますか？");
            return;
        }
        if (pOrder->_is_last_order_flg) {
            break;
        }
        pOrder = pOrder->_pOrder_next;
    }
    //既は未だであるようなので先頭にストック
    GgafOrder* pOrder_new;
    pOrder_new = NEW GgafOrder(prm_order_no);
    pOrder_new->_pObject_creation=nullptr;
    pOrder_new->_pFunc = prm_pFunc;
    pOrder_new->_pOrderer = prm_pOrderer;
    pOrder_new->_pReceiver = prm_pReceiver;
    pOrder_new->_time_of_order = timeGetTime();
    pOrder_new->_pArg1 = prm_pArg1;
    pOrder_new->_pArg2 = prm_pArg2;
    pOrder_new->_pArg3 = prm_pArg3;
    pOrder_new->_progress = 0;
    if (GgafFactory::ROOT_ORDER == nullptr) {
        _TRACE2_("GgafFactory::order ＜客:("<<prm_pOrderer<<")＞ あぁ、工場は空っきしですね。注文したら、すぐできるよね？。");
        pOrder_new->_is_first_order_flg = true;
        pOrder_new->_is_last_order_flg = true;
        pOrder_new->_pOrder_next = pOrder_new;
        pOrder_new->_pOrder_prev = pOrder_new;
        GgafFactory::ROOT_ORDER = pOrder_new;
        GgafFactory::CREATING_ORDER = pOrder_new;
    } else {
        _TRACE2_("GgafFactory::order ＜客:("<<prm_pOrderer<<")＞ 注文たまってますね、次々注文恐れ入ります。");
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

int GgafFactory::chkProgress(uint64_t prm_order_no) {
    GgafOrder* pOrder;
    pOrder = GgafFactory::ROOT_ORDER;
    if (pOrder == nullptr) {
        return -1;
    }
    while (GgafFactory::_is_working_flg) {
        if (pOrder->_order_no == prm_order_no) {
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

void* GgafFactory::obtain(uint64_t prm_order_no, GgafObject* prm_pReceiver) {
    _TRACE2_("GgafFactory::obtain ＜受取人:"<< (prm_pReceiver ? prm_pReceiver->toString() : "nullptr") <<"("<<prm_pReceiver<<")＞ まいど、["<<prm_order_no<<"/"<<prm_pReceiver<<"]を取りに来ましたよっと。");
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
        throwGgafCriticalException("GgafFactory::obtain("<<prm_order_no<<") Error! 注文リストはnullptrで全て製造済みしています。\n"<<
                                   "orederとobtainの対応が取れていません。\n"<<
                                   "受取人(obtain呼び元)="<<(prm_pReceiver ? prm_pReceiver->toString() : "nullptr")<<"("<<prm_pReceiver<<")");
    }

    //obtainメインループ
    while (GgafFactory::_is_working_flg) {
        if (pOrder->_order_no == prm_order_no && (pOrder->_pReceiver == nullptr || pOrder->_pReceiver == prm_pReceiver) ) {
            while (GgafFactory::_is_working_flg) {
                if (pOrder->_progress < 2) {
                    _TRACE2_("GgafFactory::obtain ＜受取人:"<<(prm_pReceiver ? prm_pReceiver->toString() : "nullptr")<<"("<<prm_pReceiver<<")＞ ねぇ工場長さん、["<<prm_order_no<<"/"<<prm_pReceiver<<"]の製造まだ～？、5ミリ秒だけ待ったげよう。pOrder->_progress="<<(pOrder->_progress));
#ifdef _DEBUG
                    //デバッグ時はタイムアウト無し
#else

                    if (waittime > 1000*600) { //約10分
                        _TRACE_("GgafFactory::obtain タイムアウトエラー発生！");
                        GgafFactory::debuginfo();
                        //タイムアウトエラー発生！、エラーメッセージを作る。
                        throwGgafCriticalException("GgafFactory::obtain Error! 注文["<<pOrder->getDebuginfo()<<"]の製造待ち時間タイムアウト、取得できません。\n"<<
                                                   "何らかの理由でメインスレッドが停止している可能性が大きいです。"<<
                                                   "受取人(obtain呼び元)="<<(prm_pReceiver ? prm_pReceiver->toString() : "nullptr")<<"("<<prm_pReceiver<<")");
                    } else {
                    }
#endif
                    END_SYNCHRONIZED1; // <----- 排他終了
                    Sleep(5);
                    BEGIN_SYNCHRONIZED1; // ----->排他開始
                    waittime += 5;
                    if (pOrder->_progress == 1) {
                        //着手済み
                        _TRACE_N_("製造中、");
                        continue; //待つ
                    } else if (pOrder->_progress == 0) {
                        //未着手？
                        pOrder = GgafFactory::ROOT_ORDER; //もう一度最初から探させる。
                        _TRACE_N_("待って、");
                        break;
                    } else if (pOrder->_progress == 2) {
                        //完成
                        pOrder = GgafFactory::ROOT_ORDER; //もう一度最初から探させる。
                        _TRACE_N_("完成、");
                        break;
                    }
                } else {

#ifdef MY_DEBUG
                    if (waittime > 0) {
                        _TRACE_N_("・・・おまたせしました。");
                    }
#endif
                    _TRACE2_("GgafFactory::obtain ＜受取人:"<<(prm_pReceiver ? prm_pReceiver->toString() : "nullptr")<<"("<<prm_pReceiver<<")＞ よ～し、["<<prm_order_no<<"/"<<prm_pReceiver<<"]は製造完了ですね。おおきに！");
                    if (pOrder->_is_first_order_flg && pOrder->_is_last_order_flg) {
                        //最後の一つを obtain
                        objectCreation = pOrder->_pObject_creation;
                        pOrder->_pObject_creation = nullptr;
                        GGAF_DELETE(pOrder);
                        pOrder = nullptr;
                        GgafFactory::ROOT_ORDER = nullptr;
                        GgafFactory::CREATING_ORDER = nullptr;
                        _TRACE2_("GgafFactory::obtain ＜受取人:"<<(prm_pReceiver ? prm_pReceiver->toString() : "nullptr")<<"("<<prm_pReceiver<<")＞ あ、ところでもう工場は空ですね。暇になったん？、ねぇ？");
                        return (void*)objectCreation;
                    } else {
                        //中間をobtain、鎖を繋ぎ直す。
                        pOrder_my_next = pOrder->_pOrder_next;
                        pOrder_my_prev = pOrder->_pOrder_prev;
                        pOrder_my_prev->_pOrder_next = pOrder_my_next;
                        pOrder_my_next->_pOrder_prev = pOrder_my_prev;
                        if (pOrder->_is_last_order_flg) {
                            pOrder_my_prev->_is_last_order_flg = true;
                        }
                        if (pOrder->_is_first_order_flg) {
                            GgafFactory::ROOT_ORDER = pOrder_my_next;
                            pOrder_my_next->_is_first_order_flg = true;
                        }
                        if (GgafFactory::CREATING_ORDER == pOrder) {
                            GgafFactory::CREATING_ORDER = pOrder_my_next;
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
                throwGgafCriticalException("GgafFactory::obtain Error! ＜工場長＞全部探しましたけど、そんな注文("<<(prm_pReceiver ? prm_pReceiver->toString() : "nullptr")<<"さんへの 注文番号:"<<prm_order_no<<"/"<<prm_pReceiver<<")は、ありません。\n "<<
                                           "oreder() と GgafFactory::obtain() の対応が取れていません。oreder()漏れ、或いは同じ GgafFactory::obtain() を２回以上してませんか？。\n"<<
                                           "情報：受取人(obtain呼び元)="<<(prm_pReceiver ? prm_pReceiver->toString() : "nullptr")<<"("<<prm_pReceiver<<") でした。\n" <<
                                           "（※ちなみに、現在工場の最終オーダーは、注文番号("<<pOrder->_order_no<<"/"<<pOrder->_pReceiver<<")で、発注者(order呼び元)=("<<pOrder->_pOrderer<<") でした）");
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
            _TRACE2_("GgafFactory::clean ＜神＞ 製品削除["<<pOrder->getDebuginfo()<<"]、最後のストック");
            GGAF_DELETE(pOrder);
            pOrder = nullptr;
            GgafFactory::ROOT_ORDER = nullptr;
            GgafFactory::CREATING_ORDER = nullptr;
            break;
        } else {
            _TRACE2_("GgafFactory::clean ＜神＞ 製品削除["<<pOrder->getDebuginfo()<<"]");
            GgafOrder* pOrder_my_next = pOrder->_pOrder_next;
            GGAF_DELETE(pOrder);
            pOrder = pOrder_my_next;
        }
    }
    _TRACE2_("GgafFactory::clean ＜神＞ 工場を掃除完了");
    return;
}

void GgafFactory::removeOrder(GgafObject* prm_pReceiver) {
    GgafOrder* pOrder = GgafFactory::ROOT_ORDER;
    while (pOrder) {
        if (pOrder->_pReceiver == prm_pReceiver) {
            if (pOrder->_is_last_order_flg && pOrder->_is_first_order_flg) {
                //最後の一つ
                GGAF_DELETE(pOrder);
                GgafFactory::ROOT_ORDER = nullptr;
                GgafFactory::CREATING_ORDER = nullptr;
                break; //終了
            } else {
                //間の場合、ポインタを繋ぎ直す。
                GgafOrder* pOrder_t_next = pOrder->_pOrder_next;
                GgafOrder* pOrder_t_prev = pOrder->_pOrder_prev;
                pOrder_t_prev->_pOrder_next = pOrder_t_next;
                pOrder_t_next->_pOrder_prev = pOrder_t_prev;

                if (pOrder->_is_last_order_flg) {
                    pOrder_t_prev->_is_last_order_flg = true;
                }
                if (pOrder->_is_first_order_flg) {
                    GgafFactory::ROOT_ORDER = pOrder_t_next;
                    pOrder_t_next->_is_first_order_flg = true;
                }
                if (GgafFactory::CREATING_ORDER == pOrder) {
                    GgafFactory::CREATING_ORDER = pOrder_t_next;
                }
                _TRACE_("GgafFactory::removeOrder 受取人("<<prm_pReceiver<<")死亡の為、注文を削除します。" << pOrder->getDebuginfo() << "");
                GGAF_DELETE(pOrder);
                pOrder = pOrder_t_next;
                continue;
            }
        } else {
            if (pOrder->_is_last_order_flg) {
                break; //終了
            } else {
                pOrder = pOrder->_pOrder_next;
                continue;
            }
        }
    }
}

void GgafFactory::debuginfo() {
    _TRACE_("GgafFactory::debuginfo ＜デバッグ情報＞ 現在の工場の状態");
    try {
        GgafOrder* p = GgafFactory::ROOT_ORDER;
        if (p) {
            while(p) {
                _TRACE_("・" << p->getDebuginfo() );
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
    //_CrtSetBreakAlloc(65854);
    try {
        GgafObject* (*func)(void*, void*, void*) = nullptr;
        GgafObject* pObject = nullptr;
        Sleep(1000); //god のインスタンスが完成するまでほんのちょっと待つ必要があるかもしれない

        //製品を作りまくる工場ループ！
        while (GgafFactory::_is_working_flg) {
            if (GgafFactory::_have_to_rest_flg) {
                GgafFactory::_is_resting_flg = true;
                Sleep(100);
                continue;
            } else {
                GgafFactory::_is_resting_flg = false;
            }

BEGIN_SYNCHRONIZED1; // ----->排他開始
            GgafOrder* pOrder_creating = GgafFactory::CREATING_ORDER;
            if (pOrder_creating) {
                if (pOrder_creating->_progress == 0) { //未着手ならまず作る
                    _TRACE2_("GgafFactory::work ＜工場長＞ よし、注文["<<pOrder_creating->_order_no<<"/"<<pOrder_creating->_pReceiver<<"]は未着手(_progress == "<<pOrder_creating->_progress<<")だな。ゆえに今から作ります！");
                    pOrder_creating->_progress = 1; //ステータスを製造中へ
                    pOrder_creating->_time_of_create_begin = timeGetTime();
                    func = pOrder_creating->_pFunc;
                    void* arg1 = pOrder_creating->_pArg1;
                    void* arg2 = pOrder_creating->_pArg2;
                    void* arg3 = pOrder_creating->_pArg3;
                    _TRACE2_("GgafFactory::work ＜工場長＞ 製造開始！["<<pOrder_creating->_order_no<<"/"<<pOrder_creating->_pReceiver<<"]");
                    Sleep(2);
                    END_SYNCHRONIZED1; // <----- 排他終了

                    pObject = (*func)(arg1, arg2, arg3); //製品の製造！

                    BEGIN_SYNCHRONIZED1; // ----->排他開始
                    Sleep(2);
                    _TRACE2_("GgafFactory::work ＜工場長＞ 製造完了！品は["<<pOrder_creating->_order_no<<"/"<<pOrder_creating->_pReceiver<<"] (^_^)v");
                    if (GgafFactory::CREATING_ORDER == nullptr) {
                        //GgafFactory::CREATING_ORDER が製造後 nullptr になってしまっている場合キャンセル。
                        _TRACE2_("GgafFactory::work ＜工場長＞ ガーン！。せっかく作ったのにキャンセルっすか・・・。破棄します。pObjectをdelete!");
                        GGAF_DELETE(pObject);
END_SYNCHRONIZED1; // <----- 排他終了
                        continue;
                    } else if (GgafFactory::CREATING_ORDER == pOrder_creating) {
                        //正常なケース
                        pOrder_creating->_pObject_creation = pObject; //製品登録
                        pOrder_creating->_progress = 2; //ステータスを製造済みへ
                        pOrder_creating->_time_of_create_finish = timeGetTime();
                        _TRACE2_("GgafFactory::work ＜工場長＞ 製造した注文の品["<<pOrder_creating->_order_no<<"/"<<pOrder_creating->_pReceiver<<"]を、棚に置いときます。");
                    }  else if (GgafFactory::CREATING_ORDER != pOrder_creating) {
                        _TRACE2_("GgafFactory::work ＜工場長＞ 警告、注文の品["<<pOrder_creating->_order_no<<"/"<<pOrder_creating->_pReceiver<<"]を作っている間に、"<<
                                 "CREATING_ORDER が、別の注文["<<GgafFactory::CREATING_ORDER->_order_no<<"/"<<GgafFactory::CREATING_ORDER->_pReceiver<<"]を指していました！壊れてるかもしれません！強制的に元に戻します！要調査！");
                        GgafFactory::CREATING_ORDER = pOrder_creating; //ポインタ強制戻し
                        pOrder_creating->_pObject_creation = pObject; //製品登録
                        pOrder_creating->_progress = 2; //ステータスを製造済みへ
                        pOrder_creating->_time_of_create_finish = timeGetTime();
                        _TRACE2_("GgafFactory::work ＜工場長＞ 製造した注文の品["<<pOrder_creating->_order_no<<"/"<<pOrder_creating->_pReceiver<<"]を、棚に置いときます・・・。");
                    }
                } else {
                    _TRACE2_("GgafFactory::work ＜工場長＞ 注文["<<pOrder_creating->_order_no<<"/"<<pOrder_creating->_pReceiver<<"]は、もう作って棚に置いてあるし・・・(_progress == "<<pOrder_creating->_progress<<")。");
                }
            }
            if (GgafFactory::ROOT_ORDER == nullptr) {
                //無条件待機
                _TRACE2_("GgafFactory::work ＜工場長＞ 工場には何～んもありません。さぁなんでも注文来い来い！！・・・ないのん？。（待機）");
END_SYNCHRONIZED1; // <----- 排他終了
                if (GgafGod::_pGod->_fps >= PROPERTY::FPS_TO_CLEAN_GARBAGE_BOX) {
                    _TRACE2_("GgafFactory::work ＜工場長＞ さほど忙しくないので、ゴミ箱のゴミを出しとこう。");
                    GgafGarbageBox::_pGarbageBox->clean(5); //暇なので、ゴミ箱掃除
                    GgafGarbageBox::_cnt_cleaned = 0;
                }
            } else {
                if (GgafFactory::ROOT_ORDER != nullptr && GgafFactory::ROOT_ORDER->_pOrder_prev->_progress == 0) {
                    _TRACE2_("GgafFactory::work ＜工場長＞ ・・・未製造の注文がある気配。最終目標の注文は["<<GgafFactory::ROOT_ORDER->_pOrder_prev->_order_no<<"/受取人="<<GgafFactory::ROOT_ORDER->_pOrder_prev->_pReceiver<<"]なのか？。");
                    GgafFactory::CREATING_ORDER = GgafFactory::CREATING_ORDER->_pOrder_next;
END_SYNCHRONIZED1; // <----- 排他終了
                } else {
                    _TRACE2_("GgafFactory::work ＜工場長＞ さて、未製造注文は無し。棚に製造済のんがたまってるのを早く取に来い来い！。（待機）");
END_SYNCHRONIZED1; // <----- 排他終了
                    if (GgafGod::_pGod->_fps >= PROPERTY::FPS_TO_CLEAN_GARBAGE_BOX) {
                        _TRACE2_("GgafFactory::work ＜工場長＞ さほど忙しくないさそうなので、ゴミ箱のゴミを出しとこうか。");
                        GgafGarbageBox::_pGarbageBox->clean(5); //暇なので、ゴミ箱掃除
                        GgafGarbageBox::_cnt_cleaned = 0;
                    }
                }
            }
            Sleep(2);
        } // <-- while (GgafFactory::_is_working_flg)
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

