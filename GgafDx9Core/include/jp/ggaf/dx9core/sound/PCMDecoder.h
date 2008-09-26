// PCMDecoder.h
//

#ifndef IKD_DIX_PCMDECODER_H
#define IKD_DIX_PCMDECODER_H

//#include <windows.h>
//#include <mmsystem.h>

	class PCMDecoder {
	public:
		//! コンストラクタ
		PCMDecoder();

		//! デストラクタ
		virtual ~PCMDecoder();

		//! セグメント取得
		virtual bool getSegment( char* buffer, unsigned int size, unsigned int* writeSize, bool* isEnd ) = 0;

		//! 頭出し
		virtual void setHead() = 0;

	public:
		//! クリア
		virtual void clear();

		//! ループフラグ取得
		bool isLoop();

		//! 準備できた？
		bool isReady();

		//! ループを設定
		void setLoop( bool isLoop );

		//! WAVEFORMATEX構造体を取得
		bool getWaveFormatEx( WAVEFORMATEX& waveFormatEx );

	protected:
		//! 準備フラグ設定
		void setReady( bool isReady );

		//! チャンネル数設定
		void setChannelNum( unsigned int channeNum );

		//! サンプリングレートを設定
		void setSamplingRate( unsigned int samplingRate );

		//! ビットレートを設定
		void setBitRate( unsigned int bitRate );

	protected:
		bool isLoop_;				//!< ループする？
		bool isReady_;				//!< 準備できた？
		unsigned int channelNum_;	//!< チャンネル数
		unsigned int samplingRate_;	//!< サンプリングレート
		unsigned int bitRate_;		//!< ビットレート
	};

#endif
