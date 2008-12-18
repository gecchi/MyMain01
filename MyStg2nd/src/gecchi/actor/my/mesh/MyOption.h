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
		virtual ~GeometryChain() {
			_next = NULL;
		}
	};

public:
	int _iMyNo;

	RotationActor* _pMyLaserChipRotation;

	GeometryChain* _pGeoChainRingActive;
	/** 対象アクター */
	GgafDx9UntransformedActor* _pActor_Radical;

	MyOption(string prm_name, string prm_model);

	/**
	 * ＜OverRide です＞
	 */
	void initialize();

	/**
	 * ＜OverRide です＞
	 */
	void processBehavior();

 	/**
	 * ＜OverRide です＞
	 */
	void processJudgement();

	/**
	 * ＜OverRide です＞
	 */
 	void processOnHit(GgafActor* prm_pActor_Opponent);


	void setRadicalActor(GgafDx9UntransformedActor* prm_pActor) {
 		_pActor_Radical = prm_pActor;
 	}

 	virtual ~MyOption();
};


#endif /*MYOPTION_H_*/

