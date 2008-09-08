#ifndef TAMAGOACTOR_H_
#define TAMAGOACTOR_H_


class TamagoActor : public DefaultMeshActor {


	int _rnd;

public:
	TamagoActor(string prm_name, string prm_xname);

	void initialize();

	void processBehavior();

	void processJudgement();

 	void processOnHit(GgafActor* prm_pActor_Opponent);


	virtual ~TamagoActor();
};


#endif /*TAMAGOACTOR_H_*/

