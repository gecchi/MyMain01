#ifndef FORMATIONMETIS001_H_
#define FORMATIONMETIS001_H_
namespace VioletVreath {

#define NUM_METIS_FORMATION001 10
/**
 * �t�H�[���[�V�����A�N�^�[�N���X .
 */
class FormationMetis001 : public GgafLib::TreeFormation {

    EnemyMetis* apEnemyMetis_[NUM_METIS_FORMATION001];
public:
    FormationMetis001(const char* prm_name);

    virtual void initialize() override;

    virtual ~FormationMetis001();
};

}
#endif /*FORMATIONMETIS001_H_*/