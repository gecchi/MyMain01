#ifndef ENEMYMASSALIA_H_
#define ENEMYMASSALIA_H_
namespace VioletVreath {

/**
 * マッサリア  .
 * 隕石群の隕石
 * @version 1.00
 * @since 2011/10/15
 * @author Masatoshi Tsuge
 */
class EnemyMassalia : public EnemyMassaliaBase {

protected:
    void processStaminaEnd(GgafDxCore::GgafDxGeometricActor* prm_pOther) override;

public:
    EnemyMassalia(const char* prm_name);

    void onCreateModel() override;

    void initialize() override;

    void onActive() override;

    void onInactive() override;

    virtual ~EnemyMassalia();
};

}
#endif /*ENEMYMASSALIA_H_*/

