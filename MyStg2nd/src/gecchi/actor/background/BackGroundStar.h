#ifndef BACKGROUNDSTAR_H_
#define BACKGROUNDSTAR_H_
namespace MyStg2nd {

class BackGroundStar : public GgafDx9Core::GgafDx9GeometricActor {

    BackGroundStar001** _papBackGroundStar001;

public:
    BackGroundStar(const char* prm_name);

    /**
     * 実装してます
     */
    void initialize();

    /**
     * 実装してます
     */
    void processBehavior();


    void processJudgement() {
    }

    void processPreDraw();

    /**
     * 実装してます
     */
    void processDraw(){
    }

    void processHappen(int prm_no) {
    }

    void processFinal() {
    }

    bool processBumpChkLogic(GgafCore::GgafActor* prm_pOtherActor) {
        return false;
    }

    void processOnHit(GgafCore::GgafActor* prm_pOtherActor) {
    }


    virtual ~BackGroundStar();
};

}
#endif /*BACKGROUNDSTAR_H_*/

