#ifndef GGAFACTOR_H_
#define GGAFACTOR_H_
namespace GgafCore {


/**
 * アクターの基底クラス .
 * 本プログラムで言う『アクター（演者）』とは、主にゲームのキャラクターを表します。<BR>
 * 全てのアクタークラスは、本クラスを直接・間接継承しなければなりません。<BR>
 * GgafElementに当たり判定を実現する仕組みを加えたクラスになっています。<BR>
 * 基底テンプレートクラスの GgafNode と、GgafElement の説明も参照のこと。
 * @version 1.00
 * @since 2008/06/20
 * @auther Masatoshi Tsuge
 */
class GgafActor : public GgafElement<GgafActor> {

    friend class GgafGod;
    friend class GgafMainActor;
    friend class GgafLordActor;
    friend class GgafHeadActor;
    friend class GgafDummyActor;
    friend class GgafScene;
    friend class GgafWorld;

private:

	/** 現在の所属シーン */
    GgafScene* _pScene_Platform;


	/** ループ用 */
    GgafActor* _pActor_tmp;
    GgafActor* _pActor_tmp1;
    GgafActor* _pActor_tmp2;
    GgafActor* _pActor_tmp3;
    GgafActor* _pActor_tmp4;



	/**
	 * 所属シーンを設定する。 .
	 */
	void setScenePlatform(GgafScene* prm_pScene_Platform);

	/**
	 * 【自アクター 対 自ツリーアクターのどれか1つのアクター】の衝突判定処理を実行する .
	 * 本メソッドは executeBumpChk2_WeAnd(GgafActor*)から呼び出される専用メソッド。汎用性はない。<BR>
	 * 実行すると自アクターのprocessHitLogic()を呼び出し、その結果がtrueの場合(衝突した場合)は自身のprocessOnHit()と、
	 * 相手のアクターのprocessOnHit()を呼び出す。<BR>
	 * 戻り値の bool はヒットしたorしてないを意味する物ではないので忘れるな。<BR>
	 * @param	prm_pActor_Opponent	衝突判定する自ツリーアクターのどれか1つのアクター
	 * @retval	true	パラメータが自アクター
	 * @retval	false	パラメータが自アクター以外
	 */
	bool executeBumpChk2_MeAnd(GgafActor* prm_pActor_Opponent);

	/**
	 * 【自ツリーアクター 対 自ツリーアクターのどれか1つのアクター】ついて衝突判定処理(executeBumpChk_MeAnd)を実行する .
	 * executeBumpChkRoundRobin2() から呼び出される。<BR>
	 * executeBumpChk_WeAnd(GgafActor*)と基本的に同じアルゴリズムであるが、必ずやってくる自アクター同士当たり判定のチェックを行うようになってしまった時点で<BR>
	 * 離脱し、それ以上再帰ループを行わないようしている。残りの組み合わせは後続のループで補われる。（ハズである）<BR>
	 * 離脱する理由は、自アクター配下同士の総当たりであるため、単純に襷の組み合わせで行うと<BR>
	 *  Actor① → Actor② 　　（矢印は衝突判定するという意味）<BR>
	 *  Actor② → Actor①<BR>
	 * のように、衝突判定処理が重複してしまうため、これを避けるため途中でループ離脱するのである。<BR>
	 * executeBumpChkRoundRobin2() 専用メソッドといっても良い。汎用性は無い。<BR>
	 * 戻り値の bool はヒットしたorしてないを意味する物ではないので忘れるな。<BR>
	 * @param	prm_pActor_Opponent	衝突判定する自ツリーアクターのどれか1つのアクター
	 * @retval	true	再帰処理打ち切り
	 * @retval	false	再帰処理続行
	 */
	bool executeBumpChk2_WeAnd(GgafActor* prm_pActor_Opponent);



public:


	/** アクター開始システム時刻 */
	DWORD _start_system_time;

  	/** アクター衝突判定有無フラグ */
	bool _canBump ;

	/** 同一描画レベルの次のアクター */
    GgafActor* _pNext_TheSameDrawDepthLevel;

	/**
	 * コンストラクタ .
	 * @param prm_name アクターの名前
	 */
	GgafActor(string prm_name);

	/**
	 * デストラクタ .
	 * 自ツリーアクターの解放を行います。
	 */
	virtual ~GgafActor();


	/**
	 * 自アクターの衝突判定有無を設定する。 .
	 * @param	prm_canBump  衝突判定有無(true:衝突判定有り／false:衝突判定無し)
     */
	virtual void setBumpableAlone(bool prm_canBump);

	/**
	 * 自ツリーアクターの衝突判定有無を設定する。 .
	 * @param	prm_canBump  衝突判定有無(true:衝突判定有り／false:衝突判定無し)
	 */
	virtual void setBumpable(bool prm_canBump);

	/**
	 * 衝突できるかどうか
	 * @return	bool true:衝突できる／false:衝突できない
	 */
	virtual bool canBump();

	/**
	 * 所属しているシーンを取得。 .
	 * @return	GgafScene*	所属しているシーン
	 */
	virtual GgafScene* getPlatformScene();


	/**
	 * 【自アクター 対 他アクター】の衝突判定処理を実行する .
	 * 自身のprocessHitLogic()の結果、衝突した場合(true)は自身のprocessOnHit()と、相手アクターのprocessOnHit()が実行される .
	 * @param	prm_pActor_Opponent	相手の他アクター
	 */
	virtual void executeBumpChk_MeAnd(GgafActor* prm_pActor_Opponent);

	/**
	 * 【自ツリーアクター 対 他アクター】の衝突判定処理を実行する .
	 * 内部的には、自ツリーアクター 全てについて、executeBumpChk_MeAnd(GgafActor*) を順次実行。<BR>
	 * @param	prm_pActor_Opponent	相手の他アクター
	 */
	virtual void executeBumpChk_WeAnd(GgafActor* prm_pActor_Opponent);

	/**
     * 【自ツリーアクター 対 他ツリーアクター】の総当たりで衝突判定を実行する .
	 * 内部的には、引数である 他ツリーアクター の全てについて、executeBumpChk_WeAnd(GgafActor*) を順次実行しているだけ。<BR>
	 * @param	prm_pActor_Opponent	相手の他ツリーアクター
	 */
	virtual void executeBumpChkRoundRobin(GgafActor* prm_pActor_Opponent);


	/**
     * 【自ツリーアクター 対 自ツリーアクターのどれか1つのアクターを頂点とするツリーアクター】の総当たりで衝突判定を実行する。.
	 * 内部的には、引数のアクター の全てについて、executeBumpChk2_WeAnd(GgafActor*) を順次実行しているだけ。<BR>	 * 但し自アクター同士の重複組み合わせを無視する。 <BR>
	 * @param	prm_pActor_Opponent	自ツリーアクターのどれか1つのアクター
	 */
	virtual void executeBumpChkRoundRobin2(GgafActor* prm_pActor_Opponent);

	/**
	 * 自アクターと他アクターと衝突したかどうか判定する。 .
	 * executeBumpChk_MeAnd(GgafActor*) が実行された場合に呼び出されることになります。<BR>
	 * 下位クラスで衝突判定ロジックを実装してください。<BR>
	 * @param	prm_pActor_Opponent	相手の他アクター
	 * @retval	true	衝突している
	 * @retval	false	衝突していない
	 */
	virtual bool processBumpChkLogic(GgafActor* prm_pActor_Opponent) = 0;


	/**
	 * 他アクターと衝突した時の処理 .
	 * processBumpChkLogic(GgafActor*) の場合に呼び出されることになります。<BR>
	 * 或いは、相手のアクターの processBumpChkLogic(GgafActor*) の場合も呼び出されます。<BR>
	 * 衝突判定の結果、衝突した場合の処理を下位クラス実装してください。<BR>
	 * @param	prm_pActor_Opponent	衝突している相手のアクター（１つ）
	 */
	virtual void processOnHit(GgafActor* prm_pActor_Opponent) = 0;


	/**
	 * デバッグ用：ツリー構造を表示<BR>
	 */
	virtual void dump();

	/**
	 * デバッグ用：dump()から使用される<BR>
	 */
	virtual void dump(string prm_parent);

};


}
#endif /**GGAFACTOR_H_*/
