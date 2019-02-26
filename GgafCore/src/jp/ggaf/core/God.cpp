#include "jp/ggaf/core/God.h"

#include "jp/ggaf/core/exception/CriticalException.h"
#include "jp/ggaf/core/Cradle.h"
#include "jp/ggaf/core/GarbageBox.h"
#include "jp/ggaf/core/Config.h"
#include "jp/ggaf/core/scene/Spacetime.h"
#include "jp/ggaf/core/scene/DisusedScene.h"
#include "jp/ggaf/core/actor/DisusedActor.h"

#include <process.h>

using namespace GgafCore;

CRITICAL_SECTION God::CS1;
CRITICAL_SECTION God::CS2;
#ifdef MY_DEBUG
unsigned int God::_num_drawing = 0;
#endif
unsigned int God::_num_active_actor = 0;

God* God::_pGod = nullptr;
DWORD God::_aaTime_offset_of_next_view[3][60] = {
        {17,17,16,17,17,16,17,17,16,17,17,16,17,17,16,17,17,16,17,17,16,17,17,16,17,17,16,17,17,16,17,17,16,17,17,16,17,17,16,17,17,16,17,17,16,17,17,16,17,17,16,17,17,16,17,17,16,17,17,16},
        {25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25},
        {33,33,34,33,33,34,33,33,34,33,33,34,33,33,34,33,33,34,33,33,34,33,33,34,33,33,34,33,33,34,33,33,34,33,33,34,33,33,34,33,33,34,33,33,34,33,33,34,33,33,34,33,33,34,33,33,34,33,33,34}
};
double God::_aTime_offset_of_next_view[3] = { 1.0/60.0, 1.5/60.0, 2.0/60.0};

God::God() : Object(),
  _pSpacetime(nullptr),
  _fps(0.0) {
    God::_pGod = this;
    timeBeginPeriod(1);
    _frame_of_God = 0;
    _handle_god_love01 = (HANDLE)_beginthreadex(nullptr, 0, God::love, nullptr, CREATE_SUSPENDED, &_th_id01);

    if (_handle_god_love01 == 0) {
        throwCriticalException("Error! スレッド作成失敗！");
    }
    ::InitializeCriticalSection(&(God::CS1));
    ::InitializeCriticalSection(&(God::CS2));
    ::ResumeThread(_handle_god_love01);
    ::SetThreadPriority(_handle_god_love01, THREAD_PRIORITY_IDLE);
    _time_at_beginning_frame = timeGetTime();
    _time_of_next_view = _time_at_beginning_frame;
    _time_calc_fps_next = _time_at_beginning_frame + 1;
    _visualize_frames = 0;
    _prev_visualize_frames = 0;
    _is_behaved_flg = false;
    _is_materialized_flg = false;
    GarbageBox::_pGarbageBox = NEW GarbageBox();
    _was_cleaned = false;
    _skip_count_of_frame = 0;
    _max_skip_frames = (int)CONFIG::MAX_SKIP_FRAME;
    _slowdown_mode = SLOWDOWN_MODE_DEFAULT;
    _sync_frame_time = false;
    _cnt_frame = 0;

    _pException_god = nullptr;
    _pCradleRoot = nullptr;
    _pCradleBlessing = nullptr;
    _is_loving_flg   = true;
    _have_to_rest_flg = false;
    _is_resting_flg   = false;
    _was_finished_flg = false;
}

void God::be() {

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
            throwCriticalException("Error! この世を実装して下さい！");
        }
#endif
        _pSpacetime->_pGod = this;
        _time_at_beginning_frame = timeGetTime();
        _time_of_next_view = _time_at_beginning_frame+100; //0.1秒後開始
        _time_calc_fps_next = _time_at_beginning_frame + 1;
    }
#ifdef MY_DEBUG
    //神（別スレッド）例外をチェック
    if (_pException_god) {
        throw *_pException_god;
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
                static const double inv_offset_default = 1.0f / _aTime_offset_of_next_view[SLOWDOWN_MODE_DEFAULT];
                _fps = inv_offset_default * d_visualize_frames * _aTime_offset_of_next_view[_slowdown_mode];
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

void God::presentSpacetimeMoment() {
    Spacetime* pSpacetime = _pSpacetime;
    pSpacetime->nextFrame();
    pSpacetime->behave();
    pSpacetime->settleBehavior();
}

void God::executeSpacetimeJudge() {
    _pSpacetime->preJudge();
    _pSpacetime->judge();
}

void God::makeSpacetimeMaterialize() {
    if (God::_num_active_actor > CONFIG::OBJNUM_TO_SLOWDOWN2) {
        _slowdown_mode = SLOWDOWN_MODE_30FPS;
    } else if (God::_num_active_actor > CONFIG::OBJNUM_TO_SLOWDOWN1) {
        _slowdown_mode = SLOWDOWN_MODE_40FPS;
    } else {
        _slowdown_mode = SLOWDOWN_MODE_DEFAULT;
    }
#ifdef MY_DEBUG
    God::_num_drawing = 0;
#endif
    God::_num_active_actor = 0;
    Spacetime* pSpacetime = _pSpacetime;
    pSpacetime->preDraw();
    pSpacetime->draw();
    pSpacetime->afterDraw();
}

void God::presentSpacetimeVisualize() {
    _pSpacetime->dump();
}

void God::finalizeSpacetime() {
    _pSpacetime->doFinally();
}

void God::clean() {
    if (!_was_cleaned) {
        _TRACE_(FUNC_NAME<<" start");
        if (_pSpacetime) {
            _TRACE_("_pSpacetime != nullptr");
            //神を止める
            Sleep(10);
            _is_loving_flg = false;
            _TRACE_("God::~God() 神が落ち着くまで待つ・・・");
            for (int i = 0; _was_finished_flg == false; i++) {
                Sleep(10); //神が落ち着くまで待つ
                if (i > 5*100*60) {
                    _TRACE_("God::~God() 5分待機しましたが、神から反応がありません。もう知りません！、強制 break します。要調査");
                    break;
                }
            }
            _TRACE_("God::~God() 神が落ち着きました");
            //排他の解除、スレッドが終了するまで待つ
            _TRACE_("God::~God()  WaitForSingleObject(_handle_god_love01, 120*1000) .....");
            DWORD r = WaitForSingleObject(_handle_god_love01, 120*1000);  //DeleteCriticalSectionを行うために必要
            if (r == WAIT_TIMEOUT) {
                throwCriticalException("終わったはずなのに、たぶん神がまだ終わっていません・・・・（涙）。デバッグ放置しましたか？");
            }
            _TRACE_("God::~God()  CloseHandle(_handle_god_love01) .....");
            CloseHandle(_handle_god_love01);
            _TRACE_("God::~God()  DeleteCriticalSection(&(God::CS1)); .....");
            DeleteCriticalSection(&(God::CS1));
            _handle_god_love01 = nullptr;
            _TRACE_("God::~God() 無事に神スレッドを終了。クリティカルセクション解除");

#ifdef MY_DEBUG
            //ツリー構造表示
            _TRACE_("Dumping _pSpacetime ...");
            _pSpacetime->dump();
#endif

            //洪水
            _TRACE_(FUNC_NAME<<"");
            flood();
            //ゴミ箱
#ifdef MY_DEBUG
            _TRACE_("Dumping GarbageBox::_pGarbageBox->_pDisusedScene ...");
            GarbageBox::_pGarbageBox->_pDisusedScene->dump();
            _TRACE_("GarbageBox::_pGarbageBox->_pDisusedActor ...");
            GarbageBox::_pGarbageBox->_pDisusedActor->dump();
#endif
            _TRACE_("GGAF_DELETE(GarbageBox::_pGarbageBox);");
            GGAF_DELETE(GarbageBox::_pGarbageBox);
            //この世で生きている物も掃除
            Sleep(20);
            _TRACE_("GGAF_DELETE(_pSpacetime);");
            GGAF_DELETE(_pSpacetime);
            _TRACE_("God::~God()  DeleteCriticalSection(&(God::CS2)); .....");
            DeleteCriticalSection(&(God::CS2));
        }

        //神例外 _pException_god が起こっているかもしれない。
        _TRACE_("GGAF_DELETE_NULLABLE(_pException_god);");
        GGAF_DELETE_NULLABLE(_pException_god);
        _TRACE_(FUNC_NAME<<" end");
    }
}

God::~God() {
    timeEndPeriod(1);
    clean();
    _was_cleaned = true;
}

MainActor* God::receive_Actor(uint64_t prm_cradle_no, Object* prm_pReceiver) {
    return (MainActor*)God::receive(prm_cradle_no, prm_pReceiver);
}

MainScene* God::receive_Scene(uint64_t prm_cradle_no, Object* prm_pReceiver) {
    return (MainScene*)receive(prm_cradle_no, prm_pReceiver);
}

void God::createCradle(uint64_t prm_cradle_no,
                           Object* (*prm_pFunc)(void*, void*, void*),
                           Object* prm_pWisher,
                           Object* prm_pReceiver,
                           void* prm_pArg1,
                           void* prm_pArg2,
                           void* prm_pArg3) {
    _TRACE2_("＜依頼人:("<<prm_pWisher<<")＞ 別スレッドの神さん、 [" << prm_cradle_no << "-"<<prm_pReceiver<<"]を作っといてや～。");
    //既に祝福していないかチェック
    Cradle* pCradle = _pCradleRoot;
    while (pCradle) {
        if (pCradle->_cradle_no == prm_cradle_no &&  pCradle->_pReceiver == prm_pReceiver) {
            _TRACE_("＜警告＞ God::createCradle( ちょっと、[" << prm_cradle_no << "-"<<prm_pReceiver<<"]は、２重祝福していますよ！、無視します。意図していますか？");
            return;
        }
        if (pCradle->_is_last_cradle_flg) {
            break;
        }
        pCradle = pCradle->_pCradle_next;
    }
    //既は未だであるようなので先頭にストック
    Cradle* pCradle_new;
    pCradle_new = NEW Cradle(prm_cradle_no);
    pCradle_new->_pObject_creation=nullptr;
    pCradle_new->_pFunc = prm_pFunc;
    pCradle_new->_pWisher = prm_pWisher;
    pCradle_new->_pReceiver = prm_pReceiver;
    pCradle_new->_time_of_wants = timeGetTime();
    pCradle_new->_pArg1 = prm_pArg1;
    pCradle_new->_pArg2 = prm_pArg2;
    pCradle_new->_pArg3 = prm_pArg3;
    pCradle_new->_progress = 0;
    if (_pCradleRoot == nullptr) {
        _TRACE2_("＜依頼人:("<<prm_pWisher<<")＞ あぁ、神様はお暇ですね。お願いしたら、すぐ生まれるよね？。");
        pCradle_new->_is_first_cradle_flg = true;
        pCradle_new->_is_last_cradle_flg = true;
        pCradle_new->_pCradle_next = pCradle_new;
        pCradle_new->_pCradle_prev = pCradle_new;
        _pCradleRoot = pCradle_new;
        _pCradleBlessing = pCradle_new;
    } else {
        _TRACE2_("＜依頼人:("<<prm_pWisher<<")＞ ゆりかごたまってますね、次々ゆりかご恐れ入ります。");
        pCradle_new->_is_first_cradle_flg = false;
        pCradle_new->_is_last_cradle_flg = true;
        Cradle* pCradle_last = _pCradleRoot->_pCradle_prev;
        pCradle_last->_is_last_cradle_flg = false;
        pCradle_last->_pCradle_next = pCradle_new;
        pCradle_new->_pCradle_prev = pCradle_last;
        pCradle_new->_pCradle_next = _pCradleRoot;
        _pCradleRoot->_pCradle_prev = pCradle_new;
    }
}

int God::chkCradle(uint64_t prm_cradle_no) {
    Cradle* pCradle;
    pCradle = _pCradleRoot;
    if (pCradle == nullptr) {
        return -1;
    }
    while (_is_loving_flg) {
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

void* God::receive(uint64_t prm_cradle_no, Object* prm_pReceiver) {
    _TRACE2_("＜受取人:"<< (prm_pReceiver ? prm_pReceiver->toString() : "nullptr") <<"("<<prm_pReceiver<<")＞ まいど、["<<prm_cradle_no<<"-"<<prm_pReceiver<<"]を取りに来ましたよっと。");
    Cradle* pCradle= _pCradleRoot;
    Cradle* pCradle_my_next;
    Cradle* pCradle_my_prev;
    DWORD waittime = 0;
    void* objectCreation;

    if (pCradle == nullptr) {
        //ゆりかごすら無いよエラー発生！、エラーメッセージを作る。
        _TRACE_(FUNC_NAME<<" ゆりかすら無いよエラー発生！");
        God::debuginfo();
        throwCriticalException("Error! prm_cradle_no="<<prm_cradle_no<<" ゆりかごリストはnullptrで全て祝福済みしています。\n"
                                   "createCradleとreceiveの対応が取れていません。\n"
                                   "受取人(receive呼び元)="<<(prm_pReceiver ? prm_pReceiver->toString() : "nullptr")<<"("<<prm_pReceiver<<")");
    }

    //receiveメインループ
    while (_is_loving_flg) {
        if (pCradle->_cradle_no == prm_cradle_no && (pCradle->_pReceiver == nullptr || pCradle->_pReceiver == prm_pReceiver) ) {
            while (_is_loving_flg) {
                if (pCradle->_progress < 2) {
                    _TRACE2_("＜受取人:"<<(prm_pReceiver ? prm_pReceiver->toString() : "nullptr")<<"("<<prm_pReceiver<<")＞ ねぇ神様、["<<prm_cradle_no<<"-"<<prm_pReceiver<<"]の祝福まだ～？、5ミリ秒だけ待ったげよう。pCradle->_progress="<<(pCradle->_progress));
#ifdef _DEBUG
                    //デバッグ時はタイムアウト無し
#else

                    if (waittime > 1000*600) { //約10分
                        _TRACE_(FUNC_NAME<<" タイムアウトエラー発生！");
                        God::debuginfo();
                        //タイムアウトエラー発生！、エラーメッセージを作る。
                        throwCriticalException("Error! ゆりかご["<<pCradle->getDebuginfo()<<"]の祝福待ち時間タイムアウト、取得できません。\n"
                                                   "何らかの理由でメインスレッドが停止している可能性が大きいです。"
                                                   "受取人(receive呼び元)="<<(prm_pReceiver ? prm_pReceiver->toString() : "nullptr")<<"("<<prm_pReceiver<<")");
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
                        pCradle = _pCradleRoot; //もう一度最初から探させる。
                        _TRACE_N_("…");
                        break;
                    } else if (pCradle->_progress == 2) {
                        //完成
                        pCradle = _pCradleRoot;
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
                        //最後の一つを receive
                        objectCreation = pCradle->_pObject_creation;
                        pCradle->_pObject_creation = nullptr;
                        GGAF_DELETE(pCradle);
                        pCradle = nullptr;
                        _pCradleRoot = nullptr;
                        _pCradleBlessing = nullptr;
                        _TRACE2_("＜受取人:"<<(prm_pReceiver ? prm_pReceiver->toString() : "nullptr")<<"("<<prm_pReceiver<<")＞ あ、ところでもう神は空ですね。暇になったん？、ねぇ？");
                        return (void*)objectCreation;
                    } else {
                        //中間をreceive、鎖を繋ぎ直す。
                        pCradle_my_next = pCradle->_pCradle_next;
                        pCradle_my_prev = pCradle->_pCradle_prev;
                        pCradle_my_prev->_pCradle_next = pCradle_my_next;
                        pCradle_my_next->_pCradle_prev = pCradle_my_prev;
                        if (pCradle->_is_last_cradle_flg) {
                            pCradle_my_prev->_is_last_cradle_flg = true;
                        }
                        if (pCradle->_is_first_cradle_flg) {
                            _pCradleRoot = pCradle_my_next;
                            pCradle_my_next->_is_first_cradle_flg = true;
                        }
                        if (_pCradleBlessing == pCradle) {
                            _pCradleBlessing = pCradle_my_next;
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
                God::debuginfo();
                //ゆりかごの形跡が無い、取得出来ないエラー発生！、エラーメッセージを作る。
                throwCriticalException("＜神＞全部探しましたけど、そんなゆりかご("<<(prm_pReceiver ? prm_pReceiver->toString() : "nullptr")<<"さんへの ゆりかご番号:"<<prm_cradle_no<<"-"<<prm_pReceiver<<")は、ありません。\n"
                                           "createCradle() と God::receive() の対応が取れていません。createCradle()漏れ、或いは同じ God::receive() を２回以上してませんか？。\n"
                                           "情報：受取人(receive呼び元)="<<(prm_pReceiver ? prm_pReceiver->toString() : "nullptr")<<"("<<prm_pReceiver<<") でした。\n"
                                           "（※ちなみに、現在神の最終オーダーは、ゆりかご番号("<<pCradle->_cradle_no<<"-"<<pCradle->_pReceiver<<")で、望んだ人(createCradle(呼び元)=("<<pCradle->_pWisher<<") でした）");
            } else {
                pCradle = pCradle->_pCradle_next;
            }
        }
    }
#ifdef MY_DEBUG
    if (_pException_god) {
        throw *(_pException_god);
    }
#endif
    return nullptr;
}

void God::beginRest() {
    _TRACE_(FUNC_NAME<<" ＜神＞休憩だ");
    _have_to_rest_flg = true;
}

bool God::isResting() {
    if (_is_resting_flg) {
        _TRACE_(FUNC_NAME<<" 神休止状態");
    } else {
        _TRACE_(FUNC_NAME<<" 神稼働状態");
    }
    return _is_resting_flg;
}

void God::finishRest() {
    _TRACE_(FUNC_NAME<<" ＜神＞神、休憩はおしまい。さあ動け！");
    _have_to_rest_flg = false;
}


void God::flood() {
    //神にため込んでいる全てのゆりかごを破棄
    //神(God)がアプリ終了時等に実行する予定。
    _TRACE2_("＜神＞ 洪水開始");
    Cradle* pCradle = _pCradleRoot;
    if (pCradle == nullptr) {
        _TRACE2_("＜神＞ しかし何も無い！！");
        return;
    }
    uint64_t cnt = 0;
    while (_is_loving_flg || _was_finished_flg == false) {
        Sleep(10);
        _TRACE_(FUNC_NAME<<" ＜神＞ 実はまだ愛してます・・・");
        cnt++;
        if (cnt > 100*60*5) {
            _TRACE_(FUNC_NAME<<" ＜神＞ まだ愛してます・・・が、もういいか。強制だ");
            break;
        }
    }

    God::debuginfo();

    while (true) {
        if (pCradle->_is_last_cradle_flg) {
            _TRACE2_("＜神＞ ゆりかご削除["<<pCradle->getDebuginfo()<<"]、最後のストック");
            GGAF_DELETE(pCradle);
            pCradle = nullptr;
            _pCradleRoot = nullptr;
            _pCradleBlessing = nullptr;
            break;
        } else {
            _TRACE2_("＜神＞ ゆりかご削除["<<pCradle->getDebuginfo()<<"]");
            Cradle* pCradle_my_next = pCradle->_pCradle_next;
            GGAF_DELETE(pCradle);
            pCradle = pCradle_my_next;
        }
    }
    _TRACE2_("＜神＞ 洪水完了");
    return;
}

void God::pardon(Object* prm_pReceiver) {
    //新しい命を望んだ人が無くなった為、受取人のいないゆりがこを削除する（祝福済みの命も削除）。
    Cradle* pCradle = _pCradleRoot;
    while (pCradle) {
        if (pCradle->_pReceiver == prm_pReceiver) {
            if (pCradle->_is_last_cradle_flg && pCradle->_is_first_cradle_flg) {
                //最後の一つ
                GGAF_DELETE(pCradle);
                _pCradleRoot = nullptr;
                _pCradleBlessing = nullptr;
                break; //終了
            } else {
                //間の場合、ポインタを繋ぎ直す。
                Cradle* pCradle_t_next = pCradle->_pCradle_next;
                Cradle* pCradle_t_prev = pCradle->_pCradle_prev;
                pCradle_t_prev->_pCradle_next = pCradle_t_next;
                pCradle_t_next->_pCradle_prev = pCradle_t_prev;

                if (pCradle->_is_last_cradle_flg) {
                    pCradle_t_prev->_is_last_cradle_flg = true;
                }
                if (pCradle->_is_first_cradle_flg) {
                    _pCradleRoot = pCradle_t_next;
                    pCradle_t_next->_is_first_cradle_flg = true;
                }
                if (_pCradleBlessing == pCradle) {
                    _pCradleBlessing = pCradle_t_next;
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

void God::debuginfo() {
    _TRACE_(FUNC_NAME<<" ＜神＞ 現在のゆりかご情報");
    try {
        Cradle* p = _pCradleRoot;
        if (p) {
            while(p) {
                _TRACE_("・" << p->getDebuginfo() );
                p = p->_pCradle_next;
                if (p == _pCradleRoot) {
                    break;
                }
            }
        } else {
            _TRACE_("・ゆりかごはありません！");
        }
    } catch (...) {
        _TRACE_(FUNC_NAME<<" なんということでしょう。現在の神の状態の表示が不可能です。そんな馬鹿な；");
    }
    _TRACE_(FUNC_NAME<<" 以上");
}

unsigned __stdcall God::love(void* prm_arg) {
    return pGOD->loveEternal(prm_arg);
}
unsigned God::loveEternal(void* prm_arg) {
    try {
        Object* (*funcBlessing)(void*, void*, void*) = nullptr;
        Object* pObject = nullptr;
        Sleep(1000); //god のインスタンスが完成するまでほんのちょっと待つ必要があるかもしれない

        //祝福しまくるくる神の愛ループ！
        while (_is_loving_flg) {
            if (_have_to_rest_flg) {
                _is_resting_flg = true;
                Sleep(100);
                continue;
            } else {
                _is_resting_flg = false;
            }

BEGIN_SYNCHRONIZED1; // ----->排他開始
            Cradle* pCradleBlessing = _pCradleBlessing;
            if (pCradleBlessing) {
                if (pCradleBlessing->_progress == 0) { //未着手ならまず作る
                    _TRACE2_("＜神＞ よし、ゆりかご["<<pCradleBlessing->_cradle_no<<"-"<<pCradleBlessing->_pReceiver<<"]は未着手(_progress == "<<pCradleBlessing->_progress<<")だな。ゆえに今から作ります！");
                    pCradleBlessing->_progress = 1; //ステータスを祝福中へ
                    pCradleBlessing->_time_of_create_begin = timeGetTime();
                    funcBlessing = pCradleBlessing->_pFunc;
                    void* arg1 = pCradleBlessing->_pArg1;
                    void* arg2 = pCradleBlessing->_pArg2;
                    void* arg3 = pCradleBlessing->_pArg3;
                    _TRACE2_("＜神＞ 祝福開始！["<<pCradleBlessing->_cradle_no<<"-"<<pCradleBlessing->_pReceiver<<"]");
                    Sleep(2);
                    END_SYNCHRONIZED1; // <----- 排他終了

                    pObject = (*funcBlessing)(arg1, arg2, arg3); //祝福、命が誕生。

                    BEGIN_SYNCHRONIZED1; // ----->排他開始
                    Sleep(2);
                    _TRACE2_("＜神＞ 祝福完了！生まれたのは["<<pCradleBlessing->_cradle_no<<"-"<<pCradleBlessing->_pReceiver<<"] (^_^)v");
                    if (_pCradleBlessing == nullptr) {
                        //_pCradleBlessing が祝福後 nullptr になってしまっている場合キャンセル。
                        _TRACE2_("＜神＞ ガーン！。せっかく祝福したのにキャンセルっすか・・・。破棄します。pObjectをdelete!");
                        GGAF_DELETE(pObject);
END_SYNCHRONIZED1; // <----- 排他終了
                        continue;
                    } else if (_pCradleBlessing == pCradleBlessing) {
                        //正常なケース
                        pCradleBlessing->_pObject_creation = pObject; //ゆりかごに乗せる
                        pCradleBlessing->_progress = 2; //ステータスを祝福済みへ
                        pCradleBlessing->_time_of_create_finish = timeGetTime();
                        _TRACE2_("＜神＞ 祝福したゆりかごの命["<<pCradleBlessing->_cradle_no<<"-"<<pCradleBlessing->_pReceiver<<"]を、棚に置いときます。");
                    }  else if (_pCradleBlessing != pCradleBlessing) {
                        _TRACE2_("＜神＞ 警告、ゆりかごの命["<<pCradleBlessing->_cradle_no<<"-"<<pCradleBlessing->_pReceiver<<"]を作っている間に、"
                                 "_pCradleBlessing が、別のゆりかご["<<_pCradleBlessing->_cradle_no<<"-"<<_pCradleBlessing->_pReceiver<<"]を指していました！壊れてるかもしれません！強制的に元に戻します！要調査！");
                        _pCradleBlessing = pCradleBlessing; //ポインタ強制戻し
                        pCradleBlessing->_pObject_creation = pObject; //ゆりかごに乗せる
                        pCradleBlessing->_progress = 2; //ステータスを祝福済みへ
                        pCradleBlessing->_time_of_create_finish = timeGetTime();
                        _TRACE2_("＜神＞ 祝福したゆりかごの命["<<pCradleBlessing->_cradle_no<<"-"<<pCradleBlessing->_pReceiver<<"]を、棚に置いときます・・・。");
                    }
                } else {
                    _TRACE2_("＜神＞ ゆりかご["<<pCradleBlessing->_cradle_no<<"-"<<pCradleBlessing->_pReceiver<<"]の命は、もう祝福済みでストックしてるし・・・(_progress == "<<pCradleBlessing->_progress<<")。");
                }
            }
            if (_pCradleRoot == nullptr) {
                //無条件待機
                _TRACE2_("＜神＞ 何～んもありません。ゆりかご来い来い！！・・・ないのん？。（待機）");
END_SYNCHRONIZED1; // <----- 排他終了
                if (_fps >= CONFIG::FPS_TO_CLEAN_GARBAGE_BOX) {
                    _TRACE2_("＜神＞ さほど忙しくないので、ゴミ箱のゴミを出しとこう。");
                    GarbageBox::_pGarbageBox->clean(5); //暇なので、ゴミ箱掃除
                    GarbageBox::_cnt_cleaned = 0;
                }
            } else {
                if (_pCradleRoot != nullptr && _pCradleRoot->_pCradle_prev->_progress == 0) {
                    _TRACE2_("＜神＞ ・・・未祝福のゆりかごがある気配。最終目標のゆりかごは["<<_pCradleRoot->_pCradle_prev->_cradle_no<<"/受取人="<<_pCradleRoot->_pCradle_prev->_pReceiver<<"]なのか？。");
                    _pCradleBlessing = _pCradleBlessing->_pCradle_next;
END_SYNCHRONIZED1; // <----- 排他終了
                } else {
                    _TRACE2_("＜神＞ さて、未祝福ゆりかごは無し。棚に祝福済のんがたまってるのを早く取に来い来い！。（待機）");
END_SYNCHRONIZED1; // <----- 排他終了
                    if (_fps >= CONFIG::FPS_TO_CLEAN_GARBAGE_BOX) {
                        _TRACE2_("＜神＞ さほど忙しくないさそうなので、ゴミ箱のゴミを出しとこうか。");
                        GarbageBox::_pGarbageBox->clean(5); //暇なので、ゴミ箱掃除
                        GarbageBox::_cnt_cleaned = 0;
                    }
                }
            }
            Sleep(2);
        } // <-- while (_is_loving_flg)
        _TRACE2_("＜神＞ さようなら、また会いましょう。");
        _was_finished_flg = true;
    } catch (CriticalException& e) {
        debuginfo();
        _TRACE_("＜神例外＞ 私としたことがすみません；"<<e.getMsg());
        _is_loving_flg = false;
        _was_finished_flg = true;
        _pException_god = NEW CriticalException(e.getMsg());
        return 1;
    }
    return 0;
}


