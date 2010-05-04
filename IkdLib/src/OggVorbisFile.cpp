// OggVorbisFile.cpp
//
#include "GgafCommonHeader.h"
#include "OggVorbisFile.h"
#include "string.h"

#pragma warning ( disable : 4267 )
#pragma warning ( disable : 4244 )
#pragma warning ( disable : 4996 )


namespace Dix {
	OggVorbisFile::OggVorbisFile() {
	}

	OggVorbisFile::OggVorbisFile( const char* filePath ) {
		open( filePath );
	}

	OggVorbisFile::~OggVorbisFile() {
	}

	//! クリア
	void OggVorbisFile::clear() {
		memset( filePath_, 0, sizeof( filePath_ ) );
		OggVorbisResource::clear();
	}

	//! 安全なクローンを作成
	//sp< OggVorbisResource > OggVorbisFile::createClone() {
	OggVorbisResource* OggVorbisFile::createClone() {
		OggVorbisFile* obj = NEW OggVorbisFile;
		if ( obj->open( filePath_ ) == false ) {
			return 0;
		}

//		sp< OggVorbisFile > spObj( obj );
//		return spObj;
		return obj;
	}

	//! Oggファイルオープン
	bool OggVorbisFile::open( const char* filePath ) {

		clear();

		// Oggファイルオープン
		if ( ov_fopen( (char*)filePath, &oggVorbisFile_ ) != 0 ) {
			// 失敗
			clear();
			return false;
		}

		strcpy( filePath_, filePath );
		isReady_ = true;

		return true;
	}
}
