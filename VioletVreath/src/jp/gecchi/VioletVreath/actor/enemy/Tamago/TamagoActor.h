#ifndef TAMAGOACTOR_H_
#define TAMAGOACTOR_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/ggaf/lib/actor/DefaultBoneAniMeshActor.h"

namespace VioletVreath {

/**
 * ç≈èâÇ…çÏÇ¡ÇΩ3DÇÃìG(åªç›ñ¢égóp)
 * @version 1.00
 * @since 2008/07/23
 * @author Masatoshi Tsuge
 */
class TamagoActor : public  GgafLib::DefaultBoneAniMeshActor {

    int rnd_;
    double last_time_;

public:
    TamagoActor(const char* prm_name);

    void initialize() override;

    void processBehavior() override;

    void processJudgement() override;

    void onHit(const GgafCore::Checker* prm_pOtherChecker, const GgafCore::Actor* prm_pOtherActor) override;

    int isOutOfView() override {
        return 0;
    }

    bool isOutOfSpacetime() const override {
        return false;
    }

    virtual ~TamagoActor();
};

}
#endif /*TAMAGOACTOR_H_*/

