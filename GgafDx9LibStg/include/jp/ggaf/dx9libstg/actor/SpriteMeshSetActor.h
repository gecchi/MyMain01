#ifndef SPRITEMESHSETACTOR_H_
#define SPRITEMESHSETACTOR_H_
namespace GgafDx9LibStg {

/**
 * メッシュアクターの具象クラス.
 * GgafDx9Core::GgafDx9SpriteMeshSetActor を空実装した具象アクターです。
 * @version 1.00
 * @since 2010/02/09
 * @author Masatoshi Tsuge
 */
class SpriteMeshSetActor : public GgafDx9Core::GgafDx9SpriteMeshSetActor {

public:
    /** 拡大縮小支援オブジェクト */
    GgafDx9Core::GgafDx9GeometryScaler* _pScaler;

    frame _frame_offset;

    CollisionChecker* _pCollisionChecker;
    /**
     * コンストラクタ
     * DefaultMeshSetActor で使用するモデルIDは避けて下さい。
     * @param prm_name
     * @param prm_model
     * @return
     */
    SpriteMeshSetActor(const char* prm_name, const char* prm_model);

    virtual void onCreateModel() override {
    }

    virtual void initialize() override {
    }

    virtual void processBehavior() override {
    }

    virtual void processJudgement() override {
    }

    virtual void catchEvent(int prm_no) override {
    }

    virtual void processFinal() override {
    }

    virtual void onHit(GgafCore::GgafActor* prm_pOtherActor) override {
    }

    virtual void drawHitArea() override;


    virtual ~SpriteMeshSetActor();
};

}
#endif /*SPRITEMESHSETACTOR_H_*/
