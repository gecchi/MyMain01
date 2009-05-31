#ifndef BACKGROUNDSTAR_H_
#define BACKGROUNDSTAR_H_
namespace MyStg2nd {

class BackGroundStar : public GgafDx9Core::GgafDx9UntransformedActor {

    BackGroundStar001** _papBackGroundStar001;

public:
    BackGroundStar(const char* prm_name);

    void processJudgement() {
    }

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

    /**
     * ÅÉOverRide Ç≈Ç∑ÅÑ
     */
    void initialize();

    /**
     * ÅÉOverRide Ç≈Ç∑ÅÑ
     */
    void processBehavior();

    /**
     * ÅÉOverRide Ç≈Ç∑ÅÑ
     */
    void processDrawMain();

    virtual ~BackGroundStar();
};

}
#endif /*BACKGROUNDSTAR_H_*/

