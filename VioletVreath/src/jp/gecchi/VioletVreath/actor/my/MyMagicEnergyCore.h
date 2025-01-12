#ifndef MYMAGICENERGYCORE_H_
#define MYMAGICENERGYCORE_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/gecchi/VioletVreath/actor/VvMyActor.hpp"
#include "jp/ggaf/lib/actor/DefaultMeshActor.h"

namespace VioletVreath {

/**
 * MPÉGÉlÉãÉMÅ[äj .
 * @version 1.00
 * @since 2013/10/23
 * @author Masatoshi Tsuge
 */
class MyMagicEnergyCore : public VvMyActor<GgafLib::DefaultMeshActor> {

public:
    MyMagicEnergyCore(const char* prm_name);

    void onCreateModel() override;

    void initialize() override;

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;


    void onCatchEvent(eventval prm_event_val, void* prm_pSource) override {
    }

    void onHit(const GgafCore::Checker* prm_pThisHitChecker, const GgafCore::Checker* prm_pOppHitChecker) override {
    }

    int isOutOfView() override;

    bool isOutOfSpacetime() const override;

    virtual ~MyMagicEnergyCore();
};

}
#endif /*MYMAGICENERGYCORE_H_*/

