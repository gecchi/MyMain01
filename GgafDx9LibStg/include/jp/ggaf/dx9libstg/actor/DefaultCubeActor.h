#ifndef DEFAULTCUBEACTOR_H_
#define DEFAULTCUBEACTOR_H_
namespace GgafDx9LibStg {

class DefaultCubeActor : public GgafDx9Core::GgafDx9CubeActor {

public:
    StgChecker* _pStgChecker;

    DefaultCubeActor(const char* prm_name);

    virtual void initialize() {
    }

    virtual void processBehavior() {
    }

    virtual void processJudgement() {
    }

    virtual void processPreDraw() {
        GgafDx9Core::GgafDx9CubeActor::processPreDraw();
    }

    virtual void processDraw() {
        GgafDx9Core::GgafDx9CubeActor::processDraw();
    }

    virtual void processAfterDraw() {
    }

    virtual void processHappen(int prm_no) {
    }

    virtual void processFinal() {
    }

    /**
     * オーバーライド
     * @param prm_pActor_Opponent
     * @return
     */
    virtual bool processBumpChkLogic(GgafCore::GgafActor* prm_pActor_Opponent) {
        return false;
    }

    virtual void processOnHit(GgafCore::GgafActor* prm_pActor_Opponent) {
    }

    virtual ~DefaultCubeActor();

};

}
#endif /*DEFAULTCUBEACTOR_H_*/
