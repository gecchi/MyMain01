#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDx9Core;
using namespace Dix;

OggVorbisFile::OggVorbisFile() {
}

OggVorbisFile::OggVorbisFile( const char* filePath ) {
    if (open( filePath )) {
        //OK
    } else {
        throwGgafCriticalException(filePath << "�� open �Ɏ��s���܂����B");
    }
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
    OggVorbisFile* obj = NEW OggVorbisFile;
    if ( obj->open( filePath_ ) == false ) {
        return 0;
    }
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
