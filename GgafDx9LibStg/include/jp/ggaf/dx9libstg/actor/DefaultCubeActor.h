#ifndef DEFAULTCUBEACTOR_H_
#define DEFAULTCUBEACTOR_H_
namespace GgafDx9LibStg {

/**
 * 当たり判定表示用キューブ .
 * @version 1.00
 * @since 2008/10/10
 * @author Masatoshi Tsuge
 */
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

    virtual void processHappen(int prm_no) {
    }

    virtual void processFinal() {
    }

    /**
     * オーバーライド
     * @param prm_pOtherActor
     * @return
     */
    virtual bool processBumpChkLogic(GgafCore::GgafActor* prm_pOtherActor) {
        return false;
    }

    virtual void processOnHit(GgafCore::GgafActor* prm_pOtherActor) {
    }

    virtual ~DefaultCubeActor();

};

}
#endif /*DEFAULTCUBEACTOR_H_*/
