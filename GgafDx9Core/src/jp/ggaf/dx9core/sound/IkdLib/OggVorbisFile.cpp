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
        throwGgafCriticalException(filePath << "の open に失敗しました。");
    }
}

OggVorbisFile::~OggVorbisFile() {
}

//! クリア
void OggVorbisFile::clear() {
    memset( filePath_, 0, sizeof( filePath_ ) );
    OggVorbisResource::clear();
}

//! 安全なクローンを作成
OggVorbisResource* OggVorbisFile::createClone() {
    OggVorbisFile* obj = NEW OggVorbisFile;
    if ( obj->open( filePath_ ) == false ) {
        return 0;
    }
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
