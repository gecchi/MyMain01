#ifndef LASER001PACTOR_H_
#define LASER001PACTOR_H_
namespace MyStg2nd {


class MyLaser001 : public DefaultSpriteMyActor {

	int _X_prevFrame;
	int _Y_prevFrame;
	int _Z_prevFrame;

	/** 対象アクター */
	GgafDx9Core::GgafDx9UntransformedActor* _pActor_Radical;

public:
	MyLaser001(std::string prm_name, std::string prm_model);

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
 	void processOnHit(GgafCore::GgafActor* prm_pActor_Opponent);

	/**
	 * ＜OverRide です＞
	 */
 	void onStop();


	void setRadicalActor(GgafDx9Core::GgafDx9UntransformedActor* prm_pActor) {
 		_pActor_Radical = prm_pActor;
 	}
	virtual ~MyLaser001();
};


}
#endif /*LASER001PACTOR_H_*/

