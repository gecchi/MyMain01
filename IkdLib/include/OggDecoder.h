// OggDecoder.h
//

#ifndef IKD_DIX_OGGDECODER_H
#define IKD_DIX_OGGDECODER_H

#include "vorbis/vorbisfile.h"
#include "PCMDecoder.h"
#include "OggVorbisResource.h"
#include "DixSmartPtr.h"

namespace Dix {
	class OggDecoder : public PCMDecoder {
	public:
		OggDecoder();
		OggDecoder( sp< OggVorbisResource > oggVorbisResource );
		virtual ~OggDecoder();

		//! クリア
		virtual void clear();

		//! セグメント取得
		virtual bool getSegment( char* buffer, unsigned int size, unsigned int* writeSize, bool* isEnd );

		//! 頭出し
		virtual void setHead();

		//! 安全なクローンを生成
		virtual sp< PCMDecoder > createClone();

		//! サウンドをセット
		virtual bool setResource( sp< OggVorbisResource > oggVorbisResource );

	protected:
		sp< OggVorbisResource > oggVorbisResource_;
	};
}

#endif