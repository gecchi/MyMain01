#include "stdafx.h"

// OggVorbisFile.cpp
//

//#include "OggVorbisFile.h"
//#include "string.h"

//#pragma warning ( disable : 4267 )
//#pragma warning ( disable : 4244 )
//#pragma warning ( disable : 4996 )


namespace Dix {
	OggVorbisFile::OggVorbisFile() {
	}

	OggVorbisFile::OggVorbisFile( const char* filePath ) {
		open( filePath );
	}

	OggVorbisFile::~OggVorbisFile() {
	}

	//! �N���A
	void OggVorbisFile::clear() {
		memset( filePath_, 0, sizeof( filePath_ ) );
		OggVorbisResource::clear();
	}

	//! ���S�ȃN���[�����쐬
	OggVorbisResource* OggVorbisFile::createClone() {
		OggVorbisFile* obj = new OggVorbisFile;
		if ( obj->open( filePath_ ) == false ) {
			return 0;
		}

		//OggVorbisFile* spObj( obj );
		return obj;
	}

	//! Ogg�t�@�C���I�[�v��
	bool OggVorbisFile::open( const char* filePath ) {

		clear();

		// Ogg�t�@�C���I�[�v��
		if ( ov_fopen( (char*)filePath, &oggVorbisFile_ ) != 0 ) {
			// ���s
			clear();
			return false;
		}

		strcpy( filePath_, filePath );
		isReady_ = true;

		return true;
	}
}
