#include "stdafx.h"

GgafCriticalException* GgafGod::_pException_Factory = NULL;
CRITICAL_SECTION GgafGod::CS1;
CRITICAL_SECTION GgafGod::CS2;
int GgafGod::_s_iNumCleanNodePerFrame = 0;
int GgafGod::_iNumPlayingActor = 0;
DWORD GgafGod::_aDwTime_OffsetOfNextFrame[] = {17,17,16,17,17,16,
                                      17,17,16,17,17,17,
                                      17,17,16,17,17,17,
                                      17,17,16,17,17,17,
                                      17,17,16,17,17,17,
                                      17,17,16,17,17,16,
                                      17,17,16,17,17,17,
                                      17,17,16,17,17,17,
                                      17,17,16,17,17,17,
                                      17,17,16,17,17,17 };
GgafGod::GgafGod() : GgafObject(),
_pWorld(NULL)
{
    TRACE("GgafGod::GgafGod");
    _dwFrame_God = 0;

	_handleFactory01 = (HANDLE)::_beginthreadex(
        NULL,
        0,
        GgafFactory::work,
        NULL,
        CREATE_SUSPENDED,
        &_thID01
	);

	if (_handleFactory01 == 0) {
        throw_GgafCriticalException("GgafGod::GgafGod() Error! スレッド作成失敗！");
    }
	::InitializeCriticalSection(&(GgafGod::CS1));
	::InitializeCriticalSection(&(GgafGod::CS2));
	::ResumeThread(_handleFactory01);
	::SetThreadPriority(_handleFactory01, THREAD_PRIORITY_IDLE);
	GgafFactory::_pGod = this;

	_dwTime_FrameBegin = timeGetTime();
	_dwTime_ScheduledNextFrame = (DWORD)(_dwTime_FrameBegin + 1000);
	_dwTime_Prev = _dwTime_FrameBegin;
	_dwFrame_Visualize = 0;
	_dwFrame_PrevVisualize = 0;
	_fFps = 0;
	//_pWorld = NULL;
	_isBehaved = false;
}


void GgafGod::be(){
	if (_pWorld == NULL) {
		_pWorld = createWorld();
		if (_pWorld == NULL) {
			throw_GgafCriticalException("GgafGod::be() Error! 世界を実装して下さい！");
		}
		_pWorld -> _pGod = this;
	}

	//工場（別スレッド）例外をチェック
	if (_pException_Factory != NULL) {
		throw *_pException_Factory;
	}

	if (_isBehaved == false) {
		_isBehaved = true;
		::EnterCriticalSection(&(GgafGod::CS1)); // -----> 排他開始
		_dwFrame_God++;
		_s_iNumCleanNodePerFrame = 0;
		makeWorldBe();
		makeWorldJudge();
		::LeaveCriticalSection(&(GgafGod::CS1)); // <----- 排他終了
		//描画タイミングフレーム加算
		//_dwTime_ScheduledNextFrame += _aDwTime_OffsetOfNextFrame[_dwFrame_God % 60]; //予定は変わらない
		if (_iNumPlayingActor > 1000) {
			_dwTime_ScheduledNextFrame += (_aDwTime_OffsetOfNextFrame[_dwFrame_God % 60]*3);
		} else if (_iNumPlayingActor > 500) {
			_dwTime_ScheduledNextFrame += (_aDwTime_OffsetOfNextFrame[_dwFrame_God % 60]*2);
		} else {
			_dwTime_ScheduledNextFrame += _aDwTime_OffsetOfNextFrame[_dwFrame_God % 60];
		}
		_iNumPlayingActor = 0;
	}

	_dwTime_FrameBegin = timeGetTime();	//

#ifdef OREDEBUG
	//fps計算
	if (_dwTime_FrameBegin - _dwTime_Prev >= 1000) {
		_fFps = (float)(_dwFrame_Visualize - _dwFrame_PrevVisualize) / (float)((_dwTime_FrameBegin-_dwTime_Prev)/1000.0 );
		_TRACEORE(_fFps);
		_dwTime_Prev = _dwTime_FrameBegin;
		_dwFrame_PrevVisualize = _dwFrame_Visualize;
	}
#endif

	if (_dwTime_ScheduledNextFrame <= _dwTime_FrameBegin) { //描画タイミングフレームになった、或いは過ぎている場合

		if (_dwTime_FrameBegin > _dwTime_ScheduledNextFrame+ _aDwTime_OffsetOfNextFrame[_dwFrame_God % 60]) {
			//大幅に過ぎていたら(次のフレームまで食い込んでいたら)スキップ
			_dwFrame_SkipCount++;
			if (_dwFrame_SkipCount >= GGAF_PROPERTY(MAX_SKIP_FRAME)) {
				//スキップするといってもMAX_SKIP_FRAMEフレームに１回は描画はする。
				_dwFrame_SkipCount = 0;
				_dwFrame_Visualize++;
				::EnterCriticalSection(&(GgafGod::CS1)); // -----> 排他開始
				makeWorldMaterialize();
				makeWorldVisualize();
				makeWorldFinalize();
				getWorld()->cleane(10);
				::LeaveCriticalSection(&(GgafGod::CS1)); // <----- 排他終了
			} else {
				//スキップ時はmakeWorldFinalize()だけ
				::EnterCriticalSection(&(GgafGod::CS1)); // -----> 排他開始
				makeWorldFinalize();
				//getWorld()->cleane(1);
				::LeaveCriticalSection(&(GgafGod::CS1)); // <----- 排他終了
			}
		} else {
			//通常時描画（スキップなし）
			_dwFrame_Visualize++;
			::EnterCriticalSection(&(GgafGod::CS1)); // -----> 排他開始
			makeWorldMaterialize();//描画を行う
			makeWorldVisualize();  //視覚化を行う
			makeWorldFinalize();
			//getWorld()->cleane(1);
			::LeaveCriticalSection(&(GgafGod::CS1)); // <----- 排他終了
		}
		_isBehaved = false;

	} else {//描画タイミングフレームになってない(余裕がある)
		Sleep(1); //工場（別スレッド）に回す
//		if (_dwTime_ScheduledNextFrame > timeGetTime()) { //まだ余裕がある場合
//			if (getWorld() != NULL && _s_iNumCleanNodePerFrame == 0) { //掃除でもやっとく
//				::EnterCriticalSection(&(GgafGod::CS1)); // -----> 排他開始
//				getWorld()->cleane(1);
//				::LeaveCriticalSection(&(GgafGod::CS1)); // <----- 排他終了
//			}
//		}
	}

	return;
}

void GgafGod::makeWorldBe() {
	_pWorld -> nextFrame();
	_pWorld -> behave();
}

/**
 * 世界を審判する<BR>
 */
void GgafGod::makeWorldJudge() {
	_pWorld -> judge();
}

/**
 * 世界を具現化する<BR>
 */
void  GgafGod::makeWorldMaterialize() {
	_pWorld -> drawPrior();
	_pWorld -> drawMain();
	_pWorld -> drawTerminate();
}

/**
 * 世界を視覚化する<BR>
 */
void GgafGod::makeWorldVisualize() {
	_pWorld -> dump();
}

/**
 * 世界の後始末<BR>
 */
void GgafGod::makeWorldFinalize() {
	_pWorld -> finally();
}

GgafGod::~GgafGod() {
    TRACE("GgafGod::~GgafGod start");
	//_pWorld->pronounceFinishLife();
	Sleep(20);
	::EnterCriticalSection(&(GgafGod::CS1)); // -----> 排他開始
	DELETE_IMPOSSIBLE_NULL(_pWorld);
	::LeaveCriticalSection(&(GgafGod::CS1)); // <----- 排他終了
    CloseHandle(_handleFactory01);
    DeleteCriticalSection(&(GgafGod::CS2));
	DeleteCriticalSection(&(GgafGod::CS1));
	GgafFactory::_pGod = NULL;

	DELETE_POSSIBLE_NULL(_pException_Factory);
	TRACE("GgafGod::~GgafGod end");
}
