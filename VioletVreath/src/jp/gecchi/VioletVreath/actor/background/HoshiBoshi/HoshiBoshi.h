#ifndef HOSHIBOSHI_H_
#define HOSHIBOSHI_H_
#include "VioletVreath.h"
#include "jp/ggaf/dxcore/actor/GgafDxPointSpriteActor.h"

namespace VioletVreath {

/**
 * 星々ポイントスプライト001 .
 * @version 1.00
 * @since 2010/02/28
 * @author Masatoshi Tsuge
 */
class HoshiBoshi : public GgafDxCore::GgafDxPointSpriteActor {

public:

    coord CAM_ZF_;
    float far_rate_;
    D3DXHANDLE h_fX_MyShip_;
    D3DXHANDLE h_fY_MyShip_;
    D3DXHANDLE h_fZ_MyShip_;
    D3DXHANDLE h_far_rate_;

public:
    HoshiBoshi(const char* prm_name, const char* prm_model_id);

    virtual void onCreateModel() override {
    }

    virtual void initialize() override;

    virtual void onActive() override;

    virtual void processBehavior() override;

    virtual void processSettlementBehavior() override;

    virtual void processJudgement() override;

    virtual void processDraw() override;

    virtual void onCatchEvent(hashval prm_no, void* prm_pSource) override {
    }

    virtual void onHit(GgafCore::GgafActor* prm_pOtherActor) override {
    }

    virtual void drawHitArea() override;

    virtual int isOutOfView() override;

    virtual bool isOutOfUniverse() override;

    virtual ~HoshiBoshi();



    static void setWorldMatrix_HoshiBoshi(GgafDxGeometricActor* prm_pActor, D3DXMATRIX& out_matWorld);
};

}
#endif /*HOSHIBOSHI_H_*/

