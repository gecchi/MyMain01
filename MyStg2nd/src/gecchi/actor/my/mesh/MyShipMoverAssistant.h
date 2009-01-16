#ifndef MYSHIPMOVERASSISTANT_H_
#define MYSHIPMOVERASSISTANT_H_

class MyShipMoverAssistant : public GgafDx9LibStg::DefaultMeshActor {

public:

	MyShipMoverAssistant(string prm_name, string prm_model);

	/**
	 * ÅÉOverRide Ç≈Ç∑ÅÑ
	 */
	virtual void initialize();

	/**
	 * ÅÉOverRide Ç≈Ç∑ÅÑ
	 */
	virtual void processBehavior();

 	/**
	 * ÅÉOverRide Ç≈Ç∑ÅÑ
	 */
	virtual void processJudgement() {};

	/**
	 * ÅÉOverRide Ç≈Ç∑ÅÑ
	 */
	virtual void processOnHit(GgafCore::GgafActor* prm_pActor_Opponent) {};



 	virtual ~MyShipMoverAssistant();





};


#endif /*MYSHIPMOVERASSISTANT_H_*/

