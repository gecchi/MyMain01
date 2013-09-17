#ifndef GRAPHBARACTOR_H_
#define GRAPHBARACTOR_H_
#include "jp/ggaf/lib/actor/DefaultBoardActor.h"
#include "jp/ggaf/lib/util/PxQuantity.h"

namespace GgafLib {

/**
 * 数量バー（単純長方形） .
 * @version 1.00
 * @since 2012/09/17
 * @author Masatoshi Tsuge
 */
class GraphBarActor : public DefaultBoardActor {

public:
    /** 横幅ピクセル */
    const float _chip_width;
    const float _rate_org_chip_width;

    /** 内容量 */
    PxQuantity* _pPxQuantity;
    int _min_val;
    int _max_val;
    bool _is_new_PxQuantity;
public:
    /**
     *
     * @param prm_name
     * @param prm_pPxQuantity config済みの PxQuantityオブジェクトの参照
     */
    GraphBarActor(const char* prm_name, const char* prm_model, PxQuantity* prm_pPxQuantity);

    GraphBarActor(const char* prm_name, const char* prm_model);

    /**
     * 内部のバーの値を保持する PxQuantity を置き換える .
     * @param prm_pPxQuantity
     */
    void linkPxQuantity(PxQuantity* prm_pPxQuantity);

    /**
     * バーの値に対するピクセル値を設定 .
     * @param prm_max_val バーの値の最大値
     * @param prm_max_val_px    バーの値の最大値に対する画面のピクセル値
     */
    inline void graduate(int prm_min_val, int prm_max_val, pixcoord prm_max_val_px ) {
        _min_val = prm_min_val;
        _max_val = prm_max_val;
        _pPxQuantity->graduate(prm_max_val, prm_max_val_px);
    }

    /**
     * バーの値を設定 .
     * @param prm_val メーター値
     */
    inline void setQty(int prm_val) {
        if (_max_val < prm_val) {
            _pPxQuantity->set(_max_val);
        } else if (_min_val > prm_val) {
            _pPxQuantity->set(_min_val);
        } else {
            _pPxQuantity->set(prm_val);
        }
    }

    /**
     * バーの値を取得 .
     * @return バーの値
     */
    inline int getQty() {
        return _pPxQuantity->get();
    }

    /**
     * バーの現在値に対応するピクセル値を取得
     * @return ピクセル値
     */
    inline pixcoord getBarPx() {
        return _pPxQuantity->getPx();
    }

    /**
     * バーの値を加算 .
     * @param prm_val バーの加算値
     */
    inline void incQty(int prm_val) {
        setQty(_pPxQuantity->get() + prm_val);
    }

    /**
     * バーの値を減算 .
     * @param prm_val バーの減算値
     */
    inline void decQty(int prm_val) {
        setQty(_pPxQuantity->get() - prm_val);
    }

    void processDraw() override;

    virtual ~GraphBarActor();
};

}
#endif /*GRAPHBARACTOR_H_*/

