#ifndef HOSHIBOSHI002_H_
#define HOSHIBOSHI002_H_
#include "VioletVreath.h"
#include "jp/ggaf/lib/actor/DefaultPointSpriteActor.h"

namespace VioletVreath {
//現在未使用
/**
 * 爆発エフェクトスプライト002
 * @version 1.00
 * @since 2006/01/10
 * @author Masatoshi Tsuge
 */
class HoshiBoshi002 : public GgafLib::DefaultPointSpriteActor {

public:
    int CAM_ZF_;

    HoshiBoshi002(const char* prm_name);

    void initialize() override;

    void onActive() override;

    void processBehavior() override;

    void processSettlementBehavior() override;

    void processJudgement() override;

    int isOutOfView() override;

    bool isOutOfUniverse() override;

    virtual ~HoshiBoshi002();
};

}
#endif /*HOSHIBOSHI002_H_*/

