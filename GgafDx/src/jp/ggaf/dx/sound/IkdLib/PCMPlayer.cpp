// �{�v���O�����́A<BR>
// �u���~�i�܂�؂��j����[�ǂ��ƃR���v http://marupeke296.com/index.html <BR>
// �T�C�g���R���e���c�� �uOgg Vorbis����ҁv http://marupeke296.com/OGG_main.html <BR>
// �̃T���v���v���O�������I���W�i���ł��B<BR>
// �ꕔ�ύX���Ďg�p���Ă��܂��B<BR>
//                                            2009/01/13 Masatoshi Tsuge<BR>

#include "jp/ggaf/dx/sound/IkdLib/PCMPlayer.h"

#include <process.h>
#include "jp/ggaf/dx/exception/CriticalException.h"
#include "jp/ggaf/dx/sound/IkdLib/PCMDecoder.h"
#include "jp/ggaf/dx/God.h"

#ifdef __GNUG__
    #define __null
    #define NULL    0
    #define __in
    #define __out
#endif
#include <dsound.h>  //��sal.h �� include ����
#ifdef __GNUG__
    #undef __null
    #undef __in
    #undef __out
#endif

using namespace IkdLib;


//#ifdef _MSC_VER
//
//#else
//#define nullptr 0
//#endif

namespace {
double playTime_g = 1; // 1 sec.
}

PCMPlayer::PCMPlayer() :
        _pDS8(nullptr), _pDSBuffer(nullptr), _pPCMDecoder(nullptr), _pWaveFormat(NEW WAVEFORMATEX), _pBufferDesc(NEW DSBUFFERDESC), _is_ready(false), _hnd_thread(0), _is_terminate(false), _is_looping(true), _state(STATE_NONE)
{
    clear();
}

PCMPlayer::PCMPlayer(IDirectSound8* prm_pDS8) :
        _pDS8(prm_pDS8), _pDSBuffer(nullptr), _pPCMDecoder(nullptr), _pWaveFormat(NEW WAVEFORMATEX), _pBufferDesc(NEW DSBUFFERDESC), _is_ready(false), _hnd_thread(0), _is_terminate(false), _is_looping(true), _state(STATE_NONE)
{
    clear();
}

PCMPlayer::PCMPlayer(IDirectSound8* prm_pDS8, PCMDecoder* prm_pDecoder) :
        _pDS8(prm_pDS8), _pDSBuffer(nullptr), _pPCMDecoder(nullptr), _pWaveFormat(NEW WAVEFORMATEX), _pBufferDesc(NEW DSBUFFERDESC), _is_ready(false), _hnd_thread(0), _is_terminate(false), _is_looping(true), _state(STATE_NONE)
{
    clear();
    setDecoder(prm_pDecoder);
}

PCMPlayer::~PCMPlayer() {
    //�������������Ȃ��ꍇ�̌��������̂��߁A
    //�X�}�[�g�|�C���^���O����delete��Release�ŉ��
    _TRACE_("PCMPlayer::~PCMPlayer() begin");
    _TRACE_("terminateThread();");
    terminateThread();
    GGAF_DELETE(_pWaveFormat);
    GGAF_DELETE(_pBufferDesc);

    _TRACE_("GGAF_RELEASE(_pDSBuffer);");
    GGAF_RELEASE(_pDSBuffer);
    _TRACE_("GGAF_DELETE(_pPCMDecoder);");
    GGAF_DELETE(_pPCMDecoder);
    _TRACE_("PCMPlayer::~PCMPlayer() end");
}

//! �N���A
void PCMPlayer::clear() {
    terminateThread();
    memset(_pBufferDesc, 0, sizeof(DSBUFFERDESC));
    memset(_pWaveFormat, 0, sizeof(WAVEFORMATEX));
    if (_pDSBuffer) {
        GGAF_RELEASE(_pDSBuffer);
        _pDSBuffer = nullptr;
    }
    _is_ready = false;
    _state = STATE_NONE;
}

//! �Đ����̃X���b�h���~
void PCMPlayer::terminateThread() {
    if (_hnd_thread != 0) {
        _is_terminate = true;
        bool end = false;
        int wait = 0;
        while (!end) {
            //if (wait > 1) {
            if (wait > 10000) {
                _TRACE_("�y�x���z PCMPlayer::terminateThread() �����B�������X���b�h���I�����邱�Ƃ������BREAK (T_T)");
                break;
            }
            DWORD flag = WaitForSingleObject(_hnd_thread, 4);
            switch (flag) {
                case WAIT_OBJECT_0:
                    // �X���b�h���I�����
                    end = true;
                    _TRACE_(FUNC_NAME<<" WaitForSingleObject=WAIT_OBJECT_0 OK!Done! flag="<<flag<<" wait="<<wait<<"");
                    break;
                case WAIT_TIMEOUT:
                    wait++;
                    _is_terminate = true;
                    // �܂��I�����Ă��Ȃ��̂őҋ@
                    _TRACE_(FUNC_NAME<<" WaitForSingleObject=WAIT_TIMEOUT... flag="<<flag<<" wait="<<wait<<"");
                    break;
                case WAIT_FAILED:
                    // ���s���Ă���悤�ł�
                    end = true;
                    _TRACE_(FUNC_NAME<<" WaitForSingleObject=WAIT_FAILED... flag="<<flag<<" wait="<<wait<<"");
                    break;
                default:
                    wait++;
                    _TRACE_(FUNC_NAME<<" WaitForSingleObject=?  flag="<<flag<<" wait="<<wait<<"");
                    break;
            }
            if (!end) {
                Sleep(2);
            }
        }
        _is_terminate = false;
        CloseHandle(_hnd_thread);
        _hnd_thread = 0;
    } else {
        _TRACE_(FUNC_NAME<<" �ȑO�Ɋ��Ɏ��s�ς݁B�����Bthis=" << this << "/_is_terminate=" << _is_terminate);
    }
}

//! �f�o�C�X�ݒ�
void PCMPlayer::setDevice(IDirectSound8* prm_pDS8) {
    _pDS8 = prm_pDS8;
}

//! PCM�f�R�[�_��ݒ�
bool PCMPlayer::setDecoder(PCMDecoder* prm_pPcmDecoder) {
    if (_pDS8 == nullptr || prm_pPcmDecoder == nullptr || prm_pPcmDecoder->isReady() == false) {
        _is_ready = false;
        return false;
    }

    _state = STATE_STOP;

    if (!prm_pPcmDecoder->getWaveFormatEx(_pWaveFormat)) {
        return false;
    }

    _pBufferDesc->dwSize = sizeof(DSBUFFERDESC);
    _pBufferDesc->dwFlags = DSBCAPS_CTRLPAN | DSBCAPS_CTRLVOLUME | DSBCAPS_CTRLFREQUENCY | DSBCAPS_GLOBALFOCUS | DSBCAPS_CTRLPOSITIONNOTIFY;
    _pBufferDesc->dwBufferBytes = _pWaveFormat->nAvgBytesPerSec * playTime_g;
    _pBufferDesc->dwReserved = 0;
    _pBufferDesc->lpwfxFormat = _pWaveFormat;
    _pBufferDesc->guid3DAlgorithm = GUID_NULL;

    // �N���[����ۑ�
    _pPCMDecoder = prm_pPcmDecoder->createClone();

    // �Z�J���_���o�b�t�@���܂������ꍇ�͍쐬
    if (_pDSBuffer == nullptr) {
        IDirectSoundBuffer* ptmpBuf = 0;
        if (SUCCEEDED(_pDS8->CreateSoundBuffer(_pBufferDesc, &ptmpBuf, nullptr))) {
            ptmpBuf->QueryInterface(IID_IDirectSoundBuffer8, (void**)&_pDSBuffer);
        } else {
            clear();
            return false;
        }
        ptmpBuf->Release();
    }

    // �o�b�t�@��������
    //������pDSBuffer->Lock �ŋɋH�ɂ�����B
    //��initializeBuffer() �ƍĐ���r������΂悳����
    bool r = initializeBuffer();
    if (r == false) {
        return false;
    }

    // �o�b�t�@�R�s�[�X���b�h����
    if (_hnd_thread == 0) {
        //_hnd_thread = (uintptr_t)_beginthread(PCMPlayer::streamThread, 0, (void*)this);
        _hnd_thread = (HANDLE)_beginthreadex(nullptr, 0, IkdLib::PCMPlayer::streamThread, (void*)this, 0, nullptr);
    }

    _is_ready = true;

    return true;
}

//! �o�b�t�@������������
bool PCMPlayer::initializeBuffer() {
    if (_pPCMDecoder == nullptr) {
        return false;
    }
    BEGIN_SYNCHRONIZED2; //���ꂪ�����Ă�
    _pPCMDecoder->setHead(); // ���o��
    HRESULT hr = _pDSBuffer->SetCurrentPosition(0);
    checkDxException(hr, DS_OK, " SetCurrentPosition( 0 ) �Ɏ��s���܂����B");
    // �o�b�t�@�����b�N���ď����f�[�^��������
    for (int i = 0; i < 10; i++) { //�ő�P�O�񎎍s���Ă݂�B����̍�B
                                   //����� DSBLOCK_ENTIREBUFFER �i�S�̃��b�N)��
                                   //�d�g�����̃^�C�~���O�Ŏ��s���邱�Ƃ͔�����Ȃ��ƍl�������߁B
                                   //TODO:�͂����Ă���ȕ��@�ł����̂��낤���B


        void* AP1 = 0, *AP2 = 0;
        DWORD AB1 = 0, AB2 = 0;
        hr = _pDSBuffer->Lock(0, 0, &AP1, &AB1, &AP2, &AB2, DSBLOCK_ENTIREBUFFER);
        //checkDxException(hr, DS_OK, "Lock �Ɏ��s���܂����B");
        //��TODO:���b�N���s���Ă���ꍇ������B�d���Ȃ��̂ŃG���[�`�F�b�N�̓R�����g�ɂ���B
        //  �N�������ꍇ�A���������[�N���Ă�����ۂ��B�������ԔY�񂾂����u�E�E�B
        //�N���e�B�J���Z�N�V����   BEGIN_SYNCHRONIZED2 �`    END_SYNCHRONIZED2 �ŋ��ނ悤�ɂ��Ă݂��B
        //�ǋL�F�N���e�B�J���Z�N�V�����ň͂ނ悤�ɏC�����Ă���A�������Ԉ��肵�Ă���B

        if (SUCCEEDED(hr)) {
            _pPCMDecoder->getSegment((char*)AP1, AB1, 0, 0); //�� �R�R�ł��ɋH�ɗ�����I�̂́B�i���͒������Ԉ��肵�Ă���j
            hr = _pDSBuffer->Unlock(AP1, AB1, AP2, AB2);
            checkDxException(hr, DS_OK, "Unlock �Ɏ��s���܂����B");
            break;
        } else {
            //���b�N���s��
            if (i < 10) {
                _TRACE_(FUNC_NAME<<" Lock�Ɏ��s i=" << i << " ");
//                _TRACE_("hr=" << hr << " " << DXGetErrorString(hr) << " " << DXGetErrorDescription(hr));
                _TRACE_("HRESULT="<<hr);
                hr = _pDSBuffer->Unlock(AP1, AB1, AP2, AB2);
                Sleep(5);
                continue; //�������撣��
            } else {
                //������߂�
                _TRACE_(FUNC_NAME<<" ����Lock��������߂ĉ�����܂��B�����񂩂����");
                clear();
                END_SYNCHRONIZED2;
                return false;
            }
        }
    }
    END_SYNCHRONIZED2;
    return true;
}

//! �X�g���[���Đ��X���b�h����
unsigned __stdcall PCMPlayer::streamThread(void* playerPtr) {
    PCMPlayer* player = (PCMPlayer*)playerPtr;
    unsigned int size = player->_pBufferDesc->dwBufferBytes / 2;
    unsigned int flag = 0;
    DWORD point = 0;
    void* AP1 = 0, *AP2 = 0;
    DWORD AB1 = 0, AB2 = 0;

    DWORD finishPos = 0;
    DWORD prePlayPos = 0;

    unsigned int writeSize = 0;
    bool isEnd = false;
    bool waitFinish = false;

    while (player->_is_terminate == false) {
        if (pGOD->_sync_frame_time) {
            _TRACE_("PCMPlayer::streamThread() ���t��~���E�E�E");
            Sleep(100);
            continue;
        }

        BEGIN_SYNCHRONIZED2;
        switch (player->getState()) {
            case STATE_PLAY: // �Đ���
                // �X�g���[���Đ�
                // ���݈ʒu���`�F�b�N
                player->_pDSBuffer->GetCurrentPosition(&point, 0);
                if (flag == 0 && point >= size) {
                    // �O���ɏ�������
                    if (SUCCEEDED(player->_pDSBuffer->Lock(0, size, &AP1, &AB1, &AP2, &AB2, 0))) {
                        player->_pPCMDecoder->getSegment((char*)AP1, AB1, &writeSize, &isEnd);
                        player->_pDSBuffer->Unlock(AP1, AB1, AP2, AB2);
                        flag = 1;
                    }

                    // �ŏI�������݂̏ꍇ�͏I���ʒu�����
                    if (isEnd && waitFinish == false) {
                        finishPos = writeSize;
                        player->_pDSBuffer->GetCurrentPosition(&prePlayPos, 0);
                        waitFinish = true;
                    }
                } else if (flag == 1 && point < size) {
                    // �㔼�ɏ�������
                    if (SUCCEEDED(player->_pDSBuffer->Lock(size, size * 2, &AP1, &AB1, &AP2, &AB2, 0))) {
                        player->_pPCMDecoder->getSegment((char*)AP1, AB1, &writeSize, &isEnd);
                        player->_pDSBuffer->Unlock(AP1, AB1, AP2, AB2);
                        flag = 0;
                    }

                    // �ŏI�������݂̏ꍇ��Norify��ݒ�
                    if (isEnd && waitFinish == false) {
                        finishPos = size + writeSize;
                        player->_pDSBuffer->GetCurrentPosition(&prePlayPos, 0);
                        waitFinish = true;
                    }
                }
                break;

            case STATE_STOP:
                flag = 0; // �~�߂�ƑO���������݂���n�܂邽��
                isEnd = false;
                finishPos = 0;
                prePlayPos = 0;
                break;

            case STATE_PAUSE:
                break;

            default:
                break;
        }
        END_SYNCHRONIZED2;

        // �I���ʒu����`�F�b�N
        if (isEnd) {
            DWORD curPlayPos;
            HRESULT hr = player->_pDSBuffer->GetCurrentPosition(&curPlayPos, 0);
            checkDxException(hr, DS_OK, "GetCurrentPosition �Ɏ��s���܂����B");
            if (curPlayPos < prePlayPos) {
                // �o�b�t�@�����[�v�����u��
                //if ( prePlayPos <= finishPos ) {
                if (prePlayPos <= finishPos || finishPos <= curPlayPos) {
                    // �I���錾
                    player->stop();
                }
            } else {
                if (prePlayPos <= finishPos && finishPos <= curPlayPos) {
                    // �I���錾
                    player->stop();
                }
            }
            prePlayPos = curPlayPos;
        }

        Sleep(100);
    }

    return 0;
}

//! �Đ�
bool PCMPlayer::play(bool prm_is_looping) {
    if (isReady() == false) {
        return false;
    }
    _is_looping = prm_is_looping;
    _pPCMDecoder->setLooping(_is_looping);
    HRESULT hr = _pDSBuffer->Play(0, 0, DSBPLAY_LOOPING);
    checkDxException(hr, DS_OK, "���s���܂����B prm_is_looping="<<prm_is_looping);
    _state = STATE_PLAY;
    return true;
}

//! �ꎞ��~
void PCMPlayer::pause() {
    if (_state == STATE_PLAY) {
        // �����Ă�����~�߂�
        HRESULT hr = _pDSBuffer->Stop();
        checkDxException(hr, DS_OK, "���s���܂����B");
        _state = STATE_PAUSE;
    } else if (_state == STATE_PAUSE) {
        //PAUSE����pause()���Ă�����
    } else if (_state == STATE_STOP) {
        //��~����pause()���Ă�����
    }
}
void PCMPlayer::unpause() {
    if (_state == STATE_PLAY) {
        //���t���� unpause() ���Ă�����
    } else if (_state == STATE_PAUSE) {
        // PAUSE���Ȃ�Đ�
        _state = STATE_PLAY;
        play(_is_looping);
    } else if (_state == STATE_STOP) {
        //��~����unpause()���Ă�����
    }
}

//! ��~
void PCMPlayer::stop() {
    if (isReady() == false) {
        return;
    }
    _state = STATE_STOP;
    HRESULT hr = _pDSBuffer->Stop();
    checkDxException(hr, DS_OK, "���s���܂����B");
    // �o�b�t�@�̓��o��
    bool r = initializeBuffer();
    _TRACE_(FUNC_NAME<<" initializeBuffer() = " << r);
}

//! ���ʂ�ς���
void PCMPlayer::setVolume(int db) {
    if (isReady()) {
        HRESULT hr = _pDSBuffer->SetVolume(db);
        checkDxException(hr, DS_OK, "���s���܂����B db="<<db);
    }
}

//! �p���̈ʒu��ς���
void PCMPlayer::setPan(int pan) {
    if (isReady()) {
        HRESULT hr = _pDSBuffer->SetPan(pan);
        checkDxException(hr, DS_OK, "���s���܂����Bpan="<<pan);
    }
}

//! �����ł����H
bool PCMPlayer::isReady() {
    return _is_ready;
}

//! �Đ����H
bool PCMPlayer::isPlaying() {
    return (_state == STATE_PLAY);
}

//! ��Ԃ��擾
PCMPlayer::STATE PCMPlayer::getState() {
    return _state;
}
