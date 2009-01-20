#ifndef EFFECTEXPLOSION001_H_
#define EFFECTEXPLOSION001_H_
namespace MyStg2nd {


class EffectExplosion001 : public GgafDx9LibStg::DefaultSpriteActor {

public:
	EffectExplosion001(std::string prm_name, std::string prm_model);

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



	virtual ~EffectExplosion001();
};


}
#endif /*EFFECTEXPLOSION001_H_*/

