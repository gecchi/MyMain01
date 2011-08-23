#ifndef ENEMYJUNO_H_
#define ENEMYJUNO_H_
namespace MyStg2nd {

//�W���m�[
class EnemyJuno : public GgafDx9LibStg::DefaultMeshSetActor {

public:
    int _iMovePatternNo;
    /** �e�X�g�b�N */
    GgafCore::GgafActorDepository* _pDepo_Shot;
    /** �e���ˌ��ʃG�t�F�N�g */
    GgafCore::GgafActorDepository* _pDepo_ShotEffect;
    bool _do_Shot;
    bool _can_Shot;
    frame _frame_when_shot;
    int _nMaxShot;
    int _nShot;
    velo _veloMv_begin;

    EnemyJuno(const char* prm_name);

    void onCreateModel() override;

    void initialize() override;

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;

    void onInactive() override;

    void onHit(GgafCore::GgafActor* prm_pOtherActor) override;

    virtual ~EnemyJuno();

    /**
     * ���˒e�ݒ� .
     * @param prm_pDepo (GgafDx9DrawableActor*)�ɃL���X�g�\�ȃA�N�^�[���T�u�Ɏ��f�|�W�g���̃|�C���^
     */
    void setDepository_Shot(GgafCore::GgafActorDepository* prm_pDepo) {
        _pDepo_Shot = prm_pDepo;
    }
};

}
#endif /*ENEMYJUNO_H_*/

