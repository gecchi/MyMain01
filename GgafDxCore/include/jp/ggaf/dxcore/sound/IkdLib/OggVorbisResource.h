// �{�v���O�����́A<BR>
// �u���~�i�܂�؂��j����[�ǂ��ƃR���v http://marupeke296.com/index.html <BR>
// �T�C�g���R���e���c�� �uOgg Vorbis����ҁv http://marupeke296.com/OGG_main.html <BR>
// �̃T���v���v���O�������I���W�i���ł��B<BR>
// �ꕔ�ύX���Ďg�p���Ă��܂��B<BR>
//                                            2009/01/13 Masatoshi Tsuge<BR>

#ifndef IKD_DIX_OGGVORBISRESOURCE_H
#define IKD_DIX_OGGVORBISRESOURCE_H

#include "vorbis/vorbisfile.h"

namespace Dix {
class OggVorbisResource {
public:
    OggVorbisResource() :
            _is_ready(false) {
        memset(&_ogg_vorbis_file, 0, sizeof(OggVorbis_File));
    }

    virtual ~OggVorbisResource() {
        clear();
    }

    // �N���A
    virtual void clear() {
        ov_clear(&_ogg_vorbis_file);
        memset(&_ogg_vorbis_file, 0, sizeof(OggVorbis_File));
        _is_ready = false;
    }

    // OggVorbis_File�\���̂��擾
    virtual OggVorbis_File& getOggVorbisFile() {
        return _ogg_vorbis_file;
    }

    // ���S�ȃN���[�����쐬
    virtual OggVorbisResource* createClone() = 0;

    // �����ł����H
    bool isReady() {
        return _is_ready;
    }

protected:
    OggVorbis_File _ogg_vorbis_file; // OggVorbis_File�\����
    bool _is_ready; // �����ł����H
};
}

#endif
