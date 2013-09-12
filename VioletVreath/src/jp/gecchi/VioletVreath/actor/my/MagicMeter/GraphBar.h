#ifndef GRAPHBAR_H_
#define GRAPHBAR_H_
#include "jp/ggaf/lib/actor/DefaultBoardActor.h"

namespace VioletVreath {

/**
 * バー基底 .
 * @version 1.00
 * @since 2012/05/1
 * @author Masatoshi Tsuge
 */
class GraphBar : public GgafLib::DefaultBoardActor {

public:
    /** 内容量 */
    GgafLib::PxQuantity* pPxQuantity_;
    /** 横幅ピクセル */
    pixcoord org_width_;
    double rate_org_width_;
public:
    /**
     *
     * @param prm_name
     * @param prm_pPxQuantity config済みの PxQuantityオブジェクトの参照
     */
    GraphBar(const char* prm_name, const char* prm_model, GgafLib::PxQuantity* prm_pPxQuantity);

    void processBehavior() override;
    void processDraw() override;
    virtual ~GraphBar();
};

}
#endif /*GRAPHBAR_H_*/

