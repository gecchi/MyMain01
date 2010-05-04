// OggVorbisResource.h
//

#ifndef IKD_DIX_OGGVORBISRESOURCE_H
#define IKD_DIX_OGGVORBISRESOURCE_H

#include "vorbis/vorbisfile.h"
//#include "DixSmartPtr.hpp"
#include "memory.h"

namespace Dix {
	class OggVorbisResource {
	public:
		OggVorbisResource() : isReady_( false ){
			memset( &oggVorbisFile_, 0, sizeof( OggVorbis_File ) );
		}

		virtual ~OggVorbisResource(){
			clear();
		}

		// �N���A
		virtual void clear() {
		    ov_clear( &oggVorbisFile_ );
			memset( &oggVorbisFile_, 0, sizeof( OggVorbis_File ) );
			isReady_ = false;
		}

		// OggVorbis_File�\���̂��擾
		virtual OggVorbis_File& getOggVorbisFile() {
			return oggVorbisFile_;
		}

		// ���S�ȃN���[�����쐬
		//virtual sp< OggVorbisResource > createClone() = 0;
		virtual OggVorbisResource* createClone() = 0;

		// �����ł����H
		bool isReady() {
			return isReady_;
		}

	protected:
		OggVorbis_File	oggVorbisFile_;	// OggVorbis_File�\����
		bool			isReady_;		// �����ł����H
	};
}

#endif
