#ifndef ENEMYPALLAS_H_
#define ENEMYPALLAS_H_
namespace MyStg2nd {

//ƒpƒ‰ƒX
class EnemyPallas : public DefaultMeshEnemyActor {

public:
	int _iMovePatternNo;

	EnemyPallas(std::string prm_name, std::string prm_model);

	void initialize();

	void processBehavior();

	void processJudgement();

 	void processOnHit(GgafCore::GgafActor* prm_pActor_Opponent);

	bool isOffScreen();

	virtual ~EnemyPallas();
};

}
#endif /*ENEMYPALLAS_H_*/

