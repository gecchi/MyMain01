#ifndef MYOPTIONPARENT_H_
#define MYOPTIONPARENT_H_
namespace MyStg2nd {

class MyOptionParent : public GgafDx9LibStg::DefaultMeshActor {
//class MyOptionParent : public GgafDx9Core::GgafDx9GeometricActor {


    struct AngRzRy {
        angle Rz;
        angle Ry;
    };


public:
    int _angMyOptionExpanse;
    angvelo _angveloMyOptionExpanseNomal;
    angvelo _angveloMyOptionExpanseSlow;
    MyOption* _paMyOption[8];
    int _stateMyOption[8];
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

//DefaultMeshActorで表示したい場合はコメントにすること
//    virtual void processDraw() override {}

    virtual void processHappen(int prm_no) override {}

    virtual void processFinal() override {}

    virtual void onHit(GgafCore::GgafActor* prm_pOtherActor) override {}

    //void setTerget(angle prm_angRz_Target, angle prm_angRy_Target);


    virtual ~MyOptionParent();


    static bool isRoundPush(vbsta prm_VB, DWORD prm_frame_delay);
};

}
#endif /*MYOPTIONPARENT_H_*/

