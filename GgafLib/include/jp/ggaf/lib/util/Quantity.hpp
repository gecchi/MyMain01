#ifndef GGAFLIB_QUANTITY_HPP_
#define GGAFLIB_QUANTITY_HPP_
#include "GgafLibCommonHeader.h"
#include "jp/ggaf/core/GgafObject.h"

namespace GgafLib {

/**
 * ���� .
 * �����Ɏ��l(val)�Ƃ���Ɋւ�鐔��(qty)�����B
 * ���l�𑀍�i�v�Z�j����ƁA����ɔ����Đ��ʂ������ω�����B
 * @version 1.00
 * @since 2011/02/02
 * @author Masatoshi Tsuge
 */
template<typename QTY, typename VAL>
class Quantity : public GgafCore::GgafObject {

public:

    /** [r]���l�̃|�C���^ */
    VAL* _pVal;
    /** [r]���l�Ɋւ�鐔�� */
    QTY _qty;
    /** [r]���[�^�[�l�ƃs�N�Z���̊����A */
    double _rate_val;

    bool _is_link;

public:
    /**
     * �R���X�g���N�^ .
     * @return
     */
    Quantity() : GgafCore::GgafObject() {
        _qty = (QTY)0;
        _rate_val = 1.0;
        _pVal = NEW VAL();
        *_pVal = (VAL)0;
        _is_link = false;
    }

    /**
     * �������` .
     * @param prm_val ����1.0(100%) �̏ꍇ�Ɏ��l�����l���Z�b�g
     * @param prm_qty ����1.0(100%) �̏ꍇ�ɐ��ʂ����l���Z�b�g
     */
    void graduate(VAL prm_val, QTY prm_qty) {
        _rate_val = 1.0 * prm_qty / prm_val;
    }


    /**
     * ���l�̕ϐ��i�̃|�C���^�j��ݒ� .
     * @param prm_pInt_target_value ���[�^�[�l�ϐ��̃|�C���^(int*)��ݒ�
     */
    void link(VAL* prm_pVariable) {
        if (_is_link) {
            _pVal = prm_pVariable;
        } else {
            GGAF_DELETE(_pVal);
            _pVal = prm_pVariable;
            _is_link = true;
        }

    }

    /**
     * ���l��ݒ� .
     * �ݒ肷��ƁA���݂̃��[�^�[�̒���(_qty) ���X�V�����
     * @param prm_val ���l
     */
    inline void setVal(VAL prm_val) {
        *_pVal = prm_val;
        _qty = (QTY)((*_pVal) * _rate_val);
    }

    /**
     * �l�����l�Ŏ擾 .
     */
    inline VAL getVal() {
        return *_pVal;
    }

    /**
     * �l�����l�Ɋւ�鐔�ʂŎ擾 .
     */
    inline QTY getQty() {
        return _is_link ? (QTY)((*_pVal) * _rate_val) : _qty;
    }

    virtual ~Quantity() {
        if (!_is_link) {
            GGAF_DELETE(_pVal);
        }
    }
};

}
#endif /*GGAFLIB_QUANTITY_HPP_*/

