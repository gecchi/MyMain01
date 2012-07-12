#ifndef ENEMYCELESSHOT001_H_
#define ENEMYCELESSHOT001_H_
namespace VioletVreath {

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
    enum {
        CERESSHOT001_SE_EXPLOSION = 0,
    };

    //�{Actor�̃J�X�^���v���p�e�B --->
    /** �o�����̏��� */
    int iMvVelo_1st_;
    /** �o�����̉����x�i���Œx���Ȃ� */
    int iMoveAcce_1st_;
    /** ���g���o�����Ă���A���@�̕����ɕ����]�����J�n����t���[�� */
    frame frame_TurnBegin_;
    /** �ړ����x��� */
    int iMvVelo_Top_;
    /** �Œ�ۏ؈ړ����x */
    int iMvVelo_Bottom_;
    /** �����]���ɔ�₷���Ƃ��ł���t���[���� */
    frame frame_TurnInterval_;
    /** �����]�����̊p���x�A���O���l */
    angle angVelo_Turn_;
    /** �����]�����J�n�iframe_TurnBegin_�j����Đݒ肳�������x */
    int iMoveAcce_2nd_;
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

