#ifndef GGAFDXCORE_GGAFDXSEREFLECTOR_H_
#define GGAFDXCORE_GGAFDXSEREFLECTOR_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/core/GgafObject.h"

namespace GgafDxCore {

/**
 * �T�E���h�G�t�F�N�g�o�͎x���N���X .
 * ������ GgafDxSeManager ���p���A�K�v�Œ����SE������
 * �Đ��`�����l���̋@�\�������B
 * @version 1.00
 * @since 2010/04/19
 * @author Masatoshi Tsuge
 */
class GgafDxSeTransmitter : public GgafCore::GgafObject {

public:
    /** [r]SE�����ڑ��̔z�� */
    GgafDxSeConnection** _papSeConnection;
    /** [r]����SE�̐� */
    int _se_num;
    /** [r]����SE�̃{�����[���z�� */
    double* _pa_volume;
    /** [r]����SE�̃p���l */
    float* _pa_pan;

public:
    /**
     * �R���X�g���N�^ .
     */
    GgafDxSeTransmitter();

    /**
     * SE�g�p����錾���A���������s�� .
     * �{�I�u�W�F�N�g�̋@�\�𗘗p����ɂ́A�K�{�B
     * @param prm_se_num SE���i��ސ��j
     */
    virtual void declareSeNum(int prm_se_num);

    /**
     * SE�̐ݒ���s�� .
     * �A���ASE�̍Đ����Ԃ� GGAF_END_DELAY+(�ő勗���x��) �t���[���ȓ��łȂ���΂����Ȃ��B
     * �㏑���Đݒ�\�B
     * @param prm_se_no SE�̔ԍ� ( 0 �` SE��-1 )
     * @param prm_se_key SE��`��(�v���p�e�B�t�@�C���̃L�[)
     * @param prm_cannel �Đ��`�����l���ԍ�
     */
    virtual void set(int prm_se_no, const char* prm_se_key, int prm_cannel);

    /**
     * �Đ� .
     * @param prm_se_no  SE�̔ԍ� ( 0 �` SE��-1 )
     * @param prm_can_looping  true:���[�v�Đ��^false:1��Đ�
     */
    virtual void play(int prm_se_no, bool prm_can_looping = false);


    /**
     * �{�����[���l��ݒ肷��B
     * SE�}�X�^�[�{�����[�����l�����ꂽ���ʂɐݒ肳���B
     * @param prm_se_no SE�̔ԍ�(0 �` )
     * @param prm_volume �{�����[���l(0 �` 1000)
     */
    virtual void setVolume(int prm_se_no, double prm_volume);

    /**
     * �{�����[���l���擾���� .
     * SE�}�X�^�[�{�����[�����l������Ă��Ȃ�setVolume()�Őݒ肳�ꂽ���ʂ��擾�B
     * @param prm_se_no SE�̔ԍ�(0 �` )
     * @return �{�����[���l(0 �` 1000)
     */
    virtual int getVolume(int prm_se_no) {
        return _pa_volume[prm_se_no];
    }

    /**
     * �{�����[���l�����Z���� .
     * SE�}�X�^�[�{�����[�����l�����ꂽ���ʂɐݒ肳���B
     * @param prm_se_no SE�̔ԍ�(0 �` )
     * @param prm_volume ���Z�{�����[���l(0 �` 1000)
     * @return
     */
    virtual void addVolume(int prm_se_no, double prm_volume) {
        setVolume(prm_se_no, _pa_volume[prm_se_no] + prm_volume);
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
        return _pa_pan[prm_se_no];
    }


    /**
     * �Đ���~ .
     * @param prm_se_no  SE�̔ԍ� ( 0 �` SE��-1 )
     */
    virtual void stop(int prm_se_no);


    /**
     * GgafDxSe ���擾�B
     * @param prm_se_no SE�̔ԍ� ( 0 �` SE��-1 )
     */
    virtual GgafDxSe* getSe(int prm_se_no) const;

    /**
     * �f�X�g���N�^
     */
    virtual ~GgafDxSeTransmitter();
};

}
#endif /*GGAFDXCORE_GGAFDXSEREFLECTOR_H_*/
