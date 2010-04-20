#ifndef ENEMYCIRCE_H_
#define ENEMYCIRCE_H_
namespace MyStg2nd {

/**
 * �L���P .
 * @version 1.00
 * @since 2010/03/25
 * @author Masatoshi Tsuge
 */
class EnemyCirce : public GgafDx9LibStg::DefaultMeshActor {

public:
    /** �s���p�^�[���ԍ� */
    int _iMovePatternNo;

    /**
     * �R���X�g���N�^
     * @param prm_name
     * @return
     */
    EnemyCirce(const char* prm_name);

    /**
     * �L���P���f�����������ꂽ�ۂɂP�񂾂����s����鏈��
     */
    void onCreateModel() override;
    /**
     * �L���P�̏��������i�C���X�^���X������ۏ؁j
     */
    void initialize() override;

    /**
     * �L���P�̂��A�N�e�B�u�ɂȂ����u�Ԃ̏��� .
     */
    void onActive() override;

    /**
     * �L���P�̐U�镑�� .
     */
    void processBehavior() override;


    /**
     * �L���P�̐U�镑����̔��菈�� .
     */
    void processJudgement() override;

    /**
     * �L���P�̏Փˎ����� .
     * @param prm_pOtherActor �ՓˑΏ�
     */
    void onHit(GgafCore::GgafActor* prm_pOtherActor) override;

    void onInactive() override;

    virtual ~EnemyCirce();
};

}
#endif /*ENEMYCIRCE_H_*/

