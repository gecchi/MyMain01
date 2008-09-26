// OggDecoder.h
//

#ifndef IKD_DIX_OGGDECODER_H
#define IKD_DIX_OGGDECODER_H

//#include "vorbis/vorbisfile.h"
//#include "PCMDecoder.h"
//#include "OggVorbisResource.h"
//#include "DixSmartPtr.h"

	class OggDecoder : public PCMDecoder {
	public:
		OggDecoder();
		OggDecoder( OggVorbisResource* oggVorbisResource );
		virtual ~OggDecoder();

		//! クリア
		virtual void clear();

		//! セグメント取得
		virtual bool getSegment( char* buffer, unsigned int size, unsigned int* writeSize, bool* isEnd );

		//! 頭出し
		virtual void setHead();

		//! サウンドをセット
		virtual bool setResource( OggVorbisResource* oggVorbisResource );

	protected:
		OggVorbisResource* oggVorbisResource_;
	};

#endif
