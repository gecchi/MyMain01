#ifndef DEFAULTSPRITEEFFECTACTOR_H_
#define DEFAULTSPRITEEFFECTACTOR_H_
namespace MyStg2nd {


class DefaultSpriteEffectActor : public GgafDx9LibStg::DefaultSpriteActor {

public:
	DefaultSpriteEffectActor(char* prm_name, char* prm_model);

	/**
	 * ��OverRide �ł���
	 */
	void processHappen(int prm_event);

	virtual ~DefaultSpriteEffectActor();
};

}
#endif /*DEFAULTSPRITEEFFECTACTOR_H_*/

