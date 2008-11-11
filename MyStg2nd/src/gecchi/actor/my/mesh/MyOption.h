#ifndef MYOPTION_H_
#define MYOPTION_H_

class MyOption : public DefaultMeshActor {

	class GeometryChain {
	public:
		int _X;
		int _Y;
		int _Z;
		GeometryChain* _next;
		GeometryChain(int prm_X, int prm_Y, int prm_Z) {
			_X = prm_X; _Y = prm_Y; _Z = prm_Z;
			_next = NULL;
		};

		GeometryChain(GgafDx9UntransformedActor* prm_pActor) {
			_X = prm_pActor->_X;
			_Y = prm_pActor->_Y;
			_Z = prm_pActor->_Z;
			_next = NULL;
		};

		void set(int prm_X, int prm_Y, int prm_Z) {
			_X = prm_X;
			_Y = prm_Y;
			_Z = prm_Z;
		};
		void set(GgafDx9UntransformedActor* prm_pActor) {
			_X = prm_pActor->_X;
			_Y = prm_pActor->_Y;
			_Z = prm_pActor->_Z;
		};

	};

public:

	GeometryChain* _pGeoChainRingActive;

	MyOption(DWORD prm_dwBufferFrame, string prm_model);

	/**
	 * ÅÉOverRide Ç≈Ç∑ÅÑ
	 */
	void initialize();

	/**
	 * ÅÉOverRide Ç≈Ç∑ÅÑ
	 */
	void processBehavior();

 	/**
	 * ÅÉOverRide Ç≈Ç∑ÅÑ
	 */
	void processJudgement();

	/**
	 * ÅÉOverRide Ç≈Ç∑ÅÑ
	 */
 	void processOnHit(GgafActor* prm_pActor_Opponent);

 	virtual ~MyOption();
};


#endif /*MYOPTION_H_*/

