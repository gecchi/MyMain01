#ifndef GGAFGARBAGEROOTACTOR_H_
#define GGAFGARBAGEROOTACTOR_H_
namespace GgafCore {


/**
 * お疲れルートアクター.
 * このアクターに所属したアクターは、遅かれ早かれdeleteされます。<BR>
 * 遅かれ早かれというのは、神(GgafGod)が、Fpsの余裕があるときに delete するという意味です<BR>
 */
class GgafGarbageRootActor : public GgafActor {
public:
	GgafGarbageRootActor() : GgafActor("GarbageRootActor") {};
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
	virtual ~GgafGarbageRootActor() {};
};


}
#endif /*GGAFGARBAGEROOTACTOR_H_*/
