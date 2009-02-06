#ifndef FORMATIONCERES001_H_
#define FORMATIONCERES001_H_
namespace MyStg2nd {

#define NUM_CERES_FORMATION001 1
/**
 * フォーメーションアクタークラス .
 */
class FormationCeres001 : public GgafDx9LibStg::FormationActor {

    EnemyCeres* _pEnemyCeres[NUM_CERES_FORMATION001];
public:
    FormationCeres001(const char* prm_name, const char* prm_model);

    virtual void initialize();

    virtual ~FormationCeres001();
};

}
#endif /*FORMATIONCERES001_H_*/
