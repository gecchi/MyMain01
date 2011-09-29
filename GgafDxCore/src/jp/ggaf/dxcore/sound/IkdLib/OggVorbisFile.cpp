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
        throwGgafCriticalException(filePath << "�� open �Ɏ��s���܂����B");
    }
}

OggVorbisFile::~OggVorbisFile() {
}

//! �N���A
void OggVorbisFile::clear() {
    memset(_filepath, 0, sizeof(_filepath));
    OggVorbisResource::clear();
}

//! ���S�ȃN���[�����쐬
OggVorbisResource* OggVorbisFile::createClone() {
    OggVorbisFile * obj = NEW
    OggVorbisFile;
    if (obj->open(_filepath) == false) {
        return 0;
    }
    return obj;
}

//! Ogg�t�@�C���I�[�v��
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
