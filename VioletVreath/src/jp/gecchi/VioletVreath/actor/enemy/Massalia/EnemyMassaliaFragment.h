#ifndef ENEMYMASSALIAFRAGMENT_H_
#define ENEMYMASSALIAFRAGMENT_H_
namespace VioletVreath {

/**
 * マッサリア断片  .
 * 隕石の断片
 * @version 1.00
 * @since 2012/01/12
 * @author Masatoshi Tsuge
 */
class EnemyMassaliaFragment : public EnemyMassaliaBase {
protected:
    void processStaminaEnd(GgafDxCore::GgafDxGeometricActor* prm_pOther) override;

public:
    EnemyMassaliaFragment(const char* prm_name);

    void onCreateModel() override;

    void initialize() override;

    void onActive() override;

    void onInactive() override;

    virtual ~EnemyMassaliaFragment();
};

}
#endif /*ENEMYMASSALIAFRAGMENT_H_*/

