#ifndef FORMATIONCERES001_H_
#define FORMATIONCERES001_H_


#define NUM_CERES_FORMATION001 1
/**
 * フォーメーションアクタークラス .
 */
class FormationCeres001 : public GgafDx9LibStg::FormationActor {

	EnemyCeres* _pEnemyCeres[NUM_CERES_FORMATION001];
public:
	FormationCeres001(string prm_name, string prm_model);

	virtual void initialize();

	virtual ~FormationCeres001();
};


#endif /*FORMATIONCERES001_H_*/
