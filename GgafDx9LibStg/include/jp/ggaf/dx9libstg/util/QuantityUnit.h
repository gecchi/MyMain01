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
    /** 100%�̃��[�^�[�l(��0) */
    int _max_val;
    /** ���݂̃��[�^�[�l */
    int _val;
    /** 100%�̃��[�^�[�̒���(px) */
    float _max_val_px;
    /** ���݂̃��[�^�[�̒���(px) */
    float _val_px;
    /** ���݂̃��[�^�[�l�̊��� */
    float _rate_val;

    /**
     * �R���X�g���N�^ .
     * @return
     */
    QuantityUnit() : GgafCore::GgafObject() {
        _max_val_px = 100.0f;
        _max_val = 100;
        _val_px = 100.0f;
        _val = 100;
        _rate_val = 1.0;
    }

//    /**
//     * �R���X�g���N�^ .
//     * @param prm_max_val_px  ���[�^�[�l��100%���̕��s�N�Z��
//     * @param prm_max_val     ���[�^�[�l��100%�Ƃ�����ۂ̒l(���[�^�[�l)
//     */
//    QuantityUnit(float prm_max_val_px, float prm_max_val);

    /**
     * ���[�^�[�̖ڐ�����` .
     * @param prm_max_val_px  ���[�^�[�l��100%���̕��s�N�Z��
     * @param prm_max_val     ���[�^�[�l��100%�Ƃ�����ۂ̒l(���[�^�[�l)
     */
    void config(float prm_max_val_px, int prm_max_val) {
        _max_val_px = prm_max_val_px;
        _max_val = prm_max_val;
    }

    /**
     * ���[�^�[�l��ݒ� .
     * �ݒ肷��ƁA���݂̃��[�^�[�̒���(_val_px) �y�сA
     * ���݂̃��[�^�[�l�̊���(_rate_val) ���X�V�����
     * @param prm_val ���[�^�[�l
     */
    void set(int prm_val) {
        _val = prm_val;
        _rate_val = (float)_val /  _max_val;
        _val_px = _max_val_px * _rate_val;
    }

    /**
     * ���[�^�[�l�����Z .
     * �ݒ肷��ƁA���݂̃��[�^�[�̒���(_val_px) �y�сA
     * ���݂̃��[�^�[�l�̊���(_rate_val) ���X�V�����
     * @param prm_val ���[�^�[���Z�l
     */
    void inc(int prm_val) {
        _val += prm_val;
        _rate_val = (float)_val /  _max_val;
        _val_px = _max_val_px * _rate_val;
    }



    virtual ~QuantityUnit() {
    }
};

}
#endif /*QUANTITYUNIT_H_*/

