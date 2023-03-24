#ifndef GGAF_LIB_QUANTITY_HPP_
#define GGAF_LIB_QUANTITY_HPP_
#include "jp/ggaf/GgafLibCommonHeader.h"
#include "jp/ggaf/core/Object.h"

namespace GgafLib {

/**
 * ���� .
 * �����Ɏ��l(VAL)�Ƃ���Ɋւ�鐔��(QTY)�����B
 * ���l�𑀍�i�v�Z�j����ƁA����ɔ����Đ��ʂ������ω�����B
 * @version 1.00
 * @since 2011/02/02
 * @author Masatoshi Tsuge
 */
template<typename VAL, typename QTY>
class Quantity : public GgafCore::Object {

public:

    /** [r]���l�̃|�C���^ */
    VAL* _pVal;
    /** [r]���l�Ɋւ�鐔�� */
    QTY _qty;
    /** ���l�Y�� */
    VAL _offset_val;
    /** [r]���l�Ɋւ�鐔�ʃY�� */
    QTY _offset_qty;
    /** [r]���l�Ɛ��ʂ̑��������A */
    double _rate_val;

    bool _is_link;

public:
    /**
     * �R���X�g���N�^ .
     * @return
     */
    Quantity() : GgafCore::Object() {
        _qty = (QTY)0;
        _rate_val = 1.0;
        _pVal = NEW VAL();
        *_pVal = (VAL)0;
        _offset_val = (VAL)0;
        _offset_qty = (QTY)0;
        _is_link = false;
    }

    /**
     * ���l�Ɛ��ʂƂ̊֌W���` .
     * �I�t�Z�b�g�͖���
     * @param prm_val ����1.0(100%) �̏ꍇ�Ɏ��l�����l���Z�b�g
     * @param prm_qty ����1.0(100%) �̏ꍇ�ɐ��ʂ����l���Z�b�g
     */
    void scale(VAL prm_val, QTY prm_qty) {
        scale(0.0, prm_val, 0.0, prm_qty);
    }

    /**
     * ���l�Ɛ��ʂƂ̊֌W���` .
     * @param prm_min_val ���l�ŏ��l��ݒ�
     * @param prm_max_val ���l�ő�l��ݒ�
     * @param prm_min_qty ���l�ŏ��l�ɑΉ����鐔�ʍŏ��l��ݒ�
     * @param prm_max_qty ���l�ő�l�ɑΉ����鐔�ʍő�l��ݒ�
     */
    inline void scale(VAL prm_min_val, VAL prm_max_val, QTY prm_min_qty, QTY prm_max_qty) {
        _rate_val = 1.0 *  (prm_max_qty - prm_min_qty) / (prm_max_val - prm_min_val);
        _offset_val = prm_min_val;
        _offset_qty = prm_min_qty;
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
     * �ݒ肷��ƁA�������ʂ��A�����Ă��X�V�����
     * @param prm_val ���l
     */
    inline void setVal(VAL prm_val) {
        *_pVal = prm_val;
        if (!_is_link) {
            _qty = (QTY)((((*_pVal) - _offset_val) * _rate_val ) + _offset_qty);
        }
    }

    /**
     * ���l�𐔗ʂŎw�肵�Đݒ� .
     * �ݒ肷��ƁA�������ʂ��A�����Ă��X�V�����
     * @param prm_qty ����
     */
    inline void setValByQty(QTY prm_qty) {
        setVal(cnvQty2Val(prm_qty));
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
        return _is_link ? (QTY)((((*_pVal) - _offset_val) * _rate_val ) + _offset_qty) : _qty;
    }

    /**
     * ���l�ɑ΂��Ă̐��ʂ����߂�(���l�ʋy�ѐ��ʂ́A�����ݒ肳��܂���) .
     * @param prm_val ���l
     * @return ����
     */
    inline QTY cnvVal2Qty(VAL prm_val) {
        return (QTY)(((prm_val - _offset_val) * _rate_val ) + _offset_qty);
    }

    /**
     * ���ʂɑ΂��Ă̎��l�����߂�(���l�ʋy�ѐ��ʂ́A�����ݒ肳��܂���) .
     * @param prm_qty
     * @return
     */
    inline VAL cnvQty2Val(QTY prm_qty) {
        return (VAL)((_offset_val * _rate_val - _offset_qty + prm_qty) / (1.0*_rate_val));
    }

    virtual ~Quantity() {
        if (!_is_link) {
            GGAF_DELETE(_pVal);
        }
    }
};

}
#endif /*GGAF_LIB_QUANTITY_HPP_*/

