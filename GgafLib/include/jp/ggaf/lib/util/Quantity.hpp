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
    /** 実値ズレ */
    VAL _offset_val;
    /** [r]実値に関わる数量ズレ */
    QTY _offset_qty;
    /** [r]実値と数量の増加割合、 */
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
        _offset_val = (VAL)0;
        _offset_qty = (QTY)0;
        _is_link = false;
    }

    /**
     * 実値と数量との関係を定義 .
     * オフセットは無し
     * @param prm_val 割合1.0(100%) の場合に実値が取る値をセット
     * @param prm_qty 割合1.0(100%) の場合に数量が取る値をセット
     */
    void graduate(VAL prm_val, QTY prm_qty) {
        graduate(0.0, prm_val, 0.0, prm_qty);
    }

    /**
     * 実値と数量との関係を定義 .
     * @param prm_min_val 実値最小値を設定
     * @param prm_max_val 実値最大値を設定
     * @param prm_min_qty 実値最小値に対応する数量最小値を設定
     * @param prm_max_qty 実値最大値に対応する数量最大値を設定
     */
    inline void graduate(VAL prm_min_val, VAL prm_max_val, QTY prm_min_qty, QTY prm_max_qty) {
        _rate_val = 1.0 *  (prm_max_qty - prm_min_qty) / (prm_max_val - prm_min_val);
        _offset_val = prm_min_val;
        _offset_qty = prm_min_qty;
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
        if (!_is_link) {
            _qty = (QTY)((((*_pVal) - _offset_val) * _rate_val ) + _offset_qty);
        }
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
        return _is_link ? (QTY)((((*_pVal) - _offset_val) * _rate_val ) + _offset_qty) : _qty;
    }

    virtual ~Quantity() {
        if (!_is_link) {
            GGAF_DELETE(_pVal);
        }
    }
};

}
#endif /*GGAFLIB_QUANTITY_HPP_*/

