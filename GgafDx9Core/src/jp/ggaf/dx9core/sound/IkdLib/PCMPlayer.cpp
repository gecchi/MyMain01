#include "stdafx.h"

using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace Dix;

// PCMPlayer.cpp
//
//#include "GgafDx9CommonHeader.h"
//#include "PCMPlayer.h"
//#include <process.h>
//#include <stdio.h>

#ifdef _MSC_VER

#else
#define NULL 0
#endif

namespace {
    double playTime_g = 1;	// 1 sec.
}

//namespace Dix {
    PCMPlayer::PCMPlayer() :
        pDS8_			( NULL ),
        pDSBuffer_		( NULL ),
        pPCMDecoder_   ( NULL ),
        waveFormat_     (),
        DSBufferDesc_   (),
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
        pPCMDecoder_   ( NULL ),
        waveFormat_     (),
        DSBufferDesc_   (),
        isReady_		( false ),
        threadHandle_	( 0 ),
        isTerminate_	( false ),
        isLoop_			( true ),
        state_			( STATE_NONE )
    {
        clear();
    }

    PCMPlayer::PCMPlayer( IDirectSound8* pDS8, PCMDecoder* spDecoder ) :
        pDS8_			( pDS8 ),
        pDSBuffer_		( NULL ),
        pPCMDecoder_   ( NULL ),
        waveFormat_     (),
        DSBufferDesc_   (),
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
        //正しく解放されない場合の原因究明のため、
        //スマートポインタを外してdeleteとReleaseで解放
        _TRACE_("PCMPlayer::~PCMPlayer() begin");
        _TRACE_("terminateThread();");
        terminateThread();
        _TRACE_("RELEASE_IMPOSSIBLE_NULL(pDSBuffer_);");
        RELEASE_IMPOSSIBLE_NULL(pDSBuffer_);
        _TRACE_("DELETE_IMPOSSIBLE_NULL(pPCMDecoder_);");
        DELETE_IMPOSSIBLE_NULL(pPCMDecoder_);
        _TRACE_("PCMPlayer::~PCMPlayer() end");
    }

    //! クリア
    void PCMPlayer::clear() {
        terminateThread();
        memset( &DSBufferDesc_, 0, sizeof( DSBufferDesc_ ) );
        memset( &waveFormat_, 0, sizeof( waveFormat_ ) );
        if (pDSBuffer_) {
            RELEASE_IMPOSSIBLE_NULL(pDSBuffer_);
            pDSBuffer_ = NULL;
        }
        isReady_ = false;
        state_ = STATE_NONE;
    }

    //! 再生中のスレッドを停止
    void PCMPlayer::terminateThread() {
        if ( threadHandle_ != 0 ) {
            isTerminate_ = true;
            bool end = false;
            int wait = 0;
            while( !end ) {
                if (wait > 10*100) {
                    //1秒待っても駄目な場合は警告を出して強制終了
                    _TRACE_("＜警告＞ PCMPlayer::terminateThread() 失敗しました。原因不明。頻発する場合は調査が必要！！");
                   break;
                }
                DWORD flag = WaitForSingleObject( (HANDLE)(__int64)threadHandle_, 10 );
                switch( flag ) {
                case WAIT_OBJECT_0:
                    // スレッドが終わった
                    end = true;
                    break;
                case WAIT_TIMEOUT:
                    wait++;
                    isTerminate_ = true;
                    // まだ終了していないので待機
                    break;
                case WAIT_FAILED:
                    // 失敗しているようです
                    end = true;
                    break;
                }
                //Sleep(1);
            }
            isTerminate_ = false;
            threadHandle_ = 0;
        } else {
            _TRACE_("PCMPlayer::terminateThread() スレッドはありません。多分。this="<<this<<"/isTerminate_="<<isTerminate_);
        }
    }

    //! デバイス設定
    void PCMPlayer::setDevice(IDirectSound8* pDS8 ) {
        pDS8_ = pDS8;
    }


    //! PCMデコーダを設定
    bool PCMPlayer::setDecoder( PCMDecoder* pcmDecoder ) {
        if ( pDS8_ == NULL || pcmDecoder == NULL || pcmDecoder->isReady() == false ) {
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
        pPCMDecoder_ = pcmDecoder->createClone();

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
        if (pPCMDecoder_ == NULL) {
            return false;
        }

        pPCMDecoder_->setHead();	// 頭出し
        HRESULT hr = pDSBuffer_->SetCurrentPosition( 0 );
        checkDxException(hr, DS_OK , "PCMPlayer::initializeBuffer()  SetCurrentPosition( 0 ) に失敗しました。");
        // バッファをロックして初期データ書き込み
        for (int i = 0; i < 10; i++) { //最大１０回試行する
                                       //これは DSBLOCK_ENTIREBUFFER （全体ロック)が
                                       //仕組上特定のタイミングで失敗することは避けれないと考えたため。
                                       //TODO:はたしてこんな方法でいいのだろうか。
                                       //TODO:極極稀に落ちるのはなぜか？。環境依存なのか？完全に納得していない。

            void* AP1 = 0, *AP2 = 0;
            DWORD AB1 = 0, AB2  = 0;
            hr = pDSBuffer_->Lock( 0, 0, &AP1, &AB1, &AP2, &AB2, DSBLOCK_ENTIREBUFFER );
            //checkDxException(hr, DS_OK , "PCMPlayer::initializeBuffer() Lock に失敗しました。"); //←これが起こる場合が稀にある。
                                                                                                   //  起こった場合、リークしていた。
            if ( SUCCEEDED(hr) ) {
                pPCMDecoder_->getSegment( (char*)AP1, AB1, 0, 0 );
                hr = pDSBuffer_->Unlock( AP1, AB1, AP2, AB2 );
                checkDxException(hr, DS_OK , "PCMPlayer::initializeBuffer() Unlock に失敗しました。");
                break;
            } else {
                //ロック失敗時
                if (i < 10) {
                    _TRACE_("PCMPlayer::initializeBuffer() Lockに失敗 i="<<i<<" ");
                    _TRACE_("hr="<<hr<<" "<<DXGetErrorString(hr)<<" "<<DXGetErrorDescription(hr));
                    hr = pDSBuffer_->Unlock( AP1, AB1, AP2, AB2 );
                    Sleep(5);
                    continue; //もう一回頑張る
                } else {
                    //あきらめる
                    _TRACE_("PCMPlayer::initializeBuffer() Lockをあきらめて解放します");
                    clear();
                    return false;
                }
            }
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
                        player->pPCMDecoder_->getSegment( (char*)AP1, AB1, &writeSize, &isEnd );
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
                        player->pPCMDecoder_->getSegment( (char*)AP1, AB1, &writeSize, &isEnd );
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
        pPCMDecoder_->setLoop( isLoop );
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
        bool r = initializeBuffer();
        _TRACE_("PCMPlayer::stop() initializeBuffer() = "<<r);
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

//}
