#ifndef FORMATIONCERES002_H_
#define FORMATIONCERES002_H_
namespace MyStg2nd {

#define NUM_CERES_FORMATION002 30
/**
 * フォーメーションアクタークラス .
 */
class FormationCeres002 : public GgafDx9LibStg::FormationActor {

    EnemyCeres* _pEnemyCeres[NUM_CERES_FORMATION002];
public:
    GgafDx9LibStg::RotationActor* _pRotEnemyMeshShots001;

    FormationCeres002(const char* prm_name);

    virtual void initialize();
    virtual void processJudgement();
    virtual ~FormationCeres002();
};

}
#endif /*FORMATIONCERES002_H_*/
