#ifndef MYOPTIONCONTROLLER_H_
#define MYOPTIONCONTROLLER_H_
namespace VioletVreath {

/**
 * オプションの纏め役クラス .
 * @version 1.00
 * @since 2006/06/22
 * @author Masatoshi Tsuge
 */
//class MyOptionController : public GgafLib::DefaultMeshActor {
class MyOptionController : public GgafDxCore::GgafDxGeometricActor {


    struct AngRzRy {
        angle Rz;
        angle Ry;
    };


public:
    /** [r]最大オプション数 */
    static int _max_option_num;
    /** [r]トレース時のオプションとオプションの間隔 */
    static int _o2o;

    MyOption** _papMyOption;
    MyOptionControllerGizmo* _pGizmo;
    MyOptionControllerDirectionVector* _pDirectionVector;

    GgafCore::GgafLinkedListRing<GgafDxCore::GgafDxGeoElem>* _pRing_OpConGeoHistory;
    velo _veloOptionsMv;
    MyShip::MoveWay _way_myship_prev;

    /** [r]現在のオプション数 */
    int _now_option_num;
    /** [r]オプションフリーモードの場合 true */
    bool _is_free_from_myship_mode;
    /** [r]オプションフリーモード時の、オプション操作モードの場合 true */
    bool _is_handle_move_mode;
    /** [r]オプション位置初期化中は true */
    bool _return_to_default_position_seq;


    /** 自機から離れた時（ぐるっとポン時）の座標 */
    coord _X_on_free;
    coord _Y_on_free;
    coord _Z_on_free;


    /** 対象アクター */

    /** 方向転換角速度 */
    ang_velo _angVelo_Turn;
    int _renge;
    MyOptionController(const char* prm_name);

    virtual void initialize() override;

    virtual void onReset() override;

    virtual void onActive() override;

    virtual void processBehavior() override;

    virtual void processJudgement() override {}

//DefaultMeshActor等で表示したい場合はコメントにすること
//GgafDxGeometricActorの場合はコメントを外すこと
    virtual void processDraw() override {}

    virtual void onCatchEvent(hashval prm_no, void* prm_pSource) override {}

    virtual void onHit(GgafCore::GgafActor* prm_pOtherActor) override {}

    //void setTerget(angle prm_angRz_Target, angle prm_angRy_Target);

    void setNumOption(int prm_num);

    void adjustDefaltAngPosition(frame prm_spent_frame);

    virtual ~MyOptionController();


};

}
#endif /*MYOPTIONCONTROLLER_H_*/

