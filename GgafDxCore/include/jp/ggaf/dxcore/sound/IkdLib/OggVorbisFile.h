#ifndef IKD_DIX_OGGVORBISFILE_H
#define IKD_DIX_OGGVORBISFILE_H
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/dxcore/sound/IkdLib/OggVorbisResource.h"

namespace IkdLib {

/**
 * OggVorbisFile .
 * �{�v���O�����́A<BR>
 * �u���~�i�܂�؂��j����[�ǂ��ƃR���v http://marupeke296.com/index.html <BR>
 * �T�C�g���R���e���c�� �uOgg Vorbis����ҁv http://marupeke296.com/OGG_main.html <BR>
 * �̃T���v���v���O�������I���W�i���ł��B<BR>
 * �ύX���Ďg�p���Ă��܂��B<BR>
 *                                            2009/01/13 Masatoshi Tsuge<BR>
 * @author  IKD
 */
class OggVorbisFile : public OggVorbisResource {
public:
    OggVorbisFile();
    OggVorbisFile(const char* filePath);

    virtual ~OggVorbisFile();

    //! �N���A
    virtual void clear();

    //! ���S�ȃN���[�����쐬
    virtual OggVorbisResource* createClone();

    //! Ogg�t�@�C���I�[�v��
    bool open(const char* filePath);

protected:
    char _filepath[1024];	// �t�@�C����
};

}

#endif
