#ifndef ENEMYCERES_H_
#define ENEMYCERES_H_
namespace VioletVreath {

/**
 * �G�@�P���X .
 * ��ʉE�[�Ő܂�Ԃ��č��ɒ��i���܂��B<BR>
 * initialize()�܂łɏ㏑���\�Ȑݒ�\�ȃp�����[�^<BR>
 * �E_X,_Y,_Z �����ʒu�A�A�� _Z<0 �ł��邱�ƁB�i�܂�Ԃ����t�ɂȂ��ĕς�����j<BR>
 * �EX_turn_, Y_turn_ �܂�Ԃ��ڕWXY���W�B�����ʒu���炱�̂��̒n�_��ڎw���b�X�B<BR>
 *
 */
class EnemyCeres : public GgafLib::DefaultMeshSetActor {

private:

public:
    enum {
        SE_EXPLOSION = 0,
    };

    /** �e�X�g�b�N */
    GgafCore::GgafActorDepository* pDepo_EnemyCeresShots001_;
    /** �X�v���C���v���O���� */
    GgafLib::SplineSequence* pProgram_CeresMove_;

    /** GgafActorDepository���R���X�g���N�^�Ő����������ۂ� */
    bool createGgafActorDepository_;

    int X_turn_; // �܂�Ԃ�X���W
    int Y_turn_; // �܂�Ԃ�Y���W
    int Z_turn_; // �܂�Ԃ�Z���W

    int iMovePatternNo_;
    frame frame_Active_;
    SplineLineConnection* pSplLineCon_;

    /**
     * �R���X�g���N�^
     * @param prm_name �I�u�W�F�N�g
     * @param prm_pDepo_EnemyCeresShots001 ���˒e�X�g�b�N�̃A�N�^�[������
     * @return
     */
    EnemyCeres(const char* prm_name, GgafCore::GgafActorDepository* prm_pDepo_EnemyCeresShots001 = nullptr);

    void initialize() override;

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;

    void onHit(GgafCore::GgafActor* prm_pOtherActor) override;

    bool isOutOfUniverse() override;

    void onInactive() override;

    virtual ~EnemyCeres();
};

}
#endif /*ENEMYCERES_H_*/

