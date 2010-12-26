#ifndef ENEMYTHALIA_H_
#define ENEMYTHALIA_H_

#define THALIA_SCENE_PROG_MOVE  1
#define THALIA_SCENE_PROG_TURN_OPEN  2
#define THALIA_SCENE_PROG_FIRE_BEGIN  3
#define THALIA_SCENE_PROG_IN_FIRE 4
#define THALIA_SCENE_PROG_CLOSE 5

namespace MyStg2nd {



/**
 * �G�@�^���A .
 * @version 1.00
 * @since 2010/08/03
 * @author Masatoshi Tsuge
 */
//class EnemyThalia : public GgafDx9LibStg::DefaultMorphMeshActor {
class EnemyThalia : public GgafDx9LibStg::CubeMapMorphMeshActor {
    /** �ړ��X�v���C���v���O���� */
    GgafDx9Core::GgafDx9SplineProgram* _pSplineProgram;
    /** �e�X�g�b�N */
    GgafCore::GgafActorDispatcher* _pDispatcher_Shot;
    /** �e���ˌ��ʃG�t�F�N�g */
    GgafCore::GgafActorDispatcher* _pDispatcher_ShotEffect;
public:
    /** �s���p�^�[���ԍ� */
    int _iMovePatternNo;

    velo _veloTopMv;

    GgafDx9LibStg::LaserChipDispatcher* _pLaserChipDispatcher;
    /**
     * �R���X�g���N�^
     * @param prm_name
     * @return
     */
    EnemyThalia(const char* prm_name);

    void onCreateModel() override;

    /**
     * �^���A�̏��������i�C���X�^���X������ۏ؁j
     */
    void initialize() override;

    /**
     * �^���A���A�N�e�B�u�ɂȂ����u�Ԃ̏��� .
     */
    void onActive() override;

    /**
     * �^���A�̐U�镑�� .
     */
    void processBehavior() override;

    /**
     * �^���A�̐U�镑����̔��菈�� .
     */
    void processJudgement() override;

    /**
     * �^���A�̏Փˎ����� .
     * @param prm_pOtherActor �ՓˑΏ�
     */
    void onHit(GgafCore::GgafActor* prm_pOtherActor) override;


    void onInactive() override;

    /**
     * ���˒eDispatcher�ݒ� .
     * initialize() �܂łɐݒ肵�ĉ������B
     * @param prm_pDispatcher
     */
    void setDispatcher_Shot(GgafCore::GgafActorDispatcher* prm_pDispatcher) {
        _pDispatcher_Shot = prm_pDispatcher;
    }

    /**
     * �X�v���C���ړ��ݒ� .
     * initialize() �܂łɐݒ肵�ĉ������B
     * @param prm_pSplineProgram
     */
    void setSplineProgram(GgafDx9Core::GgafDx9SplineProgram* prm_pSplineProgram) {
        _pSplineProgram = prm_pSplineProgram;
    }

    /**
     * �V���b�g���ˌ��ʃG�t�F�N�g�ݒ� .
     * @param prm_pDispatcher
     */
    void setDispatcher_ShotEffect(GgafCore::GgafActorDispatcher* prm_pDispatcher) {
        _pDispatcher_ShotEffect = prm_pDispatcher;
    }

    virtual ~EnemyThalia();
};

}
#endif /*ENEMYTHALIA_H_*/

