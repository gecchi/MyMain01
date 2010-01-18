#ifndef FORMATIONVESTA001_H_
#define FORMATIONVESTA001_H_
namespace MyStg2nd {

#define NUM_VESTA_FORMATION001 5
/**
 * フォーメーションアクタークラス .
 */
class FormationVesta001 : public GgafDx9LibStg::FormationActor {

    EnemyVesta* _pEnemyVesta[NUM_VESTA_FORMATION001];
public:
    FormationVesta001(const char* prm_name);

    virtual void initialize() override;

    virtual ~FormationVesta001();
};

}
#endif /*FORMATIONVESTA001_H_*/
