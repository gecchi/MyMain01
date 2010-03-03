#ifndef HOSHIBOSHI001_H_
#define HOSHIBOSHI001_H_
namespace MyStg2nd {

/**
 * �����G�t�F�N�g�X�v���C�g001
 * @version 1.00
 * @since 2006/01/10
 * @author Masatoshi Tsuge
 */
class HoshiBoshi001 : public GgafDx9Core::GgafDx9PointSpriteActor {

public:
    DWORD _frame_offset;

    /** �g��k���x���I�u�W�F�N�g */
    GgafDx9Core::GgafDx9GeometryScaler* _pScaler;


    int _CAM_ZF;

    D3DXHANDLE _hMyShip_fX;
    D3DXHANDLE _hMyShip_fY;
    D3DXHANDLE _hMyShip_fZ;


    HoshiBoshi001(const char* prm_name);

    void onCreateModel() override {
    }

    void initialize() override;

    void onActive() override;

    void processBehavior() override;

    void processPreJudgement() override;

    void processJudgement() override;

    void processPreDraw() override;

    void processDraw() override;


    void processFinal() override {
    }

    void processHappen(int prm_no) override {
    }

    void onHit(GgafCore::GgafActor* prm_pOtherActor) override {
    }

    void drawHitArea() override;

    int isOffscreen() override;

    bool isOutOfGameSpace() override;

    virtual ~HoshiBoshi001();
};

}
#endif /*HOSHIBOSHI001_H_*/

