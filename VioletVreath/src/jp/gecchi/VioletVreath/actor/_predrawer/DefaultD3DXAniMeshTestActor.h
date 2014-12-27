#ifndef DEFAULTD3DXANIMESHEFFECTACTOR_H_
#define DEFAULTD3DXANIMESHEFFECTACTOR_H_
#include "VioletVreath.h"
#include "jp/ggaf/lib/actor/DefaultD3DXAniMeshActor.h"

namespace VioletVreath {

/**
 * プリロード用テストアクター .
 * @version 1.00
 * @since 2011/04/18
 * @author Masatoshi Tsuge
 */
class DefaultD3DXAniMeshTestActor : public GgafLib::DefaultD3DXAniMeshActor {

public:

    DefaultD3DXAniMeshTestActor(const char* prm_name);

    void processBehavior() override;

    void processJudgement() override {
    }

    void onHit(GgafCore::GgafActor* prm_pOtherActor) override {
    }

    int isOutOfView() override {
        return 0;
    }

    bool isOutOfUniverse() const override {
        return false;
    }

    virtual ~DefaultD3DXAniMeshTestActor();

};

}
#endif /*DEFAULTD3DXANIMESHEFFECTACTOR_H_*/

