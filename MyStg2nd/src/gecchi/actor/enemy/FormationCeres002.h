#ifndef FORMATIONCERES002_H_
#define FORMATIONCERES002_H_


#define NUM_CERES_FORMATION002 100
/**
 * フォーメーションアクタークラス .
 */
class FormationCeres002 : public FormationActor {

	EnemyCeres* _pEnemyCeres[NUM_CERES_FORMATION002];
public:
	FormationCeres002(string prm_name, string prm_model);

	virtual void initialize();

	virtual ~FormationCeres002();
};

#endif /*FORMATIONCERES002_H_*/
