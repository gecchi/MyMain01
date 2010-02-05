#ifndef ENEMYTAMAGO01_H_
#define ENEMYTAMAGO01_H_
namespace MyStg2nd {

/**
 * �e�X�g�p .
 * @version 1.00
 * @since 2009/01/22
 * @author Masatoshi Tsuge
 */
class EnemyTamago01 : public GgafDx9LibStg::DefaultMeshActor {

public:
    /** �s���p�^�[���ԍ� */
    int _iMovePatternNo;
    /** �ړ��X�v���C���v���O���� */
    GgafDx9Core::GgafDx9SplineProgram* _pProgram_Tamago01Move;
    /** �e�X�g�b�N */
    GgafDx9LibStg::ActorDispatcher* _pDispatcher_Shot;
    /** �e���ˌ��ʃG�t�F�N�g */
    GgafDx9LibStg::ActorDispatcher* _pDispatcher_ShotEffect;



    /**
     * �R���X�g���N�^
     * @param prm_name
     * @return
     */
    EnemyTamago01(const char* prm_name);

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

    /**
     * ���˒e�ݒ� .
     * @param prm_pDispatcher (GgafDx9DrawableActor*)�ɃL���X�g�\�ȃA�N�^�[���T�u�Ɏ��f�B�X�p�b�`���[�̃|�C���^
     */
    void setDispatcher_Shot(GgafDx9LibStg::ActorDispatcher* prm_pDispatcher) {
        _pDispatcher_Shot = prm_pDispatcher;
    }

    /**
     * ���ʃG�t�F�N�g�ݒ� .
     * @param prm_pDispatcher (GgafDx9DrawableActor*)�ɃL���X�g�\�ȃA�N�^�[���T�u�Ɏ��f�B�X�p�b�`���[�̃|�C���^
     */
    void setDispatcher_ShotEffect(GgafDx9LibStg::ActorDispatcher* prm_pDispatcher) {
        _pDispatcher_ShotEffect = prm_pDispatcher;
    }

    virtual ~EnemyTamago01();
};

}
#endif /*ENEMYTAMAGO01_H_*/

