#ifndef DEFAULTSPRITEACTOR_H_
#define DEFAULTSPRITEACTOR_H_
namespace GgafDx9LibStg {

/**
 * �X�v���C�g�A�N�^�[�̋�ۃN���X.
 * GgafDx9Core::GgafDx9SpriteActor �������������ۃA�N�^�[�ł��B
 */
class DefaultSpriteActor : public GgafDx9Core::GgafDx9SpriteActor {

public:
	DWORD _dwFrameOffset;

	StgChecker* _pChecker;

	DefaultSpriteActor(char* prm_name, char* prm_model);

	virtual void initialize() {};

	virtual void processBehavior() {};

	virtual void processJudgement() {};

	virtual void processDrawPrior() {
		GgafDx9Core::GgafDx9SpriteActor::processDrawPrior();
	};

	virtual void processDrawMain() {
		GgafDx9Core::GgafDx9SpriteActor::processDrawMain();
	};

	virtual void processDrawTerminate();

	virtual void processHappen(int prm_no) {};

	virtual void processFinal() {};

	virtual void processOnHit(GgafCore::GgafActor* prm_pActor_Opponent) {};

	virtual ~DefaultSpriteActor();

	virtual bool isOffScreen();
};


}
#endif /*DEFAULTSPRITEACTOR_H_*/
