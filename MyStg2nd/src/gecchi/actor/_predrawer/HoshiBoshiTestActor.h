#ifndef HOSHIBOSHIEFFECTACTOR_H_
#define HOSHIBOSHIEFFECTACTOR_H_
namespace MyStg2nd {


/**
 * プリレンダ用テストアクター .
 * @version 1.00
 * @since 2011/04/18
 * @author Masatoshi Tsuge
 */
class HoshiBoshiTestActor : public GgafDx9Core::GgafDx9PointSpriteActor {

public:

    int _CAM_ZF;
    D3DXHANDLE _h_fX_MyShip;
    D3DXHANDLE _h_fY_MyShip;
    D3DXHANDLE _h_fZ_MyShip;


    HoshiBoshiTestActor(const char* prm_name);

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

    virtual ~HoshiBoshiTestActor();



    static void setWorldMatrix_HoshiBoshiTestActor(GgafDx9GeometricActor* prm_pActor, D3DXMATRIX& out_matWorld);
};

}
#endif /*HOSHIBOSHIEFFECTACTOR_H_*/

