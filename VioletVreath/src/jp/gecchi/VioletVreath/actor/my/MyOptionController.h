#ifndef MYOPTIONCONTROLLER_H_
#define MYOPTIONCONTROLLER_H_
#include "VioletVreath.h"
#include "jp/ggaf/dxcore/actor/GgafDxGeometricActor.h"

#include "jp/ggaf/core/util/GgafLinkedListRing.hpp"
#include "jp/ggaf/dxcore/util/GgafDxGeoElem.h"

namespace VioletVreath {

/**
 * �I�v�V�����̓Z�ߖ��N���X .
 * @version 1.00
 * @since 2006/06/22
 * @author Masatoshi Tsuge
 */
//class MyOptionController : public GgafLib::DefaultMeshSetActor {
class MyOptionController : public GgafDxCore::GgafDxGeometricActor {

public:
    /** [r]�ő�I�v�V������ */
    static int max_option_num_;
    /** [r]�g���[�X���̃I�v�V�����ƃI�v�V�����̊Ԋu */
    static int o2o_;
    /** [r]���ݑ������̃I�v�V������ */
    static int now_option_num_;

    /** ���s�ړ��x�� */
    GgafDxCore::GgafDxAxesMover* pAxsMver_;
    /** ���g�̃I�v�V�����C���f�b�N�X 0 �` now_option_num_-1 */
    int no_;
    MyOption* pOption_;
//    MyOptionControllerGizmo* pGizmo_;
//    MyOptionControllerDirectionVector* pDirectionVector_;

    /** �I�v�V�����R���g���[���[�̖��t���[���̐�΍��W���� */
    GgafCore::GgafLinkedListRing<GgafDxCore::GgafDxGeoElem>* pRing_OptCtrlGeoHistory_;
    velo veloOptionsMv_;


    /** [r]�I�v�V�����t���[���[�h�̏ꍇ true */
    bool is_free_from_myship_mode_;
    /** [r]�I�v�V�����t���[���[�h���́A�I�v�V�������샂�[�h�̏ꍇ true */
    bool is_handle_move_mode_;
    /** [r]�I�v�V�����ʒu���������� true */
    bool return_to_default_position_seq_;

    /** �����]���p���x */
    angvelo angVelo_Turn_;
    int renge_;

    /** �I�v�V�����t���[���[�h�ւ̏����̓_�΃J�E���^�[ */
    int ignite_option_cnt_;
    /** �I�v�V�����t���[���[�h�ֈڍs���邽�߂́A�K�v�ȓ_�΂̃J�E���g���� */
    frame frame_of_ignite_option_;
    /** �I�v�V�����t���[���[�h�ւ̏����̓_�΃J�E���g���[�h�̏ꍇ true */
    bool ignited_option_cnt_mode_;
    /** �_�΂���A�I�v�V�����t���[���[�h�ւ̈ڍs�\�ȏ�Ԃ̏ꍇ true */
    bool was_ignited_option_;

    enum {
        SE_RESTORE  ,
        SE_FREE  ,
    };

public:
    MyOptionController(const char* prm_name, int prm_no);

    virtual void initialize() override;

    virtual void onReset() override;

    virtual void onActive() override;

    virtual void processBehavior() override;

    virtual void processJudgement() override {}

//DefaultMeshActor���ŕ\���������ꍇ�̓R�����g�ɂ��邱��
//GgafDxGeometricActor�̏ꍇ�̓R�����g���O������
    virtual void processDraw() override {}

    virtual void onCatchEvent(hashval prm_no, void* prm_pSource) override {}

    virtual void onHit(const GgafCore::GgafActor* prm_pOtherActor) override {}

    //void setTerget(angle prm_ang_rz_target, angle prm_ang_ry_target);

    static void setNumOption(int prm_num);

    static void adjustDefaltAngPosition(frame prm_spent_frame);
    static void adjustDefaltAngPosition(frame prm_spent_frame, int prm_start_opt_no, int prm_end_opt_no);
    virtual ~MyOptionController();


};

}
#endif /*MYOPTIONCONTROLLER_H_*/

