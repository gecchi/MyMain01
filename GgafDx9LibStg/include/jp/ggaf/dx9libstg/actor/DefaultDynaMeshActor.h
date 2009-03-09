#ifndef DEFAULTDYNAMESHACTOR_H_
#define DEFAULTDYNAMESHACTOR_H_
namespace GgafDx9LibStg {

/**
 * メッシュアクターの具象クラス.
 * GgafDx9Core::GgafDx9DynaD3DXMeshActor を空実装した具象アクターです。
 */
class DefaultDynaMeshActor : public GgafDx9Core::GgafDx9DynaD3DXMeshActor {

public:
    DWORD _dwFrameOffset;

    StgChecker* _pChecker;

    DefaultDynaMeshActor(const char* prm_name, const char* prm_model);

    virtual void initialize() {
    }

    virtual void processBehavior() {
    }

    virtual void processJudgement() {
    }

    virtual void processDrawPrior() {
        GgafDx9Core::GgafDx9DynaD3DXMeshActor::processDrawPrior();
    }

    virtual void processDrawMain() {
        GgafDx9Core::GgafDx9DynaD3DXMeshActor::processDrawMain();
    }

    virtual void processDrawTerminate();

    virtual void processHappen(int prm_no) {
    }

    virtual void processFinal() {
    }

    virtual void processOnHit(GgafCore::GgafActor* prm_pActor_Opponent) {
    }

    virtual bool isOffScreen();

    virtual ~DefaultDynaMeshActor();
};

}
#endif /*DEFAULTDYNAMESHACTOR_H_*/
