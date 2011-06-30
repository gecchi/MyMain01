// �{�v���O�����́A<BR>
// �u���~�i�܂�؂��j����[�ǂ��ƃR���v http://marupeke296.com/index.html <BR>
// �T�C�g���R���e���c�� �uOgg Vorbis����ҁv http://marupeke296.com/OGG_main.html <BR>
// �̃T���v���v���O�������I���W�i���ł��B<BR>
// �ꕔ�ύX���Ďg�p���Ă��܂��B<BR>
//                                            2009/01/13 Masatoshi Tsuge<BR>

#ifndef IKD_DIX_OGGDECODER_H
#define IKD_DIX_OGGDECODER_H

#include "vorbis/vorbisfile.h"

namespace Dix {
    class OggDecoder : public PCMDecoder {
    public:
        OggDecoder();
        OggDecoder(OggVorbisResource* pOggVorbisResource );
        virtual ~OggDecoder();

        //! �N���A
        virtual void clear();

        //! �Z�O�����g�擾
        virtual bool getSegment( char* buffer, unsigned int size, unsigned int* writeSize, bool* isEnd );

        //! ���o��
        virtual void setHead();

        //! �N���[���𐶐�
        virtual PCMDecoder* createClone();

        //! �T�E���h���Z�b�g
        virtual bool setResource(OggVorbisResource* pOggVorbisResource );

    protected:
        OggVorbisResource* pOggVorbisResource_;
    };
}

#endif
