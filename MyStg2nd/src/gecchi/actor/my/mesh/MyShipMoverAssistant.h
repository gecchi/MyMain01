#ifndef MYSHIPMOVERASSISTANT_H_
#define MYSHIPMOVERASSISTANT_H_

class MyShipMoverAssistant : public DefaultMeshActor {

public:

	MyShipMoverAssistant(string prm_name, string prm_model);

	/**
	 * ��OverRide �ł���
	 */
	virtual void initialize();

	/**
	 * ��OverRide �ł���
	 */
	virtual void processBehavior();

 	/**
	 * ��OverRide �ł���
	 */
	virtual void processJudgement() {};

	/**
	 * ��OverRide �ł���
	 */
	virtual void processOnHit(GgafActor* prm_pActor_Opponent) {};



 	virtual ~MyShipMoverAssistant();





};


#endif /*MYSHIPMOVERASSISTANT_H_*/

