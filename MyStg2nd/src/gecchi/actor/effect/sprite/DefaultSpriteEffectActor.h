#ifndef DEFAULTSPRITEEFFECTACTOR_H_
#define DEFAULTSPRITEEFFECTACTOR_H_


class DefaultSpriteEffectActor : public DefaultSpriteActor {

public:
	DefaultSpriteEffectActor(string prm_name, string prm_xname);

	/**
	 * ��OverRide �ł���
	 */
	void processHappen(int prm_event);

	virtual ~DefaultSpriteEffectActor();
};

#endif /*DEFAULTSPRITEEFFECTACTOR_H_*/

