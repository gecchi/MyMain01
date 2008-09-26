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

		//! �N���A
		virtual void clear();

		//! �Z�O�����g�擾
		virtual bool getSegment( char* buffer, unsigned int size, unsigned int* writeSize, bool* isEnd );

		//! ���o��
		virtual void setHead();

		//! �T�E���h���Z�b�g
		virtual bool setResource( OggVorbisResource* oggVorbisResource );

	protected:
		OggVorbisResource* oggVorbisResource_;
	};

#endif
