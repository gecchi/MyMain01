#ifndef MYDUMMYOPTION_H_
#define MYDUMMYOPTION_H_
namespace MyStg2nd {

//class MyOption : public GgafDx9LibStg::DefaultMorphMeshActor {
class MyOption : public GgafDx9LibStg::DefaultMeshSetActor {


    /** �e�A�N�^�[ */
    MyOptionParent* _pMyOptionParent;

    /** �I�v�V�����ԍ� */
    int _no;

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

    /** ���b�N�I�����A�N�^�[ */
    GgafDx9Core::GgafDx9GeometricActor* _pLockonTarget;


    EffectLockon001* _pEffectLockon;

    GgafDx9LibStg::LaserChipDispatcher* _pLaserChipDispatcher;
    GgafCore::GgafActorDispatcher* _pDispatcher_MyShots001;

    /** ���[�U�[���ˎ��G�t�F�N�g */
    GgafDx9Core::GgafDx9DrawableActor* _pEffect_LaserIrradiate;


    /** �v�Z���ꂽ���݂̐���~���ړ��p���x�i�ǂݏo����p�j */
    angvelo _angveloMove;
    /** �~���㏉���ʒu�p�x�i���͊p�j�iinitialize()�܂łɕύX�^�f�t�H���g=0�j */
    angle _angPosition;
    /** ����~�����a�iinitialize()�܂łɕύX�^�f�t�H���g=200000�j */
    int _radiusPosition;
    /** ����~���ړ����x�i�����ύX�^�f�t�H���g=1000�j */
    velo _veloMv;
    /** �I�v�V�����̍L�����]�p�i�����ύX�^�f�t�H���g=0 MyOptionParent�Ɠ��������i�O���j�������Ă���j */
    angle _angExpanse;

    /** �����~���㏉���ʒu�p�x */
    angle _angPosition_default;
    /** ��������~�����a */
    int _radiusPosition_default;
    /** ��������~���ړ����x */
    velo _veloMv_default;
    /** �����I�v�V�����̍L�����]�p */
    angle _angExpanse_default;

    /** �I�v�V�����̍L�����]�p���x�i�ʏ펞�j */
    angvelo _angveloExpanseNomal;
    /** �I�v�V�����̍L�����]�p���x�i���������j */
    angvelo _angveloExpanseSlow;


    bool _return_to_default_radiusPosition_seq;
    bool _return_to_default_angExpanse_seq;


    MyOption(const char* prm_name, UINT32 prm_no, MyOptionParent* prm_pMyOptionParent);

    /**
     * �����ݒ�p�����[�^�[ .
     * �������ォ��initialize()�܂łɐݒ肷�邱�Ƃ��ł���A
     * �I�u�W�F�N�g�ŗL�p�����[�^�ł��B
     * @param prm_radiusPosition ���@����̔��a���w��
     * @param prm_angPosition ��L���a�̉~����ɂ����Ă̈ʒu���~���p�Ŏw��
     * @param prm_angExpanse ��L�̈ʒu�ł̃I�v�V�����́u�O���v�������w��B0�Ő���
     * @param prm_veloMv ����ړ����x���w��
     */
    void setInitializeProperty(
            angle prm_radiusPosition,
            angle prm_angPosition,
            angle prm_angExpanse,
            velo prm_veloMv)
    {
        _angPosition = prm_angPosition;
        _radiusPosition = prm_radiusPosition;
        _angExpanse = prm_angExpanse;
        _veloMv = prm_veloMv;

        _angPosition_default = prm_angPosition;
        _radiusPosition_default = prm_radiusPosition;
        _angExpanse_default = prm_angExpanse;
        _veloMv_default = prm_veloMv;
    }
    void onCreateModel() override;

    void initialize() override;

    void processBehavior() override;

    void processJudgement() override;

    void processFinal() override;

    void onHit(GgafCore::GgafActor* prm_pOtherActor) override;

    virtual ~MyOption();


};

}
#endif /*MYDUMMYOPTION_H_*/

