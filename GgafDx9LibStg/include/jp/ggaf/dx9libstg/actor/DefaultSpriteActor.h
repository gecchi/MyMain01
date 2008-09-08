#ifndef DEFAULTSPRITEACTOR_H_
#define DEFAULTSPRITEACTOR_H_


class DefaultSpriteActor : public GgafDx9SpriteActor {

public:
	DWORD _dwFrameOffset;

	StgMover* _pMover;

	StgChecker* _pChecker;

	DefaultSpriteActor(string prm_name, string prm_xname);

	virtual void initialize() {};

	virtual void processBehavior() {};

	virtual void processJudgement() {};

	virtual void processDrawPrior() {}; //ŽÀ‘•

	virtual void processDrawMain() {
		GgafDx9SpriteActor::processDrawMain();
	};

	virtual void processDrawTerminate();

	virtual void processOccur(int prm_no) {};

	virtual void processFinal() {};

	virtual void processOnHit(GgafActor* prm_pActor_Opponent) {};

	virtual ~DefaultSpriteActor();

	virtual bool isOffScreen();
};


#endif /*DEFAULTSPRITEACTOR_H_*/
