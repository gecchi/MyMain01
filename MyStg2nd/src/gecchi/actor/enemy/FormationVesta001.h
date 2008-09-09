#ifndef FORMATIONVESTA001_H_
#define FORMATIONVESTA001_H_


#define NUM_VESTA_FORMATION001 5
/**
 * フォーメーションアクタークラス .
 */
class FormationVesta001 : public FormationActor {

	EnemyVesta* _pEnemyVesta[NUM_VESTA_FORMATION001];
public:
	FormationVesta001(string prm_name);

	virtual void initialize();

	virtual ~FormationVesta001();
};


#endif /*FORMATIONVESTA001_H_*/
