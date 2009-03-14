#ifndef DEFAULTD3DXMESHACTOR_H_
#define DEFAULTD3DXMESHACTOR_H_
namespace GgafDx9LibStg {

/**
 * メッシュアクターの具象クラス.
 * GgafDx9Core::GgafDx9D3DXMeshActor を空実装した具象アクターです。
 */
class DefaultD3DXMeshActor : public GgafDx9Core::GgafDx9D3DXMeshActor {

public:
    DWORD _dwFrameOffset;

    StgChecker* _pChecker;

    DefaultD3DXMeshActor(const char* prm_name, const char* prm_model, const char* prm_technique);

    virtual void initialize() {
    }

    virtual void processBehavior() {
    }

    virtual void processJudgement() {
    }

    virtual void processDrawPrior() {
        GgafDx9Core::GgafDx9D3DXMeshActor::processDrawPrior();
    }

    virtual void processDrawMain() {
        GgafDx9Core::GgafDx9D3DXMeshActor::processDrawMain();
    }

    virtual void processDrawTerminate();

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
