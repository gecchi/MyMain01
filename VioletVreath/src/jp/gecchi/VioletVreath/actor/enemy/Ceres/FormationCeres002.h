#ifndef FORMATIONCERES002_H_
#define FORMATIONCERES002_H_
namespace VioletVreath {

#define NUM_CERES_FORMATION002 30
/**
 * フォーメーションアクタークラス .
 */
class FormationCeres002 : public GgafLib::TreeFormation {

    EnemyCeres* pEnemyCeres_[NUM_CERES_FORMATION002];
public:
//    GgafCore::GgafActorDepository* pDepo_EnemyMeshShots001_;

    FormationCeres002(const char* prm_name);

    void initialize() override;

    virtual ~FormationCeres002();
};

}
#endif /*FORMATIONCERES002_H_*/
