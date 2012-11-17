#ifndef FORMATIONCERES001_H_
#define FORMATIONCERES001_H_
namespace VioletVreath {

#define NUM_CERES_FORMATION001 10
/**
 * フォーメーションアクタークラス .
 */
class FormationCeres001 : public GgafLib::TreeFormation {

    EnemyCeres* pEnemyCeres_[NUM_CERES_FORMATION001];
public:
    FormationCeres001(const char* prm_name);

    virtual void initialize() override;

    virtual void onDestroyedAll(GgafCore::GgafActor* prm_pActor_last_destroyed) override;

    virtual ~FormationCeres001();
};

}
#endif /*FORMATIONCERES001_H_*/
