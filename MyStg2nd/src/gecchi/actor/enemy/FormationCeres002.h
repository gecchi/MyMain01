#ifndef FORMATIONCERES002_H_
#define FORMATIONCERES002_H_


#define NUM_CERES_FORMATION002 30
/**
 * �t�H�[���[�V�����A�N�^�[�N���X .
 */
class FormationCeres002 : public GgafDx9LibStg::FormationActor {

	EnemyCeres* _pEnemyCeres[NUM_CERES_FORMATION002];
public:
	GgafDx9LibStg::RotationActor* _pRotEnemyMeshShots001;

	FormationCeres002(string prm_name, string prm_model);

	virtual void initialize();
	virtual void processJudgement();
	virtual ~FormationCeres002();
};

#endif /*FORMATIONCERES002_H_*/
