#ifndef MYOPTIONPARENT_H_
#define MYOPTIONPARENT_H_
namespace MyStg2nd {

class MyOptionParent : public GgafDx9LibStg::DefaultMeshActor {

public:

    MoveWay _way_myship_prev;

    /** 対象アクター */
    /** 方向転換角速度 */
    GgafDx9Core::angle _angVelocity_Turn;

    MyOptionParent(const char* prm_name);

    /**
     * ＜OverRide です＞
     */
    void initialize();

    /**
     * ＜OverRide です＞
     */
    void processBehavior();

    /**
     * ＜OverRide です＞
     */
    void processJudgement();

    /**
     * ＜OverRide です＞
     */
    void processOnHit(GgafCore::GgafActor* prm_pActor_Opponent);

    void setTerget(GgafDx9Core::angle prm_angRz_Target, GgafDx9Core::angle prm_angRy_Target);


    virtual ~MyOptionParent();


};

}
#endif /*MYOPTIONPARENT_H_*/

