#ifndef ENEMYCELESSHOT001_H_
#define ENEMYCELESSHOT001_H_
namespace MyStg2nd {

/**
 * 3D�G�e001 .
 * 1)�����悭�ݒ�����ɔ�яo��<BR>
 * 2)���X�ɐ����͒x���Ȃ�A���@�̕����ɕ����]��<BR>
 * 3)���̌㎞�@���߂����Ē����ړ��B�ĉ������Ă���<BR>
 * �y�㏑���\�ȃ����o�[�z
 *
 */
class EnemyCeresShot001 : public DefaultMeshEnemyActor {
public:
    //�{Actor�̃J�X�^���v���p�e�B --->
    /** �o�����̏��� */
    int _iMvVelo_1st;
    /** �o�����̉����x�i���Œx���Ȃ� */
    int _iMoveAcce_1st;
    /** ���g���o�����Ă���A���@�̕����ɕ����]�����J�n����t���[�� */
    DWORD _dwFrame_TurnBegin;
    /** �ړ����x��� */
    int _iMvVelo_Top;
    /** �Œ�ۏ؈ړ����x */
    int _iMvVelo_Bottom;
    /** �����]���ɔ�₷���Ƃ��ł���t���[���� */
    DWORD _dwFrameInterval_Turn;
    /** �����]�����̊p���x�A���O���l */
    angle _angVelo_Turn;
    /** �����]�����J�n�i_dwFrame_TurnBegin�j����Đݒ肳�������x */
    int _iMoveAcce_2nd;
    /** �o�����Ă���̃t���[���� */
    DWORD _frame_on_change_to_active_flg;
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

