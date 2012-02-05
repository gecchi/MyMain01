#include "stdafx.h"
using namespace std;

using namespace GgafCore;

GgafCriticalException* GgafGod::_pException_Factory = NULL;
HINSTANCE GgafGod::_hInstance = NULL;
CRITICAL_SECTION GgafGod::CS1;
CRITICAL_SECTION GgafGod::CS2;

int GgafGod::_num_actor_drawing = 0;
GgafGod* GgafGod::_pGod = NULL;
DWORD GgafGod::_aaTime_OffsetOfNextFrame[3][60] = {
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
    _expected_time_of_next_frame = (frame)(_time_at_beginning_frame + 3000); //3秒松
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

//①Mo = presentUniversalMoment();
//②Ja = executeUniversalJudge();
//③Ma = makeUniversalMaterialize();
//④Vi = presentUniversalVisualize();
//⑤Fi = finalizeUniversal();

//理想型
//   _expected_time_of_next_frame                                       _expected_time_of_next_frame
//                 |                                                                |
//                 v 2Frame                                                         v 3Frame
// ----------------+----------------------------------------------------------------+-------------------------------------------------------->
//   <-- wait ---> | 2F-④Vi | 2F-⑤Fi | 3F-①Mo | 3F-②Ja | 3F-③Ma | <-- wait --->| 3F-④Vi | 3F-⑤Fi | 4F-①Mo | 4F-②Ja | 4F-③Ma |
//

        if (_is_behaved_flg == false) {
            _is_behaved_flg = true;
        ___BeginSynchronized1; // ----->排他開始
            _frame_of_God++;
            presentUniversalMoment();
            executeUniversalJudge();
        ___EndSynchronized1; // <----- 排他終了
            //描画タイミングフレーム加算
            if (_num_actor_drawing > CFG_PROPERTY(DRAWNUM_TO_SLOWDOWN2)) {
                _slowdown_mode = SLOWDOWN_MODE_30FPS;
            } else if (_num_actor_drawing > CFG_PROPERTY(DRAWNUM_TO_SLOWDOWN1)) {
                _slowdown_mode = SLOWDOWN_MODE_40FPS;
            } else {
                _slowdown_mode = SLOWDOWN_MODE_DEFAULT;
            }
            _expected_time_of_next_frame += _aaTime_OffsetOfNextFrame[_slowdown_mode][_cnt_frame];
            _cnt_frame = _cnt_frame == 59 ? 0 : _cnt_frame++;

            if (timeGetTime() >= _expected_time_of_next_frame) { //描画タイミングフレームになった、或いは過ぎている場合
                //makeUniversalMaterialize はパス
            } else {
                //余裕有り
                _is_materialized_flg = true;
                makeUniversalMaterialize();
            }
        }

        _time_at_beginning_frame = timeGetTime(); //

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

        //
        if (_time_at_beginning_frame >= _expected_time_of_next_frame) {
            //描画タイミングフレームになった、或いは過ぎている場合

            if (_is_materialized_flg) {
                //描画有り時（スキップなし）
             ___BeginSynchronized1; // ----->排他開始
                presentUniversalVisualize(); _visualize_frames++;
                finalizeUniversal();
             ___EndSynchronized1; // <----- 排他終了
            } else {
                //描画無し（スキップ時）
                if (_sync_frame_time) {
                    //無条件で描画なし。
                 ___BeginSynchronized1; // ----->排他開始
                    finalizeUniversal();
                 ___EndSynchronized1; // <----- 排他終了
                } else {
                    _skip_count_of_frame++;
                    //通常スキップ時、
                    //スキップするといってもMAX_SKIP_FRAMEフレームに１回は描画はする。
                    if (_skip_count_of_frame >= _max_skip_frames) {
                    ___BeginSynchronized1; // ----->排他開始
                        makeUniversalMaterialize();
                        presentUniversalVisualize(); _visualize_frames++;
                        finalizeUniversal();
                    ___EndSynchronized1; // <----- 排他終了
                        _skip_count_of_frame = 0;
                    } else {
                    ___BeginSynchronized1; // ----->排他開始
                       finalizeUniversal();
                    ___EndSynchronized1; // <----- 排他終了
                    }
                }
            }
             _is_behaved_flg = false;
             _is_materialized_flg = false;
         } else {//描画タイミングフレームになってない(余裕がある)
             _sync_frame_time = false;
             Sleep(2); //工場（別スレッド）に回す
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
