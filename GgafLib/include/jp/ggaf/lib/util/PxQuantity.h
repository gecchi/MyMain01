#ifndef GGAFLIB_PXQUANTITY_H_
#define GGAFLIB_PXQUANTITY_H_
#include "GgafLibCommonHeader.h"
#include "jp/ggaf/core/GgafObject.h"

namespace GgafLib {

/**
 * ピクセル数量 .
 * 実値とピクセル値と、その割合を保持。
 * 実値を操作（計算）し、結果をピクセル値を得る。
 * @version 1.00
 * @since 2011/02/02
 * @author Masatoshi Tsuge
 */
class PxQuantity : public GgafCore::GgafObject {

public:
    /** [r]100%のメーター値(≠0) */
    int _val;
    /** [r]現在のメーター値のポインタ */
    int* _pInt_val;
    /** [r]100%のメーターの長さ(px) */
    pixcoord _val_px;
    /** [r]メーター値とピクセルの割合、 */
    double _rate_val;

    bool _is_new;

public:
    /**
     * コンストラクタ .
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
     * メーターの目盛りを定義 .
     * @param prm_val    メーター値
     * @param prm_val_px メーター値の時の幅ピクセル
     */
    void graduate(int prm_val, pixcoord prm_val_px) {
        _val_px = prm_val_px;
        _val = prm_val;
        _rate_val = 1.0 * _val_px / _val;
    }


    /**
     * メータと連動させる値の変数（のポインタ）を設定 .
     * @param prm_pInt_target_value メーター値変数のポインタ(int*)を設定
     */
    void link(int* prm_pInt_target_value) {
        if (_is_new) {
            GGAF_DELETE(_pInt_val);
            _is_new = false;
        }
        _pInt_val = prm_pInt_target_value;
    }

    /**
     * メーター値を設定 .
     * 設定すると、現在のメーターの長さ(_val_px) も更新される
     * @param prm_val メーター値
     */
    inline void set(int prm_val) {
        *_pInt_val = prm_val;
    }

    /**
     * メーター値を取得 .
     */
    inline int get() {
        return *_pInt_val;
    }

    /**
     * メーター値をピクセル値で取得 .
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

