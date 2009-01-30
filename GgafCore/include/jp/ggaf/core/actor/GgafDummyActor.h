#ifndef GGAFDUMMYACTOR_H_
#define GGAFDUMMYACTOR_H_
namespace GgafCore {

/**
 * ダミーアクタークラス .
 * 子アクターが無くなれば自動的に自殺する悲しいアクターです。<BR>
 * 団体行動を採るときに、親アクターにすると便利かもしれません。<BR>
 * @version 1.00
 * @since 2008/06/20
 * @author Masatoshi Tsuge
 */
class GgafDummyActor : public GgafMainActor {

public:
	GgafDummyActor(std::string prm_name);

	/**
	 * 初期処理<BR>
	 */
	virtual void initialize() {};

	/**
	 * ＜OverRide です＞<BR>
	 */
	virtual void processBehavior() {};

 	/**
 	 * サブが無ければ死亡します。
	 * ＜OverRide です＞<BR>
	 */
	virtual void processJudgement() {
		if (getSubFirst() == NULL) {
			farewell();
		}
	}

	/**
	 * ＜OverRide です＞<BR>
	 */
	virtual void processDrawPrior() {};

	/**
	 * ＜OverRide です＞<BR>
	 */
 	virtual void processDrawMain() {};

	/**
	 * ＜OverRide です＞<BR>
	 */
 	virtual void processDrawTerminate() {};

	/**
	 * ＜OverRide です＞<BR>
	 */
 	virtual void processHappen(int prm_no) {};

	/**
	 * ＜OverRide です＞<BR>
	 */
	virtual void processFinal() {};

	/**
	 * ＜OverRide です＞<BR>
	 */
	virtual bool processBumpChkLogic(GgafActor* prm_pActor_Opponent) {
 		return false;
 	};

	/**
	 * ＜OverRide です＞<BR>
	 */
 	virtual void processOnHit(GgafActor* prm_pActor_Opponent) {};

	virtual ~GgafDummyActor();
};


}
#endif /*GGAFDUMMYACTOR_H_*/
