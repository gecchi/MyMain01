#ifndef GGAFLIB_PXQUANTITY_H_
#define GGAFLIB_PXQUANTITY_H_
#include "GgafLibCommonHeader.h"
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
    int _val;
    /** [r]���݂̃��[�^�[�l�̃|�C���^ */
    int* _pInt_val;
    /** [r]100%�̃��[�^�[�̒���(px) */
    pixcoord _val_px;
    /** [r]���[�^�[�l�ƃs�N�Z���̊����A */
    double _rate_val;

    bool _is_new;

public:
    /**
     * �R���X�g���N�^ .
     * @return
     */
    PxQuantity() : GgafCore::GgafObject() {
        _val_px = 100;
        _val = 100;
        _rate_val = 1.0;
        _pInt_val = NEW int;
        *_pInt_val = 0;
        _is_new = true;
    }

    /**
     * ���[�^�[�̖ڐ�����` .
     * @param prm_val    ���[�^�[�l
     * @param prm_val_px ���[�^�[�l�̎��̕��s�N�Z��
     */
    void graduate(int prm_val, pixcoord prm_val_px) {
        _val_px = prm_val_px;
        _val = prm_val;
        _rate_val = 1.0 * _val_px / _val;
    }


    /**
     * ���[�^�ƘA��������l�̕ϐ��i�̃|�C���^�j��ݒ� .
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

    virtual ~PxQuantity() {
        if (_is_new) {
            GGAF_DELETE(_pInt_val);
        }
    }
};

}
#endif /*GGAFLIB_PXQUANTITY_H_*/

