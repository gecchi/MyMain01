// PCMPlayer.h
//

#ifndef IKD_DIX_PCMPLAYER_H
#define IKD_DIX_PCMPLAYER_H

//#include "DixSmartPtr.h"
//#include "PCMDecoder.h"
//#include "DixComPtr.h"
//#include "dsound.h"

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
		PCMPlayer( Com_ptr< IDirectSound8 > cpDS8 );
		PCMPlayer( Com_ptr< IDirectSound8 > cpDS8, sp< PCMDecoder > spDecoder );

		~PCMPlayer();

		//! デバイス設定
		void setDevice( Com_ptr< IDirectSound8 > cpDS8 );

		//! PCMデコーダを設定
		bool setDecoder( sp< PCMDecoder > pcmDecoder );

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

	private:
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

		//! 状態取得
		STATE getState();

	private:
		sp< PCMDecoder >				spPCMDecoder_;		//!< 再生対象デコード
		WAVEFORMATEX					waveFormat_;		//!< WAVEFORMATEX構造体
		DSBUFFERDESC					DSBufferDesc_;		//!< DSBUFFERDESC構造体
		Com_ptr< IDirectSound8 >		cpDS8_;				//!< サウンドデバイス
		Com_ptr< IDirectSoundBuffer8 >	cpDSBuffer_;		//!< セカンダリバッファ
		bool							isReady_;			//!< 準備できた？
		unsigned int					threadHandle_;		//!< ストリーム再生スレッドハンドル
		bool							isTerminate_;		//!< スレッド停止
		bool							isLoop_;			//!< ループする？
		STATE							state_;				//!< 再生状態
	};
}

#endif
