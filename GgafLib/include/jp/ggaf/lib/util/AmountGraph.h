#ifndef AMOUNTGRAPH_H_
#define AMOUNTGRAPH_H_

namespace GgafLib {

/**
 * ���ʃo�[���i .
 * @version 1.00
 * @since 2011/02/02
 * @author Masatoshi Tsuge
 */
class AmountGraph : public GgafCore::GgafObject {

public:
    /** [r]100%�̃��[�^�[�l(��0) */
    int _max_val;
    /** [r]���݂̃��[�^�[�l */
    int _val;
    /** [r]100%�̃��[�^�[�̒���(px) */
    float _max_val_px;
    /** [r]���݂̃��[�^�[�̒���(px) */
    float _val_px;
    /** [r]���݂̃��[�^�[�l�̊��� */
    float _rate_val;

    /**
     * �R���X�g���N�^ .
     * @return
     */
    AmountGraph() : GgafCore::GgafObject() {
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
//    AmountGraph(float prm_max_val_px, float prm_max_val);

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

    int get() {
        return _val;
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

    void dec(int prm_val) {
        _val -= prm_val;
        _rate_val = (float)_val /  _max_val;
        _val_px = _max_val_px * _rate_val;
    }

    virtual ~AmountGraph() {
    }
};

}
#endif /*AMOUNTGRAPH_H_*/

