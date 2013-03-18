#ifndef ENEMYHERMIONEARMHEAD_H_
#define ENEMYHERMIONEARMHEAD_H_
namespace VioletVreath {

/**
 * �G�@�w���~�I�l�̐G��̓� .
 * �O���̐G��ɒ���b�b�I�I�I
 * @version 1.00
 * @since 2012/11/05
 * @author Masatoshi Tsuge
 */
class EnemyHermioneArmHead : public EnemyHermioneArm {

public:
    /** [r/w]�n�b�`���甭�˂����A�N�^�[�������o�[�Ɏ��f�|�W�g�� */
//    DepositoryConnection* pDpcon_;
//    GgafCore::GgafActorDepository* pDepo_Fired_;

public:
    EnemyHermioneArmHead(const char* prm_name);

    void onCreateModel() override;

    void initialize() override;

    void processBehavior() override;

    void onHit(GgafCore::GgafActor* prm_pOtherActor) override;

    virtual ~EnemyHermioneArmHead();
};

}
#endif /*ENEMYHERMIONEARMHEAD_H_*/

