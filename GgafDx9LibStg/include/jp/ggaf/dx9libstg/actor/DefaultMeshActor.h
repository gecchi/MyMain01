#ifndef DEFAULTMESHACTOR_H_
#define DEFAULTMESHACTOR_H_
namespace GgafDx9LibStg {

/**
 * メッシュアクターの具象クラス.
 * GgafDx9Core::GgafDx9MeshActor を空実装した具象アクターです。
 * @version 1.00
 * @since 2009/02/19
 * @author Masatoshi Tsuge
 */
class DefaultMeshActor : public GgafDx9Core::GgafDx9MeshActor {

public:
    /** 拡大縮小支援オブジェクト */
    GgafDx9Core::GgafDx9Scaler* _pScaler;

    frame _offset_frames;

    CollisionChecker* _pCollisionChecker;

    DefaultMeshActor(const char* prm_name, const char* prm_model);

    virtual void onCreateModel() override {
    }

    virtual void initialize() override {
    }

    virtual void processBehavior() override {
    }

    virtual void processJudgement() override {
    }

    virtual void onCatchEvent(UINT32 prm_no, void* prm_pSource) override {
    }

    virtual void processFinal() override {
    }

    virtual void onHit(GgafCore::GgafActor* prm_pOtherActor) override {
    }

    virtual void drawHitArea() override;


    virtual ~DefaultMeshActor();
};

}
#endif /*DEFAULTMESHACTOR_H_*/
