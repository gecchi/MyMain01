#ifndef FORMATIONCERES001_H_
#define FORMATIONCERES001_H_


#define NUM_CERES_FORMATION001 30
/**
 * フォーメーションアクタークラス .
 */
class FormationCeres001 : public FormationActor {

	EnemyCeres* _pEnemyCeres[NUM_CERES_FORMATION001];
public:
	FormationCeres001(string prm_name);

	virtual void initialize();

	virtual ~FormationCeres001();
};


#endif /*FORMATIONCERES001_H_*/
