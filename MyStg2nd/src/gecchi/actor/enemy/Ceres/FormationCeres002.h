#ifndef FORMATIONCERES002_H_
#define FORMATIONCERES002_H_
namespace MyStg2nd {

#define NUM_CERES_FORMATION002 30
/**
 * フォーメーションアクタークラス .
 */
class FormationCeres002 : public GgafDx9Core::GgafDx9FormationActor {

    EnemyCeres* _pEnemyCeres[NUM_CERES_FORMATION002];
public:
    GgafCore::GgafActorStore* _pStore_EnemyMeshShots001;

    FormationCeres002(const char* prm_name);

    void initialize() override;

    virtual ~FormationCeres002();
};

}
#endif /*FORMATIONCERES002_H_*/
