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
    DWORD _frame_offset;

    StgChecker* _pStgChecker;
    /** 拡大縮小支援オブジェクト */
    GgafDx9Core::GgafDx9GeometryScaler* _pScaler;


    DefaultD3DXAniMeshActor(const char* prm_name, const char* prm_model);

    virtual void initialize() {
    }

    virtual void processBehavior() {
    }

    virtual void processJudgement() {
    }

    virtual void processHappen(int prm_no) {
    }

    virtual void processFinal() {
    }

    virtual void processOnHit(GgafCore::GgafActor* prm_pActor_Opponent) {
    }

    virtual void drawHitArea();


    virtual ~DefaultD3DXAniMeshActor();
};

}
#endif /*DEFAULTD3DXANIMESHACTOR_H_*/
