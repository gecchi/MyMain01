#ifndef ENEMYCERES_H_
#define ENEMYCERES_H_
namespace VioletVreath {

/**
 * �G�@�P���X .
 * ��ʉE�[�Ő܂�Ԃ��č��ɒ��i���܂��B<BR>
 * initialize()�܂łɏ㏑���\�Ȑݒ�\�ȃp�����[�^<BR>
 * �E_X,_Y,_Z �����ʒu�A�A�� _Z<0 �ł��邱�ƁB�i�܂�Ԃ����t�ɂȂ��ĕς�����j<BR>
 * �E_X_turn, _Y_turn �܂�Ԃ��ڕWXY���W�B�����ʒu���炱�̂��̒n�_��ڎw���b�X�B<BR>
 * �E_veloBegin �܂�Ԃ��n�_�ɍs���܂ł̉����x<BR>
 *
 */
class EnemyCeres : public GgafLib::DefaultMeshSetActor {

private:

public:
    /** �e�X�g�b�N */
    GgafCore::GgafActorDepository* _pDepo_EnemyCeresShots001;
    /** �X�v���C���v���O���� */
    GgafLib::SplineSequence* _pProgram_CeresMove;

    /** GgafActorDepository���R���X�g���N�^�Ő����������ۂ� */
    bool _createGgafActorDepository;

    int _X_turn; // �܂�Ԃ�X���W
    int _Y_turn; // �܂�Ԃ�Y���W
    int _Z_turn; // �܂�Ԃ�Z���W
    int _veloBegin;
    int _incZ;

    int _iMovePatternNo;
    frame _frame_Active;
    SplineLineConnection* _pSplLineCon;

    /**
     * �R���X�g���N�^
     * @param prm_name �I�u�W�F�N�g
     * @param prm_pDepo_EnemyCeresShots001 ���˒e�X�g�b�N�̃A�N�^�[������
     * @return
     */
    EnemyCeres(const char* prm_name, GgafCore::GgafActorDepository* prm_pDepo_EnemyCeresShots001 = NULL);

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

