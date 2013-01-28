#ifndef ENEMYMASSALIAFRAGMENT3_H_
#define ENEMYMASSALIAFRAGMENT3_H_
namespace VioletVreath {

/**
 * �}�b�T���A�f�Ђ̒f��  .
 * 覐΂̒f�Ђ̒f��
 * @version 1.00
 * @since 2012/01/17
 * @author Masatoshi Tsuge
 */
class EnemyMassaliaFragment3 : public EnemyMassaliaBase {

protected:
    void processStaminaEnd(GgafDxCore::GgafDxGeometricActor* prm_pOther) override;

public:
    EnemyMassaliaFragment3(const char* prm_name);

    void onCreateModel() override;

    void initialize() override;

    void onActive() override;

    void onInactive() override;

    virtual ~EnemyMassaliaFragment3();
};

}
#endif /*ENEMYMASSALIAFRAGMENT3_H_*/

