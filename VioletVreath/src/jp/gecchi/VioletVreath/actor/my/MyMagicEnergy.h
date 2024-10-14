#ifndef MYMAGICENERGY_H_
#define MYMAGICENERGY_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/ggaf/lib/actor/DefaultMeshActor.h"

namespace VioletVreath {

/**
 * MPエネルギー .
 * @version 1.00
 * @since 2013/10/22
 * @author Masatoshi Tsuge
 */
class MyMagicEnergy : public GgafLib::DefaultMeshActor {
public:
    /** 親オプション */
    MyMagicEnergyCore* pCore_;

public:
   MyMagicEnergy(const char* prm_name, MyMagicEnergyCore* prm_pCore);

    void onCreateModel() override;

    void initialize() override;

    void onActive() override;

    void processBehavior() override;
//    void processSettlementBehavior() override;
    void processJudgement() override;

    void processPreDraw() override;

    void onCatchEvent(eventval prm_event_val, void* prm_pSource) override {
    }

    void onHit(const GgafCore::Checker* prm_pOtherChecker, const GgafCore::Actor* prm_pOtherActor) override {
    }

    void drawHitArea() override;

    int isOutOfView() override;

    bool isOutOfSpacetime() const override;

    virtual ~MyMagicEnergy();
};

}
#endif /*MYMAGICENERGY_H_*/

