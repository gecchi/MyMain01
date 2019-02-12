#include "jp/ggaf/dx/sound/IkdLib/OggVorbisFile.h"

#include "jp/ggaf/core/exception/CriticalException.h"

using namespace IkdLib;

OggVorbisFile::OggVorbisFile() {
}

OggVorbisFile::OggVorbisFile(const char* filePath) {
    if (open(filePath)) {
        //OK
    } else {
        throwCriticalException(filePath << "�� open �Ɏ��s���܂����B");
    }
}

OggVorbisFile::~OggVorbisFile() {
}

void OggVorbisFile::clear() {
    memset(_filepath, 0, sizeof(_filepath));
    OggVorbisResource::clear();
}

OggVorbisResource* OggVorbisFile::createClone() {
    OggVorbisFile * obj = NEW OggVorbisFile;
    if (obj->open(_filepath) == false) {
        return 0;
    }
    return obj;
}

bool OggVorbisFile::open(const char* filePath) {

    clear();
    // Ogg�t�@�C���I�[�v��
    if (ov_fopen((char*)filePath, &_ogg_vorbis_file) != 0) {
        // ���s
        clear();
        return false;
    }

    strcpy(_filepath, filePath);
    _is_ready = true;

    return true;
}
