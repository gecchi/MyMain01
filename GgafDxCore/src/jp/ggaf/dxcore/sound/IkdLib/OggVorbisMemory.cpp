#include "stdafx.h"

using namespace GgafCore;
using namespace GgafDxCore;
using namespace IkdLib;

OggVorbisMemory::OggVorbisMemory() :
        _size(0), _pos_current(0)
{
}

OggVorbisMemory::OggVorbisMemory(const char* prm_filepath) :
        _size(0), _pos_current(0)
{
    createBuffer(prm_filepath);
}

OggVorbisMemory::~OggVorbisMemory() {
    clear();
}

void OggVorbisMemory::clear() {
    _size = 0;
    _pos_current = 0;
    _buffer = 0;
    OggVorbisResource::clear();
}

OggVorbisResource* OggVorbisMemory::createClone() {
    if (_is_ready == false) {
        return 0;
    }
    OggVorbisMemory * obj = NEW
    OggVorbisMemory;
    *obj = *this; //�����F����̓t�B�[���h���̒l�R�s�[
    obj->_pos_current = 0;

    // �R�[���o�b�N�o�^
    ov_callbacks callbacks = {&OggVorbisMemory::read, &OggVorbisMemory::seek, &OggVorbisMemory::close, &OggVorbisMemory::tell};

    // Ogg�I�[�v��
    if (ov_open_callbacks(obj, &obj->_ogg_vorbis_file, 0, 0, callbacks) != 0) {
        obj->clear();
        GGAF_DELETE(obj);
        return 0;
    }
    return obj;
}

size_t OggVorbisMemory::read(void* prm_buffer, size_t prm_size, size_t prm_max_count, void* prm_stream) {
    if (prm_buffer == 0) {
        return 0;
    }

    // �X�g���[������I�u�W�F�N�g�̃|�C���^���擾
    OggVorbisMemory *p = (OggVorbisMemory*)prm_stream;

    // �擾�\�J�E���g�����Z�o
    int resSize = p->_size - p->_pos_current;
    size_t count = resSize / prm_size;
    if (count > prm_max_count) {
        count = prm_max_count;
    }
    memcpy(prm_buffer, p->_buffer + p->_pos_current, prm_size * count);

    // �|�C���^�ʒu���ړ�
    p->_pos_current += prm_size * count;

    return count;
}

int OggVorbisMemory::seek(void* prm_buffer, ogg_int64_t offset, int flag) {

    // �X�g���[������I�u�W�F�N�g�̃|�C���^���擾
    OggVorbisMemory *p = (OggVorbisMemory*)prm_buffer;

    switch (flag) {
        case SEEK_CUR:
            p->_pos_current += offset;
            break;

        case SEEK_END:
            p->_pos_current = p->_size + offset;
            break;

        case SEEK_SET:
            p->_pos_current = offset;
            break;

        default:
            return -1;
    }

    if (p->_pos_current > p->_size) {
        p->_pos_current = p->_size;
        return -1;
    } else if (p->_pos_current < 0) {
        p->_pos_current = 0;
        return -1;
    }

    return 0;
}

int OggVorbisMemory::close(void* prm_buffer) {
    // �f�X�g���N�^��N���A����ɏ������Ă���Ă���̂�
    // �����͉������Ȃ�
    return 0;
}

long OggVorbisMemory::tell(void* prm_buffer) {
    OggVorbisMemory *p = (OggVorbisMemory*)prm_buffer;
    return p->_pos_current;
}

bool OggVorbisMemory::createBuffer(const char* prm_filepath) {

    clear();

    // �t�@�C�����o�b�t�@�ɃR�s�[
    FILE *f = fopen(prm_filepath, "rb");
    if (f == 0) {
        return false; // �I�[�v�����s
    }
    fseek(f, 0, SEEK_END);
    _size = ftell(f);
    fseek(f, 0, SEEK_SET);

    _buffer = NEW
    char[ _size ];
    size_t readSize = fread(_buffer, _size, 1, f);
    if (readSize != 1) {
        // �����ςł�
        clear();
        return false;
    }

    // �R�[���o�b�N�o�^
    ov_callbacks callbacks = {&OggVorbisMemory::read, &OggVorbisMemory::seek, &OggVorbisMemory::close, &OggVorbisMemory::tell};

    // Ogg�I�[�v��
    if (ov_open_callbacks(this, &_ogg_vorbis_file, 0, 0, callbacks) != 0) {
        clear();
        return false;
    }

    strcpy(_filepath, prm_filepath);

    _is_ready = true;

    return true;
}

