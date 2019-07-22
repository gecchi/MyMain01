#ifndef MYMAGICENERGYCORE_H_
#define MYMAGICENERGYCORE_H_
#include "VioletVreath.h"
#include "jp/gecchi/VioletVreath/actor/VvMyActor.hpp"
#include "jp/ggaf/lib/actor/DefaultMeshActor.h"

namespace VioletVreath {

/**
 * MP�G�l���M�[�j .
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


    void onCatchEvent(hashval prm_no, void* prm_pSource) override {
    }

    void onHit(const GgafCore::Actor* prm_pOtherActor) override {
    }

    int isOutOfView() override;

    bool isOutOfSpacetime() const override;

    virtual ~MyMagicEnergyCore();
};

}
#endif /*MYMAGICENERGYCORE_H_*/

