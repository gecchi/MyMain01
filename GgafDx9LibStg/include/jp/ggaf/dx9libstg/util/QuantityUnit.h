#ifndef QUANTITYUNIT_H_
#define QUANTITYUNIT_H_

namespace GgafDx9LibStg {

/**
 * 数量バー部品 .
 * @version 1.00
 * @since 2011/02/02
 * @author Masatoshi Tsuge
 */
class QuantityUnit : public GgafCore::GgafObject {

public:
    /** 100%のメーター値 */
    int _max_val;
    /** 現在のメーター値 */
    int _val;
    /** 100%のメーターの長さ(px) */
    int _max_val_px;
    /** 現在のメーターの長さ(px) */
    int _val_px;

    /**
     * コンストラクタ .
     * @return
     */
    QuantityUnit() : GgafCore::GgafObject() {
        _max_val_px = 100.0f;
        _max_val = 100.0f;
        _val = 0.0f;
        _val_px = 0.0f;
    }

//    /**
//     * コンストラクタ .
//     * @param prm_max_val_px  メーター値が100%時の幅ピクセル
//     * @param prm_max_val     メーター値が100%とする実際の値(メーター値)
//     */
//    QuantityUnit(float prm_max_val_px, float prm_max_val);

    /**
     * メーターの目盛りを定義 .
     * @param prm_max_val_px  メーター値が100%時の幅ピクセル
     * @param prm_max_val     メーター値が100%とする実際の値(メーター値)
     */
    void config(int prm_max_val_px, int prm_max_val) {
        _max_val_px = prm_max_val_px;
        _max_val = prm_max_val;
    }
    /**
     * メーター量を設定 .
     * 設定すると、現在のメーターの長さ(px)が更新される
     * @param prm_val メーター値
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

