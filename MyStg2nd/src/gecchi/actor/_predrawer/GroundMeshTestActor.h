#ifndef GROUNDMESHEFFECTACTOR_H_
#define GROUNDMESHEFFECTACTOR_H_
namespace MyStg2nd {

/**
 * プリレンダ用テストアクター .
 * @version 1.00
 * @since 2011/04/18
 * @author Masatoshi Tsuge
 */
class GroundMeshTestActor : public GgafDx9Core::GgafDx9MeshActor {

public:
    GgafDx9Core::GgafDx9Scaler* _pScaler;

    frame _offset_frames;

    GgafDx9LibStg::CollisionChecker* _pCollisionChecker;

    GroundMeshTestActor(const char* prm_name);
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


    virtual ~GroundMeshTestActor();
};

}
#endif /*GROUNDMESHEFFECTACTOR_H_*/
