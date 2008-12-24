#ifndef MYSHIPMOVERASSISTANT_H_
#define MYSHIPMOVERASSISTANT_H_

class MyShipMoverAssistant : public DefaultMeshActor {

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
	virtual void processOnHit(GgafActor* prm_pActor_Opponent) {};



 	virtual ~MyShipMoverAssistant();





};


#endif /*MYSHIPMOVERASSISTANT_H_*/

