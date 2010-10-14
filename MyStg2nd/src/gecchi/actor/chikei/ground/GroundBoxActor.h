#ifndef GROUNDBOXACTOR_H_
#define GROUNDBOXACTOR_H_


#define FACE_A_IDX 5
#define FACE_B_IDX 4
#define FACE_C_IDX 3
#define FACE_D_IDX 2
#define FACE_E_IDX 1
#define FACE_F_IDX 0


namespace MyStg2nd {

/**
 */
class GroundBoxActor : public GgafDx9Core::GgafDx9MeshSetActor {

public:

    int _box_draw_face;

    int _box_dep;
    int _box_width;
    int _box_height;

    int _ground_speed;

    D3DXHANDLE _ahDrawFace[16];
    D3DXHANDLE _h_box_dep;
    D3DXHANDLE _h_box_width;
    D3DXHANDLE _h_box_height;




    GgafDx9Core::GgafDx9GeometryScaler* _pScaler;

    frame _frame_offset;

    GgafDx9LibStg::CollisionChecker* _pCollisionChecker;

    GroundBoxActor(const char* prm_name, const char* prm_model, int prm_box_dep, int prm_box_width, int prm_box_height);


    virtual void config(int prm_box_draw_face, int* prm_aColliBoxStretch);



    virtual void onCreateModel() override {
    }
    virtual void initialize() override;

    virtual void onActive() override;


    virtual void processBehavior() override;

    virtual void processJudgement() override;

//    /**
//     * フレームワークオーバーライド
//     */
//    virtual void processPreDraw() override;
    virtual void processDraw() override;

    virtual void catchEvent(UINT32 prm_no, void* prm_pSource) override {
    }

    virtual void processFinal() override {
    }

    virtual void onHit(GgafCore::GgafActor* prm_pOtherActor) override {
    }

    virtual void drawHitArea() override;



    virtual ~GroundBoxActor();
};

}
#endif /*GROUNDBOXACTOR_H_*/
