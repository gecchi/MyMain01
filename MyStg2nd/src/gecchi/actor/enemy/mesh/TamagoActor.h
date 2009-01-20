#ifndef TAMAGOACTOR_H_
#define TAMAGOACTOR_H_
namespace MyStg2nd {


class TamagoActor : public GgafDx9LibStg::DefaultMeshActor {


	int _rnd;

public:
	TamagoActor(std::string prm_name, std::string prm_model);

	void initialize();

	void processBehavior();

	void processJudgement();

 	void processOnHit(GgafCore::GgafActor* prm_pActor_Opponent);


	virtual ~TamagoActor();
};


}
#endif /*TAMAGOACTOR_H_*/

