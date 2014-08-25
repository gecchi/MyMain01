#ifndef MYOPTIONCONTROLLERGIZMO_H_
#define MYOPTIONCONTROLLERGIZMO_H_
#include "VioletVreath.h"
#include "jp/ggaf/lib/actor/DefaultMeshActor.h"

namespace VioletVreath {

/**
 * オプションの纏め役クラスのギズモ表示クラス .
 * @version 1.00
 * @since 2010/03/16
 * @author Masatoshi Tsuge
 */
class MyOptionControllerGizmo : public GgafLib::DefaultMeshActor {

public:
    int ptn_no_;

public:
   MyOptionControllerGizmo(const char* prm_name);

    void onCreateModel() override {
    }

    void initialize() override;

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;

    void onCatchEvent(hashval prm_no, void* prm_pSource) override {
    }

    void onHit(GgafCore::GgafActor* prm_pOtherActor) override {
    }

    void drawHitArea() override;

    int isOutOfView() override;

    bool isOutOfUniverse() override;

    virtual ~MyOptionControllerGizmo();
};

}
#endif /*MYOPTIONCONTROLLERGIZMO_H_*/

