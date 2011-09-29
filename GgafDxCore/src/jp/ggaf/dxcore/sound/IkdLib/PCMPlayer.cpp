#include "stdafx.h"

using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace Dix;

// PCMPlayer.cpp
//
//#include "GgafDxCommonHeader.h"
//#include "PCMPlayer.h"
//#include <process.h>
//#include <stdio.h>

#ifdef _MSC_VER

#else
#define NULL 0
#endif

namespace {
double playTime_g = 1; // 1 sec.
}

//namespace Dix {
PCMPlayer::PCMPlayer() :
        _pDS8(NULL), _pDSBuffer(NULL), _pPCMDecoder(NULL), _wave_format(), _buffer_desc(), _is_ready(false), _hnd_thread(0), _is_terminate(false), _is_looping(true), _state(STATE_NONE)
{
    clear();
}

PCMPlayer::PCMPlayer(IDirectSound8* prm_pDS8) :
        _pDS8(prm_pDS8), _pDSBuffer(NULL), _pPCMDecoder(NULL), _wave_format(), _buffer_desc(), _is_ready(false), _hnd_thread(0), _is_terminate(false), _is_looping(true), _state(STATE_NONE)
{
    clear();
}

PCMPlayer::PCMPlayer(IDirectSound8* prm_pDS8, PCMDecoder* prm_pDecoder) :
        _pDS8(prm_pDS8), _pDSBuffer(NULL), _pPCMDecoder(NULL), _wave_format(), _buffer_desc(), _is_ready(false), _hnd_thread(0), _is_terminate(false), _is_looping(true), _state(STATE_NONE)
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
    _TRACE_("RELEASE_IMPOSSIBLE_NULL(_pDSBuffer);");
    RELEASE_IMPOSSIBLE_NULL(_pDSBuffer);
    _TRACE_("DELETE_IMPOSSIBLE_NULL(_pPCMDecoder);");
    DELETE_IMPOSSIBLE_NULL(_pPCMDecoder);
    _TRACE_("PCMPlayer::~PCMPlayer() end");
}

//! �N���A
void PCMPlayer::clear() {
    terminateThread();
    memset(&_buffer_desc, 0, sizeof(_buffer_desc));
    memset(&_wave_format, 0, sizeof(_wave_format));
    if (_pDSBuffer) {
        RELEASE_IMPOSSIBLE_NULL(_pDSBuffer);
        _pDSBuffer = NULL;
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
            if (wait > 10 * 100) {
                //1�b�҂��Ă��ʖڂȏꍇ�͌x�����o���ċ����I��
                _TRACE_("���x���� PCMPlayer::terminateThread() ���s���܂����B�����s���B�p������ꍇ�͒������K�v�I�I");
                break;
            }
            DWORD flag = WaitForSingleObject((HANDLE)(__int64 )_hnd_thread, 10);
            switch (flag) {
                case WAIT_OBJECT_0:
                    // �X���b�h���I�����
                    end = true;
                    break;
                case WAIT_TIMEOUT:
                    wait++;
                    _is_terminate = true;
                    // �܂��I�����Ă��Ȃ��̂őҋ@
                    break;
                case WAIT_FAILED:
                    // ���s���Ă���悤�ł�
                    end = true;
                    break;
            }
            //Sleep(1);
        }
        _is_terminate = false;
        _hnd_thread = 0;
    } else {
        _TRACE_("PCMPlayer::terminateThread() �X���b�h�͂���܂���B�����Bthis=" << this << "/_is_terminate=" << _is_terminate);
    }
}

//! �f�o�C�X�ݒ�
void PCMPlayer::setDevice(IDirectSound8* prm_pDS8) {
    _pDS8 = prm_pDS8;
}

//! PCM�f�R�[�_��ݒ�
bool PCMPlayer::setDecoder(PCMDecoder* prm_pPcmDecoder) {
    if (_pDS8 == NULL || prm_pPcmDecoder == NULL || prm_pPcmDecoder->isReady() == false) {
        _is_ready = false;
        return false;
    }

    _state = STATE_STOP;

    if (!prm_pPcmDecoder->getWaveFormatEx(_wave_format)) {
        return false;
    }

    _buffer_desc.dwSize = sizeof(DSBUFFERDESC);
    _buffer_desc.dwFlags = DSBCAPS_CTRLPAN | DSBCAPS_CTRLVOLUME | DSBCAPS_CTRLFREQUENCY | DSBCAPS_GLOBALFOCUS | DSBCAPS_CTRLPOSITIONNOTIFY;
    _buffer_desc.dwBufferBytes = _wave_format.nAvgBytesPerSec * playTime_g;
    _buffer_desc.dwReserved = 0;
    _buffer_desc.lpwfxFormat = &_wave_format;
    _buffer_desc.guid3DAlgorithm = GUID_NULL;

    // �N���[����ۑ�
    _pPCMDecoder = prm_pPcmDecoder->createClone();

    // �Z�J���_���o�b�t�@���܂������ꍇ�͍쐬
    if (_pDSBuffer == NULL) {
        IDirectSoundBuffer* ptmpBuf = 0;
        if (SUCCEEDED(_pDS8->CreateSoundBuffer(&_buffer_desc, &ptmpBuf, NULL))) {
            ptmpBuf->QueryInterface(IID_IDirectSoundBuffer8, (void**)&_pDSBuffer);
        } else {
            clear();
            return false;
        }
        ptmpBuf->Release();
    }

    // �o�b�t�@��������
    //������pDSBuffer->Lock �ŋɋH�ɂ�����B
    //��initializeBuffer() �ƍĐ���r������΂悳�����Ƃ����悤�ȋL�������~�f���ɓ��e����Ă���.
// ___BeginSynchronized02;
    bool r = initializeBuffer();
// ___EndSynchronized02;
    if (r == false) {
        return false;
    }

    // �o�b�t�@�R�s�[�X���b�h����
    if (_hnd_thread == 0) {
        _hnd_thread = (unsigned int)_beginthread(PCMPlayer::streamThread, 0, (void*)this);
    }

    _is_ready = true;

    return true;
}

//! �o�b�t�@������������
bool PCMPlayer::initializeBuffer() {
    if (_pPCMDecoder == NULL) {
        return false;
    }

    _pPCMDecoder->setHead(); // ���o��
    HRESULT hr = _pDSBuffer->SetCurrentPosition(0);
    checkDxException(hr, DS_OK , "PCMPlayer::initializeBuffer()  SetCurrentPosition( 0 ) �Ɏ��s���܂����B");
    // �o�b�t�@�����b�N���ď����f�[�^��������
    for (int i = 0; i < 10; i++) { //�ő�P�O�񎎍s���Ă݂�B����̍�B
                                   //����� DSBLOCK_ENTIREBUFFER �i�S�̃��b�N)��
                                   //�d�g�����̃^�C�~���O�Ŏ��s���邱�Ƃ͔�����Ȃ��ƍl�������߁B
                                   //TODO:�͂����Ă���ȕ��@�ł����̂��낤���B
                                   //TODO:�ɋɋH�ɗ�����̂͂Ȃ����H�B���ˑ��Ȃ̂��H���S�ɔ[�����Ă��Ȃ��B

        void* AP1 = 0, *AP2 = 0;
        DWORD AB1 = 0, AB2 = 0;
        hr = _pDSBuffer->Lock(0, 0, &AP1, &AB1, &AP2, &AB2, DSBLOCK_ENTIREBUFFER);
        //checkDxException(hr, DS_OK , "PCMPlayer::initializeBuffer() Lock �Ɏ��s���܂����B");
        //�����b�N���s���Ă���ꍇ������B�d���Ȃ��̂ŃG���[�`�F�b�N�̓R�����g�ɂ���B
        //  �N�������ꍇ�A���������[�N���Ă����B�Q�������炢�Y�񂾂����u�B
        if (SUCCEEDED(hr)) {
            _pPCMDecoder->getSegment((char*)AP1, AB1, 0, 0);
            hr = _pDSBuffer->Unlock(AP1, AB1, AP2, AB2);
            checkDxException(hr, DS_OK , "PCMPlayer::initializeBuffer() Unlock �Ɏ��s���܂����B");
            break;
        } else {
            //���b�N���s��
            if (i < 10) {
                _TRACE_("PCMPlayer::initializeBuffer() Lock�Ɏ��s i=" << i << " ");
                _TRACE_("hr=" << hr << " " << DXGetErrorString(hr) << " " << DXGetErrorDescription(hr));
                hr = _pDSBuffer->Unlock(AP1, AB1, AP2, AB2);
                Sleep(5);
                continue; //�������撣��
            } else {
                //������߂�
                _TRACE_("PCMPlayer::initializeBuffer() ����Lock��������߂ĉ�����܂��B���߂�Ȃ����G");
                clear();
                return false;
            }
        }
    }
    return true;
}

//! �X�g���[���Đ��X���b�h����
void PCMPlayer::streamThread(void* playerPtr) {
    PCMPlayer* player = (PCMPlayer*)playerPtr;
    unsigned int size = player->_buffer_desc.dwBufferBytes / 2;
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
        switch (player->getState()) {
            case STATE_PLAY: // �Đ���
                // �X�g���[���Đ�
                // ���݈ʒu���`�F�b�N
//             ___BeginSynchronized02;
                player->_pDSBuffer->GetCurrentPosition(&point, 0);
                if (flag == 0 && point >= size) {
                    // �O���ɏ�������
                    if (SUCCEEDED(player->_pDSBuffer->Lock(0, size, &AP1, &AB1, &AP2, &AB2, 0))) {
                        player->_pPCMDecoder->getSegment((char*)AP1, AB1, &writeSize, &isEnd);
                        player->_pDSBuffer->Unlock(AP1, AB1, AP2, AB2);
                        flag = 1;
                    }

                    // �ŏI�������݂̏ꍇ�͏I���ʒu�����
                    if (isEnd == true && waitFinish == false) {
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
                    if (isEnd == true && waitFinish == false) {
                        finishPos = size + writeSize;
                        player->_pDSBuffer->GetCurrentPosition(&prePlayPos, 0);
                        waitFinish = true;
                    }
                }
//             ___EndSynchronized02;
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

        // �I���ʒu����`�F�b�N
        if (isEnd == true) {
            DWORD curPlayPos;
            player->_pDSBuffer->GetCurrentPosition(&curPlayPos, 0);
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
}

//! �Đ�
bool PCMPlayer::play(bool prm_is_looping) {
    if (isReady() == false) {
        return false;
    }
    _is_looping = prm_is_looping;
    _pPCMDecoder->setLooping(_is_looping);
    _pDSBuffer->Play(0, 0, DSBPLAY_LOOPING);
    _state = STATE_PLAY;
    return true;
}

//! �ꎞ��~
void PCMPlayer::pause() {
    if (_state == STATE_PLAY) {
        // �����Ă�����~�߂�
        _pDSBuffer->Stop();
        _state = STATE_PAUSE;
    } else {
        // �~�܂��Ă�����Đ�
        play(_is_looping);
    }
}

//! ��~
void PCMPlayer::stop() {
    if (isReady() == false) {
        return;
    }
    _state = STATE_STOP;
    _pDSBuffer->Stop();

    // �o�b�t�@�̓��o��
//    ___BeginSynchronized02;
    bool r = initializeBuffer();
//    ___EndSynchronized02;
    _TRACE_("PCMPlayer::stop() initializeBuffer() = " << r);
}

//! ���ʂ�ς���
void PCMPlayer::setVolume(int volume) {
    if (isReady() == true) {
        _pDSBuffer->SetVolume(volume);
    }
}

//! �p���̈ʒu��ς���
void PCMPlayer::setPan(int pan) {
    if (isReady() == true) {
        _pDSBuffer->SetPan(pan);
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

//}
