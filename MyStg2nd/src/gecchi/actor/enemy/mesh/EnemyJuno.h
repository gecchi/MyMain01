#ifndef ENEMYJUNO_H_
#define ENEMYJUNO_H_
namespace MyStg2nd {

//�W���m�[
class EnemyJuno : public DefaultMeshEnemyActor {

public:
	int _iMovePatternNo;

	EnemyJuno(std::string prm_name, std::string prm_model);

	void initialize();

	void processBehavior();

	void processJudgement();

 	void processOnHit(GgafCore::GgafActor* prm_pActor_Opponent);

	bool isOffScreen();

	virtual ~EnemyJuno();
};

}
#endif /*ENEMYJUNO_H_*/

