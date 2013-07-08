#ifndef ENEMYERES_H_
#define ENEMYERES_H_
#include "jp/ggaf/lib/actor/DefaultMeshSetActor.h"

namespace VioletVreath {

/**
 * �G�@�G���X .
 * ��ʉE�[�Ő܂�Ԃ��č��ɒ��i���܂��B<BR>
 * initialize()�܂łɏ㏑���\�Ȑݒ�\�ȃp�����[�^<BR>
 * �E_X,_Y,_Z �����ʒu�A�A�� _Z<0 �ł��邱�ƁB�i�܂�Ԃ����t�ɂȂ��ĕς�����j<BR>
 * �EX_turn_, Y_turn_ �܂�Ԃ��ڕWXY���W�B�����ʒu���炱�̂��̒n�_��ڎw���b�X�B<BR>
 *
 */
class EnemyEres : public GgafLib::DefaultMeshSetActor {

public:
    enum {
        SE_EXPLOSION ,
    };

    /** �e�X�g�b�N */
    GgafCore::GgafActorDepository* pDepo_EnemyEresShots001_;
    /** �X�v���C���v���O���� */
    GgafLib::SplineKurokoLeader* pProgram_EresMove_;

    /** GgafActorDepository���R���X�g���N�^�Ő����������ۂ� */
    bool createGgafActorDepository_;

    int X_turn_; // �܂�Ԃ�X���W
    int Y_turn_; // �܂�Ԃ�Y���W
    int Z_turn_; // �܂�Ԃ�Z���W

    int iMovePatternNo_;
    frame frame_Active_;
    SplineLineConnection* pSplLineConnection_;

public:
    /**
     * �R���X�g���N�^
     * @param prm_name �I�u�W�F�N�g
     * @param prm_pDepo_EnemyEresShots001 ���˒e�X�g�b�N�̃A�N�^�[������
     * @return
     */
    EnemyEres(const char* prm_name, GgafCore::GgafActorDepository* prm_pDepo_EnemyEresShots001 = nullptr);

    void initialize() override;

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;

    void onHit(GgafCore::GgafActor* prm_pOtherActor) override;

    bool isOutOfUniverse() override;

    void onInactive() override;

    virtual ~EnemyEres();
};

}
#endif /*ENEMYERES_H_*/

