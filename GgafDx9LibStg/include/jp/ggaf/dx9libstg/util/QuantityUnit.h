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
    int _max_val;
    /** ���݂̃��[�^�[�l */
    int _val;
    /** 100%�̃��[�^�[�̒���(px) */
    int _max_val_px;
    /** ���݂̃��[�^�[�̒���(px) */
    int _val_px;

    /**
     * �R���X�g���N�^ .
     * @return
     */
    QuantityUnit() : GgafCore::GgafObject() {
        _max_val_px = 100.0f;
        _max_val = 100.0f;
        _val = 0.0f;
        _val_px = 0.0f;
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
    void config(int prm_max_val_px, int prm_max_val) {
        _max_val_px = prm_max_val_px;
        _max_val = prm_max_val;
    }
    /**
     * ���[�^�[�ʂ�ݒ� .
     * �ݒ肷��ƁA���݂̃��[�^�[�̒���(px)���X�V�����
     * @param prm_val ���[�^�[�l
     */
    void set(int prm_val) {
        _val = prm_val;
        _val_px = _max_val * _max_val_px / _val / ;
    }

    virtual ~QuantityUnit() {
    }
};

}
#endif /*QUANTITYUNIT_H_*/

