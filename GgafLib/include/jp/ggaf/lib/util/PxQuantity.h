#ifndef GGAFLIB_PXQUANTITY_H_
#define GGAFLIB_PXQUANTITY_H_
#include "jp/ggaf/core/GgafObject.h"

namespace GgafLib {

/**
 * �s�N�Z������ .
 * ���l�ƃs�N�Z���l�ƁA���̊�����ێ��B
 * ���l�𑀍�i�v�Z�j���A���ʂ��s�N�Z���l�𓾂�B
 * @version 1.00
 * @since 2011/02/02
 * @author Masatoshi Tsuge
 */
class PxQuantity : public GgafCore::GgafObject {

public:
    /** [r]100%�̃��[�^�[�l(��0) */
    int _max_val;
    /** [r]���݂̃��[�^�[�l�̃|�C���^ */
    int* _pInt_val;
    /** [r]100%�̃��[�^�[�̒���(px) */
    pixcoord _max_val_px;
    /** [r]���[�^�[�l�ƃs�N�Z���̊����A */
    double _rate_val;

    bool _is_new;

public:
    /**
     * �R���X�g���N�^ .
     * @return
     */
    PxQuantity() : GgafCore::GgafObject() {
        _max_val_px = 100;
        _max_val = 100;
        _rate_val = 1.0;
        _pInt_val = NEW int;
        _is_new = true;
    }

    /**
     * ���[�^�[�̖ڐ�����` .
     * @param prm_max_val_px  ���[�^�[�l��100%���̕��s�N�Z��
     * @param prm_max_val     ���[�^�[�l��100%�Ƃ�����ۂ̒l(���[�^�[�l)
     */
    void graduate(pixcoord prm_max_val_px, int prm_max_val) {
        _max_val_px = prm_max_val_px;
        _max_val = prm_max_val;
        _rate_val = 1.0 * _max_val_px / _max_val;
    }


    /**
     * �A��������l�̕ϐ���ݒ� .
     * @param prm_pInt_target_value ���[�^�[�l�ϐ��̃|�C���^(int*)��ݒ�
     */
    void link(int* prm_pInt_target_value) {
        if (_is_new) {
            GGAF_DELETE(_pInt_val);
            _is_new = false;
        }
        _pInt_val = prm_pInt_target_value;
    }

    /**
     * ���[�^�[�l��ݒ� .
     * �ݒ肷��ƁA���݂̃��[�^�[�̒���(_val_px) ���X�V�����
     * @param prm_val ���[�^�[�l
     */
    inline void set(int prm_val) {
        *_pInt_val = prm_val;
    }

    /**
     * ���[�^�[�l���擾 .
     */
    inline int get() {
        return *_pInt_val;
    }

    /**
     * ���[�^�[�l���s�N�Z���l�Ŏ擾 .
     */
    inline pixcoord getPx() {
        return (pixcoord)((*_pInt_val) * _rate_val);
    }

    /**
     * ���[�^�[�l�����Z .
     * �ݒ肷��ƁA���݂̃��[�^�[�̒���(_val_px) ���X�V�����
     * @param prm_val ���[�^�[���Z�l
     */
    inline void inc(int prm_val) {
        *_pInt_val += prm_val;
    }

    /**
     * ���[�^�[�l�����Z .
     * �ݒ肷��ƁA���݂̃��[�^�[�̒���(_val_px) ���X�V�����
     * @param prm_val ���[�^�[���Z�l
     */
    inline void dec(int prm_val) {
        *_pInt_val -= prm_val;
    }

    virtual ~PxQuantity() {
        if (_is_new) {
            GGAF_DELETE(_pInt_val);
        }
    }
};

}
#endif /*GGAFLIB_PXQUANTITY_H_*/

