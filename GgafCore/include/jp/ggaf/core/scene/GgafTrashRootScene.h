#ifndef GGAFTRASHROOTSCENE_H_
#define GGAFTRASHROOTSCENE_H_

/**
 * ゴミルートシーン
 */
class GgafTrashRootScene : public GgafScene {
public:
	GgafTrashRootScene(): GgafScene("TrashRootScene") {};
	void initialize() {};
	void processBehavior() {};
	void processJudgement() {};
	void processDrawPrior() {};
	void processDrawMain() {};
	void processDrawTerminate() {};
	void processHappen(int prm_no) {};
	void processFinal() {};
	virtual ~GgafTrashRootScene() {};
};


#endif /*GGAFTRASHROOTSCENE_H_*/
