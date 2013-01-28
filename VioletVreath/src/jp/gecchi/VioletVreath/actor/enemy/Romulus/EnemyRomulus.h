#ifndef ENEMYROMULUS_H_
#define ENEMYROMULUS_H_
namespace VioletVreath {

/**
 * �G�@�������X .
 * �X�N�����u���n�b�`�B
 * @version 1.00
 * @since 2009/01/22
 * @author Masatoshi Tsuge
 */
class EnemyRomulus : public GgafLib::DefaultMorphMeshActor {
private:
//    /** [r]����n�b�`���J���t���[��(�����v�Z�p) */
//    frame frame_of_moment_nextopen_;
//    /** [r]����n�b�`������t���[��(�����v�Z�p) */
//    frame frame_of_moment_nextclose_;
public:
    enum {
        PROG_INIT         = 1,
        PROG_HATCH_CLOSE,
        PROG_HATCH_OPEN,
    };

    enum {
        SE_DAMAGED   = 0,
        SE_EXPLOSION,
    };

    /** [r]�� */
    bool is_open_hatch_;
    /** [r/w]�n�b�`���J���Ă���t���[���Ԋu */
    frame frame_of_open_interval_;
    /** [r/w]�n�b�`�����Ă��Ă���t���[���Ԋu */
    frame frame_of_close_interval_;
    /** [r/w]�n�b�`�J���� �y�сA���J �̃��[�t�A�j���[�V�����t���[���� */
    frame frame_of_morph_interval_;

    /** [r/w]�n�b�`���甭�˂����A�N�^�[�������o�[�Ɏ��f�|�W�g�� */
    GgafCore::GgafActorDepository* pDepo_Fired_;
    DepositoryConnection* pDpcon_;

public:
    /**
     * �R���X�g���N�^
     * @param prm_name
     * @return
     */
    EnemyRomulus(const char* prm_name);

    /**
     * �������X���f�����������ꂽ�ۂɂP�񂾂����s����鏈��
     */
    void onCreateModel() override;
    /**
     * �������X�̏��������i�C���X�^���X������ۏ؁j
     */
    void initialize() override;

    /**
     * �������X�̂��A�N�e�B�u�ɂȂ����u�Ԃ̏��� .
     */
    void onActive() override;

    /**
     * �������X�̐U�镑�� .
     */
    void processBehavior() override;
    /**
     * �������X�̐U�镑����̔��菈�� .
     */
    void processJudgement() override;

    /**
     * �������X�̏Փˎ����� .
     * @param prm_pOtherActor �ՓˑΏ�
     */
    void onHit(GgafCore::GgafActor* prm_pOtherActor) override;


    void onInactive() override;

    virtual ~EnemyRomulus();
};

}
#endif /*ENEMYROMULUS_H_*/

