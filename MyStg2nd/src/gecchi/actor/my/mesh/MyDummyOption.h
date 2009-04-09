#ifndef MYDUMMYOPTION_H_
#define MYDUMMYOPTION_H_
namespace MyStg2nd {

class MyDummyOption : public GgafDx9LibStg::DefaultMeshActor {
    /** �e�A�N�^�[ */
    MyOptionParent* _pMyOptionParent;

    /** �I�v�V�����ԍ� */
    int _no;

    //�ꎞ�ϐ��B
    int _Xorg,_Yorg,_Zorg;
    float _RXorg,_RYorg,_RZorg;
    float _vXwk,_vYwk,_vZwk;
    float _Xwk,_Ywk,_Zwk;

public:
    /** ���݂̍ŏI�I�ȍ��W */
    int _X2, _Y2, _Z2;
    /** ���݂̍ŏI�I�Ȏ���]�p�x */
    GgafDx9Core::angle _RZ2, _RY2;
    /** ����ړ��p���x�i�ǂݏo����p�j */
    GgafDx9Core::angvelo _angveloMove;

    /** �~���㏉���ʒu�p�x�i���͊p�j�i�㏑�������ݒ�j */
    GgafDx9Core::angle _angPosition;
    /** �������a�����i�㏑�������ݒ�j */
    int _radius;

    /** ����ړ����x�i�ǂݏ����j */
    GgafDx9Core::velo _veloMove;
    /** �I�v�V�����̍L�����]�p�i�ǂݏ����j */
    GgafDx9Core::angle _angExpanse;
    /** �I�v�V�����̍L�����]�p���x �i�ǂݏ����j*/
    GgafDx9Core::angvelo _angveloExpanse;


    MyDummyOption(const char* prm_name, int prm_no, MyOptionParent* prm_pMyOptionParent);

    /**
     * ��OverRide �ł���
     */
    void initialize();

    /**
     * ��OverRide �ł���
     */
    void processBehavior();

    /**
     * ��OverRide �ł���
     */
    void processJudgement();

    /**
     * ��OverRide �ł���
     */
    void processOnHit(GgafCore::GgafActor* prm_pActor_Opponent);


    virtual ~MyDummyOption();
};

}
#endif /*MYDUMMYOPTION_H_*/

