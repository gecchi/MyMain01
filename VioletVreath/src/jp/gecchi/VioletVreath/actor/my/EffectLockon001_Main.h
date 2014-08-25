#ifndef EFFECTLOCKON001MAIN_H_
#define EFFECTLOCKON001MAIN_H_
#include "VioletVreath.h"
#include "jp/gecchi/VioletVreath/actor/my/EffectLockon001.h"

namespace VioletVreath {

/**
 * ロックオン
 * @version 1.00
 * @since 2010/01/28
 * @author Masatoshi Tsuge
 */
class EffectLockon001_Main : public EffectLockon001 {

public:
    /** 拡大縮小支援オブジェクト */
    GgafDxCore::GgafDxScaler* pScaler_;

public:
    EffectLockon001_Main(const char* prm_name);

    void initialize() override;

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;

    void onInactive() override;

    void releaseLockon() override;

    void lockon(GgafDxGeometricActor* prm_pTarget) override;

    virtual ~EffectLockon001_Main();
};

}
#endif /*EFFECTLOCKON001MAIN_H_*/

