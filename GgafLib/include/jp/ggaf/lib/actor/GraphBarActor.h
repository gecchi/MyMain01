#ifndef GRAPHBARACTOR_H_
#define GRAPHBARACTOR_H_
#include "jp/ggaf/lib/actor/DefaultBoardActor.h"
#include "jp/ggaf/lib/util/PxQuantity.h"

namespace GgafLib {

/**
 * 横の数量バー .
 * （VVのクラスから昇格）
 * @version 1.00
 * @since 2012/09/11
 * @author Masatoshi Tsuge
 */
class GraphBarActor : public DefaultBoardActor {

public:
    /** 横幅ピクセル */
    const float _chip_width;
    const float _rate_org_chip_width;

    /** 内容量 */
    PxQuantity* _pPxQuantity;
    bool _is_new_PxQuantity;
public:
    /**
     *
     * @param prm_name
     * @param prm_pPxQuantity config済みの PxQuantityオブジェクトの参照
     */
    GraphBarActor(const char* prm_name, const char* prm_model, PxQuantity* prm_pPxQuantity);

    GraphBarActor(const char* prm_name, const char* prm_model);

    void linkPxQuantity(PxQuantity* prm_pPxQuantity);


    inline void graduatePxQty(pixcoord prm_max_val_px, int prm_max_val) {
        _pPxQuantity->graduate(prm_max_val_px, prm_max_val);
    }

    /**
     * メーター値を設定 .
     * @param prm_val メーター値
     */
    inline void setQty(int prm_val) {
        _pPxQuantity->set(prm_val);
    }

    /**
     * メーター値を取得 .
     */
    inline int getQty() {
        return _pPxQuantity->get();
    }

    inline pixcoord getBarPx() {
        return _pPxQuantity->getPx();
    }
    /**
     * メーター値を加算 .
     * 設定すると、現在のメーターの長さ(_val_px) も更新される
     * @param prm_val メーター加算値
     */
    inline void incQty(int prm_val) {
        _pPxQuantity->inc(prm_val);
    }

    /**
     * メーター値を減算 .
     * 設定すると、現在のメーターの長さ(_val_px) も更新される
     * @param prm_val メーター加算値
     */
    inline void decQty(int prm_val) {
        _pPxQuantity->dec(prm_val);
    }
    void processBehavior() override;
    void processDraw() override;
    virtual ~GraphBarActor();
};

}
#endif /*GRAPHBARACTOR_H_*/

