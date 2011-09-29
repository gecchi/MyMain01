#ifndef ENEMYCELESSHOT001_H_
#define ENEMYCELESSHOT001_H_
namespace MyStg2nd {

/**
 * 3D�G�e001 .
 * 1)�����悭�ݒ�����ɔ�яo��<BR>
 * 2)���X�ɐ����͒x���Ȃ�A���@�̕����ɕ����]��<BR>
 * 3)���̌㎩�@���߂����Ē����ړ��B�ĉ������Ă���<BR>
 * �y�㏑���\�ȃ����o�[�z
 *
 */
class EnemyCeresShot001 : public GgafLib::DefaultMeshSetActor {
public:
    //�{Actor�̃J�X�^���v���p�e�B --->
    /** �o�����̏��� */
    int _iMvVelo_1st;
    /** �o�����̉����x�i���Œx���Ȃ� */
    int _iMoveAcce_1st;
    /** ���g���o�����Ă���A���@�̕����ɕ����]�����J�n����t���[�� */
    frame _frame_TurnBegin;
    /** �ړ����x��� */
    int _iMvVelo_Top;
    /** �Œ�ۏ؈ړ����x */
    int _iMvVelo_Bottom;
    /** �����]���ɔ�₷���Ƃ��ł���t���[���� */
    frame _frame_TurnInterval;
    /** �����]�����̊p���x�A���O���l */
    angle _angVelo_Turn;
    /** �����]�����J�n�i_frame_TurnBegin�j����Đݒ肳�������x */
    int _iMoveAcce_2nd;
    //<--- �{Actor�̃J�X�^���v���p�e�B

public:
    EnemyCeresShot001(const char* prm_name);

    void initialize() override;

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;

    void onHit(GgafCore::GgafActor* prm_pOtherActor) override;

    void onInactive() override;

    virtual ~EnemyCeresShot001();
};

}
#endif /*ENEMYCELESSHOT001_H_*/

