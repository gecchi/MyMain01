#ifndef GGAFTRASHROOTACTOR_H_
#define GGAFTRASHROOTACTOR_H_
/**
 * ゴミルートアクター
 */
class GgafTrashRootActor : public GgafActor {
public:
	GgafTrashRootActor() : GgafActor("TrashRootActor") {};
	void initialize() {};
	void processBehavior() {};
	void processJudgement() {};
	void processDrawPrior() {};
	void processDrawMain() {};
	void processDrawTerminate() {};
	void processHappen(int prm_no) {};
	void processFinal() {};
	bool processBumpChkLogic(GgafActor* prm_pActor_Opponent) { return false; };
	void processOnHit(GgafActor* prm_pActor_Opponent) {};
	GgafGod* askGod() { return NULL; };
	virtual ~GgafTrashRootActor() {};
};

#endif /*GGAFTRASHROOTACTOR_H_*/
