#ifndef MYOPTIONPARENT_H_
#define MYOPTIONPARENT_H_
namespace MyStg2nd {

class MyOptionParent : public GgafDx9Core::GgafDx9GeometricActor {
//class MyOptionParent : public GgafDx9LibStg::DefaultMeshActor {

    struct AngRzRy {
        angle Rz;
        angle Ry;
    };


public:

    AngRzRy angtarget[5][27];

    GgafCore::GgafLinkedListRing<GgafDx9LibStg::GeoElement>* _pRing_GeoHistory;

    MoveWay _way_myship_prev;

    bool _is_rotate;

    /** 対象アクター */

    /** 方向転換角速度 */
    angle _angVelo_Turn;

    MyOptionParent(const char* prm_name);

    virtual void initialize() override;

    virtual void processBehavior() override;

    virtual void processJudgement() override {}

    virtual void processDraw() override {}

    virtual void processHappen(int prm_no) override {}

    virtual void processFinal() override {}

    virtual void onHit(GgafCore::GgafActor* prm_pOtherActor) override {}

    //void setTerget(angle prm_angRz_Target, angle prm_angRy_Target);


    virtual ~MyOptionParent();


};

}
#endif /*MYOPTIONPARENT_H_*/

