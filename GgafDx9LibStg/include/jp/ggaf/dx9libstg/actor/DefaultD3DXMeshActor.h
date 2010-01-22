#ifndef DEFAULTD3DXMESHACTOR_H_
#define DEFAULTD3DXMESHACTOR_H_
namespace GgafDx9LibStg {

/**
 * メッシュアクターの具象クラス.
 * GgafDx9Core::GgafDx9D3DXMeshActor を空実装した具象アクターです。
 * @version 1.00
 * @since 2008/11/17
 * @author Masatoshi Tsuge
 */
class DefaultD3DXMeshActor : public GgafDx9Core::GgafDx9D3DXMeshActor {

public:
    DWORD _frame_offset;

    CollisionChecker* _pCollisionChecker;
    /** 拡大縮小支援オブジェクト */
    GgafDx9Core::GgafDx9GeometryScaler* _pScaler;


    DefaultD3DXMeshActor(const char* prm_name, const char* prm_model);

    virtual void initialize() override {
    }

    virtual void processBehavior() override {
    }

    virtual void processJudgement() override {
    }

    virtual void processHappen(int prm_no) override {
    }

    virtual void processFinal() override {
    }

    virtual void onHit(GgafCore::GgafActor* prm_pOtherActor) override {
    }

    virtual void drawHitArea() override;

    virtual ~DefaultD3DXMeshActor();
};

}
#endif /*DEFAULTD3DXMESHACTOR_H_*/
