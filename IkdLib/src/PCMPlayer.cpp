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

    //! クリア
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
                //Sleep(1);
            }
        }
        isTerminate_ = false;
        threadHandle_ = 0;
    }

    //! デバイス設定
    void PCMPlayer::setDevice(IDirectSound8* pDS8 ) {
        pDS8_ = pDS8;
    }


    //! PCMデコーダを設定
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

        // クローンを保存
        spPCMDecoder_ = pcmDecoder->createClone();

        // セカンダリバッファがまだ無い場合は作成
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
//        if ( spPCMDecoder_.GetPtr() == 0 ) {
//            return false;
//        }
        if (spPCMDecoder_ = 0) {
            return false;
        }

        spPCMDecoder_->setHead();	// 頭出し
        pDSBuffer_->SetCurrentPosition( 0 );

        // バッファをロックして初期データ書き込み
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

    //! ストリーム再生スレッド生成
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
            case STATE_PLAY:	// 再生中
                // ストリーム再生
                // 現在位置をチェック
                player->pDSBuffer_->GetCurrentPosition( &point, 0 );
                if ( flag == 0 && point >= size ) {
                    // 前半に書き込み
                    if ( SUCCEEDED( player->pDSBuffer_->Lock( 0, size, &AP1, &AB1, &AP2, &AB2, 0 ) ) ) {
                        player->spPCMDecoder_->getSegment( (char*)AP1, AB1, &writeSize, &isEnd );
                        player->pDSBuffer_->Unlock( AP1, AB1, AP2, AB2 );
                        flag = 1;
                    }

                    // 最終書き込みの場合は終了位置を特定
                    if ( isEnd == true && waitFinish == false ) {
                        finishPos = writeSize;
                        player->pDSBuffer_->GetCurrentPosition( &prePlayPos, 0 );
                        waitFinish = true;
                    }
                }
                else if ( flag == 1 && point < size ) {
                    // 後半に書き込み
                    if ( SUCCEEDED( player->pDSBuffer_->Lock( size, size * 2, &AP1, &AB1, &AP2, &AB2, 0 ) ) ) {
                        player->spPCMDecoder_->getSegment( (char*)AP1, AB1, &writeSize, &isEnd );
                        player->pDSBuffer_->Unlock( AP1, AB1, AP2, AB2 );
                        flag = 0;
                    }

                    // 最終書き込みの場合はNorifyを設定
                    if ( isEnd == true && waitFinish == false ) {
                        finishPos = size + writeSize;
                        player->pDSBuffer_->GetCurrentPosition( &prePlayPos, 0 );
                        waitFinish = true;
                    }
                }
                break;

            case STATE_STOP:
                flag = 0;	// 止めると前半書き込みから始まるため
                isEnd = false;
                finishPos = 0;
                prePlayPos = 0;
                break;

            case STATE_PAUSE:
                break;

            default:
                break;
            }

            // 終了位置判定チェック
            if ( isEnd == true ) {
                DWORD curPlayPos;
                player->pDSBuffer_->GetCurrentPosition( &curPlayPos, 0 );
                if ( curPlayPos < prePlayPos ) {
                    // バッファをループした瞬間
                    //if ( prePlayPos <= finishPos ) {
                    if ( prePlayPos <= finishPos || finishPos <= curPlayPos ) {
                        // 終了宣言
                        player->stop();
                    }
                } else {
                    if ( prePlayPos <= finishPos && finishPos <= curPlayPos ) {
                        // 終了宣言
                        player->stop();
                    }
                }
                prePlayPos = curPlayPos;
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
        pDSBuffer_->Play( 0, 0, DSBPLAY_LOOPING );
        state_ = STATE_PLAY;
        return true;
    }

    //! 一時停止
    void PCMPlayer::pause() {
        if ( state_ == STATE_PLAY ) {
            // 動いていたら止める
            pDSBuffer_->Stop();
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
        pDSBuffer_->Stop();

        // バッファの頭出し
        initializeBuffer();
    }

    //! 音量を変える
    void PCMPlayer::setVolume( int volume ) {
        if ( isReady() == true ) {
            pDSBuffer_->SetVolume( volume );
        }
    }

    //! パンの位置を変える
    void PCMPlayer::setPan( int pan ) {
        if ( isReady() == true ) {
            pDSBuffer_->SetPan( pan );
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

}
