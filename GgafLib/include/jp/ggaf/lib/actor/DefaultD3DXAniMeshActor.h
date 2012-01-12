#ifndef DEFAULTD3DXANIMESHACTOR_H_
#define DEFAULTD3DXANIMESHACTOR_H_
namespace GgafLib {

/**
 * メッシュアクターの具象クラス.
 * GgafDxCore::GgafDxD3DXAniMeshActor を空実装した具象アクターです。
 * @version 1.00
 * @since 2009/11/25
 * @author Masatoshi Tsuge
 */
class DefaultD3DXAniMeshActor : public GgafDxCore::GgafDxD3DXAniMeshActor {


public:
    /** 拡大縮小支援オブジェクト */
    GgafDxCore::GgafDxScaler* _pScaler;
    /** 衝突判定支援オブジェクト */
    CollisionChecker* _pCollisionChecker;

    DefaultD3DXAniMeshActor(const char* prm_name, const char* prm_model, GgafCore::GgafStatus* prm_pStat);

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


    virtual ~DefaultD3DXAniMeshActor();
};

}
#endif /*DEFAULTD3DXANIMESHACTOR_H_*/
