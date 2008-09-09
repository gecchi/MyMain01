#ifndef GGAFLORDACTOR_H_
#define GGAFLORDACTOR_H_

/**
 * 管理者アクタークラス .
 * シーンとアクターの橋渡しを行う特別なアクターです。<BR>
 * 全てのシーン(GgafSceaneオブジェクト)に必ず１人つ管理者アクターがメンバーになっています。<BR>
 * 管理者アクターは、必ずアクターツリーの頂点に位置します。<BR>
 * 管理者アクター(GgafLordActor)のサブアクターは必ずヘッドアクター(GgafHeadActor)になっています。<BR>
 * ヘッドアクター(GgafHeadActor)の解説もあわせて参照して下さい。
 * @version 1.00
 * @since 2008/06/20
 * @auther Masatoshi Tsuge
 */
class GgafLordActor : public GgafActor {
public:
	GgafLordActor(GgafScene* prm_pScene_Platform) ;


	/**
	 * 初期処理<BR>
	 */
	void initialize() {};

 	/**
	 * ＜OverRide です＞<BR>
	 */
	void processBehavior() {};

 	/**
	 * ＜OverRide です＞<BR>
	 */
	void processJudgement() {};

	/**
	 * ＜OverRide です＞<BR>
	 */
	void processDrawPrior() {};
	/**
	 * ＜OverRide です＞<BR>
	 */
	void processDrawMain() {};
	/**
	 * ＜OverRide です＞<BR>
	 */
	void processDrawTerminate() {};

	/**
	 * ＜OverRide です＞<BR>
	 */
	void processHappen(int prm_no) {};

	/**
	 * ＜OverRide です＞<BR>
	 */
	virtual void processFinal() {};

	/**
	 * ＜OverRide です＞<BR>
	 */
	bool processBumpChkLogic(GgafActor* prm_pActor_Opponent) {
		return false;
	};

	/**
	 * ＜OverRide です＞<BR>
	 */
	void processOnHit(GgafActor* prm_pActor_Opponent) {};

	/**
	 * ＜OverRide です＞<BR>
	 */
	void remove();

	/**
	 * 単独GgafActor、或いはGgafDummyActorが単独親となるGgafActor連続体を<BR>
     * 種別と共に登録する。
	 * 種別とは、内部で生成される GgafHeadActor名 になる。<BR>
	 * GgafHeadActor は初回種別登録時だけ生成される。２回目以降の同一種別登録は、<BR>
	 * 既存の GgafHeadActor が使用される。<BR>
	 * 本関数は内部的には prm_pActor を GgafHeadActor の子アクターとしているだけである。<BR>
     * @param   prm_kind    種別名（＝GgafHeadActor名）
     * @param   prm_pMainActor   登録するアクター
	 */
    void accept(actorkind prm_kind, GgafMainActor* prm_pActor);





	bool hasSubHeadActor(actorkind prm_kind);
	GgafHeadActor* getSubHeadActor(actorkind prm_kind);




	/**
	 * 直属のGgafHeadActorを取得する。<BR>
     * @param   prm_kind    種別("*"による省略可能)
     * @param   prm_pActor   登録するアクター
	 */
//    virtual GgafHeadActor* getHeadActor(string prm_kind);


    /**
	 * 神様に接見 .
	 * @return	呼ばれて出てきた神様
	 */
	virtual GgafGod* askGod();

	virtual ~GgafLordActor();
};
#endif /**GGAFLORDACTOR_H_*/
