#ifndef MYOPTIONCONTROLLER_H_
#define MYOPTIONCONTROLLER_H_
namespace VioletVreath {

/**
 * �I�v�V�����̓Z�ߖ��N���X .
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
    /** [r]�ő�I�v�V������ */
    static int _max_option_num;
    /** [r]�g���[�X���̃I�v�V�����ƃI�v�V�����̊Ԋu */
    static int _o2o;

    MyOption** _papMyOption;
    MyOptionControllerGizmo* _pGizmo;
    MyOptionControllerDirectionVector* _pDirectionVector;

    GgafCore::GgafLinkedListRing<GgafDxCore::GgafDxGeoElem>* _pRing_OpConGeoHistory;
    velo _veloOptionsMv;
    MyShip::MoveWay _way_myship_prev;

    /** [r]���݂̃I�v�V������ */
    int _now_option_num;
    /** [r]�I�v�V�����t���[���[�h�̏ꍇ true */
    bool _is_free_from_myship_mode;
    /** [r]�I�v�V�����t���[���[�h���́A�I�v�V�������샂�[�h�̏ꍇ true */
    bool _is_handle_move_mode;
    /** [r]�I�v�V�����ʒu���������� true */
    bool _return_to_default_position_seq;


    /** ���@���痣�ꂽ���i������ƃ|�����j�̍��W */
    coord _X_on_free;
    coord _Y_on_free;
    coord _Z_on_free;


    /** �ΏۃA�N�^�[ */

    /** �����]���p���x */
    ang_velo _angVelo_Turn;
    int _renge;
    MyOptionController(const char* prm_name);

    virtual void initialize() override;

    virtual void onReset() override;

    virtual void onActive() override;

    virtual void processBehavior() override;

    virtual void processJudgement() override {}

//DefaultMeshActor���ŕ\���������ꍇ�̓R�����g�ɂ��邱��
//GgafDxGeometricActor�̏ꍇ�̓R�����g���O������
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

