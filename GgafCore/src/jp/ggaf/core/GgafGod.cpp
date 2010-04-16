﻿#include "stdafx.h"
using namespace std;

using namespace GgafCore;

GgafCriticalException* GgafGod::_pException_Factory = NULL;
CRITICAL_SECTION GgafGod::CS1;
CRITICAL_SECTION GgafGod::CS2;
int GgafGod::_num_actor_drawing = 0;
GgafGod* GgafGod::_pGod = NULL;
DWORD GgafGod::_aTime_OffsetOfNextFrame[] = {17, 17, 16, 17, 17, 16, 17, 17, 16, 17, 17, 17, 17, 17, 16, 17, 17, 17,
                                             17, 17, 16, 17, 17, 17, 17, 17, 16, 17, 17, 17, 17, 17, 16, 17, 17, 16,
                                             17, 17, 16, 17, 17, 17, 17, 17, 16, 17, 17, 17, 17, 17, 16, 17, 17, 17,
                                             17, 17, 16, 17, 17, 17};
GgafGod::GgafGod() : GgafObject(),
  _pUniverse(NULL),
  _fps(0) {
    TRACE("GgafGod::GgafGod");
    _godframe = 0;

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
    _expected_time_of_next_frame = (DWORD)(_time_at_beginning_frame + 3000); //3秒松
    _time_prev = _time_at_beginning_frame;
    _frame_of_visualize = 0;
    _frame_of_prev_visualize = 0;
    _is_behaved_flg = false;
    _is_materialized_flg = false;
    GgafFactory::_pGarbageBox = NEW GgafGarbageBox();

}

void GgafGod::be() {
    if (_pUniverse == NULL) {
        _pUniverse = createUniverse();
#ifdef MY_DEBUG
        if (_pUniverse == NULL) {
            throwGgafCriticalException("GgafGod::be() Error! この世を実装して下さい！");
        }
#endif
        _pUniverse->_pGod = this;
    }

    //工場（別スレッド）例外をチェック
    if (_pException_Factory != NULL) {
        throw *_pException_Factory;
    }

    if (_is_behaved_flg == false) {
        _is_behaved_flg = true;
     ___BeginSynchronized; // ----->排他開始
        _godframe++;
        presentUniversalMoment();
        executeUniversalJudge();
     ___EndSynchronized; // <----- 排他終了
        //描画タイミングフレーム加算
        //_expected_time_of_next_frame += _aTime_OffsetOfNextFrame[_godframe % 60]; //予定は変わらない
        if (_num_actor_drawing > 500) {
            _expected_time_of_next_frame += (DWORD)(_aTime_OffsetOfNextFrame[_godframe % 60] * 2);
        } else if (_num_actor_drawing > 400) {
            _expected_time_of_next_frame += (DWORD)(_aTime_OffsetOfNextFrame[_godframe % 60] * 1.5);
        } else {
            _expected_time_of_next_frame += _aTime_OffsetOfNextFrame[_godframe % 60];
        }


        if (_expected_time_of_next_frame <= timeGetTime()) { //描画タイミングフレームになった、或いは過ぎている場合
            //makeUniversalMaterialize はパス
        } else {
            //余裕有り
            _is_materialized_flg = true;
            makeUniversalMaterialize();
        }
    }

    _time_at_beginning_frame = timeGetTime(); //

    //fps計算
    if (_time_at_beginning_frame - _time_prev >= 1000) {
        _fps = (float)(_frame_of_visualize - _frame_of_prev_visualize) / (float)((_time_at_beginning_frame - _time_prev) / 1000.0f);
        _TRACE_(_godframe<<"Frame "<<_num_actor_drawing<<"Actor "<<_fps<<"Fps");
        _time_prev = _time_at_beginning_frame;
        _frame_of_prev_visualize = _frame_of_visualize;
    }

    if (_expected_time_of_next_frame <= _time_at_beginning_frame) { //描画タイミングフレームになった、或いは過ぎている場合

        if (_time_at_beginning_frame > _expected_time_of_next_frame + _aTime_OffsetOfNextFrame[_godframe % 60]) {
            //大幅に過ぎていたら(次のフレームまで食い込んでいたら)スキップ
            _skip_count_of_frame++;
            if (_skip_count_of_frame >= GGAF_PROPERTY(MAX_SKIP_FRAME)) {
                //スキップするといってもMAX_SKIP_FRAMEフレームに１回は描画はする。
                _skip_count_of_frame = 0;
                _frame_of_visualize++;
             ___BeginSynchronized; // ----->排他開始
                if (_is_materialized_flg) {
                    presentUniversalVisualize();
                    finalizeUniversal();
                } else {
                    makeUniversalMaterialize();
                    presentUniversalVisualize();
                    finalizeUniversal();
                }
                //getUniverse()->cleane(10);
             ___EndSynchronized; // <----- 排他終了
            } else {
                //スキップ時はfinalizeUniversal()だけ
             ___BeginSynchronized; // ----->排他開始
                finalizeUniversal();
             ___EndSynchronized; // <----- 排他終了
            }
        } else {
            //通常時描画（スキップなし）
            _frame_of_visualize++;
         ___BeginSynchronized; // ----->排他開始
            if (_is_materialized_flg) {
                presentUniversalVisualize();
                finalizeUniversal();
            } else {
                makeUniversalMaterialize();
                presentUniversalVisualize();
                finalizeUniversal();

            }
         ___EndSynchronized; // <----- 排他終了
        }
        _is_behaved_flg = false;
        _is_materialized_flg = false;
    } else {//描画タイミングフレームになってない(余裕がある)
        Sleep(2); //工場（別スレッド）に回す
    }

    return;
}

void GgafGod::presentUniversalMoment() {
    _pUniverse->nextFrame();
    _pUniverse->behave();
}

void GgafGod::executeUniversalJudge() {
    _pUniverse->preJudge();
    _pUniverse->judge();
}

void GgafGod::makeUniversalMaterialize() {
    _num_actor_drawing = 0;
    _pUniverse->preDraw();
    _pUniverse->draw();
    _pUniverse->afterDraw();
}

void GgafGod::presentUniversalVisualize() {
    _pUniverse->dump();
}

void GgafGod::finalizeUniversal() {
    _pUniverse->finally();
}

GgafGod::~GgafGod() {
    _TRACE_("GgafGod::~GgafGod start");
    if (_pUniverse != NULL) {
        _TRACE_("_pUniverse != NULL");
        //工場を止める
        Sleep(1);
        GgafFactory::_is_working_flg = false;
        for (int i = 0; GgafFactory::_was_finished_flg == false; i++) {
            Sleep(60); //工場が落ち着くまで待つ
            if (i > 2000) {
                _TRACE_("GgafGod::~GgafGod() ２分待機しましたが、工場から反応がありません。breakします。要調査");
            }
        }
        //排他の解除
        CloseHandle(_handleFactory01);
        DeleteCriticalSection(&(GgafGod::CS2));
        DeleteCriticalSection(&(GgafGod::CS1));
        //工場掃除
    // ___BeginSynchronized; // ----->排他開始
        GgafFactory::clean();
        _TRACE_("GgafFactory::clean()");
    //___EndSynchronized; // <----- 排他終了
        //ゴミ箱
        //GgafFactory::_pGarbageBox->_pSayonaraScene->dump();
        //GgafFactory::_pGarbageBox->_pSayonaraActor->dump();
        DELETE_IMPOSSIBLE_NULL(GgafFactory::_pGarbageBox);
        //この世で生きている物も掃除
        Sleep(20);
     //___BeginSynchronized; // ----->排他開始
        DELETE_IMPOSSIBLE_NULL(_pUniverse);
     //___EndSynchronized; // <----- 排他終了
    }

    //工場例外 _pException_Factory が起こっているかもしれない。
    DELETE_POSSIBLE_NULL(_pException_Factory);
    _TRACE_("GgafGod::~GgafGod end");
}
