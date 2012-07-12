#ifndef ENEMYVESTA_H_
#define ENEMYVESTA_H_
namespace VioletVreath {

/**
 * ���F�X�^ .
 * @version 1.00
 * @since 2009/01/22
 * @author Masatoshi Tsuge
 */
class EnemyVesta : public GgafLib::DefaultMorphMeshActor {
private:
    /** [r]����n�b�`���J���t���[�� */
    frame frame_of_moment_nextopen_;
    /** [r]����n�b�`������t���[�� */
    frame frame_of_moment_nextclose_;
public:
    enum {
        SE_DAMAGED   = 0,
        SE_EXPLOSION,
    };

    /** [r]�s���p�^�[���ԍ� */
    int iMovePatternNo_;
    /** [r]�� */
    bool is_open_hatch_;
    /** [r/w]�n�b�`���J���Ă���t���[���Ԋu */
    frame frame_of_open_interval_;
    /** [r/w]�n�b�`�����Ă��Ă���t���[���Ԋu */
    frame frame_of_close_interval_;
    /** [r/w]�n�b�`�J���� �����́A���J �̃��[�t�A�j���[�V�����t���[���� */
    frame frame_of_morph_interval_;
    /** [r/w]�n�b�`�̓y��ƂȂ��Ă�A�N�^�[ */

    /** [r/w]�n�b�`���甭�˂����A�N�^�[�������o�[�Ɏ��f�|�W�g�� */
    GgafCore::GgafActorDepository* pDepo_Fired_;
    DepositoryConnection* pDpcon_;

    /**
     * �R���X�g���N�^
     * @param prm_name
     * @return
     */
    EnemyVesta(const char* prm_name);

    /**
     * ���F�X�^���f�����������ꂽ�ۂɂP�񂾂����s����鏈��
     */
    void onCreateModel() override;
    /**
     * ���F�X�^�̏��������i�C���X�^���X������ۏ؁j
     */
    void initialize() override;

    /**
     * ���F�X�^�̂��A�N�e�B�u�ɂȂ����u�Ԃ̏��� .
     */
    void onActive() override;

    /**
     * ���F�X�^�̐U�镑�� .
     */
    void processBehavior() override;
    /**
     * ���F�X�^�̐U�镑����̔��菈�� .
     */
    void processJudgement() override;

    /**
     * ���F�X�^�̏Փˎ����� .
     * @param prm_pOtherActor �ՓˑΏ�
     */
    void onHit(GgafCore::GgafActor* prm_pOtherActor) override;


    void onInactive() override;

    virtual ~EnemyVesta();
};

}
#endif /*ENEMYVESTA_H_*/

