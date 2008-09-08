#include "stdafx.h"


CRITICAL_SECTION GgafGod::_cs1;
CRITICAL_SECTION GgafGod::_cs2;
int GgafGod::_iNumClean_Node = 0;
DWORD GgafGod::_dwNextTimeOffset[] = {17,17,16,17,17,16,17,17,16,17,17,16,17,17,16,17,17,16,17,17,16,17,17,16,17,17,16,17,17,16,17,17,16,17,17,16,17,17,16,17,17,16,17,17,16,17,17,16,17,17,16,17,17,16,17,17,16,17,17,16};
GgafGod::GgafGod() : GgafObject(),
_pWorld(NULL)
{
    TRACE("GgafGod::GgafGod");
    _dwFrame_God = 0;

	_handleFactory01 = (HANDLE)::_beginthreadex(
        NULL,
        0,
        GgafSubcontractor::work,
        NULL,
        CREATE_SUSPENDED,
        &_thID01
	);

	if (_handleFactory01 == 0) {
        throw_GgafCriticalException("GgafGod::GgafGod() Error! スレッド作成失敗！");
    }
	::InitializeCriticalSection(&(GgafGod::_cs1));
	::InitializeCriticalSection(&(GgafGod::_cs2));
	::ResumeThread(_handleFactory01);
	::SetThreadPriority(_handleFactory01, THREAD_PRIORITY_IDLE);
	GgafSubcontractor::_pGod = this;

	_dwTime_FrameBegin = timeGetTime();
	_dwTime_ScheduledNextFrame = (DWORD)(_dwTime_FrameBegin + 1000);
	_dwTime_Prev = _dwTime_FrameBegin;
	_dwFrame_Visualize = 0;
	_dwFrame_PrevVisualize = 0;
	_fFps = 0;
	//_pWorld = NULL;
}


void GgafGod::be(){
	if (_pWorld == NULL) {
		_pWorld = createWorld();
		if (_pWorld == NULL) {
			throw_GgafCriticalException("GgafGod::be() Error! Worldを実装して下さい！");
		}
		_pWorld -> _pGod = this;
	}


	TRACE("GgafGod::being()");
	_dwTime_FrameBegin = timeGetTime();
	if (_dwTime_ScheduledNextFrame <= _dwTime_FrameBegin) {
		::EnterCriticalSection(&(GgafGod::_cs1)); // -----> 排他開始
		_dwTime_ScheduledNextFrame = _dwTime_ScheduledNextFrame + _dwNextTimeOffset[_dwFrame_God % 60]; //予定は変わらない
		_dwFrame_God++;

		//fps計算
		if (_dwTime_FrameBegin - _dwTime_Prev >= 1000) {
			_fFps = (float)(_dwFrame_Visualize - _dwFrame_PrevVisualize) / (float)((_dwTime_FrameBegin-_dwTime_Prev)/1000.0 );
			_TRACEORE(_fFps);
			_dwTime_Prev = _dwTime_FrameBegin;
			_dwFrame_PrevVisualize = _dwFrame_Visualize;
		}
		_iNumClean_Node = 0;
		makeWorldBe();
		makeWorldJudge();
		DWORD dwTime_Now = timeGetTime();
		if (_dwTime_ScheduledNextFrame > dwTime_Now) {
			_dwFrame_Visualize++;
			makeWorldMaterialize();//描画を行う
			makeWorldVisualize();  //視覚化を行う
		} else {
			_dwFrame_SkipCount++;
			if (_dwFrame_SkipCount >= GGAF_PROPERTY(MAX_SKIP_FRAME)) {
				_dwFrame_SkipCount = 0;
				_dwFrame_Visualize++;
				makeWorldMaterialize();
				makeWorldVisualize();
				if (getWorld() != NULL && _iNumClean_Node == 0) {
					getWorld()->cleane(); //掃除
				}
			}
		}
		makeWorldFinalize();
		::LeaveCriticalSection(&(GgafGod::_cs1)); // <----- 排他終了

	} else {
		::EnterCriticalSection(&(GgafGod::_cs1)); // -----> 排他開始
		if (getWorld() != NULL && _iNumClean_Node == 0) {
			getWorld()->cleane(); //掃除
		}
		::LeaveCriticalSection(&(GgafGod::_cs1));
		Sleep(1); //工場が動くでしょう。
	}
	return;
}

void GgafGod::makeWorldBe() {
	_pWorld -> nextFrame();
	_pWorld -> behave();
}

void GgafGod::makeWorldJudge() {
	_pWorld -> judge();
}

void GgafGod::makeWorldMaterialize() {
	_pWorld -> drawPrior();
	_pWorld -> drawMain();
	_pWorld -> drawTerminate();
}

void GgafGod::makeWorldVisualize() {
	_pWorld -> dump();
}

void GgafGod::makeWorldFinalize() {
	_pWorld -> finally();
	//_pWorld -> cleane();//死んだのを抹消
}

GgafWorld* GgafGod::getWorld(){
	return _pWorld;
}

GgafGod::~GgafGod() {
    TRACE("GgafGod::~GgafGod start");
	//_pWorld->pronounceFinishLife();
	Sleep(20);
	::EnterCriticalSection(&(GgafGod::_cs1)); // -----> 排他開始
    delete _pWorld;
	::LeaveCriticalSection(&(GgafGod::_cs1)); // <----- 排他終了
    CloseHandle(_handleFactory01);
    DeleteCriticalSection(&(GgafGod::_cs2));
	DeleteCriticalSection(&(GgafGod::_cs1));
	GgafSubcontractor::_pGod = NULL;

	TRACE("GgafGod::~GgafGod end");
}
