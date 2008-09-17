#include "stdafx.h"


CRITICAL_SECTION GgafGod::CS1;
CRITICAL_SECTION GgafGod::CS2;
int GgafGod::_s_iNumClean_Node = 0;
DWORD GgafGod::_dwNextTimeOffset[] = {17,17,17,17,16,17,17,17,17,16,
		                              17,17,17,17,16,17,17,17,17,16,
		                              17,17,17,17,16,17,17,17,17,16,
		                              17,17,17,17,16,17,17,17,17,16,
		                              17,17,17,17,16,17,17,17,17,16,
		                              17,17,17,17,16,17,17,17,17,16};
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
        throw_GgafCriticalException("GgafGod::GgafGod() Error! �X���b�h�쐬���s�I");
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
}


void GgafGod::be(){
	if (_pWorld == NULL) {
		_pWorld = createWorld();
		if (_pWorld == NULL) {
			throw_GgafCriticalException("GgafGod::be() Error! World���������ĉ������I");
		}
		_pWorld -> _pGod = this;
	}


	TRACE("GgafGod::being()");
	_dwTime_FrameBegin = timeGetTime();
	if (_dwTime_ScheduledNextFrame <= _dwTime_FrameBegin) {
		::EnterCriticalSection(&(GgafGod::CS1)); // -----> �r���J�n
		_dwTime_ScheduledNextFrame = _dwTime_ScheduledNextFrame + _dwNextTimeOffset[_dwFrame_God % 60]; //�\��͕ς��Ȃ�
		_dwFrame_God++;

		//fps�v�Z
		if (_dwTime_FrameBegin - _dwTime_Prev >= 1000) {
			_fFps = (float)(_dwFrame_Visualize - _dwFrame_PrevVisualize) / (float)((_dwTime_FrameBegin-_dwTime_Prev)/1000.0 );
			_TRACEORE(_fFps);
			_dwTime_Prev = _dwTime_FrameBegin;
			_dwFrame_PrevVisualize = _dwFrame_Visualize;
		}
		_s_iNumClean_Node = 0;
		makeWorldBe();
		makeWorldJudge();
		DWORD dwTime_Now = timeGetTime();
		if (_dwTime_ScheduledNextFrame > dwTime_Now) {
			_dwFrame_Visualize++;
			makeWorldMaterialize();//�`����s��
			makeWorldVisualize();  //���o�����s��
		} else {
			_dwFrame_SkipCount++;
			if (_dwFrame_SkipCount >= GGAF_PROPERTY(MAX_SKIP_FRAME)) {
				_dwFrame_SkipCount = 0;
				_dwFrame_Visualize++;
				makeWorldMaterialize();
				makeWorldVisualize();
				if (getWorld() != NULL && _s_iNumClean_Node == 0) {
					getWorld()->cleane(); //�|��
				}
			}
		}
		makeWorldFinalize();
		::LeaveCriticalSection(&(GgafGod::CS1)); // <----- �r���I��

	} else {
		::EnterCriticalSection(&(GgafGod::CS1)); // -----> �r���J�n
		if (getWorld() != NULL && _s_iNumClean_Node == 0) {
			getWorld()->cleane(); //�|��
		}
		::LeaveCriticalSection(&(GgafGod::CS1));
		Sleep(1); //�H�ꂪ�����ł��傤�B
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
	//_pWorld -> cleane();//���񂾂̂𖕏�
}

GgafWorld* GgafGod::getWorld(){
	return _pWorld;
}

GgafGod::~GgafGod() {
    TRACE("GgafGod::~GgafGod start");
	//_pWorld->pronounceFinishLife();
	Sleep(20);
	::EnterCriticalSection(&(GgafGod::CS1)); // -----> �r���J�n
    delete _pWorld;
	::LeaveCriticalSection(&(GgafGod::CS1)); // <----- �r���I��
    CloseHandle(_handleFactory01);
    DeleteCriticalSection(&(GgafGod::CS2));
	DeleteCriticalSection(&(GgafGod::CS1));
	GgafFactory::_pGod = NULL;

	TRACE("GgafGod::~GgafGod end");
}
