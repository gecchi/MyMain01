#ifndef GGAFHEADACTOR_H_
#define GGAFHEADACTOR_H_



/**
 * ヘッドアクタークラス .
 * キャラクタを表現するアクターを纏めてグループにし、配下のアクターの種別を表すアクターになります。<BR>
 * 種別とは、当たり判定自の [自機の弾]ｘ[敵本体] 等の [] の中身を表すものです。<BR>
 * ヘッドアクターは配下のアクターが消滅すると、次のフレームに自身も自殺します。<BR>
 * 管理者アクター(GgafLordActor)のサブアクターは、全て必ずこのヘッドアクターになっています。<BR>
 * また、ヘッドアクター配下にヘッドアクターが存在してはいけないことになっています。<BR>
 * ＜補足：オブジェクトイメージ図＞<BR>
 * <PRE>
 * 　　　　･･･⇔ GgafScene ⇔ GgafScene ⇔･･･
 * 　　　　　　　　　｜
 * 　　　　　　　　　↓メンバー
 * 　　　　　GgafLordActor　（←1つのSceneに必ず１つのLordActor）
 * 　　　　　　　｜
 * 　　　　　　　｜SubFirst
 * 　　　　　　　↓
 * 　　GgafHeadActor ⇔ GgafHeadActor ⇔ GgafHeadActor ⇔
 * 　　　　　　｜　　　　　　　　｜　　　　　　　　　｜
 * 　　　　　　｜SubFirst　　　｜　　　　　　　　　｜
 * 　　　　　　↓　　　　　　　　↓　　　　　　　　　↓
 * 　　キャラのアクター達　　キャラのアクター達　　キャラのアクター
 * </PRE>
 * @version 1.00
 * @since 2008/06/20
 * @auther Masatoshi Tsuge
 */
class GgafHeadActor : public GgafActor {

public:

	actorkind _kind;

	GgafHeadActor(actorkind prm_kind);

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
	void processJudgement();

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
	 * 神様に接見 .
	 * @return	呼ばれて出てきた神様
	 */
	virtual GgafGod* askGod();

	virtual ~GgafHeadActor();
};


#endif /*GGAFHEADACTOR_H_*/
