#ifndef MYMAGICENERGY_H_
#define MYMAGICENERGY_H_
#include "VioletVreath.h"
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

    void onCatchEvent(hashval prm_no, void* prm_pSource) override {
    }

    void onHit(const GgafCore::Actor* prm_pOtherActor) override {
    }

    void drawHitArea() override;

    int isOutOfView() override;

    bool isOutOfSpacetime() const override;

    virtual ~MyMagicEnergy();
};

}
#endif /*MYMAGICENERGY_H_*/

