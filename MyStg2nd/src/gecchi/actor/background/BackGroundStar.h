#ifndef BACKGROUNDSTAR_H_
#define BACKGROUNDSTAR_H_
namespace MyStg2nd {

class BackGroundStar : public GgafDx9Core::GgafDx9GeometricActor {

    BackGroundStar001** _papBackGroundStar001;

public:
    BackGroundStar(const char* prm_name);

    /**
     * �������Ă܂�
     */
    void initialize() override;

    /**
     * �������Ă܂�
     */
    void processBehavior() override;


    void processJudgement() override {
    }

    void processPreDraw() override;

    /**
     * �������Ă܂�
     */
    void processDraw() override{
    }

    void processHappen(int prm_no) override {
    }

    void processFinal() override {
    }

    bool processHitChkLogic(GgafCore::GgafActor* prm_pOtherActor) override {
        return false;
    }

    void onHit(GgafCore::GgafActor* prm_pOtherActor) override {
    }


    virtual ~BackGroundStar();
};

}
#endif /*BACKGROUNDSTAR_H_*/

