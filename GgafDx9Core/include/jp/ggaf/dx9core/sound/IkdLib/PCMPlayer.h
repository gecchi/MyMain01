// 本プログラムは、<BR>
// 「○×（まるぺけ）つくろーどっとコム」 http://marupeke296.com/index.html <BR>
// サイト内コンテンツの 「Ogg Vorbis入門編」 http://marupeke296.com/OGG_main.html <BR>
// のサンプルプログラムのがオリジナルです。<BR>
// 一部変更して使用しています。<BR>
//                                            2009/01/13 Masatoshi Tsuge<BR>


#ifndef IKD_DIX_PCMPLAYER_H
#define IKD_DIX_PCMPLAYER_H

namespace Dix {
    class PCMPlayer {
    public:
        // 再生状態
        enum STATE {
            STATE_NONE,
            STATE_PLAY,
            STATE_PAUSE,
            STATE_STOP
        };

    public:
        PCMPlayer();
        PCMPlayer( IDirectSound8* pDS8 );
        PCMPlayer( IDirectSound8* pDS8, PCMDecoder* spDecoder );

        virtual ~PCMPlayer(); //virtual 追加

        //! デバイス設定
        void setDevice(IDirectSound8* pDS8 );

        //! PCMデコーダを設定
        bool setDecoder( PCMDecoder* pcmDecoder );
        //! 再生
        bool play( bool isLoop );

        //! 一時停止
        void pause();

        //! 停止
        void stop();

        //! 音量を変える
        void setVolume( int volume );

        //! パンの位置を変える
        void setPan( int pan );

        //! クリア
        void clear();

        //! 状態取得
        STATE getState();


    public:
        //! 再生中のスレッドを停止
        void terminateThread();

        //! バッファを初期化する
        bool initializeBuffer();

        //! バッファコピースレッド生成
        static void __cdecl streamThread( void* player );

        //! 準備できた？
        bool isReady();

        //! 再生中？
        bool isPlaying();


    public:
        IDirectSound8*                  pDS8_;				//!< サウンドデバイス
        IDirectSoundBuffer8*            pDSBuffer_;		//!< セカンダリバッファ
        PCMDecoder*                     pPCMDecoder_;
        WAVEFORMATEX                    waveFormat_;        //!< WAVEFORMATEX構造体
        DSBUFFERDESC                    DSBufferDesc_;      //!< DSBUFFERDESC構造体
        bool							isReady_;			//!< 準備できた？
        unsigned int					threadHandle_;		//!< ストリーム再生スレッドハンドル
        bool							isTerminate_;		//!< スレッド停止
        bool							isLoop_;			//!< ループする？
        STATE							state_;				//!< 再生状態
    };
}

#endif
