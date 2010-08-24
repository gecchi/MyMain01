#ifndef MYOPTIONPARENT_H_
#define MYOPTIONPARENT_H_
namespace MyStg2nd {

/**
 * �I�v�V�����̓Z�ߖ��N���X .
 * @version 1.00
 * @since 2006/06/22
 * @author Masatoshi Tsuge
 */
//class MyOptionParent : public GgafDx9LibStg::DefaultMeshActor {
class MyOptionParent : public GgafDx9Core::GgafDx9GeometricActor {


    struct AngRzRy {
        angle Rz;
        angle Ry;
    };


public:
    MyOption* _paMyOption[8];
    MyOptionParentGizmo* _pGizmo;
    MyOptionParentDirectionVector* _pDirectionVector;

    GgafCore::GgafLinkedListRing<GgafDx9LibStg::GeoElement>* _pRing_GeoHistory;
    velo _veloOptionsMv;
    MoveWay _way_myship_prev;

    bool _is_handle_move_mode;
    bool _is_free_from_myship_mode;

    bool _return_to_default_position_seq;
    /** �ΏۃA�N�^�[ */

    /** �����]���p���x */
    angle _angVelo_Turn;
    int _renge;
    MyOptionParent(const char* prm_name);

    virtual void initialize() override;

    virtual void processBehavior() override;

    virtual void processJudgement() override {}

//DefaultMeshActor���ŕ\���������ꍇ�̓R�����g�ɂ��邱��
//GgafDx9GeometricActor�̏ꍇ�̓R�����g���O������
    virtual void processDraw() override {}

    virtual void catchEvent(UINT32 prm_no, void* prm_pSource) override {}

    virtual void processFinal() override {}

    virtual void onHit(GgafCore::GgafActor* prm_pOtherActor) override {}

    //void setTerget(angle prm_angRz_Target, angle prm_angRy_Target);


    virtual ~MyOptionParent();


};

}
#endif /*MYOPTIONPARENT_H_*/

