#ifndef GRAPHBARACTOR_H_
#define GRAPHBARACTOR_H_
#include "jp/ggaf/lib/actor/DefaultBoardActor.h"
#include "jp/ggaf/lib/util/PxQuantity.h"

namespace GgafLib {

/**
 * 数量バー（単純長方形） .
 * @version 1.00
 * @since 2013/09/17
 * @author Masatoshi Tsuge
 */
class GraphBarActor : public DefaultBoardActor {

protected:
    /** [r]コンストラクタでPxQuantity をnewした場合 true */
    bool _is_new_PxQuantity;
    /** [r]モデルチップ横幅ピクセル */
    const float _chip_width;
    /** [r] 1.0 / _chip_width の値。計算用 */
    const float _rate_org_chip_width;

public:
    /** [r]数量バー内容値 */
    PxQuantity* _pPxQty;
    /** [r]数量バー最大値 */
    int _min_val;
    /** [r]数量バー最小値 */
    int _max_val;

public:
    /**
     *
     * @param prm_name
     * @param prm_pPxQty config済みの PxQuantityオブジェクトの参照
     */
    GraphBarActor(const char* prm_name, const char* prm_model, PxQuantity* prm_pPxQty);

    GraphBarActor(const char* prm_name, const char* prm_model);

    /**
     * 内部のバーの値を保持する PxQuantity を置き換える .
     * @param prm_pPxQty
     */
    void linkQty(PxQuantity* prm_pPxQty);

    /**
     * バーの値に対するピクセル値を設定 .
     * @param prm_max_val バーの値の最大値
     * @param prm_max_val_px    バーの値の最大値に対する画面のピクセル値
     */

    /**
     * バーの値に対するピクセルの目盛りを付ける。
     * @param prm_min_val バー最小値を設定（これ以下の値はセットできなくなる）
     * @param prm_max_val バー最大値を設定（これ以上の値はセットできなくなる）
     * @param prm_px_from_min_to_max 最小値～最大値の画面上のピクセル幅を設定
     */
    inline void graduate(int prm_min_val, int prm_max_val, pixcoord prm_px_from_min_to_max ) {
        _min_val = prm_min_val;
        _max_val = prm_max_val;
        _pPxQty->graduate(prm_max_val - prm_min_val, prm_px_from_min_to_max);
    }

    /**
     * バーの値を設定 .
     * @param prm_val メーター値
     */
    inline void setQty(int prm_val) {
        if (_max_val < prm_val) {
            _pPxQty->set(_max_val);
        } else if (_min_val > prm_val) {
            _pPxQty->set(_min_val);
        } else {
            _pPxQty->set(prm_val);
        }
    }

    /**
     * バーの値を取得 .
     * @return バーの値
     */
    inline int getQty() {
        return _pPxQty->get();
    }

    /**
     * バーの現在値に対応するピクセル値を取得
     * @return ピクセル値
     */
    inline pixcoord getBarPx() {
        return _pPxQty->getPx();
    }

    /**
     * バーの値を加算 .
     * @param prm_val バーの加算値
     */
    inline void incQty(int prm_val) {
        setQty(_pPxQty->get() + prm_val);
    }

    /**
     * バーの値を減算 .
     * @param prm_val バーの減算値
     */
    inline void decQty(int prm_val) {
        setQty(_pPxQty->get() - prm_val);
    }

    void processDraw() override;

    virtual ~GraphBarActor();
};

}
#endif /*GRAPHBARACTOR_H_*/

