#ifndef FORMATIONCERES001_H_
#define FORMATIONCERES001_H_
namespace VioletVreath {

#define NUM_CERES_FORMATION001 10
/**
 * �t�H�[���[�V�����A�N�^�[�N���X .
 */
class FormationCeres001 : public GgafLib::TreeFormation {

    EnemyCeres* pEnemyCeres_[NUM_CERES_FORMATION001];
public:
    FormationCeres001(const char* prm_name);

    virtual void initialize() override;

    virtual ~FormationCeres001();
};

}
#endif /*FORMATIONCERES001_H_*/