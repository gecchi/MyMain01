#include "jp/ggaf/dxcore/sound/IkdLib/OggVorbisFile.h"

#include "jp/ggaf/core/exception/GgafCriticalException.h"

using namespace IkdLib;

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

void OggVorbisFile::clear() {
    memset(_filepath, 0, sizeof(_filepath));
    OggVorbisResource::clear();
}

OggVorbisResource* OggVorbisFile::createClone() {
    OggVorbisFile * obj = NEW
    OggVorbisFile;
    if (obj->open(_filepath) == false) {
        return 0;
    }
    return obj;
}

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
