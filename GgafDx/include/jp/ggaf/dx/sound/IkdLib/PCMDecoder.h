#ifndef IKD_DIX_PCMDECODER_H
#define IKD_DIX_PCMDECODER_H
#include "jp/ggaf/GgafDxCommonHeader.h"
#include <windows.h>

namespace IkdLib {

/**
 * PCMDecoder .
 * �{�v���O�����́A<BR>
 * �u���~�i�܂�؂��j����[�ǂ��ƃR���v http://marupeke296.com/index.html <BR>
 * �T�C�g���R���e���c�� �uOgg Vorbis����ҁv http://marupeke296.com/OGG_main.html <BR>
 * �̃T���v���v���O�������I���W�i���ł��B<BR>
 * �ύX���Ďg�p���Ă��܂��B<BR>
 *                                            2009/01/13 Masatoshi Tsuge<BR>
 * @author  IKD
 */
class PCMDecoder {
public:
    //! �R���X�g���N�^
    PCMDecoder();

    //! �f�X�g���N�^
    virtual ~PCMDecoder();

    //! �Z�O�����g�擾
    virtual bool getSegment(char* prm_buffer,
                            unsigned int prm_size,
                            unsigned int* pUInt_write_size,
                            bool* pBool_is_end) = 0;

    //! ���o��
    virtual void setHead() = 0;

    //! ���S�ȃN���[���𐶐�
    virtual PCMDecoder* createClone() = 0;

public:
    //! �N���A
    virtual void clear();

    //! ���[�v�t���O�擾
    bool isLooping();

    //! �����ł����H
    bool isReady();

    //! ���[�v��ݒ�
    void setLooping(bool prm_is_looping);

    //! WAVEFORMATEX�\���̂��擾
    bool getWaveFormatEx(WAVEFORMATEX* out_waveFormatEx);

protected:
    //! �����t���O�ݒ�
    void setReady(bool prm_is_ready);

    //! �`�����l�����ݒ�
    void setChannelNum(unsigned int prm_num_channel);

    //! �T���v�����O���[�g��ݒ�
    void setSamplingRate(unsigned int prm_sampling_rate);

    //! �r�b�g���[�g��ݒ�
    void setBitRate(unsigned int prm_bit_rate);

protected:
    bool _is_looping; //!< ���[�v����H
    bool _is_ready; //!< �����ł����H
    unsigned int _num_channel; //!< �`�����l����
    unsigned int _sampling_rate; //!< �T���v�����O���[�g
    unsigned int _bit_rate; //!< �r�b�g���[�g
};
}

#endif
