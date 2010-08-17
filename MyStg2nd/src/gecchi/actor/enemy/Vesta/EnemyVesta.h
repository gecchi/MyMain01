#ifndef ENEMYVESTA_H_
#define ENEMYVESTA_H_
namespace MyStg2nd {

/**
 * ���F�X�^ .
 * @version 1.00
 * @since 2009/01/22
 * @author Masatoshi Tsuge
 */
class EnemyVesta : public GgafDx9LibStg::DefaultMorphMeshActor {
private:
    /** [r]����n�b�`���J���t���[�� */
    frame _frame_of_moment_nextopen;
    /** [r]����n�b�`������t���[�� */
    frame _frame_of_moment_nextclose;
public:
    /** [r]�s���p�^�[���ԍ� */
    int _iMovePatternNo;
    /** [r]�� */
    bool _is_open_hatch;
    /** [r/w]�n�b�`���J���Ă���t���[���Ԋu */
    frame _frame_of_open_interval;
    /** [r/w]�n�b�`�����Ă��Ă���t���[���Ԋu */
    frame _frame_of_close_interval;
    /** [r/w]�n�b�`�J���� �����́A���J �̃��[�t�A�j���[�V�����t���[���� */
    frame _frame_of_morph_interval;
    /** [r/w]�n�b�`�̓y��ƂȂ��Ă�A�N�^�[ */

    /** [r/w]�n�b�`���甭�˂����A�N�^�[�������o�[�Ɏ��f�B�X�p�b�`���[ */
    GgafCore::GgafActorDispatcher* _pDispatcher_Fired;
    DispatcherConnection* _pDpcon;

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

