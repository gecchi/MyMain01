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
	FormationVesta001(string prm_name, string prm_model);

	virtual void initialize();

	virtual ~FormationVesta001();
};


}
#endif /*FORMATIONVESTA001_H_*/
