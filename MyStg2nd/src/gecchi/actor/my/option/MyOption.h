#ifndef MYDUMMYOPTION_H_
#define MYDUMMYOPTION_H_
namespace MyStg2nd {


//class MyOption : public GgafDx9LibStg::DefaultMorphMeshActor {
class MyOption : public GgafDx9LibStg::DefaultMeshSetActor {

    //�ꎞ�ϐ��B
    int _Xorg,_Yorg,_Zorg;
    //angle _RXorg,_RYorg,_RZorg;
    float _vXwk,_vYwk,_vZwk;
    GgafDx9Core::GgafDx9Quaternion _Q;

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
     */
    void addRadiusPosition(int prm_radius_offset);





public:


    /** [r]�e�A�N�^�[ */
    MyOptionController* _pMyOptionController;
    /** [r]���g�̃I�v�V�����ԍ�(�O�`�E�E�E) */
    int _no;
    /** [r]�P�I�v�V����������̍ő�\���b�N�I���� */
    static int _max_lockon_num;
    /** [r]���b�N�I���R���g���[���[ */
    MyOptionLockonController* _pLockonController;
    /** [r]�����R���g���[���[ */
    MyOptionTorpedoController* _pTorpedoController;
    /** [r]���˂��郌�[�U�[�`�b�v�̃f�B�X�p�b�`���[ */
    GgafDx9LibStg::LaserChipDispatcher* _pLaserChipDispatcher;
    /** [r]���˂���V���b�g�̃f�B�X�p�b�`���[ */
    GgafCore::GgafActorDispatcher* _pDispatcher_MyShots001;
    /** [r]���[�U�[���˒��̃G�t�F�N�g */
    GgafDx9Core::GgafDx9DrawableActor* _pEffect_LaserIrradiate;


    /** [r]�v�Z���ꂽ���݂̐���~���ړ��p���x�i�ǂݏo����p�j */
    angvelo _angveloMove;
    /** [r]�~���㏉���ʒu�p�x�i���͊p�j�iinitialize()�܂łɕύX�^�f�t�H���g=0�j */
    angle _angPosition;
    /** [r]����~�����a�iinitialize()�܂łɕύX�^�f�t�H���g=200000�j */
    int _radiusPosition;
    /** [r/w]����~���ړ����x�i�����ύX�^�f�t�H���g=1000�j */
    velo _veloMv;
    /** [r/w]�I�v�V�����̍L�����]�p�i�����ύX�^�f�t�H���g=0 MyOptionController�Ɠ��������i�O���j�������Ă���j */
    angle _angExpanse;

    /** [r]�����~���㏉���ʒu�p�x */
    angle _angPosition_base;
    /** [r]��������~�����a */
    int _radiusPosition_base;
    /** [r]��������~���ړ����x */
    velo _veloMv_base;
    /** [r]�����I�v�V�����̍L�����]�p */
    angle _angExpanse_default;

    /** �I�v�V�����̍L�����]�p���x�i�ʏ펞�j */
    angvelo _angveloExpanseNomal;
    /** �I�v�V�����̍L�����]�p���x�i���������j */
    angvelo _angveloExpanseSlow;

    /** �I�v�V�����̏����ʒu�Ɏ����߂���s���Ă���Œ��� true */
    bool _return_to_base_radiusPosition_seq;
    /** �I�v�V�����̏����~�����a�Ɏ����߂���s���Ă���Œ��� true */
    bool _return_to_base_angExpanse_seq;



    bool _adjust_angPosition_seq;

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
        _angPosition = prm_angPosition;
        _radiusPosition = prm_radiusPosition;
        _angExpanse = prm_angExpanse;
        _veloMv = prm_veloMv;

        _angPosition_base = prm_angPosition;
        _radiusPosition_base = prm_radiusPosition;
        _angExpanse_default = prm_angExpanse;
        _veloMv_base = prm_veloMv;
    }
    void onCreateModel() override;

    void initialize() override;

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;

    void processFinal() override;

    void onHit(GgafCore::GgafActor* prm_pOtherActor) override;

    virtual ~MyOption();


    void adjustAngPosition(angle prm_new_angPosition_base);

};

}
#endif /*MYDUMMYOPTION_H_*/

