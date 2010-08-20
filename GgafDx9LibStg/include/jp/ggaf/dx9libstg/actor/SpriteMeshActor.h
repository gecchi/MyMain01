#ifndef SPRITEMESHACTOR_H_
#define SPRITEMESHACTOR_H_
namespace GgafDx9LibStg {

/**
 * メッシュアクターの具象クラス.
 * GgafDx9Core::GgafDx9SpriteMeshActor を空実装した具象アクターです。
 * @version 1.00
 * @since 2010/02/09
 * @author Masatoshi Tsuge
 */
class SpriteMeshActor : public GgafDx9Core::GgafDx9SpriteMeshActor {

public:
    /** 拡大縮小支援オブジェクト */
    GgafDx9Core::GgafDx9GeometryScaler* _pScaler;

    frame _frame_offset;

    CollisionChecker* _pCollisionChecker;

    SpriteMeshActor(const char* prm_name, const char* prm_model);

    virtual void onCreateModel() override {
    }

    virtual void initialize() override {
    }

    virtual void processBehavior() override {
    }

    virtual void processJudgement() override {
    }

    virtual void catchEvent(UINT32 prm_no) override {
    }

    virtual void processFinal() override {
    }

    virtual void onHit(GgafCore::GgafActor* prm_pOtherActor) override {
    }

    virtual void drawHitArea() override;


    virtual ~SpriteMeshActor();
};

}
#endif /*SPRITEMESHACTOR_H_*/
