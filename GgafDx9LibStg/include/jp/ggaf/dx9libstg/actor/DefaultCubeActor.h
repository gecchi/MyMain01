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
    CollisionChecker* _pCollisionChecker;

    DefaultCubeActor(const char* prm_name);

    virtual void onCreateModel() override {
    }

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

    /**
     * オーバーライド
     * @param prm_pOtherActor
     * @return
     */
    virtual bool processHitChkLogic(GgafCore::GgafActor* prm_pOtherActor) override {
        return false;
    }

    virtual void onHit(GgafCore::GgafActor* prm_pOtherActor) override {
    }

    virtual ~DefaultCubeActor();

};

}
#endif /*DEFAULTCUBEACTOR_H_*/
