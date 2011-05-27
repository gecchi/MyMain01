#ifndef HOSHIBOSHI001_H_
#define HOSHIBOSHI001_H_
namespace MyStg2nd {

/**
 * 星々ポイントスプライト001 .
 * @version 1.00
 * @since 2010/02/28
 * @author Masatoshi Tsuge
 */
class HoshiBoshi001 : public GgafDx9Core::GgafDx9PointSpriteActor {

public:

    int _CAM_ZF;
    float _far_rate;
    D3DXHANDLE _h_fX_MyShip;
    D3DXHANDLE _h_fY_MyShip;
    D3DXHANDLE _h_fZ_MyShip;
    D3DXHANDLE _h_far_rate;

    HoshiBoshi001(const char* prm_name);

    void onCreateModel() override {
    }

    void initialize() override;

    void onActive() override;

    void processBehavior() override;

    void processSettlementBehavior() override;

    void processJudgement() override;

    void processDraw() override;


    void processFinal() override {
    }

    void onCatchEvent(UINT32 prm_no, void* prm_pSource) override {
    }

    void onHit(GgafCore::GgafActor* prm_pOtherActor) override {
    }

    void drawHitArea() override;

    int isOutOfView() override;

    bool isOutOfUniverse() override;

    virtual ~HoshiBoshi001();



    static void setWorldMatrix_HoshiBoshi001(GgafDx9GeometricActor* prm_pActor, D3DXMATRIX& out_matWorld);
};

}
#endif /*HOSHIBOSHI001_H_*/

