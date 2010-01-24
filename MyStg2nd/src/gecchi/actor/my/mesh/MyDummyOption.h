#ifndef MYDUMMYOPTION_H_
#define MYDUMMYOPTION_H_
namespace MyStg2nd {

//class MyDummyOption : public GgafDx9LibStg::DefaultMorphMeshActor {
class MyDummyOption : public GgafDx9LibStg::DefaultMeshSetActor {

    /** �e�A�N�^�[ */
    MyOptionParent* _pMyOptionParent;

    /** �I�v�V�����ԍ� */
    int _no;

    //�ꎞ�ϐ��B
    int _Xorg,_Yorg,_Zorg;
    //angle _RXorg,_RYorg,_RZorg;
    float _vXwk,_vYwk,_vZwk;
    GgafDx9Core::GgafDx9Quaternion _Q;

public:
    LaserChipDispatcher* _pLaserChipDispatcher;
    GgafDx9Core::GgafDx9SeConnection* _pSeCon_Laser;


    /** ���݂̍ŏI�I�ȍ��W�i�ǂݏo����p�j */
    //int _X2, _Y2, _Z2;
    /** ���݂̍ŏI�I�Ȏ���]�p�x�i�ǂݏo����p�j */
    //angle _RZ2, _RY2;
    /** ���݂̐���~���ړ��p���x�i�ǂݏo����p�j */
    angvelo _angveloMove;

    /** �~���㏉���ʒu�p�x�i���͊p�j�iinitialize()�܂łɕύX�^�f�t�H���g=0�j */
    angle _angPosition;
    /** ����~�����a�iinitialize()�܂łɕύX�^�f�t�H���g=200000�j */
    int _radiusPosition;
    /** ����~���ړ����x�i�����ύX�^�f�t�H���g=1000�j */
    velo _veloMove;
    /** �I�v�V�����̍L�����]�p�i�����ύX�^�f�t�H���g=0 MyOptionParent�Ɠ��������i�O���j�������Ă���j */
    angle _angExpanse;
    /** �I�v�V�����̍L�����]�p���x �i�����ύX�^�f�t�H���g=100�j*/
    angvelo _angveloExpanse;

    MyDummyOption(const char* prm_name, int prm_no, MyOptionParent* prm_pMyOptionParent);

    void initialize() override;

    void processBehavior() override;

    void processJudgement() override;

    void onHit(GgafCore::GgafActor* prm_pOtherActor) override;

    virtual ~MyDummyOption();
};

}
#endif /*MYDUMMYOPTION_H_*/

