#include "stdafx.h"
using namespace std;
using namespace GgafCore;
using namespace GgafDxCore;
using namespace Dix;

OggVorbisFile::OggVorbisFile() {
}

OggVorbisFile::OggVorbisFile(const char* filePath) {
    if (open(filePath)) {
        //OK
    } else {
        throwGgafCriticalException(filePath << "の open に失敗しました。");
    }
}

OggVorbisFile::~OggVorbisFile() {
}

//! クリア
void OggVorbisFile::clear() {
    memset(_filepath, 0, sizeof(_filepath));
    OggVorbisResource::clear();
}

//! 安全なクローンを作成
OggVorbisResource* OggVorbisFile::createClone() {
    OggVorbisFile * obj = NEW
    OggVorbisFile;
    if (obj->open(_filepath) == false) {
        return 0;
    }
    return obj;
}

//! Oggファイルオープン
bool OggVorbisFile::open(const char* filePath) {

    clear();

    // Oggファイルオープン
    if (ov_fopen((char*)filePath, &_ogg_vorbis_file) != 0) {
        // 失敗
        clear();
        return false;
    }

    strcpy(_filepath, filePath);
    _is_ready = true;

    return true;
}
