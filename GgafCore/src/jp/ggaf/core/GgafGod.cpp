#include "jp/ggaf/core/GgafGod.h"

#include "jp/ggaf/core/exception/GgafCriticalException.h"
#include "jp/ggaf/core/GgafCradle.h"
#include "jp/ggaf/core/GgafGarbageBox.h"
#include "jp/ggaf/core/GgafConfig.h"
#include "jp/ggaf/core/scene/GgafSpacetime.h"
#include "jp/ggaf/core/scene/GgafDisusedScene.h"
#include "jp/ggaf/core/actor/GgafDisusedActor.h"

#include <process.h>

using namespace GgafCore;

GgafCriticalException* GgafGod::_pException_factory = nullptr;

CRITICAL_SECTION GgafGod::CS1;
CRITICAL_SECTION GgafGod::CS2;
#ifdef MY_DEBUG
unsigned int GgafGod::_num_drawing = 0;
#endif
unsigned int GgafGod::_num_active_actor = 0;

GgafGod* GgafGod::_pGod = nullptr;
DWORD GgafGod::_aaTime_offset_of_next_view[3][60] = {
        {17,17,16,17,17,16,17,17,16,17,17,16,17,17,16,17,17,16,17,17,16,17,17,16,17,17,16,17,17,16,17,17,16,17,17,16,17,17,16,17,17,16,17,17,16,17,17,16,17,17,16,17,17,16,17,17,16,17,17,16},
        {25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25},
        {33,33,34,33,33,34,33,33,34,33,33,34,33,33,34,33,33,34,33,33,34,33,33,34,33,33,34,33,33,34,33,33,34,33,33,34,33,33,34,33,33,34,33,33,34,33,33,34,33,33,34,33,33,34,33,33,34,33,33,34}
};

GgafGod::GgafGod() : GgafObject(),
  _pSpacetime(nullptr),
  _fps(0) {
    timeBeginPeriod(1);
    _frame_of_God = 0;
    _handle_god_love01 = (HANDLE)_beginthreadex(nullptr, 0, GgafCore::GgafGod::love, nullptr, CREATE_SUSPENDED, &_th_id01);

    if (_handle_god_love01 == 0) {
        throwGgafCriticalException("Error! スレッド作成失敗！");
    }
    ::InitializeCriticalSection(&(GgafGod::CS1));
    ::InitializeCriticalSection(&(GgafGod::CS2));
    ::ResumeThread(_handle_god_love01);
    ::SetThreadPriority(_handle_god_love01, THREAD_PRIORITY_IDLE);
    GgafGod::_pGod = this;
    _time_at_beginning_frame = timeGetTime();
    _time_of_next_view = _time_at_beginning_frame;
    _time_calc_fps_next = _time_at_beginning_frame + 1;
    _visualize_frames = 0;
    _prev_visualize_frames = 0;
    _is_behaved_flg = false;
    _is_materialized_flg = false;
    GgafGarbageBox::_pGarbageBox = NEW GgafGarbageBox();
    _was_cleaned = false;
    _skip_count_of_frame = 0;
    _max_skip_frames = (int)CONFIG::MAX_SKIP_FRAME;
    _slowdown_mode = SLOWDOWN_MODE_DEFAULT;
    _sync_frame_time = false;
    _cnt_frame = 0;
}

void GgafGod::be() {

    // 【メモ】
    // １サイクル（１フレーム）の処理は以下の様に大きく５つに分け、順に実行するものとした。
    //
    // ①Mo = presentSpacetimeMoment();     ･･･ メイン処理・必須処理
    // ②Ju = executeSpacetimeJudge();      ･･･ 判定処理・必須処理
    // ③Ma = makeSpacetimeMaterialize();   ･･･ 描画処理(重い)・スキップ可
    // ④Vi = presentSpacetimeVisualize();  ･･･ 描画フリップ処理・スキップ可(但し③と④はセット処理)
    // ⑤Fi = finalizeSpacetime();          ･･･ 最終処理・必須処理
    //
    // ここで行ないたいことは『できる限り、④Vi を 1/60 秒毎に安定して実行すること』とした。
    // そこで、次の様な設計を行った。
    // ・先ず ④Vi を実行したいタイミングを予め決定する。これは、如何に処理が重くなろうとも変わらない。
    //    _time_of_next_view = _time_of_next_view + (1/60秒)
    //   とする。
    // ・②Ju を実行した時点で、③Ma、④Vi を実行するかどうかを残りの_time_of_next_view までの時間で判断する。
    //   時間に余裕が有る場合、②Ju 実行後即座に ③Ma 実行、その後 _time_of_next_view まで待ち ④Vi 実行する。
    //   もし ②Ju 実行後、次フレームにめり込んでいた場合 ③Ma、④Vi はスキップ。
    // ・上記を基本ルールとしつつ、_max_skip_frames フレームに１回は必ず ③Ma、④Vi を実行する。
    //   これはどんなに処理が重たくなろうとも、プログラムが動いていることを視覚化するため。
    //
    //
    //【安定時の理想図】
    //        _time_of_next_view                                              _time_of_next_view
    //                 |              3frame begin                                      |              4frame begin
    //                 |                   |                                            |                   |
    //                 v                   v                                            v                   v
    // ==================================================================================================================================================> 時間
    //  <--- wait ---> |(2f-④Vi)| 2f-⑤Fi | 3f-①Mo | 3f-②Ju |(3f-③Ma)|<--- wait --->|(3f-④Vi)| 3f-⑤Fi | 4f-①Mo | 4f-②Ju |(4f-③Ma)|<--- wait -
    //                 |                   |                                            |                   |
    // -- 2frame ------------------------->|<-------------------------- 3frame ---------------------------->|<----------------  4frame ---------
    //                 |                                                                |
    //                 |<----------------------- 1/60 sec ----------------------------->|
    //                 |                                                 |
    //                 |<--- 速く処理終われば、順次前詰めにできる ------>|
    //                       その分waitが増え安定する。
    //
    // ＜留意＞
    // ・あくまで ④Vi の 1/60 秒毎処理を優先で目指す仕組みであって、
    //   内部フレームカウンタが 1/60 秒毎にカウントアップされるという仕組みでは無い（考慮していない）。
    //   _time_of_next_view ～ 次の _time_of_next_view は常に固定時間(1/60 sec)であるが、
    //   例えば上図での 3frame begin  ～ 4frame begin 間の時間は前処理により変動する。
    //

    if (_pSpacetime == nullptr) {
        //この世がまだ無い場合は、先ずこの世を作成。
        _pSpacetime = createSpacetime();
#ifdef MY_DEBUG
        if (_pSpacetime == nullptr) {
            throwGgafCriticalException("Error! この世を実装して下さい！");
        }
#endif
        _pSpacetime->_pGod = this;
        _time_at_beginning_frame = timeGetTime();
        _time_of_next_view = _time_at_beginning_frame+100; //0.1秒後開始
        _time_calc_fps_next = _time_at_beginning_frame + 1;
    }
#ifdef MY_DEBUG
    //神（別スレッド）例外をチェック
    if (_pException_factory) {
        throw *_pException_factory;
    }
#endif

    if (_is_behaved_flg == false) {
        _is_behaved_flg = true;
        BEGIN_SYNCHRONIZED1; // ----->排他開始
        _frame_of_God++;
        presentSpacetimeMoment(); //①
        executeSpacetimeJudge();  //②
        _time_of_next_view += _aaTime_offset_of_next_view[_slowdown_mode][_cnt_frame];
        _cnt_frame++;
        if (_cnt_frame == 60) { _cnt_frame = 0; }
        if (timeGetTime() >= _time_of_next_view) { //描画タイミングフレームになった、或いは過ぎている場合
            //makeSpacetimeMaterialize はパス
            _is_materialized_flg = false;
        } else {
            //描画タイミングフレームになっていない。余裕がある。
             _is_materialized_flg = true;
            makeSpacetimeMaterialize(); //③
            //但し makeSpacetimeMaterialize() によりオーバーするかもしれない。
        }
        END_SYNCHRONIZED1;  // <-----排他終了
    }

    _time_at_beginning_frame = timeGetTime();

    if (_time_at_beginning_frame >= _time_of_next_view) {
        //描画タイミングフレームになった、或いは過ぎている場合
        BEGIN_SYNCHRONIZED1;  // ----->排他開始
        if (_is_materialized_flg) { // ③ makeSpacetimeMaterialize() 実行済みの場合
            //描画有り（スキップなし）
            presentSpacetimeVisualize();  _visualize_frames++; //④
            finalizeSpacetime(); //⑤
        } else {                   // ③ makeSpacetimeMaterialize() 実行していない場合
            //描画無し（スキップ時）
            if (_sync_frame_time) { //同期調整モード時は
                //無条件で描画なし。
                finalizeSpacetime(); //⑤
            } else {   //同期調整モードではない場合は通常スキップ
                _skip_count_of_frame++;
                //但し、スキップするといっても MAX_SKIP_FRAME フレームに１回は描画はする。
                if (_skip_count_of_frame >= _max_skip_frames) {
                    makeSpacetimeMaterialize(); //③
                    presentSpacetimeVisualize();  _visualize_frames++; //④
                    finalizeSpacetime();        //⑤
                    _skip_count_of_frame = 0;
                } else {
                    finalizeSpacetime(); //⑤
                }
            }
        }
        _is_behaved_flg = false;
        END_SYNCHRONIZED1;    // <-----排他終了

        //fps計算
        if (_time_at_beginning_frame >= _time_calc_fps_next) {
            const int d_visualize_frames = _visualize_frames - _prev_visualize_frames;
            if (d_visualize_frames == 0) {
                _fps = 0;
            } else {
                _fps = (float)(d_visualize_frames) *
                              ((1.0f * _aaTime_offset_of_next_view[_slowdown_mode][0]) / (1.0f*_aaTime_offset_of_next_view[SLOWDOWN_MODE_DEFAULT][0]));
            }
            _time_calc_fps_next += 1000;
            _prev_visualize_frames = _visualize_frames;
        }

     } else { //描画タイミングフレームになってない(余裕がある)
         _sync_frame_time = false;
         Sleep(1); //<--- wait ---> な ひととき
     }
    return;
}

void GgafGod::presentSpacetimeMoment() {
    GgafSpacetime* pSpacetime = _pSpacetime;
    pSpacetime->nextFrame();
    pSpacetime->behave();
    pSpacetime->settleBehavior();
}

void GgafGod::executeSpacetimeJudge() {
    _pSpacetime->preJudge();
    _pSpacetime->judge();
}

void GgafGod::makeSpacetimeMaterialize() {
    if (GgafGod::_num_active_actor > CONFIG::OBJNUM_TO_SLOWDOWN2) {
        _slowdown_mode = SLOWDOWN_MODE_30FPS;
    } else if (GgafGod::_num_active_actor > CONFIG::OBJNUM_TO_SLOWDOWN1) {
        _slowdown_mode = SLOWDOWN_MODE_40FPS;
    } else {
        _slowdown_mode = SLOWDOWN_MODE_DEFAULT;
    }
#ifdef MY_DEBUG
    GgafGod::_num_drawing = 0;
#endif
    GgafGod::_num_active_actor = 0;
    GgafSpacetime* pSpacetime = _pSpacetime;
    pSpacetime->preDraw();
    pSpacetime->draw();
    pSpacetime->afterDraw();
}

void GgafGod::presentSpacetimeVisualize() {
    _pSpacetime->dump();
}

void GgafGod::finalizeSpacetime() {
    _pSpacetime->doFinally();
}

void GgafGod::clean() {
    if (!_was_cleaned) {
        _TRACE_(FUNC_NAME<<" start");
        if (_pSpacetime) {
            _TRACE_("_pSpacetime != nullptr");
            //神を止める
            Sleep(10);
            GgafGod::_is_working_flg = false;
            _TRACE_("GgafGod::~GgafGod() 神が落ち着くまで待つ・・・");
            for (int i = 0; GgafGod::_was_finished_flg == false; i++) {
                Sleep(10); //神が落ち着くまで待つ
                if (i > 10*100*60) {
                    _TRACE_("GgafGod::~GgafGod() 10分待機しましたが、神から反応がありません。強制breakします。要調査");
                    break;
                }
            }
            _TRACE_("GgafGod::~GgafGod() 神が落ち着きました");
            //排他の解除、スレッドが終了するまで待つ
            _TRACE_("GgafGod::~GgafGod()  WaitForSingleObject(_handle_god_love01, 120*1000) .....");
            DWORD r = WaitForSingleObject(_handle_god_love01, 120*1000);  //DeleteCriticalSectionを行うために必要
            if (r == WAIT_TIMEOUT) {
                throwGgafCriticalException("神が落ち着いたにもかかわらず、２分たってもスレッドが残っています。");
            }
            _TRACE_("GgafGod::~GgafGod()  CloseHandle(_handle_god_love01) .....");
            CloseHandle(_handle_god_love01);
            _TRACE_("GgafGod::~GgafGod()  DeleteCriticalSection(&(GgafGod::CS1)); .....");
            DeleteCriticalSection(&(GgafGod::CS1));
            _handle_god_love01 = nullptr;
            _TRACE_("GgafGod::~GgafGod() 無事に神スレッドを終了。クリティカルセクション解除");

#ifdef MY_DEBUG
            //ツリー構造表示
            _TRACE_("Dumping _pSpacetime ...");
            _pSpacetime->dump();
#endif

            //神掃除
            _TRACE_(FUNC_NAME<<"");
            GgafGod::cleanCradle();
            //ゴミ箱
#ifdef MY_DEBUG
            _TRACE_("Dumping GgafGarbageBox::_pGarbageBox->_pDisusedScene ...");
            GgafGarbageBox::_pGarbageBox->_pDisusedScene->dump();
            _TRACE_("GgafGarbageBox::_pGarbageBox->_pDisusedActor ...");
            GgafGarbageBox::_pGarbageBox->_pDisusedActor->dump();
#endif
            _TRACE_("GGAF_DELETE(GgafGarbageBox::_pGarbageBox);");
            GGAF_DELETE(GgafGarbageBox::_pGarbageBox);
            //この世で生きている物も掃除
            Sleep(20);
            _TRACE_("GGAF_DELETE(_pSpacetime);");
            GGAF_DELETE(_pSpacetime);
            _TRACE_("GgafGod::~GgafGod()  DeleteCriticalSection(&(GgafGod::CS2)); .....");
            DeleteCriticalSection(&(GgafGod::CS2));
        }

        //神例外 _pException_factory が起こっているかもしれない。
        _TRACE_("GGAF_DELETE_NULLABLE(_pException_factory);");
        GGAF_DELETE_NULLABLE(_pException_factory);
        _TRACE_(FUNC_NAME<<" end");
    }
}


GgafGod::~GgafGod() {
    timeEndPeriod(1);
    clean();
    _was_cleaned = true;
}


//初期化
GgafCradle* GgafGod::ROOT_CRADLE = nullptr;
GgafCradle* GgafGod::CREATING_CRADLE = nullptr;
#ifdef _MSC_VER
volatile bool GgafGod::_is_working_flg   = true;
volatile bool GgafGod::_have_to_rest_flg = false;
volatile bool GgafGod::_is_resting_flg   = false;
volatile bool GgafGod::_was_finished_flg = false;
#else
volatile std::atomic<bool> GgafGod::_is_working_flg(true);
volatile std::atomic<bool> GgafGod::_have_to_rest_flg(false);
volatile std::atomic<bool> GgafGod::_is_resting_flg(false);
volatile std::atomic<bool> GgafGod::_was_finished_flg(false);
#endif

GgafMainActor* GgafGod::receiveActor2(uint64_t prm_cradle_no, GgafObject* prm_pReceiver) {
    return (GgafMainActor*)GgafGod::receive(prm_cradle_no, prm_pReceiver);
}

GgafMainScene* GgafGod::receiveScene2(uint64_t prm_cradle_no, GgafObject* prm_pReceiver) {
    return (GgafMainScene*)GgafGod::receive(prm_cradle_no, prm_pReceiver);
}


//このメソッドはメインスレッドが実行する。
void GgafGod::createCradle(uint64_t prm_cradle_no,
                        GgafObject* (*prm_pFunc)(void*, void*, void*),
                        GgafObject* prm_pWisher,
                        GgafObject* prm_pReceiver,
                        void* prm_pArg1,
                        void* prm_pArg2,
                        void* prm_pArg3) {

    _TRACE2_("＜客:("<<prm_pWisher<<")＞ 別スレッドの神さん、 [" << prm_cradle_no << "-"<<prm_pReceiver<<"]を作っといてや～。");
    //既に祝福していないかチェック
    GgafCradle* pCradle = GgafGod::ROOT_CRADLE;
    while (pCradle) {
        if (pCradle->_cradle_no == prm_cradle_no &&  pCradle->_pReceiver == prm_pReceiver) {
            _TRACE_("＜警告＞ GgafGod::createCradle( ちょっと、[" << prm_cradle_no << "-"<<prm_pReceiver<<"]は、２重祝福していますよ！、無視します。意図していますか？");
            return;
        }
        if (pCradle->_is_last_cradle_flg) {
            break;
        }
        pCradle = pCradle->_pCradle_next;
    }
    //既は未だであるようなので先頭にストック
    GgafCradle* pCradle_new;
    pCradle_new = NEW GgafCradle(prm_cradle_no);
    pCradle_new->_pObject_creation=nullptr;
    pCradle_new->_pFunc = prm_pFunc;
    pCradle_new->_pWisher = prm_pWisher;
    pCradle_new->_pReceiver = prm_pReceiver;
    pCradle_new->_time_of_wish = timeGetTime();
    pCradle_new->_pArg1 = prm_pArg1;
    pCradle_new->_pArg2 = prm_pArg2;
    pCradle_new->_pArg3 = prm_pArg3;
    pCradle_new->_progress = 0;
    if (GgafGod::ROOT_CRADLE == nullptr) {
        _TRACE2_("＜客:("<<prm_pWisher<<")＞ あぁ、神は空っきしですね。祝福したら、すぐできるよね？。");
        pCradle_new->_is_first_cradle_flg = true;
        pCradle_new->_is_last_cradle_flg = true;
        pCradle_new->_pCradle_next = pCradle_new;
        pCradle_new->_pCradle_prev = pCradle_new;
        GgafGod::ROOT_CRADLE = pCradle_new;
        GgafGod::CREATING_CRADLE = pCradle_new;
    } else {
        _TRACE2_("＜客:("<<prm_pWisher<<")＞ ゆりかごたまってますね、次々ゆりかご恐れ入ります。");
        pCradle_new->_is_first_cradle_flg = false;
        pCradle_new->_is_last_cradle_flg = true;
        GgafCradle* pCradle_last = GgafGod::ROOT_CRADLE->_pCradle_prev;
        pCradle_last->_is_last_cradle_flg = false;
        pCradle_last->_pCradle_next = pCradle_new;
        pCradle_new->_pCradle_prev = pCradle_last;
        pCradle_new->_pCradle_next = GgafGod::ROOT_CRADLE;
        GgafGod::ROOT_CRADLE->_pCradle_prev = pCradle_new;
    }
}

int GgafGod::chkProgress(uint64_t prm_cradle_no) {
    GgafCradle* pCradle;
    pCradle = GgafGod::ROOT_CRADLE;
    if (pCradle == nullptr) {
        return -1;
    }
    while (GgafGod::_is_working_flg) {
        if (pCradle->_cradle_no == prm_cradle_no) {
            return pCradle->_progress;
        } else {
            if (pCradle->_is_last_cradle_flg) {
                return -1;
            } else {
                pCradle = pCradle->_pCradle_next;
            }
        }
    }
    return -2;
}

void* GgafGod::receive(uint64_t prm_cradle_no, GgafObject* prm_pReceiver) {
    _TRACE2_("＜受取人:"<< (prm_pReceiver ? prm_pReceiver->toString() : "nullptr") <<"("<<prm_pReceiver<<")＞ まいど、["<<prm_cradle_no<<"-"<<prm_pReceiver<<"]を取りに来ましたよっと。");
    GgafCradle* pCradle= GgafGod::ROOT_CRADLE;
    GgafCradle* pCradle_my_next;
    GgafCradle* pCradle_my_prev;
    DWORD waittime = 0;
    void* objectCreation;

    if (pCradle == nullptr) {
        //ゆりかごが無いよエラー発生！、エラーメッセージを作る。
        _TRACE_(FUNC_NAME<<" ゆりかごが無いよエラー発生！");
        GgafGod::debuginfo();
        throwGgafCriticalException("Error! prm_cradle_no="<<prm_cradle_no<<" ゆりかごリストはnullptrで全て祝福済みしています。\n"
                                   "orederとobtainの対応が取れていません。\n"
                                   "受取人(obtain呼び元)="<<(prm_pReceiver ? prm_pReceiver->toString() : "nullptr")<<"("<<prm_pReceiver<<")");
    }

    //obtainメインループ
    while (GgafGod::_is_working_flg) {
        if (pCradle->_cradle_no == prm_cradle_no && (pCradle->_pReceiver == nullptr || pCradle->_pReceiver == prm_pReceiver) ) {
            while (GgafGod::_is_working_flg) {
                if (pCradle->_progress < 2) {
                    _TRACE2_("＜受取人:"<<(prm_pReceiver ? prm_pReceiver->toString() : "nullptr")<<"("<<prm_pReceiver<<")＞ ねぇ神長さん、["<<prm_cradle_no<<"-"<<prm_pReceiver<<"]の祝福まだ～？、5ミリ秒だけ待ったげよう。pCradle->_progress="<<(pCradle->_progress));
#ifdef _DEBUG
                    //デバッグ時はタイムアウト無し
#else

                    if (waittime > 1000*600) { //約10分
                        _TRACE_(FUNC_NAME<<" タイムアウトエラー発生！");
                        GgafGod::debuginfo();
                        //タイムアウトエラー発生！、エラーメッセージを作る。
                        throwGgafCriticalException("Error! ゆりかご["<<pCradle->getDebuginfo()<<"]の祝福待ち時間タイムアウト、取得できません。\n"
                                                   "何らかの理由でメインスレッドが停止している可能性が大きいです。"
                                                   "受取人(obtain呼び元)="<<(prm_pReceiver ? prm_pReceiver->toString() : "nullptr")<<"("<<prm_pReceiver<<")");
                    } else {
                    }
#endif
                    END_SYNCHRONIZED1; // <----- 排他終了
                    Sleep(5);
                    BEGIN_SYNCHRONIZED1; // ----->排他開始
                    waittime += 5;
                    if (pCradle->_progress == 1) {
                        //着手済み
                        _TRACE_N_("！");
                        continue; //待つ
                    } else if (pCradle->_progress == 0) {
                        //未着手？
                        pCradle = GgafGod::ROOT_CRADLE; //もう一度最初から探させる。
                        _TRACE_N_("…");
                        break;
                    } else if (pCradle->_progress == 2) {
                        //完成
                        pCradle = GgafGod::ROOT_CRADLE; //もう一度最初から探させる。
                        _TRACE_N_("(^_^)v");
                        break;
                    }
                } else {

#ifdef MY_DEBUG
                    if (waittime > 0) {
                        _TRACE_N_("お待たせ！");
                    }
#endif
                    _TRACE2_("＜受取人:"<<(prm_pReceiver ? prm_pReceiver->toString() : "nullptr")<<"("<<prm_pReceiver<<")＞ よ～し、["<<prm_cradle_no<<"-"<<prm_pReceiver<<"]は祝福完了ですね。おおきに！");
                    if (pCradle->_is_first_cradle_flg && pCradle->_is_last_cradle_flg) {
                        //最後の一つを obtain
                        objectCreation = pCradle->_pObject_creation;
                        pCradle->_pObject_creation = nullptr;
                        GGAF_DELETE(pCradle);
                        pCradle = nullptr;
                        GgafGod::ROOT_CRADLE = nullptr;
                        GgafGod::CREATING_CRADLE = nullptr;
                        _TRACE2_("＜受取人:"<<(prm_pReceiver ? prm_pReceiver->toString() : "nullptr")<<"("<<prm_pReceiver<<")＞ あ、ところでもう神は空ですね。暇になったん？、ねぇ？");
                        return (void*)objectCreation;
                    } else {
                        //中間をobtain、鎖を繋ぎ直す。
                        pCradle_my_next = pCradle->_pCradle_next;
                        pCradle_my_prev = pCradle->_pCradle_prev;
                        pCradle_my_prev->_pCradle_next = pCradle_my_next;
                        pCradle_my_next->_pCradle_prev = pCradle_my_prev;
                        if (pCradle->_is_last_cradle_flg) {
                            pCradle_my_prev->_is_last_cradle_flg = true;
                        }
                        if (pCradle->_is_first_cradle_flg) {
                            GgafGod::ROOT_CRADLE = pCradle_my_next;
                            pCradle_my_next->_is_first_cradle_flg = true;
                        }
                        if (GgafGod::CREATING_CRADLE == pCradle) {
                            GgafGod::CREATING_CRADLE = pCradle_my_next;
                        }
                        objectCreation = pCradle->_pObject_creation;
                        pCradle->_pObject_creation = nullptr;
                        GGAF_DELETE(pCradle);
                        pCradle = nullptr;

                        return (void*)objectCreation;
                    }
                }
            }
        } else {
            if (pCradle->_is_last_cradle_flg) {
                _TRACE_(FUNC_NAME<<" ゆりかごの形跡が無い、取得出来ないエラー発生！");
                GgafGod::debuginfo();
                //ゆりかごの形跡が無い、取得出来ないエラー発生！、エラーメッセージを作る。
                throwGgafCriticalException("＜神＞全部探しましたけど、そんなゆりかご("<<(prm_pReceiver ? prm_pReceiver->toString() : "nullptr")<<"さんへの ゆりかご番号:"<<prm_cradle_no<<"-"<<prm_pReceiver<<")は、ありません。\n"
                                           "oreder() と GgafGod::receive() の対応が取れていません。oreder()漏れ、或いは同じ GgafGod::receive() を２回以上してませんか？。\n"
                                           "情報：受取人(obtain呼び元)="<<(prm_pReceiver ? prm_pReceiver->toString() : "nullptr")<<"("<<prm_pReceiver<<") でした。\n"
                                           "（※ちなみに、現在神の最終オーダーは、ゆりかご番号("<<pCradle->_cradle_no<<"-"<<pCradle->_pReceiver<<")で、望んだ人(createCradle(呼び元)=("<<pCradle->_pWisher<<") でした）");
            } else {
                pCradle = pCradle->_pCradle_next;
            }
        }
    }
    if (GgafGod::_pException_factory) {
        throw *(GgafGod::_pException_factory);
    }
    return nullptr;
}

void GgafGod::beginRest() {
    _TRACE_(FUNC_NAME<<" ＜神＞神、休憩しなさい");
    GgafGod::_have_to_rest_flg = true;
}

bool GgafGod::isResting() {
    if (GgafGod::_is_resting_flg) {
        _TRACE_(FUNC_NAME<<" 神休止状態");
    } else {
        _TRACE_(FUNC_NAME<<" 神稼働状態");
    }
    return GgafGod::_is_resting_flg;
}

void GgafGod::finishRest() {
    _TRACE_(FUNC_NAME<<" ＜神＞神、休憩はおしまい。さあ動け！");
    GgafGod::_have_to_rest_flg = false;
}

//神にため込んでいる全てのゆりかごを破棄
//神(GgafGod)がアプリ終了時等に実行する予定。
void GgafGod::cleanCradle() {
    _TRACE2_("＜神＞ ゆりかご掃除開始");
    GgafCradle* pCradle = GgafGod::ROOT_CRADLE;
    if (pCradle == nullptr) {
        _TRACE2_("＜神＞ しかし何も無い！！");
        return;
    }
    uint64_t cnt = 0;
    while (GgafGod::_is_working_flg || GgafGod::_was_finished_flg == false) {
        Sleep(10);
        _TRACE_(FUNC_NAME<<" ＜神＞ まだ愛してます・・・");
        cnt++;
        if (cnt > 100*60*5) {
            _TRACE_(FUNC_NAME<<" ＜神＞ まだ愛してます・・・もう待ってられません。強制だ");
            break;
        }
    }

    GgafGod::debuginfo();

    while (true) {
        if (pCradle->_is_last_cradle_flg) {
            _TRACE2_("＜神＞ ゆりかご削除["<<pCradle->getDebuginfo()<<"]、最後のストック");
            GGAF_DELETE(pCradle);
            pCradle = nullptr;
            GgafGod::ROOT_CRADLE = nullptr;
            GgafGod::CREATING_CRADLE = nullptr;
            break;
        } else {
            _TRACE2_("＜神＞ ゆりかご削除["<<pCradle->getDebuginfo()<<"]");
            GgafCradle* pCradle_my_next = pCradle->_pCradle_next;
            GGAF_DELETE(pCradle);
            pCradle = pCradle_my_next;
        }
    }
    _TRACE2_("＜神＞ ゆりかごを掃除完了");
    return;
}

void GgafGod::fate(GgafObject* prm_pReceiver) {
    GgafCradle* pCradle = GgafGod::ROOT_CRADLE;
    while (pCradle) {
        if (pCradle->_pReceiver == prm_pReceiver) {
            if (pCradle->_is_last_cradle_flg && pCradle->_is_first_cradle_flg) {
                //最後の一つ
                GGAF_DELETE(pCradle);
                GgafGod::ROOT_CRADLE = nullptr;
                GgafGod::CREATING_CRADLE = nullptr;
                break; //終了
            } else {
                //間の場合、ポインタを繋ぎ直す。
                GgafCradle* pCradle_t_next = pCradle->_pCradle_next;
                GgafCradle* pCradle_t_prev = pCradle->_pCradle_prev;
                pCradle_t_prev->_pCradle_next = pCradle_t_next;
                pCradle_t_next->_pCradle_prev = pCradle_t_prev;

                if (pCradle->_is_last_cradle_flg) {
                    pCradle_t_prev->_is_last_cradle_flg = true;
                }
                if (pCradle->_is_first_cradle_flg) {
                    GgafGod::ROOT_CRADLE = pCradle_t_next;
                    pCradle_t_next->_is_first_cradle_flg = true;
                }
                if (GgafGod::CREATING_CRADLE == pCradle) {
                    GgafGod::CREATING_CRADLE = pCradle_t_next;
                }
                _TRACE_(FUNC_NAME<<" 受取人("<<prm_pReceiver<<")死亡の為、ゆりかごを削除します。" << pCradle->getDebuginfo() << "");
                GGAF_DELETE(pCradle);
                pCradle = pCradle_t_next;
                continue;
            }
        } else {
            if (pCradle->_is_last_cradle_flg) {
                break; //終了
            } else {
                pCradle = pCradle->_pCradle_next;
                continue;
            }
        }
    }
}

void GgafGod::debuginfo() {
    _TRACE_(FUNC_NAME<<" ＜デバッグ情報＞ 現在の神の状態");
    try {
        GgafCradle* p = GgafGod::ROOT_CRADLE;
        if (p) {
            while(p) {
                _TRACE_("・" << p->getDebuginfo() );
                p = p->_pCradle_next;
                if (p == GgafGod::ROOT_CRADLE) {
                    break;
                }
            }
        } else {
            _TRACE_("・オーダーありません！");
        }
    } catch (...) {
        _TRACE_(FUNC_NAME<<" なんということでしょう。現在の神の状態の表示が不可能です。");
    }
    _TRACE_(FUNC_NAME<<" 以上");
}

unsigned __stdcall GgafGod::love(void* prm_arg) {
    //_CrtSetBreakAlloc(65854);
    try {
        GgafObject* (*func)(void*, void*, void*) = nullptr;
        GgafObject* pObject = nullptr;
        Sleep(1000); //god のインスタンスが完成するまでほんのちょっと待つ必要があるかもしれない

        //製品を作りまくる神ループ！
        while (GgafGod::_is_working_flg) {
            if (GgafGod::_have_to_rest_flg) {
                GgafGod::_is_resting_flg = true;
                Sleep(100);
                continue;
            } else {
                GgafGod::_is_resting_flg = false;
            }

BEGIN_SYNCHRONIZED1; // ----->排他開始
            GgafCradle* pCradle_creating = GgafGod::CREATING_CRADLE;
            if (pCradle_creating) {
                if (pCradle_creating->_progress == 0) { //未着手ならまず作る
                    _TRACE2_("＜神＞ よし、ゆりかご["<<pCradle_creating->_cradle_no<<"-"<<pCradle_creating->_pReceiver<<"]は未着手(_progress == "<<pCradle_creating->_progress<<")だな。ゆえに今から作ります！");
                    pCradle_creating->_progress = 1; //ステータスを祝福中へ
                    pCradle_creating->_time_of_create_begin = timeGetTime();
                    func = pCradle_creating->_pFunc;
                    void* arg1 = pCradle_creating->_pArg1;
                    void* arg2 = pCradle_creating->_pArg2;
                    void* arg3 = pCradle_creating->_pArg3;
                    _TRACE2_("＜神＞ 祝福開始！["<<pCradle_creating->_cradle_no<<"-"<<pCradle_creating->_pReceiver<<"]");
                    Sleep(2);
                    END_SYNCHRONIZED1; // <----- 排他終了

                    pObject = (*func)(arg1, arg2, arg3); //製品の祝福！

                    BEGIN_SYNCHRONIZED1; // ----->排他開始
                    Sleep(2);
                    _TRACE2_("＜神＞ 祝福完了！品は["<<pCradle_creating->_cradle_no<<"-"<<pCradle_creating->_pReceiver<<"] (^_^)v");
                    if (GgafGod::CREATING_CRADLE == nullptr) {
                        //GgafGod::CREATING_CRADLE が祝福後 nullptr になってしまっている場合キャンセル。
                        _TRACE2_("＜神＞ ガーン！。せっかく作ったのにキャンセルっすか・・・。破棄します。pObjectをdelete!");
                        GGAF_DELETE(pObject);
END_SYNCHRONIZED1; // <----- 排他終了
                        continue;
                    } else if (GgafGod::CREATING_CRADLE == pCradle_creating) {
                        //正常なケース
                        pCradle_creating->_pObject_creation = pObject; //製品登録
                        pCradle_creating->_progress = 2; //ステータスを祝福済みへ
                        pCradle_creating->_time_of_create_finish = timeGetTime();
                        _TRACE2_("＜神＞ 祝福したゆりかごの品["<<pCradle_creating->_cradle_no<<"-"<<pCradle_creating->_pReceiver<<"]を、棚に置いときます。");
                    }  else if (GgafGod::CREATING_CRADLE != pCradle_creating) {
                        _TRACE2_("＜神＞ 警告、ゆりかごの品["<<pCradle_creating->_cradle_no<<"-"<<pCradle_creating->_pReceiver<<"]を作っている間に、"
                                 "CREATING_CRADLE が、別のゆりかご["<<GgafGod::CREATING_CRADLE->_cradle_no<<"-"<<GgafGod::CREATING_CRADLE->_pReceiver<<"]を指していました！壊れてるかもしれません！強制的に元に戻します！要調査！");
                        GgafGod::CREATING_CRADLE = pCradle_creating; //ポインタ強制戻し
                        pCradle_creating->_pObject_creation = pObject; //製品登録
                        pCradle_creating->_progress = 2; //ステータスを祝福済みへ
                        pCradle_creating->_time_of_create_finish = timeGetTime();
                        _TRACE2_("＜神＞ 祝福したゆりかごの品["<<pCradle_creating->_cradle_no<<"-"<<pCradle_creating->_pReceiver<<"]を、棚に置いときます・・・。");
                    }
                } else {
                    _TRACE2_("＜神＞ ゆりかご["<<pCradle_creating->_cradle_no<<"-"<<pCradle_creating->_pReceiver<<"]は、もう作って棚に置いてあるし・・・(_progress == "<<pCradle_creating->_progress<<")。");
                }
            }
            if (GgafGod::ROOT_CRADLE == nullptr) {
                //無条件待機
                _TRACE2_("＜神＞ 神には何～んもありません。さぁなんでもゆりかご来い来い！！・・・ないのん？。（待機）");
END_SYNCHRONIZED1; // <----- 排他終了
                if (GgafGod::_pGod->_fps >= CONFIG::FPS_TO_CLEAN_GARBAGE_BOX) {
                    _TRACE2_("＜神＞ さほど忙しくないので、ゴミ箱のゴミを出しとこう。");
                    GgafGarbageBox::_pGarbageBox->clean(5); //暇なので、ゴミ箱掃除
                    GgafGarbageBox::_cnt_cleaned = 0;
                }
            } else {
                if (GgafGod::ROOT_CRADLE != nullptr && GgafGod::ROOT_CRADLE->_pCradle_prev->_progress == 0) {
                    _TRACE2_("＜神＞ ・・・未祝福のゆりかごがある気配。最終目標のゆりかごは["<<GgafGod::ROOT_CRADLE->_pCradle_prev->_cradle_no<<"/受取人="<<GgafGod::ROOT_CRADLE->_pCradle_prev->_pReceiver<<"]なのか？。");
                    GgafGod::CREATING_CRADLE = GgafGod::CREATING_CRADLE->_pCradle_next;
END_SYNCHRONIZED1; // <----- 排他終了
                } else {
                    _TRACE2_("＜神＞ さて、未祝福ゆりかごは無し。棚に祝福済のんがたまってるのを早く取に来い来い！。（待機）");
END_SYNCHRONIZED1; // <----- 排他終了
                    if (GgafGod::_pGod->_fps >= CONFIG::FPS_TO_CLEAN_GARBAGE_BOX) {
                        _TRACE2_("＜神＞ さほど忙しくないさそうなので、ゴミ箱のゴミを出しとこうか。");
                        GgafGarbageBox::_pGarbageBox->clean(5); //暇なので、ゴミ箱掃除
                        GgafGarbageBox::_cnt_cleaned = 0;
                    }
                }
            }
            Sleep(2);
        } // <-- while (GgafGod::_is_working_flg)
        _TRACE2_("＜神＞ 神はこれにて店じまいです。さようなら、また会いましょう。");
        GgafGod::_was_finished_flg = true;
    } catch (GgafCriticalException& e) {
        GgafGod::debuginfo();
        _TRACE_("＜神例外＞ 私としたことがすみません；"<<e.getMsg());
        GgafGod::_is_working_flg = false;
        GgafGod::_was_finished_flg = true;
        GgafGod::_pException_factory = NEW GgafCriticalException(e.getMsg());
        return 1;
    }
    return 0;
}


