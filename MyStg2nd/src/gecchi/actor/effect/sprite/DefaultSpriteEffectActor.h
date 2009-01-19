#ifndef DEFAULTSPRITEEFFECTACTOR_H_
#define DEFAULTSPRITEEFFECTACTOR_H_
namespace MyStg2nd {


class DefaultSpriteEffectActor : public GgafDx9LibStg::DefaultSpriteActor {

public:
	DefaultSpriteEffectActor(string prm_name, string prm_model);

	/**
	 * ÅÉOverRide Ç≈Ç∑ÅÑ
	 */
	void processHappen(int prm_event);

	virtual ~DefaultSpriteEffectActor();
};

}
#endif /*DEFAULTSPRITEEFFECTACTOR_H_*/

