#ifndef ENEMYHERMIONEARMBODY_H_
#define ENEMYHERMIONEARMBODY_H_
namespace VioletVreath {

/**
 * 敵機ヘルミオネの触手の胴体 .
 * グラの触手に挑戦ッッ！！！
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

