#ifndef MYOPTIONCONTROLLER_H_
#define MYOPTIONCONTROLLER_H_
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
    int no_;
    MyOption* pOption_;
//    MyOptionControllerGizmo* pGizmo_;
//    MyOptionControllerDirectionVector* pDirectionVector_;

    GgafCore::GgafLinkedListRing<GgafDxCore::GgafDxGeoElem>* pRing_OptCtrlGeoHistory_;
    velo veloOptionsMv_;

    /** [r]���݂̃I�v�V������ */
    static int now_option_num_;
    /** [r]�I�v�V�����t���[���[�h�̏ꍇ true */
    bool is_free_from_myship_mode_;
    /** [r]�I�v�V�����t���[���[�h���́A�I�v�V�������샂�[�h�̏ꍇ true */
    bool is_handle_move_mode_;
    /** [r]�I�v�V�����ʒu���������� true */
    bool return_to_default_position_seq_;

    /** �����]���p���x */
    angvelo angVelo_Turn_;
    int renge_;

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

    virtual void onHit(GgafCore::GgafActor* prm_pOtherActor) override {}

    //void setTerget(angle prm_angRz_Target, angle prm_angRy_Target);

    static void setNumOption(int prm_num);

    static void adjustDefaltAngPosition(frame prm_spent_frame);

    virtual ~MyOptionController();


};

}
#endif /*MYOPTIONCONTROLLER_H_*/

