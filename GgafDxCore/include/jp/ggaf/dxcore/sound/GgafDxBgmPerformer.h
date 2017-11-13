#ifndef GGAFDXCORE_GGAFDXBGMPERFORMER_H_
#define GGAFDXCORE_GGAFDXBGMPERFORMER_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/core/GgafObject.h"

#include <vector>

namespace GgafDxCore {

/**
 * BGM���t�x���N���X .
 * BGM�Ƃ���ɕR�����ʁA�p���̒l��ێ�
 * BGM�}�X�^�[�{�����[�����l��
 * @version 1.00
 * @since 2010/04/19
 * @author Masatoshi Tsuge
 */
class GgafDxBgmPerformer : public GgafCore::GgafObject {

public:
//    static int _active_bgm_bpm;
    /** [r]BGM�ԍ��� */
    int _bgm_num;
    /** [r]Bgm�����ڑ� */
    std::vector<GgafDxBgmConnection*>  _vecBgmConnection;
    /** [r]BGM�̃{�����[���z��(�Y����BGM�ԍ�) */
    std::vector<double> _vec_volume;
    /** [r]BGM�̃p���l(�Y����BGM�ԍ�) */
    std::vector<float> _vec_pan;


public:
    GgafDxBgmPerformer();

    /**
     * BGM��ݒ肷��B
     * @param prm_bgm_no BGM�ԍ�(0 �` )
     * @param prm_bgm_name �v���p�e�B�t�@�C��key������
     */
    virtual void ready(int prm_bgm_no, const char* prm_bgm_name);

    /**
     * �{�����[���l��ݒ肷��B
     * BGM�}�X�^�[�{�����[�����l�����ꂽ���ʂɐݒ肳���B
     * @param prm_bgm_no BGM�ԍ�(0 �` )
     * @param prm_volume �{�����[���l(0 �` 1000)
     */
    virtual void setVolume(int prm_bgm_no, double prm_volume);

    /**
     * �{�����[���l���擾���� .
     * BGM�}�X�^�[�{�����[�����l������Ă��Ȃ�setVolume()�Őݒ肳�ꂽ���ʂ��擾�B
     * @param prm_bgm_no BGM�ԍ�(0 �` )
     * @return �{�����[���l(0 �` 1000)
     */
    virtual int getVolume(int prm_bgm_no) {
        return _vec_volume[prm_bgm_no];
    }

    /**
     * �{�����[���l�����Z���� .
     * BGM�}�X�^�[�{�����[�����l�����ꂽ���ʂɐݒ肳���B
     * @param prm_bgm_no BGM�ԍ�(0 �` )
     * @param prm_volume ���Z�{�����[���l(0 �` 1000)
     * @return
     */
    virtual void addVolume(int prm_bgm_no, double prm_volume) {
        setVolume(prm_bgm_no, _vec_volume[prm_bgm_no] + prm_volume);
    }

    /**
     * �p���l��ݒ� .
     * BGM�}�X�^�[�p���͖��쐬�̂��߁A���̂܂ܔ��f
     * @param prm_pan �p���l(left:-1.0 �` center:0 �` right:1.0)
     */
    virtual void setPan(int prm_bgm_no, float prm_pan);

    /**
     * �p���l���擾���� .
     * @param prm_bgm_no
     * @return
     */
    virtual float getPan(int prm_bgm_no) {
        return _vec_pan[prm_bgm_no];
    }

    /**
     * BGM���Đ�����B
     * @param prm_bgm_no  BGM�ԍ�(0 �` )
     * @param prm_is_loop  ���[�v���邩�ǂ����itrue:���[�v�Đ�����^false:���[�v�Đ����Ȃ��j
     */
    virtual void play(int prm_bgm_no, bool prm_is_loop = true);

    /**
     * BGM���~���� .
     * @param prm_bgm_no BGM�ԍ�(0 �` )
     */
    virtual void stop(int prm_bgm_no);

    /**
     * BGM���ꎞ��~���� .
     * @param prm_bgm_no BGM�ԍ�(0 �` )
     */
    virtual void pause(int prm_bgm_no);

    /**
     * BGM�̈ꎞ��~���������� .
     * @param prm_bgm_no  BGM�ԍ�(0 �` )
     */
    virtual void unpause(int prm_bgm_no);

    /**
     * �SBGM�ԍ���BGM���~ .
     */
    virtual void stop();

    /**
     * �SBGM�ԍ���BGM���ꎞ��~ .
     */
    virtual void pause();

    /**
     * �SBGM�ԍ���BGM�̈ꎞ��~���������� .
     */
    virtual void unpause();

    virtual GgafDxBgm* getBgm(int prm_bgm_no);

    virtual ~GgafDxBgmPerformer();
};

}
#endif /*GGAFDXCORE_GGAFDXBGMPERFORMER_H_*/
