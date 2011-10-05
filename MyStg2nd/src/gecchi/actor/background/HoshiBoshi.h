#ifndef HOSHIBOSHI_H_
#define HOSHIBOSHI_H_
namespace MyStg2nd {

/**
 * 星々ポイントスプライト001 .
 * @version 1.00
 * @since 2010/02/28
 * @author Masatoshi Tsuge
 */
class HoshiBoshi : public GgafDxCore::GgafDxPointSpriteActor {

public:

    coord _CAM_ZF;
    float _far_rate;
    D3DXHANDLE _h_fX_MyShip;
    D3DXHANDLE _h_fY_MyShip;
    D3DXHANDLE _h_fZ_MyShip;
    D3DXHANDLE _h_far_rate;

    HoshiBoshi(const char* prm_name, const char* prm_model_id);

    virtual void onCreateModel() override {
    }

    virtual void initialize() override;

    virtual void onActive() override;

    virtual void processBehavior() override;

    virtual void processSettlementBehavior() override;

    virtual void processJudgement() override;

    virtual void processDraw() override;

    virtual void processFinal() override {
    }

    virtual void onCatchEvent(UINT32 prm_no, void* prm_pSource) override {
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

