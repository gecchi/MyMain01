#ifndef HOMINGLASERCHIP_H_
#define HOMINGLASERCHIP_H_
namespace MyStg2nd {

class HomingLaserChip : public LaserChip {
    friend class LaserChipDispatcher;



public:

    int _begining_X;
    int _begining_Y;
    int _begining_Z;
    float _begining_vX;
    float _begining_vY;
    float _begining_vZ;
    int _begining_RzMoveAngle;
    int _begining_RyMoveAngle;
//    GgafDx9Core::angle _begining_target_RzMoveAngle;
//    GgafDx9Core::angle _begining_target_RyMoveAngle;


    int _prev_X;
    int _prev_Y;
    int _prev_Z;
    int _prev_RX;
    int _prev_RY;
    int _prev_RZ;



    HomingLaserChip(const char* prm_name, const char* prm_model);

    virtual void initialize();

    /**
     * ���[�U�[�`�b�v���W�v�Z������ .
     * �Ǝ��ݒ肵�����ꍇ�A�p�����ĕʃN���X���쐬���A�I�[�o�[���C�h���Ă��������B
     * ���̍� �́A�{�N���X�� processBehavior() ���\�b�h���Ăяo���Ă��������B
     */
    virtual void processBehavior();


    virtual void processBehaviorHeadChip() {}
    /**
     * ���[�U�[�`�b�v���蓙���� .
     * �Ǝ��ݒ肵�����ꍇ�A�p�����ĕʃN���X���쐬���A�I�[�o�[���C�h���Ă��������B
     * ���̍� �́A�{�N���X�� processJudgement() ���\�b�h���Ăяo���Ă��������B
     * ���͖{���\�b�h�ŁAGgafDx9GeometricActor::updateWorldMatrix_Mv(this, _matWorld) ���Ăяo���Ă���A
     * ���̃^�C�~���O�Ń��[���h�ϊ��s�񂪊m�肵�܂��̂ŁA�I�[�o�[���C�h�̍ۂ͍Ō�� HomingLaserChip::processJudgement(); ��
     * �����ق����ǂ��ł��傤�B
     */
    virtual void processJudgement();

    /**
     * ���[�U�[�`�b�v�o�������� .
     * �Ǝ��ݒ肵�����ꍇ�A�p�����ĕʃN���X���쐬���A�I�[�o�[���C�h���Ă��������B
     * ���̍� �́A�{�N���X�� onActive() ���\�b�h���Ăяo���Ă��������B
     */
    virtual void onActive();

    /**
     * ���[�U�[�`�b�v���������� .
     * �Ǝ��ݒ肵�����ꍇ�A�p�����ĕʃN���X���쐬���A�I�[�o�[���C�h���Ă��������B
     * ���̍� �́A�{�N���X�� onInactive() ���\�b�h���Ăяo���Ă��������B
     */
    virtual void onInactive();


    //virtual void initializeHoming(GgafDx9Core::GgafDx9GeometricActor* prm_pActor_Target);

    virtual ~HomingLaserChip();

};

}
#endif /*HOMINGLASERCHIP_H_*/

