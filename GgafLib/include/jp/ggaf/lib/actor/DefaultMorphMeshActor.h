#ifndef DEFAULTMORPHMESHACTOR_H_
#define DEFAULTMORPHMESHACTOR_H_
namespace GgafLib {

/**
 * モーフメッシュアクターの具象クラス.
 * GgafDxCore::GgafDxMorphMeshActor を空実装した具象アクターです。
 * @version 1.00
 * @since 2009/05/08
 * @author Masatoshi Tsuge
 */
class DefaultMorphMeshActor : public GgafDxCore::GgafDxMorphMeshActor {

public:
    frame _offset_frames;
    /** 拡大縮小支援オブジェクト */
    GgafDxCore::GgafDxScaler* _pScaler;
	/** モーフィング支援オブジェクト */
    GgafDxCore::GgafDxMorpher* _pMorpher;
	/** チェッカー */
    CollisionChecker* _pCollisionChecker;

    DefaultMorphMeshActor(const char* prm_name, const char* prm_model_id, GgafCore::GgafStatus* prm_pStat);

    virtual void onCreateModel() override {
    }

    virtual void initialize() override {
    }

    virtual void processBehavior() override {
    }

    virtual void processJudgement() override {
    }

    virtual void onCatchEvent(hashval prm_no, void* prm_pSource) override {
    }

    virtual void processFinal() override {
    }

    virtual void onHit(GgafCore::GgafActor* prm_pOtherActor) override {
    }

    virtual void drawHitArea() override;

    virtual ~DefaultMorphMeshActor();
};

}
#endif /*DEFAULTMORPHMESHACTOR_H_*/
