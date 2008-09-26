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

	//! クリア
	void PCMPlayer::clear() {
		terminateThread();
		memset( &DSBufferDesc_, 0, sizeof( DSBufferDesc_ ) );
		memset( &waveFormat_, 0, sizeof( waveFormat_ ) );
		cpDSBuffer_ = 0;
		isReady_ = false;
		state_ = STATE_NONE;
	}

	//! 再生中のスレッドを停止
	void PCMPlayer::terminateThread() {
		isTerminate_ = true;
		if ( threadHandle_ != 0 ) {
			bool end = false;
			while( !end ) {
				DWORD flag = WaitForSingleObject( (HANDLE)(__int64)threadHandle_, 100 );
				switch( flag ) {
				case WAIT_OBJECT_0:
					// スレッドが終わった
					end = true;
					break;
				case WAIT_TIMEOUT:
					// まだ終了していないので待機
					break;
				case WAIT_FAILED:
					// 失敗しているようです
					end = true;
					break;
				}
			}
		}
		isTerminate_ = false;
		threadHandle_ = 0;
	}

	//! デバイス設定
	void PCMPlayer::setDevice( IDirectSound8* cpDS8 ) {
		cpDS8_ = cpDS8;
	}

	//! PCMデコーダを設定
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

		// セカンダリバッファがまだ無い場合は作成
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

		// バッファを初期化
		if ( initializeBuffer() == false ) {
			return false;
		}

		// バッファコピースレッド生成
		if ( threadHandle_ == 0 ) {
			threadHandle_ = (unsigned int)_beginthread( PCMPlayer::streamThread, 0, (void*)this );
		}

		isReady_ = true;

		return true;
	}

	//! バッファを初期化する
	bool PCMPlayer::initializeBuffer() {
		if ( spPCMDecoder_ == 0 ) {
			return false;
		}

		spPCMDecoder_->setHead();	// 頭出し
		cpDSBuffer_->SetCurrentPosition( 0 );

		// バッファをロックして初期データ書き込み
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

	//! ストリーム再生スレッド生成
	void PCMPlayer::streamThread( void* playerPtr ) {
		PCMPlayer* player = (PCMPlayer*)playerPtr;
		unsigned int size = player->DSBufferDesc_.dwBufferBytes / 2;
		unsigned int flag = 0;
		DWORD point = 0;
		void* AP1 = 0, *AP2 = 0;
		DWORD AB1 = 0, AB2  = 0;

		while( player->isTerminate_ == false ) {
			switch ( player->getState() ) {
			case STATE_PLAY:	// 再生中
				// ストリーム再生
				// 現在位置をチェック
				player->cpDSBuffer_->GetCurrentPosition( &point, 0 );
				if ( flag == 0 && point >= size ) {
					// 前半に書き込み
					if ( SUCCEEDED( player->cpDSBuffer_->Lock( 0, size, &AP1, &AB1, &AP2, &AB2, 0 ) ) ) {
						player->spPCMDecoder_->getSegment( (char*)AP1, AB1, 0, 0 );
						player->cpDSBuffer_->Unlock( AP1, AB1, AP2, AB2 );
						flag = 1;
					}
				}
				else if ( flag == 1 && point < size ) {
					// 後半に書き込み
					if ( SUCCEEDED( player->cpDSBuffer_->Lock( size, size * 2, &AP1, &AB1, &AP2, &AB2, 0 ) ) ) {
						player->spPCMDecoder_->getSegment( (char*)AP1, AB1, 0, 0 );
						player->cpDSBuffer_->Unlock( AP1, AB1, AP2, AB2 );
						flag = 0;
					}
				}
				break;

			case STATE_STOP:
				flag = 0;	// 止めると前半書き込みから始まるため
				break;

			case STATE_PAUSE:
				break;

			default:
				break;
			}

			Sleep( 100 );
		}
	}

	//! 再生
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

	//! 一時停止
	void PCMPlayer::pause() {
		if ( state_ == STATE_PLAY ) {
			// 動いていたら止める
			cpDSBuffer_->Stop();
			state_ = STATE_PAUSE;
		}
		else {
			// 止まっていたら再生
			play( isLoop_ );
		}
	}

	//! 停止
	void PCMPlayer::stop() {
		if ( isReady() == false ) {
			return;
		}
		state_ = STATE_STOP;
		cpDSBuffer_->Stop();

		// バッファの頭出し
		initializeBuffer();
	}

	//! 音量を変える
	void PCMPlayer::setVolume( int volume ) {
		if ( isReady() == true ) {
			cpDSBuffer_->SetVolume( volume );
		}
	}

	//! パンの位置を変える
	void PCMPlayer::setPan( int pan ) {
		if ( isReady() == true ) {
			cpDSBuffer_->SetPan( pan );
		}
	}

	//! 準備できた？
	bool PCMPlayer::isReady() {
		return isReady_;
	}

	//! 再生中？
	bool PCMPlayer::isPlaying() {
		return ( state_ == STATE_PLAY );
	}

	//! 状態を取得
	PCMPlayer::STATE PCMPlayer::getState() {
		return state_;
	}
