#ifndef FORMATIONACTOR_H_
#define FORMATIONACTOR_H_
namespace GgafDx9LibStg {

/**
 * フォーメーションアクタークラス .
 */
class FormationActor : public GgafDx9Core::GgafDx9UntransformedActor {

public:
    /** 座標移動支援オブジェクト */
    GgafDx9Core::GgafDx9GeometryMover* _pMover;

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

    virtual void processDrawPrior() {
    }

    virtual void processDrawMain() {
    }

    virtual void processDrawTerminate() {
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
