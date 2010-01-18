#ifndef MYOPTIONPARENT_H_
#define MYOPTIONPARENT_H_
namespace MyStg2nd {

class MyOptionParent : public GgafDx9Core::GgafDx9GeometricActor {
//class MyOptionParent : public GgafDx9LibStg::DefaultMeshActor {

public:

    GgafCore::GgafLinkedListRing<GgafDx9LibStg::GeoElement>* _pRing_GeoHistory;

    MoveWay _way_myship_prev;

    /** 対象アクター */

    /** 方向転換角速度 */
    GgafDx9Core::angle _angVelocity_Turn;

    MyOptionParent(const char* prm_name);

    virtual void initialize() override;

    virtual void processBehavior() override;

    virtual void processJudgement() override {}

    virtual void processDraw() override {}

    virtual void processHappen(int prm_no) override {}

    virtual void processFinal() override {}

    virtual void processOnHit(GgafCore::GgafActor* prm_pOtherActor) override {}

    //void setTerget(GgafDx9Core::angle prm_angRz_Target, GgafDx9Core::angle prm_angRy_Target);


    virtual ~MyOptionParent();


};

}
#endif /*MYOPTIONPARENT_H_*/

