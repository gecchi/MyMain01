#include "stdafx.h"

// PCMPlayer.cpp
//

//#include "PCMPlayer.h"
//#include <process.h>
//#include <stdio.h>

namespace {
	unsigned int playTime_g = 1;	// 1 sec.
}

	PCMPlayer::PCMPlayer() :
		isReady_		( false ),
		threadHandle_	( 0 ),
		isTerminate_	( false ),
		isLoop_			( true ),
		state_			( STATE_NONE )
	{
		clear();
	}

	PCMPlayer::PCMPlayer( IDirectSound8* cpDS8 ) :
		cpDS8_			( cpDS8 ),
		isReady_		( false ),
		threadHandle_	( 0 ),
		isTerminate_	( false ),
		isLoop_			( true ),
		state_			( STATE_NONE )
	{
		clear();
	}

	PCMPlayer::PCMPlayer( IDirectSound8* cpDS8, PCMDecoder* spDecoder ) :
		cpDS8_			( cpDS8 ),
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
		cpDSBuffer_ = 0;
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
			}
		}
		isTerminate_ = false;
		threadHandle_ = 0;
	}

	//! �f�o�C�X�ݒ�
	void PCMPlayer::setDevice( IDirectSound8* cpDS8 ) {
		cpDS8_ = cpDS8;
	}

	//! PCM�f�R�[�_��ݒ�
	bool PCMPlayer::setDecoder( PCMDecoder* pcmDecoder ) {
		if ( cpDS8_ == 0 || pcmDecoder == 0 || pcmDecoder->isReady() == false ) {
			isReady_ = false;
			return false;
		}

		state_ = STATE_STOP;

		if ( !pcmDecoder->getWaveFormatEx( waveFormat_ ) ) {
			return false;
		}

		DSBufferDesc_.dwSize = sizeof( DSBUFFERDESC );
		DSBufferDesc_.dwFlags = DSBCAPS_CTRLPAN | DSBCAPS_CTRLVOLUME | DSBCAPS_CTRLFREQUENCY | DSBCAPS_GLOBALFOCUS;
		DSBufferDesc_.dwBufferBytes = waveFormat_.nAvgBytesPerSec * playTime_g;
		DSBufferDesc_.dwReserved = 0;
		DSBufferDesc_.lpwfxFormat = &waveFormat_;
		DSBufferDesc_.guid3DAlgorithm = GUID_NULL;

		spPCMDecoder_ = pcmDecoder;

		// �Z�J���_���o�b�t�@���܂������ꍇ�͍쐬
		if ( cpDSBuffer_ == 0 ) {
			IDirectSoundBuffer*	 ptmpBuf = 0;
			if ( SUCCEEDED( cpDS8_->CreateSoundBuffer( &DSBufferDesc_, &ptmpBuf, NULL ) ) ) {
				ptmpBuf->QueryInterface( IID_IDirectSoundBuffer8 , (void**)&cpDSBuffer_);
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
		if ( spPCMDecoder_ == 0 ) {
			return false;
		}

		spPCMDecoder_->setHead();	// ���o��
		cpDSBuffer_->SetCurrentPosition( 0 );

		// �o�b�t�@�����b�N���ď����f�[�^��������
		void* AP1 = 0, *AP2 = 0;
		DWORD AB1 = 0, AB2  = 0;
		if ( SUCCEEDED( cpDSBuffer_->Lock( 0, 0, &AP1, &AB1, &AP2, &AB2, DSBLOCK_ENTIREBUFFER ) ) ) {
			spPCMDecoder_->getSegment( (char*)AP1, AB1, 0, 0 );
			cpDSBuffer_->Unlock( AP1, AB1, AP2, AB2 );
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

		while( player->isTerminate_ == false ) {
			switch ( player->getState() ) {
			case STATE_PLAY:	// �Đ���
				// �X�g���[���Đ�
				// ���݈ʒu���`�F�b�N
				player->cpDSBuffer_->GetCurrentPosition( &point, 0 );
				if ( flag == 0 && point >= size ) {
					// �O���ɏ�������
					if ( SUCCEEDED( player->cpDSBuffer_->Lock( 0, size, &AP1, &AB1, &AP2, &AB2, 0 ) ) ) {
						player->spPCMDecoder_->getSegment( (char*)AP1, AB1, 0, 0 );
						player->cpDSBuffer_->Unlock( AP1, AB1, AP2, AB2 );
						flag = 1;
					}
				}
				else if ( flag == 1 && point < size ) {
					// �㔼�ɏ�������
					if ( SUCCEEDED( player->cpDSBuffer_->Lock( size, size * 2, &AP1, &AB1, &AP2, &AB2, 0 ) ) ) {
						player->spPCMDecoder_->getSegment( (char*)AP1, AB1, 0, 0 );
						player->cpDSBuffer_->Unlock( AP1, AB1, AP2, AB2 );
						flag = 0;
					}
				}
				break;

			case STATE_STOP:
				flag = 0;	// �~�߂�ƑO���������݂���n�܂邽��
				break;

			case STATE_PAUSE:
				break;

			default:
				break;
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
		cpDSBuffer_->Play( 0, 0, DSBPLAY_LOOPING );
		state_ = STATE_PLAY;
		return true;
	}

	//! �ꎞ��~
	void PCMPlayer::pause() {
		if ( state_ == STATE_PLAY ) {
			// �����Ă�����~�߂�
			cpDSBuffer_->Stop();
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
		cpDSBuffer_->Stop();

		// �o�b�t�@�̓��o��
		initializeBuffer();
	}

	//! ���ʂ�ς���
	void PCMPlayer::setVolume( int volume ) {
		if ( isReady() == true ) {
			cpDSBuffer_->SetVolume( volume );
		}
	}

	//! �p���̈ʒu��ς���
	void PCMPlayer::setPan( int pan ) {
		if ( isReady() == true ) {
			cpDSBuffer_->SetPan( pan );
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
