// PCMPlayer.cpp
//
#include "GgafCommonHeader.h"
#include "PCMPlayer.h"
#include <process.h>
#include <stdio.h>

#ifdef _MSC_VER

#else
#define NULL 0
#endif

namespace {
    double playTime_g = 1;	// 1 sec.
}

namespace Dix {
    PCMPlayer::PCMPlayer() :
        pDS8_			( NULL ),
        pDSBuffer_		( NULL ),
        isReady_		( false ),
        threadHandle_	( 0 ),
        isTerminate_	( false ),
        isLoop_			( true ),
        state_			( STATE_NONE )
    {
        clear();
    }

    PCMPlayer::PCMPlayer( IDirectSound8* pDS8 ) :
        pDS8_			( pDS8 ),
        pDSBuffer_		( NULL ),
        isReady_		( false ),
        threadHandle_	( 0 ),
        isTerminate_	( false ),
        isLoop_			( true ),
        state_			( STATE_NONE )
    {
        clear();
    }

    //PCMPlayer::PCMPlayer( IDirectSound8* pDS8, sp< PCMDecoder > spDecoder ) :
    PCMPlayer::PCMPlayer( IDirectSound8* pDS8, PCMDecoder* spDecoder ) :
        pDS8_			( pDS8 ),
        pDSBuffer_		( NULL ),
        isReady_		( false ),
        threadHandle_	( 0 ),
        isTerminate_	( false ),
        isLoop_			( true ),
        state_			( STATE_NONE )
    {
        clear();
        setDecoder( spDecoder );
    }

    PCMPlayer::~PCMPlayer() {
        terminateThread();
    }

    //! �N���A
    void PCMPlayer::clear() {
        terminateThread();
        memset( &DSBufferDesc_, 0, sizeof( DSBufferDesc_ ) );
        memset( &waveFormat_, 0, sizeof( waveFormat_ ) );
        if (pDSBuffer_ != NULL) {
            DELETE_IMPOSSIBLE_NULL(pDSBuffer_);
            //delete pDSBuffer_;
            pDSBuffer_ = NULL;
        }
        isReady_ = false;
        state_ = STATE_NONE;
    }

    //! �Đ����̃X���b�h���~
    void PCMPlayer::terminateThread() {
        isTerminate_ = true;
        if ( threadHandle_ != 0 ) {
            bool end = false;
            while( !end ) {
                DWORD flag = WaitForSingleObject( (HANDLE)(__int64)threadHandle_, 100 );
                switch( flag ) {
                case WAIT_OBJECT_0:
                    // �X���b�h���I�����
                    end = true;
                    break;
                case WAIT_TIMEOUT:
                    // �܂��I�����Ă��Ȃ��̂őҋ@
                    break;
                case WAIT_FAILED:
                    // ���s���Ă���悤�ł�
                    end = true;
                    break;
                }
                //Sleep(1);
            }
        }
        isTerminate_ = false;
        threadHandle_ = 0;
    }

    //! �f�o�C�X�ݒ�
    void PCMPlayer::setDevice(IDirectSound8* pDS8 ) {
        pDS8_ = pDS8;
    }


    //! PCM�f�R�[�_��ݒ�
    //bool PCMPlayer::setDecoder( sp< PCMDecoder > pcmDecoder ) {
    bool PCMPlayer::setDecoder( PCMDecoder* pcmDecoder ) {
        //if ( pDS8_ == NULL || pcmDecoder.GetPtr() == 0 || pcmDecoder->isReady() == false ) {
        if ( pDS8_ == NULL || pcmDecoder == 0 || pcmDecoder->isReady() == false ) {
            isReady_ = false;
            return false;
        }

        state_ = STATE_STOP;

        if ( !pcmDecoder->getWaveFormatEx( waveFormat_ ) ) {
            return false;
        }

        DSBufferDesc_.dwSize = sizeof( DSBUFFERDESC );
        DSBufferDesc_.dwFlags = DSBCAPS_CTRLPAN | DSBCAPS_CTRLVOLUME | DSBCAPS_CTRLFREQUENCY | DSBCAPS_GLOBALFOCUS | DSBCAPS_CTRLPOSITIONNOTIFY;
        DSBufferDesc_.dwBufferBytes = waveFormat_.nAvgBytesPerSec * playTime_g;
        DSBufferDesc_.dwReserved = 0;
        DSBufferDesc_.lpwfxFormat = &waveFormat_;
        DSBufferDesc_.guid3DAlgorithm = GUID_NULL;

        // �N���[����ۑ�
        spPCMDecoder_ = pcmDecoder->createClone();

        // �Z�J���_���o�b�t�@���܂������ꍇ�͍쐬
        if ( pDSBuffer_ == NULL ) {
            IDirectSoundBuffer*	 ptmpBuf = 0;
            if ( SUCCEEDED( pDS8_->CreateSoundBuffer( &DSBufferDesc_, &ptmpBuf, NULL ) ) ) {
                ptmpBuf->QueryInterface( IID_IDirectSoundBuffer8 , (void**)&pDSBuffer_);
            }
            else {
                clear();
                return false;
            }
            ptmpBuf->Release();
        }

        // �o�b�t�@��������
        if ( initializeBuffer() == false ) {
            return false;
        }

        // �o�b�t�@�R�s�[�X���b�h����
        if ( threadHandle_ == 0 ) {
            threadHandle_ = (unsigned int)_beginthread( PCMPlayer::streamThread, 0, (void*)this );
        }

        isReady_ = true;

        return true;
    }

    //! �o�b�t�@������������
    bool PCMPlayer::initializeBuffer() {
//        if ( spPCMDecoder_.GetPtr() == 0 ) {
//            return false;
//        }
        if (spPCMDecoder_ = 0) {
            return false;
        }

        spPCMDecoder_->setHead();	// ���o��
        pDSBuffer_->SetCurrentPosition( 0 );

        // �o�b�t�@�����b�N���ď����f�[�^��������
        void* AP1 = 0, *AP2 = 0;
        DWORD AB1 = 0, AB2  = 0;
        if ( SUCCEEDED( pDSBuffer_->Lock( 0, 0, &AP1, &AB1, &AP2, &AB2, DSBLOCK_ENTIREBUFFER ) ) ) {
            spPCMDecoder_->getSegment( (char*)AP1, AB1, 0, 0 );
            pDSBuffer_->Unlock( AP1, AB1, AP2, AB2 );
        }
        else {
            clear();
            return false;
        }

        return true;
    }

    //! �X�g���[���Đ��X���b�h����
    void PCMPlayer::streamThread( void* playerPtr ) {
        PCMPlayer* player = (PCMPlayer*)playerPtr;
        unsigned int size = player->DSBufferDesc_.dwBufferBytes / 2;
        unsigned int flag = 0;
        DWORD point = 0;
        void* AP1 = 0, *AP2 = 0;
        DWORD AB1 = 0, AB2  = 0;

        DWORD finishPos = 0;
        DWORD prePlayPos = 0;

        unsigned int writeSize = 0;
        bool isEnd = false;
        bool waitFinish = false;

        while( player->isTerminate_ == false ) {
            switch ( player->getState() ) {
            case STATE_PLAY:	// �Đ���
                // �X�g���[���Đ�
                // ���݈ʒu���`�F�b�N
                player->pDSBuffer_->GetCurrentPosition( &point, 0 );
                if ( flag == 0 && point >= size ) {
                    // �O���ɏ�������
                    if ( SUCCEEDED( player->pDSBuffer_->Lock( 0, size, &AP1, &AB1, &AP2, &AB2, 0 ) ) ) {
                        player->spPCMDecoder_->getSegment( (char*)AP1, AB1, &writeSize, &isEnd );
                        player->pDSBuffer_->Unlock( AP1, AB1, AP2, AB2 );
                        flag = 1;
                    }

                    // �ŏI�������݂̏ꍇ�͏I���ʒu�����
                    if ( isEnd == true && waitFinish == false ) {
                        finishPos = writeSize;
                        player->pDSBuffer_->GetCurrentPosition( &prePlayPos, 0 );
                        waitFinish = true;
                    }
                }
                else if ( flag == 1 && point < size ) {
                    // �㔼�ɏ�������
                    if ( SUCCEEDED( player->pDSBuffer_->Lock( size, size * 2, &AP1, &AB1, &AP2, &AB2, 0 ) ) ) {
                        player->spPCMDecoder_->getSegment( (char*)AP1, AB1, &writeSize, &isEnd );
                        player->pDSBuffer_->Unlock( AP1, AB1, AP2, AB2 );
                        flag = 0;
                    }

                    // �ŏI�������݂̏ꍇ��Norify��ݒ�
                    if ( isEnd == true && waitFinish == false ) {
                        finishPos = size + writeSize;
                        player->pDSBuffer_->GetCurrentPosition( &prePlayPos, 0 );
                        waitFinish = true;
                    }
                }
                break;

            case STATE_STOP:
                flag = 0;	// �~�߂�ƑO���������݂���n�܂邽��
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
            if ( isEnd == true ) {
                DWORD curPlayPos;
                player->pDSBuffer_->GetCurrentPosition( &curPlayPos, 0 );
                if ( curPlayPos < prePlayPos ) {
                    // �o�b�t�@�����[�v�����u��
                    //if ( prePlayPos <= finishPos ) {
                    if ( prePlayPos <= finishPos || finishPos <= curPlayPos ) {
                        // �I���錾
                        player->stop();
                    }
                } else {
                    if ( prePlayPos <= finishPos && finishPos <= curPlayPos ) {
                        // �I���錾
                        player->stop();
                    }
                }
                prePlayPos = curPlayPos;
            }

            Sleep( 100 );
        }
    }

    //! �Đ�
    bool PCMPlayer::play( bool isLoop ) {
        if ( isReady() == false ) {
            return false;
        }
        isLoop_ = isLoop;
        spPCMDecoder_->setLoop( isLoop );
        pDSBuffer_->Play( 0, 0, DSBPLAY_LOOPING );
        state_ = STATE_PLAY;
        return true;
    }

    //! �ꎞ��~
    void PCMPlayer::pause() {
        if ( state_ == STATE_PLAY ) {
            // �����Ă�����~�߂�
            pDSBuffer_->Stop();
            state_ = STATE_PAUSE;
        }
        else {
            // �~�܂��Ă�����Đ�
            play( isLoop_ );
        }
    }

    //! ��~
    void PCMPlayer::stop() {
        if ( isReady() == false ) {
            return;
        }
        state_ = STATE_STOP;
        pDSBuffer_->Stop();

        // �o�b�t�@�̓��o��
        initializeBuffer();
    }

    //! ���ʂ�ς���
    void PCMPlayer::setVolume( int volume ) {
        if ( isReady() == true ) {
            pDSBuffer_->SetVolume( volume );
        }
    }

    //! �p���̈ʒu��ς���
    void PCMPlayer::setPan( int pan ) {
        if ( isReady() == true ) {
            pDSBuffer_->SetPan( pan );
        }
    }

    //! �����ł����H
    bool PCMPlayer::isReady() {
        return isReady_;
    }

    //! �Đ����H
    bool PCMPlayer::isPlaying() {
        return ( state_ == STATE_PLAY );
    }

    //! ��Ԃ��擾
    PCMPlayer::STATE PCMPlayer::getState() {
        return state_;
    }

}
