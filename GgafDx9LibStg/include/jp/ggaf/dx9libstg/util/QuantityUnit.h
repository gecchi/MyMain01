#ifndef QUANTITYUNIT_H_
#define QUANTITYUNIT_H_

namespace GgafDx9LibStg {

/**
 * ���ʃo�[���i .
 * @version 1.00
 * @since 2011/02/02
 * @author Masatoshi Tsuge
 */
class QuantityUnit : public GgafCore::GgafObject {

public:
    /** 100%�̃��[�^�[�l */
    float _max_val;
    /** ���݂̃��[�^�[�l */
    float _val;
    /** 100%�̃��[�^�[�̒���(px) */
    float _max_val_px;
    /** ���݂̃��[�^�[�̒���(px) */
    float _val_px;

    /**
     * �R���X�g���N�^ .
     * @return
     */
    QuantityUnit();

    /**
     * �R���X�g���N�^ .
     * @param prm_max_val_px  ���[�^�[�l��100%���̕��s�N�Z��
     * @param prm_max_val     ���[�^�[�l��100%�Ƃ�����ۂ̒l(���[�^�[�l)
     */
    QuantityUnit(float prm_max_val_px, float prm_max_val);

    /**
     * ���[�^�[�̖ڐ�����` .
     * @param prm_max_val_px  ���[�^�[�l��100%���̕��s�N�Z��
     * @param prm_max_val     ���[�^�[�l��100%�Ƃ�����ۂ̒l(���[�^�[�l)
     */
    void config(float prm_max_val_px, float prm_max_val);

    /**
     * ���[�^�[�ʂ�ݒ� .
     * �ݒ肷��ƁA���݂̃��[�^�[�̒���(px)���X�V�����
     * @param prm_val ���[�^�[�l
     */
    inline void set(float prm_val) {
        _val = prm_val;
        _val_px = (_max_val / _val) * _max_val_px;
    }

    virtual ~QuantityUnit();
};

}
#endif /*QUANTITYUNIT_H_*/

