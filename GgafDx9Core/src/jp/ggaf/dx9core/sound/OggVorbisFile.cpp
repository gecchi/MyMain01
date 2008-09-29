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
	//	if (m_lpFile) {
	//		fclose(m_lpFile);
	//	}

}

//! �N���A
void OggVorbisFile::clear() {
	memset(filePath_, 0, sizeof(filePath_));
	OggVorbisResource::clear();
}

//! ���S�ȃN���[�����쐬
OggVorbisResource* OggVorbisFile::createClone() {
	OggVorbisFile* obj = NEW OggVorbisFile;
	if (obj->open(filePath_) == false) {
		return 0;
	}
	//OggVorbisFile* spObj( obj );
	return obj;
}

//! Ogg�t�@�C���I�[�v��
bool OggVorbisFile::open(const char* filePath) {

	clear();
//	FILE *pFile = fopen((char*) filePath, "rb");
//	if (!pFile) {
//		clear();
//		return false;
//	} else {
//		int ret = ov_open(pFile, &oggVorbisFile_, NULL, 0);
//		if (ret) {
//			fclose(pFile);
//		} else {
//			clear();
//			return false;
//		}

				// Ogg�t�@�C���I�[�v��
				if ( ov_fopen( (char*)filePath, &oggVorbisFile_ ) != 0 ) {
					// ���s
					clear();
					return false;
				}

		strcpy(filePath_, filePath);
		isReady_ = true;

		return true;
//	}
}
