#ifndef MYOPTION_H_
#define MYOPTION_H_
#include "VioletVreath.h"
#include "jp/ggaf/lib/actor/DefaultMeshSetActor.h"


#define OPT_RADIUS_POS_MIN (PX_C(30))
#define OPT_RADIUS_POS_MAX (PX_C(1000))

namespace VioletVreath {

//class MyOption : public GgafLib::DefaultMorphMeshActor {
class MyOption : public GgafLib::DefaultMeshSetActor {


private:
    /**
     * ����~�����a���Đݒ肷�� .
     * ����̏������ł̂݌Ăяo���\�B
     * @param prm_radius ���a
     */
    void setRadiusPosition(int prm_radius);

    /**
     * ����~�����a�������ōĐݒ肷�� .
     * ����̏������ł̂݌Ăяo���\�B
     * @param prm_radius_offset ���a����
     * @param prm_min_radius �Œᔼ�a����
     */
    void addRadiusPosition(int prm_radius_offset, int prm_min_radius = OPT_RADIUS_POS_MIN, int prm_max_radius = OPT_RADIUS_POS_MAX);

public:
    enum {
        SE_FIRE_LASER  ,
        SE_FIRE_SHOT   ,
        SE_FIRE_TORPEDO,
    };

    //�ꎞ�ϐ��B
    coord x_org_,y_org_,z_org_;

    /** [r]�e�A�N�^�[ */
    MyOptionController* pOptionCtrler_;
    /** [r]���g�̃I�v�V�����ԍ�(�O�`�E�E�E) */
    int no_;

    /** [r]���b�N�I���R���g���[���[ */
    MyLockonController* pLockonCtrler_;
    /** [r]�����R���g���[���[ */
    MyTorpedoController* pTorpedoCtrler_;
    /** [r]���[�U�[�`�b�v�̃f�|�W�g�� */
    GgafLib::LaserChipDepository* pLaserChipDepo_;
    /** [r]�V���b�g�̃f�|�W�g�� */
    GgafCore::GgafActorDepository* pDepo_MyOptionShot_;
    /** [r]�X�i�C�v�V���b�g�̃f�|�W�g�� */
    GgafCore::GgafActorDepository* pDepo_MySnipeOptionShot_;
    /** [r]���[�U�[���˒��̃G�t�F�N�g */
    GgafDxCore::GgafDxFigureActor* pEffect_LaserIrradiate_;

    /** [r]�v�Z���ꂽ���݂̐���~���ړ��p���x�i�ǂݏo����p�j */
    angvelo angveloMove_;
    /** [r]�~���㏉���ʒu�p�x�i���͊p�j�iinitialize()�܂łɕύX�^�f�t�H���g=0�j */
    angle angPosition_;
    /** [r]���݂̐���~�����a�iinitialize()�܂łɕύX�^�f�t�H���g=200000�j */
    int radiusPosition_;
    /** [r/w]����~���ړ����x�i�����ύX�^�f�t�H���g=1000�j */
    velo veloMv_;
    /** [r/w]�I�v�V�����̍L�����]�p�i�����ύX�^�f�t�H���g=0 MyOptionController�Ɠ��������i�O���j�������Ă���j */
    angle angExpanse_;

    /** [r]�����~����p�x�ʒu */
    angle angPosition_base_;
    /** [r]��������~�����a */
    int radiusPosition_base_;
    /** [r]��~���ɖ߂�ׂ���~�����a */
    int radiusPosition_stopping_;
    /** [r]���a�ړ����x(OPTION���쎞) */
    int radiusPosition_velo_;

    /** [r]��������~���ړ����x */
    velo veloMv_base_;
    /** [r]�����I�v�V�����̍L�����]�p */
    angle angExpanse_default_;

    /** �I�v�V�����̍L�����]�p���x�i�ʏ펞�j */
    angvelo angveloExpanseNomal_;
    /** �I�v�V�����̍L�����]�p���x�i���������j */
    angvelo angveloExpanseSlow_;

    /** �I�v�V�����̏����ʒu�Ɏ����߂���s���Ă���Œ��� true */
    bool return_to_base_radiusPosition_seq_;
    /** �I�v�V�����̏����~�����a�Ɏ����߂���s���Ă���Œ��� true */
    bool return_to_base_angExpanse_seq_;


    /** [r]�����~����p�x�ʒu�֎����߂�V�[�N�G���X�i���ԍ� */
    int adjust_angPos_seq_progress_;
    /** [r]�����~����p�x�ʒu�֎����߂�V�[�N�G���X���A�^�[�Q�b�g�~����p�x�ʒu */
    angle adjust_angPos_seq_new_angPosition_base_;
    /** [r]�����~����p�x�ʒu�֎����߂�V�[�N�G���X���A�^�[�Q�b�g�~����p�x�ʒu�ɓ��B����܂łɔ�₳���t���[���� */
    frame adjust_angPos_seq_spent_frame_;

    //GgafDxCore::GgafDxQuaternion Q_;
    EffectMyOption* pEffect_;

    /** [r]��~���A�����~����p�x�ʒu�֎����߂�V�[�N�G���X�̎��s���K�v���ǂ����t���O */
    bool need_adjust_pos_flg_;

public:
    /**
     * �R���X�g���N�^ .
     * @param prm_name
     * @param prm_no �I�v�V�����ԍ��i0�`...)
     * @param prm_pOptCtrler �e�A�N�^�[
     * @return
     */
    MyOption(const char* prm_name, uint32_t prm_no, MyOptionController* prm_pOptCtrler);

    /**
     * �����ݒ�p�����[�^�[ .
     * �������ォ��initialize()�܂łɐݒ肷�邱�Ƃ��ł���A
     * �I�u�W�F�N�g�ŗL�p�����[�^�ł��B
     * @param prm_radiusPosition ���@����̔��a���w��
     * @param prm_angPosition ��L���a�̉~����ɂ����Ă̈ʒu���~���p�Ŏw��
     * @param prm_angExpanse ��L�̈ʒu�ł̃I�v�V�����́u�O���v�������w��B0�Ő���
     * @param prm_velo_mv ����ړ����x���w��
     */
    void config(
            angle prm_radiusPosition,
            angle prm_angPosition,
            angle prm_angExpanse,
            velo prm_velo_mv)
    {
        angPosition_ = prm_angPosition;
        angExpanse_ = prm_angExpanse;
        veloMv_ = prm_velo_mv;
        angPosition_base_ = prm_angPosition;
        radiusPosition_base_ = prm_radiusPosition;
        radiusPosition_ = radiusPosition_base_;
        radiusPosition_stopping_ = radiusPosition_base_;
        radiusPosition_velo_ = 3000 * (radiusPosition_base_/60000);
        angExpanse_default_ = prm_angExpanse;
        veloMv_base_ = prm_velo_mv;
        reset();
    }
    void onCreateModel() override;

    void initialize() override;

    void onReset() override;

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;

    void onInactive() override;

    void onHit(const GgafCore::GgafActor* prm_pOtherActor) override;

    virtual ~MyOption();


    void adjustAngPosition(angle prm_new_angPosition_base, frame prm_spent_frame);

};

}
#endif /*MYOPTION_H_*/

