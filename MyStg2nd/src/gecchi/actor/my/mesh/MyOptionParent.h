#ifndef MYOPTIONPARENT_H_
#define MYOPTIONPARENT_H_
namespace MyStg2nd {

class MyOptionParent : public GgafDx9LibStg::DefaultMeshActor {

public:

    MoveWay _way_myship_prev;

    /** �ΏۃA�N�^�[ */
    /** �����]���p���x */
    GgafDx9Core::angle _angVelocity_Turn;

    MyOptionParent(const char* prm_name);

    /**
     * ��OverRide �ł���
     */
    void initialize();

    /**
     * ��OverRide �ł���
     */
    void processBehavior();

    /**
     * ��OverRide �ł���
     */
    void processJudgement();

    /**
     * ��OverRide �ł���
     */
    void processOnHit(GgafCore::GgafActor* prm_pActor_Opponent);

    void setTerget(GgafDx9Core::angle prm_angRz_Target, GgafDx9Core::angle prm_angRy_Target);


    virtual ~MyOptionParent();


};

}
#endif /*MYOPTIONPARENT_H_*/

