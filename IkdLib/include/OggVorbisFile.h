// OggVorbisFile.h
//

#ifndef IKD_DIX_OGGVORBISFILE_H
#define IKD_DIX_OGGVORBISFILE_H

#include "OggVorbisResource.h"
#include "DixSmartPtr.hpp"
#include "memory.h"

namespace Dix {
	class OggVorbisFile : public OggVorbisResource {
	public:
		OggVorbisFile();
		OggVorbisFile( const char* filePath );

		virtual ~OggVorbisFile();

		//! �N���A
		virtual void clear();

		//! ���S�ȃN���[�����쐬
		virtual sp< OggVorbisResource > createClone();

		//! Ogg�t�@�C���I�[�v��
		bool open( const char* filePath );

	protected:
		char filePath_[ 256 ];	// �t�@�C����
	};
}

#endif