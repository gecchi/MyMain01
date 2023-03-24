#ifndef GGAF_DX_SEREFLECTOR_H_
#define GGAF_DX_SEREFLECTOR_H_
#include "jp/ggaf/GgafDxCommonHeader.h"
#include "jp/ggaf/core/Object.h"

#include <vector>

namespace GgafDx {

/**
 * �T�E���h�G�t�F�N�g�o�͎x���N���X .
 * ������ SeManager ���p���A�K�v�Œ����SE������
 * �Đ��`�����l���̋@�\�������B
 * @version 1.00
 * @since 2010/04/19
 * @author Masatoshi Tsuge
 */
class SeTransmitter : public GgafCore::Object {

public:
    /** [r]����SE�̐� */
    int _se_num;
    /** [r]SE�����ڑ��̔z�� */
    std::vector<SeConnection*> _vecSeConnection;
    /** [r]����SE�̃{�����[���z�� */
    std::vector<double> _vec_volume;
    /** [r]����SE�̃p���l */
    std::vector<float> _vec_pan;

public:
    /**
     * �R���X�g���N�^ .
     */
    SeTransmitter();

    /**
     * SE�̐ݒ���s�� .
     * �����̃`�����l���ԍ����قȂ�΁A����SE��`����Wave�ł��A���������������ł���B
     * �����̃`�����l���ԍ��������ł���΁A��̔��������ł��Ȃ��B
     * �A���ASE�̍Đ����Ԃ� GGAF_END_DELAY+(�ő勗���x��) �t���[���ȓ��łȂ���΂����Ȃ��B
     * �㏑���Đݒ�\�B
     * @param prm_se_no SE�o�^�ԍ� ( 0 �` SE��-1 )
     * @param prm_se_key SE��`��(�v���p�e�B�t�@�C����wave�t�@�C���w��̃L�[)
     * @param prm_cannel �Đ��`�����l���ԍ�
     */
    virtual void set(int prm_se_no, const char* prm_se_key, int prm_cannel);

    /**
     * �Đ� .
     * @param prm_se_no  SE�o�^�ԍ� ( 0 �` SE��-1 )
     * @param prm_can_looping  true:���[�v�Đ��^false:1��Đ�
     */
    virtual void play(int prm_se_no, bool prm_can_looping = false);


    /**
     * �{�����[���l��ݒ肷��B
     * SE�}�X�^�[�{�����[�����l�����ꂽ���ʂɐݒ肳���B
     * @param prm_se_no SE�o�^�ԍ�(0 �` )
     * @param prm_volume �{�����[���l(0 �` 1000)
     */
    virtual void setVolume(int prm_se_no, double prm_volume);

    /**
     * �{�����[���l���擾���� .
     * SE�}�X�^�[�{�����[�����l������Ă��Ȃ�setVolume()�Őݒ肳�ꂽ���ʂ��擾�B
     * @param prm_se_no SE�o�^�ԍ�(0 �` )
     * @return �{�����[���l(0 �` 1000)
     */
    virtual int getVolume(int prm_se_no) {
        return _vec_volume[prm_se_no];
    }

    /**
     * �{�����[���l�����Z���� .
     * SE�}�X�^�[�{�����[�����l�����ꂽ���ʂɐݒ肳���B
     * @param prm_se_no SE�o�^�ԍ�(0 �` )
     * @param prm_volume ���Z�{�����[���l(0 �` 1000)
     * @return
     */
    virtual void addVolume(int prm_se_no, double prm_volume) {
        setVolume(prm_se_no, _vec_volume[prm_se_no] + prm_volume);
    }

    /**
     * �p���l��ݒ� .
     * SE�}�X�^�[�p���͖��쐬�̂��߁A���̂܂ܔ��f
     * @param prm_pan �p���l(left:-1.0 �` center:0 �` right:1.0)
     */
    virtual void setPan(int prm_se_no, float prm_pan);

    /**
     * �p���l���擾���� .
     * @param prm_se_no
     * @return
     */
    virtual float getPan(int prm_se_no) {
        return _vec_pan[prm_se_no];
    }


    /**
     * �Đ���~ .
     * @param prm_se_no  SE�o�^�ԍ� ( 0 �` SE��-1 )
     */
    virtual void stop(int prm_se_no);


    /**
     * Se ���擾�B
     * @param prm_se_no SE�o�^�ԍ� ( 0 �` SE��-1 )
     */
    virtual Se* getSe(int prm_se_no) const;

    /**
     * �f�X�g���N�^
     */
    virtual ~SeTransmitter();
};

}
#endif /*GGAF_DX_SEREFLECTOR_H_*/
