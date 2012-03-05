#ifndef MYOPTION_H_
#define MYOPTION_H_
namespace VioletVreath {

//class MyOption : public GgafLib::DefaultMorphMeshActor {
class MyOption : public GgafLib::DefaultMeshSetActor {


    GgafDxCore::GgafDxQuaternion Q_;

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
    void addRadiusPosition(int prm_radius_offset, int prm_min_radius = 30000, int prm_max_radius = 1000000);


public:
    //�ꎞ�ϐ��B
    int Xorg_,Yorg_,Zorg_;

    /** [r]�e�A�N�^�[ */
    MyOptionController* pMyOptionController_;
    /** [r]���g�̃I�v�V�����ԍ�(�O�`�E�E�E) */
    int no_;
    /** [r]�P�I�v�V����������̍ő�\���b�N�I���� */
    static int max_lockon_num_;
    /** [r]�P�I�v�V����������̌��݉\���b�N�I���� */
    static int lockon_num_;
    /** [r]���b�N�I���R���g���[���[ */
    MyOptionLockonController* pLockonController_;
    /** [r]�����R���g���[���[ */
    MyOptionTorpedoController* pTorpedoController_;
    /** [r]���˂��郌�[�U�[�`�b�v�̃f�|�W�g�� */
    GgafLib::LaserChipDepository* pLaserChipDepo_;
    /** [r]���˂���V���b�g�̃f�|�W�g�� */
    GgafCore::GgafActorDepository* pDepo_MyShots001_;
    /** [r]���[�U�[���˒��̃G�t�F�N�g */
    GgafDxCore::GgafDxDrawableActor* pEffect_LaserIrradiate_;

    int velo_radius_;

    /** [r]�v�Z���ꂽ���݂̐���~���ړ��p���x�i�ǂݏo����p�j */
    ang_velo ang_veloMove_;
    /** [r]�~���㏉���ʒu�p�x�i���͊p�j�iinitialize()�܂łɕύX�^�f�t�H���g=0�j */
    angle angPosition_;
    /** [r]����~�����a�iinitialize()�܂łɕύX�^�f�t�H���g=200000�j */
    int radiusPosition_;
    /** [r/w]����~���ړ����x�i�����ύX�^�f�t�H���g=1000�j */
    velo veloMv_;
    /** [r/w]�I�v�V�����̍L�����]�p�i�����ύX�^�f�t�H���g=0 MyOptionController�Ɠ��������i�O���j�������Ă���j */
    angle angExpanse_;

    /** [r]�����~���㏉���ʒu�p�x */
    angle angPosition_base_;
    /** [r]��������~�����a */
    int radiusPosition_base_;
    int radiusPosition_stopping_;

    /** [r]��������~���ړ����x */
    velo veloMv_base_;
    /** [r]�����I�v�V�����̍L�����]�p */
    angle angExpanse_default_;

    /** �I�v�V�����̍L�����]�p���x�i�ʏ펞�j */
    ang_velo ang_veloExpanseNomal_;
    /** �I�v�V�����̍L�����]�p���x�i���������j */
    ang_velo ang_veloExpanseSlow_;

    /** �I�v�V�����̏����ʒu�Ɏ����߂���s���Ă���Œ��� true */
    bool return_to_base_radiusPosition_seq_;
    /** �I�v�V�����̏����~�����a�Ɏ����߂���s���Ă���Œ��� true */
    bool return_to_base_angExpanse_seq_;



    int adjust_angPos_seq_progress_;
    angle adjust_angPos_seq_new_angPosition_base_;
    frame adjust_angPos_seq_spent_frame_;
    angle adjust_angPos_seq_angPosition_;

    //GgafDxCore::GgafDxQuaternion Q_;
    EffectMyOption* pEffect_;

    /**
     * �R���X�g���N�^ .
     * @param prm_name
     * @param prm_no �I�v�V�����ԍ��i0�`...)
     * @param prm_pMyOptionController �e�A�N�^�[
     * @return
     */
    MyOption(const char* prm_name, UINT32 prm_no, MyOptionController* prm_pMyOptionController);

    /**
     * �����ݒ�p�����[�^�[ .
     * �������ォ��initialize()�܂łɐݒ肷�邱�Ƃ��ł���A
     * �I�u�W�F�N�g�ŗL�p�����[�^�ł��B
     * @param prm_radiusPosition ���@����̔��a���w��
     * @param prm_angPosition ��L���a�̉~����ɂ����Ă̈ʒu���~���p�Ŏw��
     * @param prm_angExpanse ��L�̈ʒu�ł̃I�v�V�����́u�O���v�������w��B0�Ő���
     * @param prm_veloMv ����ړ����x���w��
     */
    void config(
            angle prm_radiusPosition,
            angle prm_angPosition,
            angle prm_angExpanse,
            velo prm_veloMv)
    {
        angPosition_ = prm_angPosition;
        radiusPosition_ = prm_radiusPosition;
        angExpanse_ = prm_angExpanse;
        veloMv_ = prm_veloMv;
        angPosition_base_ = prm_angPosition;
        radiusPosition_base_ = prm_radiusPosition;
        radiusPosition_stopping_ = radiusPosition_base_;
        velo_radius_ = 0;
        angExpanse_default_ = prm_angExpanse;
        veloMv_base_ = prm_veloMv;
    }
    void onCreateModel() override;

    void initialize() override;

    void onReset() override;

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;

    void onInactive() override;

    void onHit(GgafCore::GgafActor* prm_pOtherActor) override;

    virtual ~MyOption();


    void adjustAngPosition(angle prm_new_angPosition_base, frame prm_spent_frame);

};

}
#endif /*MYOPTION_H_*/

