#include "stdafx.h"

// OggVorbisFile.cpp
//

//#include "OggVorbisFile.h"
//#include "string.h"

//#pragma warning ( disable : 4267 )
//#pragma warning ( disable : 4244 )
//#pragma warning ( disable : 4996 )


OggVorbisFile::OggVorbisFile() {
}

OggVorbisFile::OggVorbisFile(const char* filePath) {
	open(filePath);
}

OggVorbisFile::~OggVorbisFile() {
}

//! クリア
void OggVorbisFile::clear() {
	memset(filePath_, 0, sizeof(filePath_));
	OggVorbisResource::clear();
}

//! 安全なクローンを作成
OggVorbisResource* OggVorbisFile::createClone() {
	OggVorbisFile* obj = NEW OggVorbisFile;
	if ( obj->open( filePath_ ) == false ){
		return 0;
	}
	//OggVorbisFile* spObj( obj );
	return obj;
}

//! Oggファイルオープン
bool OggVorbisFile::open(const char* filePath) {

	clear();
	m_lpFile = fopen(filePath, "rb");
	if (m_lpFile == NULL) {
		return false;
	}

	if (ov_open(m_lpFile, &oggVorbisFile_, NULL, 0) < 0) {
		clear();
		fclose(m_lpFile);
		return false;
	}

	//		// Oggファイルオープン
	//		if ( ov_fopen( (char*)filePath, &oggVorbisFile_ ) != 0 ) {
	//			// 失敗
	//			clear();
	//			return false;
	//		}

	strcpy(filePath_, filePath);
	isReady_ = true;

	return true;
}
