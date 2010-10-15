#ifndef WALLACTOR_H_
#define WALLACTOR_H_


#define FACE_A_IDX 5
#define FACE_B_IDX 4
#define FACE_C_IDX 3
#define FACE_D_IDX 2
#define FACE_E_IDX 1
#define FACE_F_IDX 0


namespace GgafDx9LibStg {

/**
 */
class WallActor : public GgafDx9Core::GgafDx9MeshSetActor {

public:

    int _wall_draw_face;

    int _wall_dep;
    int _wall_width;
    int _wall_height;
    int _ground_speed;

    D3DXHANDLE _ahDrawFace[16];
    D3DXHANDLE _h_distance_AlphaTarget;
    GgafDx9Core::GgafDx9GeometricActor* _pTarget_FrontAlpha;
    WalledScene* _pWalledScene;
    GgafDx9Core::GgafDx9GeometryScaler* _pScaler;

    frame _frame_offset;

    GgafDx9LibStg::CollisionChecker* _pCollisionChecker;

    WallActor(const char* prm_name, const char* prm_model);


    virtual void config(int prm_wall_draw_face, int* prm_aColliBoxStretch);



    virtual void onCreateModel() override {
    }
    virtual void initialize() override;

    virtual void onActive() override;

    virtual void processDraw() override;

    virtual void processBehavior() override;

    virtual void processJudgement() override;


    virtual void catchEvent(UINT32 prm_no, void* prm_pSource) override {
    }

    virtual void processFinal() override {
    }

    virtual void onHit(GgafCore::GgafActor* prm_pOtherActor) override {
    }

    virtual void drawHitArea() override;

    void enableFrontAlpha(GgafDx9Core::GgafDx9GeometricActor* prm_pTarget_FrontAlpha) {
        _pTarget_FrontAlpha = prm_pTarget_FrontAlpha;
    }

    virtual ~WallActor();
};

}
#endif /*WALLACTOR_H_*/
