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
	_isBehaved = false;
}


void GgafGod::be(){
	if (_pWorld == NULL) {
		_pWorld = createWorld();
		if (_pWorld == NULL) {
			throw_GgafCriticalException("GgafGod::be() Error! ���E���������ĉ������I");
		}
		_pWorld -> _pGod = this;
	}

	//�H��i�ʃX���b�h�j��O���`�F�b�N
	if (_pException_Factory != NULL) {
		throw *_pException_Factory;
	}

	if (_isBehaved == false) {
		_isBehaved = true;
		::EnterCriticalSection(&(GgafGod::CS1)); // -----> �r���J�n
		_dwFrame_God++;
		_s_iNumCleanNodePerFrame = 0;
		makeWorldBe();
		makeWorldJudge();
		::LeaveCriticalSection(&(GgafGod::CS1)); // <----- �r���I��
		//�`��^�C�~���O�t���[�����Z
		//_dwTime_ScheduledNextFrame += _aDwTime_OffsetOfNextFrame[_dwFrame_God % 60]; //�\��͕ς��Ȃ�
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
	//fps�v�Z
	if (_dwTime_FrameBegin - _dwTime_Prev >= 1000) {
		_fFps = (float)(_dwFrame_Visualize - _dwFrame_PrevVisualize) / (float)((_dwTime_FrameBegin-_dwTime_Prev)/1000.0 );
		_TRACEORE(_fFps);
		_dwTime_Prev = _dwTime_FrameBegin;
		_dwFrame_PrevVisualize = _dwFrame_Visualize;
	}
#endif

	if (_dwTime_ScheduledNextFrame <= _dwTime_FrameBegin) { //�`��^�C�~���O�t���[���ɂȂ����A�����͉߂��Ă���ꍇ

		if (_dwTime_FrameBegin > _dwTime_ScheduledNextFrame+ _aDwTime_OffsetOfNextFrame[_dwFrame_God % 60]) {
			//�啝�ɉ߂��Ă�����(���̃t���[���܂ŐH������ł�����)�X�L�b�v
			_dwFrame_SkipCount++;
			if (_dwFrame_SkipCount >= GGAF_PROPERTY(MAX_SKIP_FRAME)) {
				//�X�L�b�v����Ƃ����Ă�MAX_SKIP_FRAME�t���[���ɂP��͕`��͂���B
				_dwFrame_SkipCount = 0;
				_dwFrame_Visualize++;
				::EnterCriticalSection(&(GgafGod::CS1)); // -----> �r���J�n
				makeWorldMaterialize();
				makeWorldVisualize();
				makeWorldFinalize();
				getWorld()->cleane(10);
				::LeaveCriticalSection(&(GgafGod::CS1)); // <----- �r���I��
			} else {
				//�X�L�b�v����makeWorldFinalize()����
				::EnterCriticalSection(&(GgafGod::CS1)); // -----> �r���J�n
				makeWorldFinalize();
				//getWorld()->cleane(1);
				::LeaveCriticalSection(&(GgafGod::CS1)); // <----- �r���I��
			}
		} else {
			//�ʏ펞�`��i�X�L�b�v�Ȃ��j
			_dwFrame_Visualize++;
			::EnterCriticalSection(&(GgafGod::CS1)); // -----> �r���J�n
			makeWorldMaterialize();//�`����s��
			makeWorldVisualize();  //���o�����s��
			makeWorldFinalize();
			//getWorld()->cleane(1);
			::LeaveCriticalSection(&(GgafGod::CS1)); // <----- �r���I��
		}
		_isBehaved = false;

	} else {//�`��^�C�~���O�t���[���ɂȂ��ĂȂ�(�]�T������)
		Sleep(1); //�H��i�ʃX���b�h�j�ɉ�
//		if (_dwTime_ScheduledNextFrame > timeGetTime()) { //�܂��]�T������ꍇ
//			if (getWorld() != NULL && _s_iNumCleanNodePerFrame == 0) { //�|���ł�����Ƃ�
//				::EnterCriticalSection(&(GgafGod::CS1)); // -----> �r���J�n
//				getWorld()->cleane(1);
//				::LeaveCriticalSection(&(GgafGod::CS1)); // <----- �r���I��
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
 * ���E��R������<BR>
 */
void GgafGod::makeWorldJudge() {
	_pWorld -> judge();
}

/**
 * ���E���������<BR>
 */
void  GgafGod::makeWorldMaterialize() {
	_pWorld -> drawPrior();
	_pWorld -> drawMain();
	_pWorld -> drawTerminate();
}

/**
 * ���E�����o������<BR>
 */
void GgafGod::makeWorldVisualize() {
	_pWorld -> dump();
}

/**
 * ���E�̌�n��<BR>
 */
void GgafGod::makeWorldFinalize() {
	_pWorld -> finally();
}

GgafGod::~GgafGod() {
    TRACE("GgafGod::~GgafGod start");
	//_pWorld->pronounceFinishLife();
	Sleep(20);
	::EnterCriticalSection(&(GgafGod::CS1)); // -----> �r���J�n
	DELETE_IMPOSSIBLE_NULL(_pWorld);
	::LeaveCriticalSection(&(GgafGod::CS1)); // <----- �r���I��
    CloseHandle(_handleFactory01);
    DeleteCriticalSection(&(GgafGod::CS2));
	DeleteCriticalSection(&(GgafGod::CS1));
	GgafFactory::_pGod = NULL;

	DELETE_POSSIBLE_NULL(_pException_Factory);
	TRACE("GgafGod::~GgafGod end");
}
