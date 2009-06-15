#ifndef BACKGROUNDSTAR_H_
#define BACKGROUNDSTAR_H_
namespace MyStg2nd {

class BackGroundStar : public GgafDx9Core::GgafDx9UntransformedActor {

    BackGroundStar001** _papBackGroundStar001;

public:
    BackGroundStar(const char* prm_name);

    /**
     * ŽÀ‘•‚µ‚Ä‚Ü‚·
     */
    void initialize();

    /**
     * ŽÀ‘•‚µ‚Ä‚Ü‚·
     */
    void processBehavior();

    void processJudgement() {
    }

    void processDrawPrior();

    /**
     * ŽÀ‘•‚µ‚Ä‚Ü‚·
     */
    void processDrawMain();


    void processDrawTerminate() {
    }

    void processHappen(int prm_no) {
    }

    void processFinal() {
    }

    bool processBumpChkLogic(GgafCore::GgafActor* prm_pActor_Opponent) {
        return false;
    }

    void processOnHit(GgafCore::GgafActor* prm_pActor_Opponent) {
    }


    virtual ~BackGroundStar();
};

}
#endif /*BACKGROUNDSTAR_H_*/

