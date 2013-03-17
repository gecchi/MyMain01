#ifndef AMOUNTGRAPH_H_
#define AMOUNTGRAPH_H_

namespace GgafLib {

/**
 * 数量バー部品 .
 * 実値とピクセル値と、その割合を保持。
 * 実値を操作（計算）し、結果をピクセル値を得る。
 * @version 1.00
 * @since 2011/02/02
 * @author Masatoshi Tsuge
 */
class AmountGraph : public GgafCore::GgafObject {

public:
    /** [r]100%のメーター値(≠0) */
    int _max_val;
    /** [r]現在のメーター値のポインタ */
    int* _pInt_val;
    /** [r]100%のメーターの長さ(px) */
    pixcoord _max_val_px;
    /** [r]現在のメーター値の割合 */
    double _rate_val;

    bool _is_new;

public:
    /**
     * コンストラクタ .
     * @return
     */
    AmountGraph() : GgafCore::GgafObject() {
        _max_val_px = 100.0f;
        _max_val = 100;
        _rate_val = 1.0;
        _pInt_val = NEW int;
        _is_new = true;
    }

    /**
     * メーターの目盛りを定義 .
     * @param prm_max_val_px  メーター値が100%時の幅ピクセル
     * @param prm_max_val     メーター値が100%とする実際の値(メーター値)
     */
    void config(pixcoord prm_max_val_px, int prm_max_val) {
        _max_val_px = prm_max_val_px;
        _max_val = prm_max_val;
        _rate_val = 1.0* _max_val_px / _max_val;
    }
    /**
     *      * メーターの目盛りを定義 .
     * @param prm_max_val_px  メーター値が100%時の幅ピクセル
     * @param prm_max_val     メーター値が100%とする実際の値(メーター値)
     * @param prm_pInt_target_value メーター値変数のポインタ(int*)を設定
     */
    void config(pixcoord prm_max_val_px, int prm_max_val, int* prm_pInt_target_value) {
        _max_val_px = prm_max_val_px;
        _max_val = prm_max_val;
        _rate_val = 1.0* _max_val_px / _max_val;
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

    /**
     * メーター値を加算 .
     * 設定すると、現在のメーターの長さ(_val_px) も更新される
     * @param prm_val メーター加算値
     */
    inline void inc(int prm_val) {
        *_pInt_val += prm_val;
    }

    /**
     * メーター値を減算 .
     * 設定すると、現在のメーターの長さ(_val_px) も更新される
     * @param prm_val メーター加算値
     */
    inline void dec(int prm_val) {
        *_pInt_val -= prm_val;
    }

    virtual ~AmountGraph() {
        if (_is_new) {
            GGAF_DELETE(_pInt_val);
        }
    }
};

}
#endif /*AMOUNTGRAPH_H_*/

