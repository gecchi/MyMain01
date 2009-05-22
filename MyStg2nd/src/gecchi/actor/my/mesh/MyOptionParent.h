#ifndef MYOPTIONPARENT_H_
#define MYOPTIONPARENT_H_
namespace MyStg2nd {

class MyOptionParent : public GgafDx9Core::GgafDx9UntransformedActor {

public:
    /** ���W�ړ��x���I�u�W�F�N�g */
    GgafDx9Core::GgafDx9GeometryMover* _pMover;

    GgafCore::GgafLinkedListRing<GgafDx9LibStg::GeoElement>* _pRing_GeoHistory;

    MoveWay _way_myship_prev;

    /** �ΏۃA�N�^�[ */

    /** �����]���p���x */
    GgafDx9Core::angle _angVelocity_Turn;

    MyOptionParent(const char* prm_name);

    virtual void initialize();


    virtual void processBehavior();


    virtual void processJudgement() {
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


    void setTerget(GgafDx9Core::angle prm_angRz_Target, GgafDx9Core::angle prm_angRy_Target);


    virtual ~MyOptionParent();


};

}
#endif /*MYOPTIONPARENT_H_*/

