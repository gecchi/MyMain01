#ifndef GROUNDBOXACTOR_H_
#define GROUNDBOXACTOR_H_
namespace MyStg2nd {

/**
 */
class GroundBoxActor : public GgafDx9Core::GgafDx9MeshSetActor {

public:

    int _box_type;


















    GgafDx9Core::GgafDx9GeometryScaler* _pScaler;

    frame _frame_offset;

    GgafDx9LibStg::CollisionChecker* _pCollisionChecker;

    GroundBoxActor(const char* prm_name, const char* prm_model);
    virtual void onCreateModel() override {
    }
    virtual void initialize() override;

    virtual void onActive() override;


    virtual void processBehavior() override;

    virtual void processJudgement() override {
    }

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
