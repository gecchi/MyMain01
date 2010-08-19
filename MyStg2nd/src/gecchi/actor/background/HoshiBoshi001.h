#ifndef HOSHIBOSHI001_H_
#define HOSHIBOSHI001_H_
namespace MyStg2nd {

/**
 * 爆発エフェクトスプライト001
 * @version 1.00
 * @since 2006/01/10
 * @author Masatoshi Tsuge
 */
class HoshiBoshi001 : public GgafDx9Core::GgafDx9PointSpriteActor {

public:
    frame _frame_offset;

    /** 拡大縮小支援オブジェクト */
    GgafDx9Core::GgafDx9GeometryScaler* _pScaler;


    int _CAM_ZF;

    D3DXHANDLE _h_fX_MyShip;
    D3DXHANDLE _h_fY_MyShip;
    D3DXHANDLE _h_fZ_MyShip;


    HoshiBoshi001(const char* prm_name);

    void onCreateModel() override {
    }

    void initialize() override;

    void onActive() override;

    void processBehavior() override;

    void processSettlementBehavior() override;

    void processJudgement() override;

//    void processPreDraw() override;

    void processDraw() override;


    void processFinal() override {
    }

    void catchEvent(int prm_no) override {
    }

    void onHit(GgafCore::GgafActor* prm_pOtherActor) override {
    }

    void drawHitArea() override;

    int isOffscreen() override;

    bool isOutOfGameSpace() override;

    virtual ~HoshiBoshi001();



    static void setWorldMatrix_HoshiBoshi001(GgafDx9GeometricActor* prm_pActor, D3DXMATRIX& out_matWorld);
};

}
#endif /*HOSHIBOSHI001_H_*/

