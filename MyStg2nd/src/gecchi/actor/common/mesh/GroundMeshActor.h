#ifndef GROUNDMESHACTOR_H_
#define GROUNDMESHACTOR_H_
namespace MyStg2nd {

/**
 * メッシュアクターの具象クラス.
 * GgafDx9Core::GgafDx9MeshActor を空実装した具象アクターです。
 */
class GroundMeshActor : public GgafDx9Core::GgafDx9MeshActor {

public:
    GgafDx9Core::GgafDx9GeometryScaler* _pScaler;

    DWORD _frame_offset;

    GgafDx9LibStg::CollisionChecker* _pCollisionChecker;

    GroundMeshActor(const char* prm_name, const char* prm_model);

    virtual void initialize() override {
    }

    virtual void processBehavior() override {
    }

    virtual void processJudgement() override {
    }

//    /**
//     * フレームワークオーバーライド
//     */
//    virtual void processPreDraw() override;
    virtual void processDraw() override;

    virtual void processHappen(int prm_no) override {
    }

    virtual void processFinal() override {
    }

    virtual void processOnHit(GgafCore::GgafActor* prm_pOtherActor) override {
    }

    virtual void drawHitArea() override;


    virtual ~GroundMeshActor();
};

}
#endif /*GROUNDMESHACTOR_H_*/
