#ifndef FORMATIONCERES001_H_
#define FORMATIONCERES001_H_
namespace MyStg2nd {

#define NUM_CERES_FORMATION001 10
/**
 * フォーメーションアクタークラス .
 */
class FormationCeres001 : public GgafLib::FormationActor {

    EnemyCeres* _pEnemyCeres[NUM_CERES_FORMATION001];
public:
    FormationCeres001(const char* prm_name);

    virtual void initialize() override;

    virtual ~FormationCeres001();
};

}
#endif /*FORMATIONCERES001_H_*/
