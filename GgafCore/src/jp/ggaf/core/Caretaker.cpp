#include "jp/ggaf/core/Caretaker.h"

#include "jp/ggaf/core/exception/CriticalException.h"
#include "jp/ggaf/core/Cradle.h"
#include "jp/ggaf/core/GarbageBox.h"
#include "jp/ggaf/core/Config.h"
#include "jp/ggaf/core/scene/Spacetime.h"
#include "jp/ggaf/core/scene/DisusedScene.h"
#include "jp/ggaf/core/actor/DisusedActor.h"

#include <process.h>

using namespace GgafCore;

CRITICAL_SECTION Caretaker::CS1;
CRITICAL_SECTION Caretaker::CS2;
//CRITICAL_SECTION Caretaker::CS3;

#ifdef MY_DEBUG
unsigned int Caretaker::_num_draw = 0;
unsigned int Caretaker::_num_draw_actors = 0;
#endif
unsigned int Caretaker::_num_active_actors = 0;

Caretaker* Caretaker::_pCaretaker = nullptr;

Caretaker::Caretaker() : Object(),
  _pSpacetime(nullptr),
  _fps(0.0) {
    Caretaker::_pCaretaker = this;
    timeBeginPeriod(1);
    _frame_of_Caretaker = 0;
    _handle_god_love01 = (HANDLE)_beginthreadex(nullptr, 0, Caretaker::love, nullptr, CREATE_SUSPENDED, &_th_id01);

    if (_handle_god_love01 == 0) {
        throwCriticalException("Error! Caretaker::love() スレッド作成失敗！");
    }

//    _handle_god_send03 = (HANDLE)_beginthreadex(nullptr, 0, Caretaker::send, nullptr, CREATE_SUSPENDED, &_th_id03);
//    if (_handle_god_send03 == 0) {
//        throwCriticalException("Error!  Caretaker::send() スレッド作成失敗！");
//    }

    ::InitializeCriticalSection(&(Caretaker::CS1));
    ::InitializeCriticalSection(&(Caretaker::CS2));
//    ::InitializeCriticalSection(&(Caretaker::CS3));
    ::ResumeThread(_handle_god_love01);
    ::SetThreadPriority(_handle_god_love01, BELOW_NORMAL_PRIORITY_CLASS );
//    ::ResumeThread(_handle_god_send03);
//    ::SetThreadPriority(_handle_god_send03, NORMAL_PRIORITY_CLASS );


    DWORD time_now = timeGetTime();
    _time_of_next_view = time_now;
    _time_calc_fps_next = time_now + 1;
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
    _was_finished_loving_flg = false;
    _is_sending_flg   = false;
    _was_finished_sending_flg = false;
    //_base_fps = CONFIG::FPS;
    _aTime_offset_of_next_view[0] = 1.0 / CONFIG::FPS;
    _aTime_offset_of_next_view[1] = CONFIG::RATE_OF_SLOWDOWN1 / CONFIG::FPS;
    _aTime_offset_of_next_view[2] = CONFIG::RATE_OF_SLOWDOWN2 / CONFIG::FPS;

    _apaTime_offset_of_next_view[0] = getArrTimeOffset((DWORD)(1.0 * 1000), CONFIG::FPS); // 1フレームを、(1000 / CONFIG::FPS) ミリ秒とする
    _apaTime_offset_of_next_view[1] = getArrTimeOffset((DWORD)(CONFIG::RATE_OF_SLOWDOWN1 * 1000), CONFIG::FPS); // 1フレームを、(1500 / CONFIG::FPS) ミリ秒とする
    _apaTime_offset_of_next_view[2] = getArrTimeOffset((DWORD)(CONFIG::RATE_OF_SLOWDOWN2 * 1000), CONFIG::FPS); // 1フレームを、(2000 / CONFIG::FPS) ミリ秒とする

}


//void Caretaker::setSpacetimeFps(int prm_fps) {
//    GGAF_DELETEARR_NULLABLE(_apaTime_offset_of_next_view[0]);
//    GGAF_DELETEARR_NULLABLE(_apaTime_offset_of_next_view[1]);
//    GGAF_DELETEARR_NULLABLE(_apaTime_offset_of_next_view[2]);
//    _base_fps = prm_fps;
//    _apaTime_offset_of_next_view[0] = getArrTimeOffset(1000, _base_fps);
//    _apaTime_offset_of_next_view[1] = getArrTimeOffset(1500, _base_fps);
//    _apaTime_offset_of_next_view[2] = getArrTimeOffset(2000, _base_fps);
//    _aTime_offset_of_next_view[0] = 1.0 / _base_fps;
//    _aTime_offset_of_next_view[1] = 1.5 / _base_fps;
//    _aTime_offset_of_next_view[2] = 2.0 / _base_fps;
//}

DWORD* Caretaker::getArrTimeOffset(DWORD sec, DWORD fps) {
    DWORD base = sec / fps;
    DWORD r = sec % fps;
    double rr = 1.0*r / fps;
    DWORD* paTimeOffset = new DWORD[fps];
    double x = 1.0;

    for (int i = 0; i < (int)fps; i++) {
        x += rr;
        if (x > 1.0) {
            paTimeOffset[i] = base + 1;
            x -= 1.0;
        } else {
            paTimeOffset[i] = base;
        }
    }
    return paTimeOffset;

}


void Caretaker::present() {
    // 【メモ】
    // １サイクル（１フレーム）の処理は以下の様に大きく５つに分け、順に実行するものとした。
    //
    // ①Mo = presentMoment();      ･･･ メイン処理・必須処理
    // ②Be = presentBehave();      ･･･ 移動処理・必須処理
    // ③Ju = presentJudge();       ･･･ 判定処理・必須処理
    // ④Ma = presentMaterialize(); ･･･ 描画処理(重い)・スキップ可
    // ⑤Vi = presentVisualize();   ･･･ 描画フリップ処理・スキップ可(但し④と⑤はセット処理)
    // ⑥Cl = presentClosing();     ･･･ 最終処理・必須処理
    //
    // ここで行ないたいことは『できる限り、⑤Vi を 1/60 秒毎に安定して実行すること』とした。
    // そこで、次の様な設計を行った。
    // ・先ず ⑤Vi を実行したいタイミングを予め決定する。これは、如何に処理が重くなろうとも変わらない。
    //    _time_of_next_view = _time_of_next_view + (1/60秒)
    //   とする。
    // ・③Ju を実行した時点で、④Ma、⑤Vi を実行するかどうかを残りの_time_of_next_view までの時間で判断する。
    //   時間に余裕が有る場合、③Ju 実行後即座に ④Ma 実行、その後 _time_of_next_view まで待ち ④Vi 実行する。
    //   もし ③Ju 実行後、次フレームにめり込んでいた場合 ④Ma、⑤Vi はスキップ。
    // ・上記を基本ルールとしつつ、_max_skip_frames フレームに１回は必ず ④Ma、⑤Vi を実行する。
    //   これはどんなに処理が重たくなろうとも、プログラムが動いていることを視覚化するため。
    //
    //
    //【安定時の理想図】
    //        _time_of_next_view                                        _time_of_next_view
    //                 |        3frame begin(_frame_of_Caretaker++)               |        4frame begin(_frame_of_Caretaker++)
    //                 |             |                                            |             |
    //                 v             v                                            v             v
    // ====================================================================================================================================> 時間
    //  <--- wait ---> |(⑤Vi)| ⑥Cl | ①Mo | ②Be | ③Ju |(④Ma)|<---- wait ---->|(⑤Vi)| ⑥Cl | ①Mo | ②Be | ③Ju |(④Ma)|<--- wait -
    //                 |             |                                            |             |
    // -- 2frame ------------------->|<-------------------------- 3frame ---------------------->|<-------------  4frame -------------------
    //                 |                                                          |
    //                 |<----------------- 1/60 sec ----------------------------->|
    //                 |                                         |
    //                 |<----- 速く処理できれば前詰め処理    --->|
    //                         その分waitが増え安定する。
    //
    // ＜留意＞
    // ・あくまで ⑤Vi の 1/60 秒毎のタイミングで処理する事を優先で目指す仕組みであって、
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
        _pSpacetime->_pCaretaker = this;
        DWORD time_now = timeGetTime();
        _time_of_next_view = time_now + 100; //0.1秒後開始
        _time_calc_fps_next = time_now + 1;
    }
#ifdef MY_DEBUG
    //管理者（別スレッド）例外をチェック
    if (_pException_god) {
        throw *_pException_god;
    }
#endif
    //フレームと時間の同期を行う
    if (_sync_frame_time) {
        DWORD time_now = timeGetTime();
        _time_of_next_view = time_now + 100; //0.1秒後開始
        _time_calc_fps_next = time_now + 1;
        _TRACE_("Caretaker::present() フレームと時間の同期を実施。");
        _sync_frame_time = false;
    }

    if (_is_behaved_flg == false) {
        //BEGIN_SYNCHRONIZED1; // ----->排他開始
        _frame_of_Caretaker++;
        presentMoment(); //①
        presentBehave(); //②
        presentJudge();  //③
        _time_of_next_view += _apaTime_offset_of_next_view[_slowdown_mode][_cnt_frame];
        _cnt_frame++;
        if (_cnt_frame >= CONFIG::FPS) { _cnt_frame = 0; }
        //④を実行するか悩む
        if (timeGetTime() >= _time_of_next_view) {
            //描画タイミングフレームになった、或いは過ぎている場合
            //描画無し（スキップ時）④はパスする。
            _is_materialized_flg = false;
        } else {
            //描画タイミングフレームになっていない。余裕がある。
            //描画有り（スキップなし）
             _is_materialized_flg = true;
            presentMaterialize(); //④
            //但し ④ によりオーバーしたかもしれない。
        }
        _is_behaved_flg = true;
        //END_SYNCHRONIZED1;  // <-----排他終了
    }

    DWORD time_now = timeGetTime();
    if (time_now >= _time_of_next_view) {
        //描画タイミングフレームになった、或いは過ぎている場合
//TODO:要確認
//        BEGIN_SYNCHRONIZED1;  // ----->排他開始
        if (_is_materialized_flg) {
            //描画有り（スキップなし）（①②③④ 実行済みの場合）
            presentVisualize();  _visualize_frames++; //⑤
        } else {
            //描画無し（スキップ時）（①②③実行済み、④実行していないので⑤もスキップしようかな）
            _skip_count_of_frame++;

            if (_skip_count_of_frame >= _max_skip_frames) {
                //但し、スキップするといっても MAX_SKIP_FRAME フレームに１回は
                //無理やり描画して、アプリが動作していることをアピール。（無理やり④⑤を実行）
                presentMaterialize(); //④
                presentVisualize();  _visualize_frames++; //⑤
                _skip_count_of_frame = 0;
            } else {
                //④⑤をスキップとなる。
            }
        }
        presentClosing(); //⑥
        _is_behaved_flg = false;
//TODO:要確認
//        END_SYNCHRONIZED1;    // <-----排他終了

        //fps計算
        if (time_now >= _time_calc_fps_next) {
            const int d_visualize_frames = _visualize_frames - _prev_visualize_frames;
            if (d_visualize_frames == 0) {
                _fps = 0;
            } else {
                static const double inv_offset_default = 1.0f / _aTime_offset_of_next_view[SLOWDOWN_MODE_DEFAULT];
                _fps = inv_offset_default * d_visualize_frames * _aTime_offset_of_next_view[SLOWDOWN_MODE_DEFAULT];
            }
            _time_calc_fps_next += 1000;
            _prev_visualize_frames = _visualize_frames;
        }

     } else { //描画タイミングフレームになってない(余裕がある)
         Sleep(1); //<--- wait ---> な ひととき
     }
    return;
}

void Caretaker::presentMoment() {
    _pSpacetime->nextFrame();
}
void Caretaker::presentBehave() {
    _pSpacetime->behave();
    _pSpacetime->settleBehavior();
}
void Caretaker::presentJudge() {
    _pSpacetime->judge();
#ifdef MY_DEBUG
    _pSpacetime->_is_running_processHitCheck = true;
#endif
    _pSpacetime->processHitCheck(); //Spacetimeのみ
#ifdef MY_DEBUG
    _pSpacetime->_is_running_processHitCheck = false;
#endif
}

void Caretaker::presentMaterialize() {
    if (Caretaker::_num_active_actors > CONFIG::OBJNUM_TO_SLOWDOWN2) {
        _slowdown_mode = SLOWDOWN_MODE2;
    } else if (Caretaker::_num_active_actors > CONFIG::OBJNUM_TO_SLOWDOWN1) {
        _slowdown_mode = SLOWDOWN_MODE1;
    } else {
        _slowdown_mode = SLOWDOWN_MODE_DEFAULT;
    }
#ifdef MY_DEBUG
    Caretaker::_num_draw = 0;
    Caretaker::_num_draw_actors = 0;
#endif
    Caretaker::_num_active_actors = 0;
    Spacetime* pSpacetime = _pSpacetime;
    pSpacetime->preDraw();
    pSpacetime->draw();
    pSpacetime->afterDraw();
}

void Caretaker::presentVisualize() {
    _pSpacetime->dump();
}

void Caretaker::presentClosing() {
    _pSpacetime->doFinally();
}
void Caretaker::calmDown() {
    _TRACE_("Caretaker::calmDown() _was_finished_loving_flg="<<_was_finished_loving_flg);
    if (_was_finished_loving_flg == false) {
        _is_loving_flg = false;
        Sleep(10);
        _TRACE_("Caretaker::~Caretaker() 管理者が落ち着くまで待つ・・・");
        for (int i = 0; _was_finished_loving_flg == false; i++) {
            Sleep(10); //管理者が落ち着くまで待つ
            if (i > 5*100*60) {
                _TRACE_("Caretaker::~Caretaker() 5分待機しましたが、管理者から反応がありません。もう知りません！、強制 break します。要調査");
                break;
            }
        }
        _TRACE_("Caretaker::~Caretaker() 管理者が落ち着きました");
    }
}
void Caretaker::clean() {
    _TRACE_(FUNC_NAME<<" begin");
    if (!_was_cleaned) {
        if (_pSpacetime) {
            _TRACE_("_pSpacetime != nullptr");
            //管理者を止める
            calmDown();
            //排他の解除、スレッドが終了するまで待つ
            _TRACE_("Caretaker::~Caretaker()  WaitForSingleObject(_handle_god_love01, 120*1000) .....");
            DWORD r = WaitForSingleObject(_handle_god_love01, 120*1000);  //DeleteCriticalSectionを行うために必要
            if (r == WAIT_TIMEOUT) {
                throwCriticalException("終わったはずなのに、たぶん管理者の愛がまだ終わっていません・・・・（涙）。デバッグ放置しましたか？");
            }
            _TRACE_("Caretaker::~Caretaker()  CloseHandle(_handle_god_love01) .....");
            CloseHandle(_handle_god_love01);
            _TRACE_("Caretaker::~Caretaker()  DeleteCriticalSection(&(Caretaker::CS1)); .....");
            DeleteCriticalSection(&(Caretaker::CS1));
            _handle_god_love01 = nullptr;

//            _TRACE_("Caretaker::~Caretaker()  WaitForSingleObject(_handle_god_send03, 120*1000) .....");
//            r = WaitForSingleObject(_handle_god_send03, 120*1000);  //DeleteCriticalSectionを行うために必要
//            if (r == WAIT_TIMEOUT) {
//                throwCriticalException("終わったはずなのに、たぶん管理者の異界送りがまだ終わっていません・・・・（涙）。デバッグ放置しましたか？");
//            }
//            _TRACE_("Caretaker::~Caretaker()  CloseHandle(_handle_god_send03) .....");
//            CloseHandle(_handle_god_send03);
//            _TRACE_("Caretaker::~Caretaker()  DeleteCriticalSection(&(Caretaker::CS3)); .....");
//            DeleteCriticalSection(&(Caretaker::CS3));
//            _handle_god_send03 = nullptr;

            _TRACE_("Caretaker::~Caretaker() 無事に管理者スレッドを終了。クリティカルセクション解除");

#ifdef MY_DEBUG
            //ツリー構造表示
            _TRACE_("Dumping _pSpacetime ...");
            _pSpacetime->dump();
#endif

            //洪水
            desert();
            //ゴミ箱
#ifdef MY_DEBUG
            _TRACE_("Dumping GarbageBox::_pGarbageBox->_pDisusedScene ...");
            GarbageBox::_pGarbageBox->_pDisusedScene->dump();
            _TRACE_("Dumping GarbageBox::_pGarbageBox->_pDisusedActor ...");
            GarbageBox::_pGarbageBox->_pDisusedActor->dump();
#endif
            _TRACE_(FUNC_NAME<<" GGAF_DELETE(GarbageBox::_pGarbageBox) begin");
            GGAF_DELETE(GarbageBox::_pGarbageBox);
            _TRACE_(FUNC_NAME<<" GGAF_DELETE(GarbageBox::_pGarbageBox) end");
            //この世で生きている物も掃除
            Sleep(20);
            _TRACE_(FUNC_NAME<<" GGAF_DELETE(_pSpacetime); begin");
            GGAF_DELETE(_pSpacetime);
            _TRACE_(FUNC_NAME<<" GGAF_DELETE(_pSpacetime); end");

            _TRACE_("Caretaker::~Caretaker()  DeleteCriticalSection(&(Caretaker::CS2)); .....");
            DeleteCriticalSection(&(Caretaker::CS2));
        }

        GGAF_DELETEARR(_apaTime_offset_of_next_view[0]);
        GGAF_DELETEARR(_apaTime_offset_of_next_view[1]);
        GGAF_DELETEARR(_apaTime_offset_of_next_view[2]);
        //管理者例外 _pException_god が起こっているかもしれない。
        _TRACE_("GGAF_DELETE_NULLABLE(_pException_god);");
        GGAF_DELETE_NULLABLE(_pException_god);
    }
    _TRACE_(FUNC_NAME<<" end");
}

Caretaker::~Caretaker() {
    _sync_frame_time = false;
    calmDown();
    timeEndPeriod(1);
    clean();
    _was_cleaned = true;
}

MainActor* Caretaker::takeOutActor(uint64_t prm_cradle_no, Object* prm_pReceiver, bool prm_was_just_wondering) {
    return (MainActor*)takeOutObject(prm_cradle_no, prm_pReceiver, prm_was_just_wondering);
}

MainScene* Caretaker::takeOutScene(uint64_t prm_cradle_no, Object* prm_pReceiver, bool prm_was_just_wondering) {
    return (MainScene*)takeOutObject(prm_cradle_no, prm_pReceiver, prm_was_just_wondering);
}

void Caretaker::addCradle(uint64_t prm_cradle_no,
                          Object* (*prm_pFunc)(void*, void*, void*),
                          Object* prm_pWisher,
                          Object* prm_pReceiver,
                          void* prm_pArg1,
                          void* prm_pArg2,
                          void* prm_pArg3) {
    _TRACE2_("＜依頼人:("<<prm_pWisher<<")＞ 別スレッドの管理者さん、 [" << prm_cradle_no << "-"<<prm_pReceiver<<"]を作っといてや～。");
    //既に祝福していないかチェック
    Cradle* pCradle = _pCradleRoot;
    while (pCradle) {
        if (pCradle->_cradle_no == prm_cradle_no &&  pCradle->_pReceiver == prm_pReceiver) {
            _TRACE_("【警告】 Caretaker::addCradle() ゆりかご[" << prm_cradle_no << "-"<<prm_pReceiver<<"]は既に存在してますよ！。意図していますか？");
            return;
        }
        if (pCradle->_is_last_cradle_flg) {
            break;
        }
        pCradle = pCradle->_pCradle_next;
    }
    //ゆりかごは未だであるようなので先頭にストック
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
    pCradle_new->_progress_no = 0;
    if (_pCradleRoot == nullptr) {
        _TRACE2_("＜依頼人:("<<prm_pWisher<<")＞ あぁ、管理者様はお暇ですね。お願いしたら、すぐ生まれるよね？。");
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

int Caretaker::chkCradle(uint64_t prm_cradle_no) {
    Cradle* pCradle;
    pCradle = _pCradleRoot;
    if (pCradle == nullptr) {
        return -1;
    }
    while (_is_loving_flg) {
        if (pCradle->_cradle_no == prm_cradle_no) {
            return pCradle->_progress_no;
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


void* Caretaker::takeOutObject(uint64_t prm_cradle_no, Object* prm_pReceiver, bool prm_was_just_wondering) {
    _TRACE2_("＜受取人:"<< (prm_pReceiver ? prm_pReceiver->toString() : "nullptr") <<"("<<prm_pReceiver<<")＞ まいど、["<<prm_cradle_no<<"-"<<prm_pReceiver<<"]を取りに来ましたよっと。");
#ifdef _DEBUG
    if (_is_behaved_flg) {
        throwCriticalException("Error! prm_cradle_no="<<prm_cradle_no<<" presentMoment()、presentJudge() で受け取ってほしいです。\n"
                               " たぶん今は クリティカルセクション外ではないだろうか・・・それは困る。\n"
                                   "受取人(receive呼び元)="<<(prm_pReceiver ? prm_pReceiver->toString() : "nullptr")<<"("<<prm_pReceiver<<")");
    }
#endif
    Cradle* pCradle= _pCradleRoot;
    Cradle* pCradle_my_next;
    Cradle* pCradle_my_prev;
    DWORD waittime = 0;
    void* objectCreation;

    if (pCradle == nullptr) {
        //ゆりかごすら無いよエラー発生！、エラーメッセージを作る。
        _TRACE_(FUNC_NAME<<" ゆりかごすら無いよエラー発生！");
        Caretaker::debuginfo();
        throwCriticalException("Error! prm_cradle_no="<<prm_cradle_no<<" ゆりかごリストはnullptrで全て祝福済みしています。\n"
                                   "addCradleとreceiveの対応が取れていません。\n"
                                   "受取人(receive呼び元)="<<(prm_pReceiver ? prm_pReceiver->toString() : "nullptr")<<"("<<prm_pReceiver<<")");
    }

    //receiveメインループ
    BEGIN_SYNCHRONIZED1;
    while (_is_loving_flg) {
        if (pCradle->_cradle_no == prm_cradle_no && (pCradle->_pReceiver == nullptr || pCradle->_pReceiver == prm_pReceiver) ) {
            while (_is_loving_flg) {
                if (pCradle->_progress_no < 2) {
                    _TRACE2_("＜受取人:"<<(prm_pReceiver ? prm_pReceiver->toString() : "nullptr")<<"("<<prm_pReceiver<<")＞ ねぇ管理者様、["<<prm_cradle_no<<"-"<<prm_pReceiver<<"]の祝福まだ～？、5ミリ秒だけ待ったげよう。pCradle->_phase_no="<<(pCradle->_progress_no));
#ifdef _DEBUG
                    //デバッグ時はタイムアウト無し
#else
                    if (waittime > 1000*600) { //約10分
                        _TRACE_(FUNC_NAME<<" タイムアウトエラー発生！");
                        Caretaker::debuginfo();
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
                    if (pCradle->_progress_no == 1) {
                        //着手済み
                        _TRACE_N_("！");
                        continue; //待つ
                    } else if (pCradle->_progress_no == 0) {
                        //未着手？
                        pCradle = _pCradleRoot; //もう一度最初から探させる。
                        _TRACE_N_("…");
                        break;
                    } else if (pCradle->_progress_no == 2) {
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
                    if (prm_was_just_wondering) {
                        _TRACE2_("＜受取人:"<<(prm_pReceiver ? prm_pReceiver->toString() : "nullptr")<<"("<<prm_pReceiver<<")＞ だがしかし、まだ受け取りません！。ちょっと聞いてみただけ～");
                        objectCreation = pCradle->_pObject_creation;
                        END_SYNCHRONIZED1;
                        return (void*)objectCreation;
                    }
                    if (pCradle->_is_first_cradle_flg && pCradle->_is_last_cradle_flg) {
                        //最後の一つを receive
                        objectCreation = pCradle->_pObject_creation;
                        pCradle->_pObject_creation = nullptr;
                        GGAF_DELETE(pCradle);
                        pCradle = nullptr;
                        _pCradleRoot = nullptr;
                        _pCradleBlessing = nullptr;
                        _TRACE2_("＜受取人:"<<(prm_pReceiver ? prm_pReceiver->toString() : "nullptr")<<"("<<prm_pReceiver<<")＞ あ、ところでもう管理者は空ですね。暇になったん？、ねぇ？");
                        END_SYNCHRONIZED1;
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
                        END_SYNCHRONIZED1;
                        return (void*)objectCreation;
                    }
                }
            }
        } else {
            if (pCradle->_is_last_cradle_flg) {
                _TRACE_(FUNC_NAME<<" ゆりかごの形跡が無い、取得出来ないエラー発生！");
                Caretaker::debuginfo();
                END_SYNCHRONIZED1;
                //ゆりかごの形跡が無い、取得出来ないエラー発生！、エラーメッセージを作る。
                throwCriticalException("＜管理者＞全部探しましたけど、そんなゆりかご("<<(prm_pReceiver ? prm_pReceiver->toString() : "nullptr")<<"さんへの ゆりかご番号:"<<prm_cradle_no<<"-"<<prm_pReceiver<<")は、ありません。\n"
                                           "addCradle() と Caretaker::takeOutObject() の対応が取れていません。addCradle()漏れ、或いは同じ Caretaker::takeOutObject() を２回以上してませんか？。\n"
                                           "情報：受取人(receive呼び元)="<<(prm_pReceiver ? prm_pReceiver->toString() : "nullptr")<<"("<<prm_pReceiver<<") でした。\n"
                                           "（※ちなみに、現在管理者の最終オーダーは、ゆりかご番号("<<pCradle->_cradle_no<<"-"<<pCradle->_pReceiver<<")で、望んだ人(addCradle(呼び元)=("<<pCradle->_pWisher<<") でした）");
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
    END_SYNCHRONIZED1;
    return nullptr;
}

void Caretaker::beginRest() {
    _TRACE_(FUNC_NAME<<" ＜管理者＞休憩だ");
    _have_to_rest_flg = true;
}

bool Caretaker::isResting() {
    if (_is_resting_flg) {
        _TRACE_(FUNC_NAME<<" 管理者休止状態");
    } else {
        _TRACE_(FUNC_NAME<<" 管理者稼働状態");
    }
    return _is_resting_flg;
}

void Caretaker::finishRest() {
    _TRACE_(FUNC_NAME<<" ＜管理者＞管理者、休憩はおしまい。さあ動け！");
    _have_to_rest_flg = false;
}


void Caretaker::desert() {
    //管理者にため込んでいる全てのゆりかごを破棄
    //管理者(Caretaker)がアプリ終了時等に実行する予定。
    _TRACE_("＜管理者＞ もう・・・見捨てよう・・・");
    Cradle* pCradle = _pCradleRoot;
    if (pCradle == nullptr) {
        _TRACE_("＜管理者＞ しかし何も無い！！");
        return;
    }
    uint64_t cnt = 0;
    while (_is_loving_flg || _was_finished_loving_flg == false) {
        Sleep(10);
        _TRACE_(FUNC_NAME<<" ＜管理者の愛＞ 実はまだ愛してます・・・");
        cnt++;
        if (cnt > 100*60*5) {
            _TRACE_(FUNC_NAME<<" ＜管理者の愛＞ まだ愛してます・・・が、もういいか。限界です");
            break;
        }
    }

    Caretaker::debuginfo();
    _TRACE_("＜管理者＞ ゆりかご削除開始");
    while (true) {
        if (pCradle->_is_last_cradle_flg) {
            _TRACE_("＜管理者＞ ゆりかご削除["<<pCradle->getDebuginfo()<<"]、最後のストック");
            GGAF_DELETE(pCradle);
            pCradle = nullptr;
            _pCradleRoot = nullptr;
            _pCradleBlessing = nullptr;
            break;
        } else {
            _TRACE_("＜管理者＞ ゆりかご削除["<<pCradle->getDebuginfo()<<"]");
            Cradle* pCradle_my_next = pCradle->_pCradle_next;
            GGAF_DELETE(pCradle);
            pCradle = pCradle_my_next;
        }
    }
    _TRACE_("＜管理者＞ ゆりかご削除終了");
    return;
}

void Caretaker::repent(Object* prm_pReceiver) {
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

void Caretaker::debuginfo() {
    _TRACE_(FUNC_NAME<<" ＜管理者＞ 現在のゆりかご情報");
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
        _TRACE_(FUNC_NAME<<" なんということでしょう。現在の管理者の状態の表示が不可能です。そんな馬鹿な；");
    }
    _TRACE_(FUNC_NAME<<" 以上");
}

unsigned __stdcall Caretaker::love(void* prm_arg) {
    return pCARETAKER->loving(prm_arg);
}
unsigned Caretaker::loving(void* prm_arg) {
    try {
        Object* (*funcBlessing)(void*, void*, void*) = nullptr;
        Object* pObject = nullptr;
        Sleep(1000); //crtkr のインスタンスが完成するまでほんのちょっと待つ必要があるかもしれない

        //祝福しまくるくる管理者の愛ループ！
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
                if (pCradleBlessing->_progress_no == 0) { //未着手ならまず作る
                    _TRACE2_("＜管理者の愛＞ よし、ゆりかご["<<pCradleBlessing->_cradle_no<<"-"<<pCradleBlessing->_pReceiver<<"]は未着手(_phase_no == "<<pCradleBlessing->_progress_no<<")だな。ゆえに今から作ります！");
                    pCradleBlessing->_progress_no = 1; //ステータスを祝福中へ
                    pCradleBlessing->_time_of_create_begin = timeGetTime();
                    funcBlessing = pCradleBlessing->_pFunc;
                    void* arg1 = pCradleBlessing->_pArg1;
                    void* arg2 = pCradleBlessing->_pArg2;
                    void* arg3 = pCradleBlessing->_pArg3;
                    _TRACE2_("＜管理者の愛＞ 祝福開始！["<<pCradleBlessing->_cradle_no<<"-"<<pCradleBlessing->_pReceiver<<"]");
//                    Sleep(2);
                    END_SYNCHRONIZED1; // <----- 排他終了

                    pObject = (*funcBlessing)(arg1, arg2, arg3); //祝福、命が誕生。

                    BEGIN_SYNCHRONIZED1; // ----->排他開始
//                    Sleep(2);
                    _TRACE2_("＜管理者の愛＞ 祝福完了！生まれたのは["<<pCradleBlessing->_cradle_no<<"-"<<pCradleBlessing->_pReceiver<<"] (^_^)v");
                    if (_pCradleBlessing == nullptr) {
                        //_pCradleBlessing が祝福後 nullptr になってしまっている場合キャンセル。
                        _TRACE2_("＜管理者の愛＞ ガーン！。せっかく祝福したのにキャンセルっすか・・・。破棄します。pObjectをdelete!");
                        GGAF_DELETE(pObject);
END_SYNCHRONIZED1; // <----- 排他終了
                        continue;
                    } else if (_pCradleBlessing == pCradleBlessing) {
                        //正常なケース
                        pCradleBlessing->_pObject_creation = pObject; //ゆりかごに乗せる
                        pCradleBlessing->_progress_no = 2; //ステータスを祝福済みへ
                        pCradleBlessing->_time_of_create_finish = timeGetTime();
                        _TRACE2_("＜管理者の愛＞ 祝福したゆりかごの命["<<pCradleBlessing->_cradle_no<<"-"<<pCradleBlessing->_pReceiver<<"]を、棚に置いときます。");
                    }  else if (_pCradleBlessing != pCradleBlessing) {
                        _TRACE2_("＜管理者の愛＞ 警告、ゆりかごの命["<<pCradleBlessing->_cradle_no<<"-"<<pCradleBlessing->_pReceiver<<"]を作っている間に、"
                                 "_pCradleBlessing が、別のゆりかご["<<_pCradleBlessing->_cradle_no<<"-"<<_pCradleBlessing->_pReceiver<<"]を指していました！壊れてるかもしれません！強制的に元に戻します！要調査！");
                        _pCradleBlessing = pCradleBlessing; //ポインタ強制戻し
                        pCradleBlessing->_pObject_creation = pObject; //ゆりかごに乗せる
                        pCradleBlessing->_progress_no = 2; //ステータスを祝福済みへ
                        pCradleBlessing->_time_of_create_finish = timeGetTime();
                        _TRACE2_("＜管理者の愛＞ 祝福したゆりかごの命["<<pCradleBlessing->_cradle_no<<"-"<<pCradleBlessing->_pReceiver<<"]を、棚に置いときます・・・。");
                    }
                } else {
                    _TRACE2_("＜管理者の愛＞ ゆりかご["<<pCradleBlessing->_cradle_no<<"-"<<pCradleBlessing->_pReceiver<<"]の命は、もう祝福済みでストックしてるし・・・(_phase_no == "<<pCradleBlessing->_progress_no<<")。");
                }
            }
            if (_pCradleRoot == nullptr) {
                //無条件待機
                _TRACE2_("＜管理者の愛＞ 何～んもありません。ゆりかご来い来い！！・・・ないのん？。（待機）");
END_SYNCHRONIZED1; // <----- 排他終了
                if (_fps >= CONFIG::FPS_TO_CLEAN_GARBAGE_BOX) {
                    _TRACE2_("＜管理者の愛＞ さほど忙しくないので、ゴミ箱のゴミを出しとこう。");
                    GarbageBox::_pGarbageBox->clean(5); //暇なので、ゴミ箱掃除
                    GarbageBox::_cnt_cleaned = 0;
                }
            } else {
                if (_pCradleRoot != nullptr && _pCradleRoot->_pCradle_prev->_progress_no == 0) {
                    _TRACE2_("＜管理者の愛＞ ・・・！、未祝福のゆりかごがある気配。最終目標のゆりかごは["<<_pCradleRoot->_pCradle_prev->_cradle_no<<"/受取人="<<_pCradleRoot->_pCradle_prev->_pReceiver<<"]なのか？。");
                    _pCradleBlessing = _pCradleBlessing->_pCradle_next;
END_SYNCHRONIZED1; // <----- 排他終了
                } else {
                    _TRACE2_("＜管理者の愛＞ さて、未祝福ゆりかごは無し。棚にたまってるのを早く取りに来い来い！。（待機）");
END_SYNCHRONIZED1; // <----- 排他終了
                    if (_fps >= CONFIG::FPS_TO_CLEAN_GARBAGE_BOX) {
                        _TRACE2_("＜管理者の愛＞ さほど忙しくないさそうなので、ゴミ箱のゴミを出しとこうか…。");
                        GarbageBox::_pGarbageBox->clean(5); //暇なので、ゴミ箱掃除
                        GarbageBox::_cnt_cleaned = 0;
                    }
                }
            }
            Sleep(2);
        } // <-- while (_is_loving_flg)
        _TRACE2_("＜管理者の愛＞ さようなら、また会いましょう。");
        _was_finished_loving_flg = true;
    } catch (CriticalException& e) {
        debuginfo();
        _TRACE_("＜管理者例外の愛＞ 私としたことがすみません；"<<e.getMsg());
        _is_loving_flg = false;
        _was_finished_loving_flg = true;
        _pException_god = NEW CriticalException(e.getMsg());
        return 1;
    }
    return 0;
}

unsigned __stdcall Caretaker::send(void* prm_arg) {
    return pCARETAKER->sending(prm_arg);
}

unsigned Caretaker::sending(void* prm_arg) {
    try {
        //Object* (*funcBlessing)(void*, void*, void*) = nullptr;
        //Object* pObject = nullptr;
        Sleep(1000); //crtkr のインスタンスが完成するまでほんのちょっと待つ必要があるかもしれない

        //ゴミ掃除しまくる管理者の異界送りループ！
        while (_is_sending_flg) {
BEGIN_SYNCHRONIZED1; // ----->排他開始
            GarbageBox::_pGarbageBox->clean(5); //天国へ
            GarbageBox::_cnt_cleaned = 0;
END_SYNCHRONIZED1; // <----- 排他終了
            Sleep(2);
        } // <-- while (_is_loving_flg)
        _TRACE2_("＜管理者の異界送り＞ さようなら、また会いましょう。");
        _was_finished_sending_flg = true;
    } catch (CriticalException& e) {
        debuginfo();
        _TRACE_("＜管理者例外の異界送り＞ 私としたことがすみません；"<<e.getMsg());
        _is_sending_flg = false;
        _was_finished_sending_flg = true;
        _pException_god = NEW CriticalException(e.getMsg());
        return 1;
    }
    return 0;
}


