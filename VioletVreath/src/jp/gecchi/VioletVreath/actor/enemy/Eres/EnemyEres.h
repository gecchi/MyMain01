#ifndef ENEMYERES_H_
#define ENEMYERES_H_
#include "VioletVreath.h"
#include "jp/gecchi/VioletVreath/actor/VvEnemyActor.hpp"
#include "jp/ggaf/lib/actor/DefaultMeshSetActor.h"

namespace VioletVreath {

/**
 * �G�@�G���X .
 * ��ʉE�[�Ő܂�Ԃ��č��ɒ��i���܂��B<BR>
 * initialize()�܂łɏ㏑���\�Ȑݒ�\�ȃp�����[�^<BR>
 * �E_x,_y,_z �����ʒu�A�A�� _z<0 �ł��邱�ƁB�i�܂�Ԃ����t�ɂȂ��ĕς�����j<BR>
 * �EX_turn_, Y_turn_ �܂�Ԃ��ڕWXY���W�B�����ʒu���炱�̂��̒n�_��ڎw���b�X�B<BR>
 *
 */
class EnemyEres : public VvEnemyActor<GgafLib::DefaultMeshSetActor> {

public:
    /** �e�X�g�b�N */
    GgafCore::ActorDepository* pDepo_shot001_;
    /** �X�v���C���v���O���� */
    GgafDx::VehicleLeader* pVehicleLeader_;
    /** GgafCore::ActorDepository���R���X�g���N�^�Ő����������ۂ� */
    bool createActorDepository_;

    int iMovePatternNo_;
    GgafDx::CurveManufactureConnection* pCurveManufConn_;

public:
    /**
     * �R���X�g���N�^
     * @param prm_name �I�u�W�F�N�g
     * @param prm_pDepo_EnemyEresShots001 ���˒e�X�g�b�N�̃A�N�^�[������
     * @return
     */
    EnemyEres(const char* prm_name, GgafCore::ActorDepository* prm_pDepo_EnemyEresShots001 = nullptr);

    void initialize() override;

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;

    void onHit(const GgafCore::Actor* prm_pOtherActor) override;

    bool isOutOfSpacetime() const override;

    void onInactive() override;

    virtual ~EnemyEres();
};

}
#endif /*ENEMYERES_H_*/

