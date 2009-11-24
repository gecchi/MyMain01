#ifndef FORMATIONACTOR_H_
#define FORMATIONACTOR_H_
namespace GgafDx9LibStg {

/**
 * フォーメーションアクタークラス .
 * @version 1.00
 * @since 2008/08/08
 * @author Masatoshi Tsuge
 */
class FormationActor : public GgafDx9Core::GgafDx9GeometricActor {

public:

    FormationActor(const char* prm_name);

    virtual void initialize() {
    }

    virtual void processBehavior() {
    }

    /**
     * サブが無ければ死
     * ＜OverRide です＞<BR>
     */
    virtual void processJudgement() {
        if (getSubFirst() == NULL) {
            adios();
        }
    }

    virtual void processDraw() {
    }

    virtual void processHappen(int prm_no) {
    }

    virtual void processFinal() {
    }

    virtual void processOnHit(GgafCore::GgafActor* prm_pActor_Opponent) {
    }

    virtual ~FormationActor();
};

}
#endif /*FORMATIONACTOR_H_*/
