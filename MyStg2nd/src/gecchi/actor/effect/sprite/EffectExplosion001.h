#ifndef EFFECTEXPLOSION001_H_
#define EFFECTEXPLOSION001_H_
namespace MyStg2nd {


class EffectExplosion001 : public GgafDx9LibStg::DefaultSpriteActor {

public:
	EffectExplosion001(const char* prm_name, const char* prm_model);

	/**
	 * ��OverRide �ł���
	 */
	void initialize();

	/**
	 * ��OverRide �ł���
	 */
	void processBehavior();

 	/**
	 * ��OverRide �ł���
	 */
	void processJudgement();



	virtual ~EffectExplosion001();
};


}
#endif /*EFFECTEXPLOSION001_H_*/

