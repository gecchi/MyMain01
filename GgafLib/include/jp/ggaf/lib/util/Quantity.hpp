#ifndef GGAFLIB_QUANTITY_HPP_
#define GGAFLIB_QUANTITY_HPP_
#include "GgafLibCommonHeader.h"
#include "jp/ggaf/core/GgafObject.h"

namespace GgafLib {

/**
 * 数量 .
 * 内部に実値(val)とそれに関わる数量(qty)を持つ。
 * 実値を操作（計算）すると、それに伴って数量が割合変化する。
 * @version 1.00
 * @since 2011/02/02
 * @author Masatoshi Tsuge
 */
template<typename QTY, typename VAL>
class Quantity : public GgafCore::GgafObject {

public:

    /** [r]実値のポインタ */
    VAL* _pVal;
    /** [r]実値に関わる数量 */
    QTY _qty;
    /** [r]メーター値とピクセルの割合、 */
    double _rate_val;

    bool _is_link;

public:
    /**
     * コンストラクタ .
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
     * 割合を定義 .
     * @param prm_val 割合1.0(100%) の場合に実値が取る値をセット
     * @param prm_qty 割合1.0(100%) の場合に数量が取る値をセット
     */
    void graduate(VAL prm_val, QTY prm_qty) {
        _rate_val = 1.0 * prm_qty / prm_val;
    }


    /**
     * 実値の変数（のポインタ）を設定 .
     * @param prm_pInt_target_value メーター値変数のポインタ(int*)を設定
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
     * 実値を設定 .
     * 設定すると、現在のメーターの長さ(_qty) も更新される
     * @param prm_val 実値
     */
    inline void setVal(VAL prm_val) {
        *_pVal = prm_val;
        _qty = (QTY)((*_pVal) * _rate_val);
    }

    /**
     * 値を実値で取得 .
     */
    inline VAL getVal() {
        return *_pVal;
    }

    /**
     * 値を実値に関わる数量で取得 .
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

