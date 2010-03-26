#ifndef ENEMYVESTA_H_
#define ENEMYVESTA_H_
namespace MyStg2nd {

/**
 * �e�X�g�p .
 * @version 1.00
 * @since 2009/01/22
 * @author Masatoshi Tsuge
 */
class EnemyVesta : public GgafDx9LibStg::DefaultMorphMeshActor {
private:
    /** [r]����n�b�`���J���t���[�� */
    DWORD _frame_of_moment_nextopen;
    /** [r]����n�b�`������t���[�� */
    DWORD _frame_of_moment_nextclose;
public:
    /** [r]�s���p�^�[���ԍ� */
    int _iMovePatternNo;
    /** [r]�� */
    bool _is_open_hatch;
    /** [r/w]�n�b�`���J���Ă���t���[���Ԋu */
    DWORD _frame_of_open_interval;
    /** [r/w]�n�b�`�����Ă��Ă���t���[���Ԋu */
    DWORD _frame_of_close_interval;
    /** [r/w]�n�b�`�J���� �����́A���J �̃��[�t�A�j���[�V�����t���[���� */
    DWORD _frame_of_morph_interval;
    /** [r/w]�n�b�`�̓y��ƂȂ��Ă�A�N�^�[ */

    /** [r/w]�n�b�`���甭�˂����A�N�^�[�������o�[�Ɏ��f�B�X�p�b�`���[ */
    GgafCore::GgafActorDispatcher* _pDispatcher_Fired;
    DispatcherConnection* _pDpcon;

    angle _RX_local;
    angle _RY_local;
    angle _RZ_local;

    /**
     * �R���X�g���N�^
     * @param prm_name
     * @return
     */
    EnemyVesta(const char* prm_name);

    /**
     * ���܂����f�����������ꂽ�ۂɂP�񂾂����s����鏈��
     */
    void onCreateModel() override;
    /**
     * ���܂��̏��������i�C���X�^���X������ۏ؁j
     */
    void initialize() override;

    /**
     * ���܂��̂��A�N�e�B�u�ɂȂ����u�Ԃ̏��� .
     */
    void onActive() override;

    /**
     * ���܂��̐U�镑�� .
     */
    void processBehavior() override;
    /**
     * ���܂��̐U�镑����̔��菈�� .
     */
    void processJudgement() override;

    /**
     * ���܂��̏Փˎ����� .
     * @param prm_pOtherActor �ՓˑΏ�
     */
    void onHit(GgafCore::GgafActor* prm_pOtherActor) override;


    void onInactive() override;

    virtual ~EnemyVesta();
};

}
#endif /*ENEMYVESTA_H_*/

