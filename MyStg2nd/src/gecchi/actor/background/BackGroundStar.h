#ifndef BACKGROUNDSTAR_H_
#define BACKGROUNDSTAR_H_
namespace MyStg2nd {

class BackGroundStar : public GgafDx9Core::GgafDx9GeometricActor {

    BackGroundStar001** _papBackGroundStar001;

public:
    BackGroundStar(const char* prm_name);

    /**
     * ŽÀ‘•‚µ‚Ä‚Ü‚·
     */
    void initialize() override;

    /**
     * ŽÀ‘•‚µ‚Ä‚Ü‚·
     */
    void processBehavior() override;


    void processJudgement() override {
    }

    void processPreDraw() override;

    /**
     * ŽÀ‘•‚µ‚Ä‚Ü‚·
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

