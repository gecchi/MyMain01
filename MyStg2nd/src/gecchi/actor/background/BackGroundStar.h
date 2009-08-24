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
    void initialize();

    /**
     * ŽÀ‘•‚µ‚Ä‚Ü‚·
     */
    void processBehavior();


    void processPreJudgement();


    void processJudgement() {
    }

    void processPreDraw();

    /**
     * ŽÀ‘•‚µ‚Ä‚Ü‚·
     */
    void processDraw();

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

