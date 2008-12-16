#ifndef GGAFTRASHBOX_H_
#define GGAFTRASHBOX_H_

/**
 * ゴミ箱 .
 * 不要になったオブジェクトは、とりあえずココに登録。<BR>
 * 処理の余裕のあるときに神(GgafGod) が DELETE してゆきます<BR>
 * @version 1.00
 * @since 2008/12/16
 * @auther Masatoshi Tsuge
 */
class GgafTrashBox : public GgafObject {
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

public:

	GgafTrashRootActor* _pTrashRootActor;
	GgafTrashRootScene* _pTrashRootScene;

	GgafTrashBox();

	void add(GgafActor* prm_pActor) {
		_pTrashRootActor->addSubLast(prm_pActor->tear());
	};

	void add(GgafScene* prm_pScene) {
		_pTrashRootScene->addSubLast(prm_pScene->tear());
	};


	void cleane(int prm_iNumCleanNode) {
		_pTrashRootScene->cleane(prm_iNumCleanNode);
		_pTrashRootActor->cleane(prm_iNumCleanNode);
	};


	virtual ~GgafTrashBox();
};

#endif /*GGAFTRASHBOX_H_*/
