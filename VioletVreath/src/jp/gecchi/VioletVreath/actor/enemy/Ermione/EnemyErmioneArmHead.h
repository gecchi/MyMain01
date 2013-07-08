#ifndef ENEMYERMIONEARMHEAD_H_
#define ENEMYERMIONEARMHEAD_H_
#include "jp/gecchi/VioletVreath/actor/enemy/Ermione/EnemyErmioneArm.h"

namespace VioletVreath {

/**
 * �G�@�G�~�I�l�̐G��̓� .
 * �O���̐G��ɒ���b�b�I�I�I
 * @version 1.00
 * @since 2012/11/05
 * @author Masatoshi Tsuge
 */
class EnemyErmioneArmHead : public EnemyErmioneArm {

public:
    /** [r/w]�n�b�`���甭�˂����A�N�^�[�������o�[�Ɏ��f�|�W�g�� */
//    DepositoryConnection* pDepoConnection_;
//    GgafCore::GgafActorDepository* pDepo_Fired_;

public:
    EnemyErmioneArmHead(const char* prm_name);

    void onCreateModel() override;

    void initialize() override;

    void processBehavior() override;

    void onHit(GgafCore::GgafActor* prm_pOtherActor) override;

    virtual ~EnemyErmioneArmHead();
};

}
#endif /*ENEMYERMIONEARMHEAD_H_*/

