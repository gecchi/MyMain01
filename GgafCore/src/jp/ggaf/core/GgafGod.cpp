#include "stdafx.h"
using namespace std;

using namespace GgafCore;

GgafCriticalException* GgafGod::_pException_Factory = NULL;
HINSTANCE GgafGod::_hInstance = NULL;
CRITICAL_SECTION GgafGod::CS1;
CRITICAL_SECTION GgafGod::CS2;

int GgafGod::_num_actor_drawing = 0;
GgafGod* GgafGod::_pGod = NULL;
DWORD GgafGod::_aaTime_offset_of_next_view[3][60] = {
        {17,17,16,17,17,16,17,17,16,17,17,16,17,17,16,17,17,16,17,17,16,17,17,16,17,17,16,17,17,16,17,17,16,17,17,16,17,17,16,17,17,16,17,17,16,17,17,16,17,17,16,17,17,16,17,17,16,17,17,16},
        {25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25,25},
        {33,33,34,33,33,34,33,33,34,33,33,34,33,33,34,33,33,34,33,33,34,33,33,34,33,33,34,33,33,34,33,33,34,33,33,34,33,33,34,33,33,34,33,33,34,33,33,34,33,33,34,33,33,34,33,33,34,33,33,34}
};
volatile bool GgafGod::_can_be = false;

GgafGod::GgafGod(HINSTANCE prm_hInstance) : GgafObject(),
  _pUniverse(NULL),
  _fps(0) {
    TRACE("GgafGod::GgafGod");
    GgafGod::_hInstance = prm_hInstance;

    _frame_of_God = 0;
    _handleFactory01 = (HANDLE)::_beginthreadex(NULL, 0, GgafFactory::work, NULL, CREATE_SUSPENDED, &_thID01);

    if (_handleFactory01 == 0) {
        throwGgafCriticalException("GgafGod::GgafGod() Error! スレッド作成失敗！");
    }
    ::InitializeCriticalSection(&(GgafGod::CS1));
    ::InitializeCriticalSection(&(GgafGod::CS2));
    ::ResumeThread(_handleFactory01);
    ::SetThreadPriority(_handleFactory01, THREAD_PRIORITY_IDLE);
    GgafGod::_pGod = this;
    _time_at_beginning_frame = timeGetTime();
    _time_of_next_view = (frame)(_time_at_beginning_frame + 3000); //3秒松
    _time_calc_fps_next = _time_at_beginning_frame + 1;
    _visualize_frames = 0;
    _prev_visualize_frames = 0;
    _is_behaved_flg = false;
    _is_materialized_flg = false;
    GgafFactory::_pGarbageBox = NEW GgafGarbageBox();
    _is_being = false;
//    _can_be = true;
    _was_cleaned = false;
    _skip_count_of_frame = 0;
    _max_skip_frames = (int)CFG_PROPERTY(MAX_SKIP_FRAME);
    _slowdown_mode = SLOWDOWN_MODE_DEFAULT;
    _sync_frame_time = false;
    _cnt_frame = 0;
    _can_be = true;
}

void GgafGod::be() {

    //
    // ①Mo = presentUniversalMoment();     ･･･ メイン処理・必須処理
    // ②Ja = executeUniversalJudge();      ･･･ 判定処理・必須処理
    // ③Ma = makeUniversalMaterialize();   ･･･ 描画処理(重い)・スキップ可
    // ④Vi = presentUniversalVisualize();  ･･･ フリップ処理・③とセット
    // ⑤Fi = finalizeUniversal();          ･･･ 最終処理・必須処理
    // とする。
    // ④Vi を 1/60 秒毎に安定して実行することを理想とする。
    // ③Ma、④Vi を実行するかどうかは、②Ja を実行した時点で判断。
    // ③Ma 実行後、_time_of_next_view まで待ち ④Vi 実行。過ぎていれば、即座に ④Vi 実行。
    //
    //【安定時の理想】
    //        _time_of_next_view                                              _time_of_next_view
    //                 |              3frame begin                                      |              4frame begin
    //                 |                   |                                            |                   |
    //                 v                   v                                            v                   v
    // ----------------+----------------------------------------------------------------+----------------------------------------------------------->
    //  <--- wait ---> | 2f-④Vi | 2f-⑤Fi | 3f-①Mo | 3f-②Ja | 3f-③Ma |<--- wait --->| 3f-④Vi | 3f-⑤Fi | 4f-①Mo | 4f-②Ja | 4f-③Ma |<--- wait
    //                 |                   |                                            |                   |
    // -- 2frame ------------------------->|<-------------------------- 3frame ---------------------------->|<----------------  4frame ---------
    //                 |                                                                |
    //                 |<---------------- 1/60 sec (17 or 16 msec)  ------------------->|
    //
    //

    if (_can_be) {
        _is_being = true;
        if (_pUniverse == NULL) {
            //この世がまだ無い場合は、先ずこの世を作成。
            _pUniverse = createUniverse();
#ifdef MY_DEBUG
            if (_pUniverse == NULL) {
                throwGgafCriticalException("GgafGod::be() Error! この世を実装して下さい！");
            }
#endif
            _pUniverse->_pGod = this;
        }
#ifdef MY_DEBUG
        //工場（別スレッド）例外をチェック
        if (_pException_Factory) {
            throw *_pException_Factory;
        }
#endif

        if (_is_behaved_flg == false) {
            _is_behaved_flg = true;
         ___BeginSynchronized1; // ----->排他開始
            _frame_of_God++;
            presentUniversalMoment(); //①
            executeUniversalJudge();  //②
            _time_of_next_view += _aaTime_offset_of_next_view[_slowdown_mode][_cnt_frame];
            _cnt_frame = _cnt_frame == 59 ? 0 : _cnt_frame++;
            if (timeGetTime() >= _time_of_next_view) { //描画タイミングフレームになった、或いは過ぎている場合
                //makeUniversalMaterialize はパス
                _is_materialized_flg = false;
            } else {
                //描画タイミングフレームになっていない。余裕がある。
                 _is_materialized_flg = true;
                makeUniversalMaterialize(); //③
                //但し makeUniversalMaterialize() によりオーバーするかもしれない。
            }
         ___EndSynchronized1;  // <-----排他終了
        }

        _time_at_beginning_frame = timeGetTime();

        if (_time_at_beginning_frame >= _time_of_next_view) {
            //描画タイミングフレームになった、或いは過ぎている場合
         ___BeginSynchronized1;  // ----->排他開始
            if (_is_materialized_flg) { // ③ makeUniversalMaterialize() 実行済みの場合
                //描画有り（スキップなし）
                presentUniversalVisualize(); _visualize_frames++; //④
                finalizeUniversal(); //⑤
            } else {                   // ③ makeUniversalMaterialize() 実行していない場合
                //描画無し（スキップ時）
                if (_sync_frame_time) { //同期調整モード時は
                    //無条件で描画なし。
                    finalizeUniversal(); //⑤
                } else {   //同期調整モードではない場合は通常スキップ
                    _skip_count_of_frame++;
                    //但し、スキップするといっても MAX_SKIP_FRAME フレームに１回は描画はする。
                    if (_skip_count_of_frame >= _max_skip_frames) {
                        makeUniversalMaterialize(); //③
                        presentUniversalVisualize(); _visualize_frames++; //④
                        finalizeUniversal();        //⑤
                        _skip_count_of_frame = 0;
                    } else {
                        finalizeUniversal(); //⑤
                    }
                }
            }
            _is_behaved_flg = false;
         ___EndSynchronized1;    // <-----排他終了

            //fps計算
            if (_time_at_beginning_frame >= _time_calc_fps_next) {
                int d_visualize_frames = _visualize_frames - _prev_visualize_frames;
                if (d_visualize_frames == 0) {
                    _fps = 0;
                } else {
                    _fps = (float)(d_visualize_frames) * (1000.0f / 200);
                }
                _time_calc_fps_next += 200;
                _prev_visualize_frames = _visualize_frames;
            }

         } else { //描画タイミングフレームになってない(余裕がある)
             _sync_frame_time = false;
             Sleep(1); //<--- wait ---> な ひととき
         }
        _is_being = false;
    }
    return;
}

void GgafGod::presentUniversalMoment() {
    _pUniverse->nextFrame();
    _pUniverse->behave();
}

void GgafGod::executeUniversalJudge() {
    _pUniverse->settleBehavior();
    _pUniverse->judge();
}

void GgafGod::makeUniversalMaterialize() {
    if (_num_actor_drawing > CFG_PROPERTY(DRAWNUM_TO_SLOWDOWN2)) {
        _slowdown_mode = SLOWDOWN_MODE_30FPS;
    } else if (_num_actor_drawing > CFG_PROPERTY(DRAWNUM_TO_SLOWDOWN1)) {
        _slowdown_mode = SLOWDOWN_MODE_40FPS;
    } else {
        _slowdown_mode = SLOWDOWN_MODE_DEFAULT;
    }
    _num_actor_drawing = 0;
    _pUniverse->preDraw();
    _pUniverse->draw();
#ifdef MY_DEBUG
    //afterDraw() はデバッグ時の当たり判定領域表示に使用されている。
    _pUniverse->afterDraw();
#endif
}

void GgafGod::presentUniversalVisualize() {
    _pUniverse->dump();
}

void GgafGod::finalizeUniversal() {
    _pUniverse->doFinally();
}

void GgafGod::clean() {
    if (!_was_cleaned) {
        _TRACE_("GgafGod::clean() start");
        if (_pUniverse) {
            _TRACE_("_pUniverse != NULL");
            //工場を止める
            Sleep(10);
            GgafFactory::_is_working_flg = false;
            _TRACE_("GgafGod::~GgafGod() 工場が落ち着くまで待つ・・・");
            for (int i = 0; GgafFactory::_was_finished_flg == false; i++) {
                Sleep(60); //工場が落ち着くまで待つ
                if (i > 3000) {
                    _TRACE_("GgafGod::~GgafGod() ３分待機しましたが、工場から反応がありません。強制breakします。要調査");
                    break;
                }
            }
            _TRACE_("GgafGod::~GgafGod() 工場が落ち着きました");
            //排他の解除、スレッドが終了するまで待つ
            _TRACE_("GgafGod::~GgafGod()  WaitForSingleObject(_handleFactory01, 120*1000) .....");
            DWORD r = WaitForSingleObject(_handleFactory01, 120*1000);  //DeleteCriticalSectionを行うために必要
            if (r == WAIT_TIMEOUT) {
                throwGgafCriticalException("GgafGod::~GgafGod() 工場が落ち着いたにもかかわらず、２分たってもスレッドが残っています。");
            }
            _TRACE_("GgafGod::~GgafGod()  CloseHandle(_handleFactory01) .....");
            CloseHandle(_handleFactory01);
            _TRACE_("GgafGod::~GgafGod()  DeleteCriticalSection(&(GgafGod::CS1)); .....");
            DeleteCriticalSection(&(GgafGod::CS1));
            _handleFactory01 = NULL;
            _TRACE_("GgafGod::~GgafGod() 無事に工場スレッドを終了。クリティカルセクション解除");

    #ifdef MY_DEBUG
            //ツリー構造表示
            _TRACE_("Dumping _pUniverse ...");
            _pUniverse->dump();
    #endif

            //工場掃除
            _TRACE_("GgafFactory::clean()");
            GgafFactory::clean();
            //ゴミ箱
    #ifdef MY_DEBUG
            _TRACE_("Dumping GgafFactory::_pGarbageBox->_pDisusedScene ...");
            GgafFactory::_pGarbageBox->_pDisusedScene->dump();
            _TRACE_("GgafFactory::_pGarbageBox->_pDisusedActor ...");
            GgafFactory::_pGarbageBox->_pDisusedActor->dump();
    #endif
            _TRACE_("DELETE_IMPOSSIBLE_NULL(GgafFactory::_pGarbageBox);");
            DELETE_IMPOSSIBLE_NULL(GgafFactory::_pGarbageBox);
            //この世で生きている物も掃除
            Sleep(20);
            _TRACE_("DELETE_IMPOSSIBLE_NULL(_pUniverse);");
            DELETE_IMPOSSIBLE_NULL(_pUniverse);
            _TRACE_("GgafGod::~GgafGod()  DeleteCriticalSection(&(GgafGod::CS2)); .....");
            DeleteCriticalSection(&(GgafGod::CS2));
        }

        //工場例外 _pException_Factory が起こっているかもしれない。
        _TRACE_("DELETE_POSSIBLE_NULL(_pException_Factory);");
        DELETE_POSSIBLE_NULL(_pException_Factory);
        _TRACE_("GgafGod::clean() end");
    }
}


GgafGod::~GgafGod() {
    clean();
    _was_cleaned = true;
}
