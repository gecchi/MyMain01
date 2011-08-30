#ifndef GROUNDMESHACTOR_H_
#define GROUNDMESHACTOR_H_
namespace MyStg2nd {

/**
 * メッシュアクターの具象クラス.
 * GgafDx9Core::GgafDx9MeshActor を空実装した具象アクターです。
 */
class GroundMeshActor : public GgafDx9Core::GgafDx9MeshActor {

public:
    GgafDx9Core::GgafDx9Scaler* _pScaler;

    frame _offset_frames;

    GgafDx9LibStg::CollisionChecker* _pCollisionChecker;

    GroundMeshActor(const char* prm_name, const char* prm_model, GgafCore::GgafStatus* prm_pStat);
    virtual void onCreateModel() override {
    }
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

    virtual void onCatchEvent(UINT32 prm_no, void* prm_pSource) override {
    }

    virtual void processFinal() override {
    }

    virtual void onHit(GgafCore::GgafActor* prm_pOtherActor) override {
    }

    virtual void drawHitArea() override;


    virtual ~GroundMeshActor();
};

}
#endif /*GROUNDMESHACTOR_H_*/
