#ifndef DEFAULTD3DXMESHACTOR_H_
#define DEFAULTD3DXMESHACTOR_H_
namespace GgafDx9LibStg {

/**
 * メッシュアクターの具象クラス.
 * GgafDx9Core::GgafDx9D3DXMeshActor を空実装した具象アクターです。
 */
class DefaultD3DXMeshActor : public GgafDx9Core::GgafDx9D3DXMeshActor {

public:
    DWORD _frame_offset;

    StgChecker* _pStgChecker;
    /** 座標移動支援オブジェクト */
    GgafDx9Core::GgafDx9GeometryMover* _pMover;
    /** 拡大縮小支援オブジェクト */
    GgafDx9Core::GgafDx9GeometryScaler* _pScaler;


    DefaultD3DXMeshActor(const char* prm_name, const char* prm_model);

    virtual void initialize() {
    }

    virtual void processBehavior() {
    }

    virtual void processJudgement() {
    }

    virtual void processPreDraw() {
        GgafDx9Core::GgafDx9D3DXMeshActor::processPreDraw();
    }

    virtual void processDraw() {
        GgafDx9Core::GgafDx9D3DXMeshActor::processDraw();
    }

    virtual void processAfterDraw();

    virtual void processHappen(int prm_no) {
    }

    virtual void processFinal() {
    }

    virtual void processOnHit(GgafCore::GgafActor* prm_pActor_Opponent) {
    }

    virtual ~DefaultD3DXMeshActor();
};

}
#endif /*DEFAULTD3DXMESHACTOR_H_*/
