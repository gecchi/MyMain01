#ifndef ENEMYJUNO_H_
#define ENEMYJUNO_H_
namespace MyStg2nd {

//ÉWÉÖÉmÅ[
class EnemyJuno : public DefaultMeshEnemyActor {

public:
	int _iMovePatternNo;

	EnemyJuno(char* prm_name, char* prm_model);

	void initialize();

	void processBehavior();

	void processJudgement();

 	void processOnHit(GgafCore::GgafActor* prm_pActor_Opponent);

	bool isOffScreen();

	virtual ~EnemyJuno();
};

}
#endif /*ENEMYJUNO_H_*/

