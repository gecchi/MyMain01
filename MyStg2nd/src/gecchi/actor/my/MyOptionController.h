#ifndef MYOPTIONCONTROLLER_H_
#define MYOPTIONCONTROLLER_H_
namespace MyStg2nd {

/**
 * オプションの纏め役クラス .
 * @version 1.00
 * @since 2006/06/22
 * @author Masatoshi Tsuge
 */
//class MyOptionController : public GgafDx9LibStg::DefaultMeshActor {
class MyOptionController : public GgafDx9Core::GgafDx9GeometricActor {


    struct AngRzRy {
        angle Rz;
        angle Ry;
    };


public:
    MyOption** _papMyOption;
    MyOptionControllerGizmo* _pGizmo;
    MyOptionControllerDirectionVector* _pDirectionVector;

    GgafCore::GgafLinkedListRing<GgafDx9LibStg::GeoElement>* _pRing_GeoHistory;
    velo _veloOptionsMv;
    MoveWay _way_myship_prev;
    static int _max_option_num;
    int _now_option_num;
    bool _is_handle_move_mode;
    bool _is_free_from_myship_mode;

    bool _return_to_default_position_seq;
    /** 対象アクター */

    /** 方向転換角速度 */
    angle _angVelo_Turn;
    int _renge;
    MyOptionController(const char* prm_name);

    virtual void initialize() override;

    virtual void processBehavior() override;

    virtual void processJudgement() override {}

//DefaultMeshActor等で表示したい場合はコメントにすること
//GgafDx9GeometricActorの場合はコメントを外すこと
    virtual void processDraw() override {}

    virtual void catchEvent(UINT32 prm_no, void* prm_pSource) override {}

    virtual void processFinal() override {}

    virtual void onHit(GgafCore::GgafActor* prm_pOtherActor) override {}

    //void setTerget(angle prm_angRz_Target, angle prm_angRy_Target);


    virtual ~MyOptionController();


};

}
#endif /*MYOPTIONCONTROLLER_H_*/

