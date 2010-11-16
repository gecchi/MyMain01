#ifndef DEFAULTD3DXANIMESHACTOR_H_
#define DEFAULTD3DXANIMESHACTOR_H_
namespace GgafDx9LibStg {

/**
 * メッシュアクターの具象クラス.
 * GgafDx9Core::GgafDx9D3DXAniMeshActor を空実装した具象アクターです。
 * @version 1.00
 * @since 2009/11/25
 * @author Masatoshi Tsuge
 */
class DefaultD3DXAniMeshActor : public GgafDx9Core::GgafDx9D3DXAniMeshActor {


public:
    frame _frame_offset;

    CollisionChecker* _pCollisionChecker;
    /** 拡大縮小支援オブジェクト */
    GgafDx9Core::GgafDx9GeometricScaler* _pScaler;


    DefaultD3DXAniMeshActor(const char* prm_name, const char* prm_model);

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


    virtual ~DefaultD3DXAniMeshActor();
};

}
#endif /*DEFAULTD3DXANIMESHACTOR_H_*/
