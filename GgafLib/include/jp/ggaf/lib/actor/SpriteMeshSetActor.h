#ifndef SPRITEMESHSETACTOR_H_
#define SPRITEMESHSETACTOR_H_
namespace GgafLib {

/**
 * メッシュアクターの具象クラス.
 * GgafDxCore::GgafDxSpriteMeshSetActor を空実装した具象アクターです。
 * @version 1.00
 * @since 2010/02/09
 * @author Masatoshi Tsuge
 */
class SpriteMeshSetActor : public GgafDxCore::GgafDxSpriteMeshSetActor {

public:
    /** 拡大縮小支援オブジェクト */
    GgafDxCore::GgafDxScaler* _pScaler;

    frame _offset_frames;

    CollisionChecker* _pCollisionChecker;
    /**
     * コンストラクタ
     * DefaultMeshSetActor で使用するモデルIDは避けて下さい。
     * @param prm_name
     * @param prm_model
     * @return
     */
    SpriteMeshSetActor(const char* prm_name, const char* prm_model, GgafCore::GgafStatus* prm_pStat);

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


    virtual ~SpriteMeshSetActor();
};

}
#endif /*SPRITEMESHSETACTOR_H_*/
