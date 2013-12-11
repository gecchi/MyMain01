#ifndef MYMAGICENERGYCORE_H_
#define MYMAGICENERGYCORE_H_
#include "jp/ggaf/lib/actor/DefaultMeshActor.h"

namespace VioletVreath {

/**
 * MPエネルギー核 .
 * @version 1.00
 * @since 2013/10/23
 * @author Masatoshi Tsuge
 */
class MyMagicEnergyCore : public GgafLib::DefaultMeshActor {

public:
    /** 拡大縮小支援オブジェクト */
    GgafDxCore::GgafDxScaler* pScaler_;
    /** 平行移動支援 */
    GgafDxCore::GgafDxAxesMover* pAxMver_;

public:
   MyMagicEnergyCore(const char* prm_name);

    void onCreateModel() override;

    void initialize() override;

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;

    /**
     * オプション詠唱開始時アニメーション .
     */
    void execOptionMagic();

    void onCatchEvent(hashval prm_no, void* prm_pSource) override {
    }

    void onHit(GgafCore::GgafActor* prm_pOtherActor) override {
    }

    int isOutOfView() override;

    bool isOutOfUniverse() override;

    virtual ~MyMagicEnergyCore();
};

}
#endif /*MYMAGICENERGYCORE_H_*/

