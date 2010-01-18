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

    bool processBumpChkLogic(GgafCore::GgafActor* prm_pOtherActor) override {
        return false;
    }

    void processOnHit(GgafCore::GgafActor* prm_pOtherActor) override {
    }


    virtual ~BackGroundStar();
};

}
#endif /*BACKGROUNDSTAR_H_*/

