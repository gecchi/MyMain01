#ifndef FORMATIONMETIS001_H_
#define FORMATIONMETIS001_H_
namespace MyStg2nd {

#define NUM_METIS_FORMATION001 10
/**
 * フォーメーションアクタークラス .
 */
class FormationMetis001 : public GgafLib::TreeFormation {

    EnemyMetis* _pEnemyMetis[NUM_METIS_FORMATION001];
public:
    FormationMetis001(const char* prm_name);

    virtual void initialize() override;

    virtual ~FormationMetis001();
};

}
#endif /*FORMATIONMETIS001_H_*/
