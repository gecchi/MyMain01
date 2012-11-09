#ifndef ENEMYHERMIONEARMBODY_H_
#define ENEMYHERMIONEARMBODY_H_
namespace VioletVreath {

/**
 * �G�@�w���~�I�l�̐G��̓��� .
 * �O���̐G��ɒ���b�b�I�I�I
 * @version 1.00
 * @since 2012/11/05
 * @author Masatoshi Tsuge
 */
class EnemyHermioneArmBody : public EnemyHermioneArm {
public:

    EnemyHermioneArmBody(const char* prm_name);

    void onCreateModel() override;

    void initialize() override;

    void onHit(GgafCore::GgafActor* prm_pOtherActor) override;

    virtual ~EnemyHermioneArmBody();
};

}
#endif /*ENEMYHERMIONEARMBODY_H_*/

