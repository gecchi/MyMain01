#ifndef GGAFSCENE_H_
#define GGAFSCENE_H_
namespace GgafCore {


/**
 * シーンの基底クラス .
 * 本プログラムで言う『シーン（場面）』とは、主にアクター(GgafActor)に指示するオブジェクトで<BR>
 * 各シーンは、必ず１つのアクターツリーをメンバとして保持しています。<BR>
 * 全てのシーンクラスは、本クラスを直接・間接継承しなければなりません。<BR>
 * また、シーン同士のポインタで、ツリー階層構造を採る事ができます。（このツリー構造はクラスの継承とは関係ありません）<BR>
 * シーンに実装されているメソッド郡のほとんどは、自分自身と自分配下のシーン（自ツリーシーン）全てに影響する仕様になっています。<BR>
 * ゲームをオブジェクト指向で表現するため、様々な『シーン（場面）』で『アクター(キャラ)』たちが活躍する、イメージで設計してあります。<BR>
 * <B>【用語補足】</B>
 * <TABLE border='1'>
 * <TR>
 * <TD>「シーン」</TD>
 * <TD>シーンクラスのインスタンス（オブジェクト）を省略して、単にシーンと呼ぶことにします。</TD>
 * </TR><TR>
 * <TD>「自シーン」「自」</TD>
 * <TD>メソッドが実行されるシーンオブジェクト自身を指しています。</TD>
 * </TR><TR>
 * <TD>「サブシーン」「サブ」</TD>
 * <TD>シーン同士のツリー階層構造上において、シーンに<B>直に</B>ぶら下がる１階層下のシーン達を指しています。</TD>
 * </TR><TR>
 * <TD>「シーン配下」「配下」</TD>
 * <TD>シーン同士のツリー階層構造上において、シーン<B>に</B>ぶら下がる全てのシーンを指しています。</TD>
 * </TR><TR>
 * <TD>「親シーン」「親」</TD>
 * <TD>シーン同士のツリー階層構造上において、自シーン<B>が</B>直接或いは間接的にぶら下がっているシーンを指しています。</TD>
 * </TR><TR>
 * <TD>「他シーン」「他」</TD>
 * <TD>自シーン以外のシーンを指しています。</TD>
 * </TR><TR>
 * <TD>「ツリー」</TD>
 * <TD>シーン同士がツリー階層構造によって連結されている1つのまとまりを指します。</TD>
 * </TR><TR>
 * <TD>「自所属ツリー」</TD>
 * <TD>自シーンが含まれているツリー構造部分全て指します。<</TD>
 * </TR><TR>
 * <TD>「自ツリー」</TD>
 * <TD>自シーンを頂点とする、自シーン＋自シーン配下のツリー階層構造部分を指します。</TD>
 * </TR><TR>
 * <TD>「自ツリーシーン」</TD>
 * <TD>自シーン＋自シーン配下のシーン全てを指します。自シーンが自ツリーの頂点（最も親）に位置していることも意味しています</TD>
 * </TR><TR>
 * <TD>「シーンクラス」</TD>
 * <TD>GgafActorクラスを直接・間接継承しているクラス全般を指します。</TD>
 * </TR><TR>
 * <TD>「上位」「下位」</TD>
 * <TD>シーンクラスのクラス継承関係を表しています。
 * クラス継承関係の表現は「スーパー」「サブ」又は「親」「子」と言わずに<B>「上位」「下位」</B>で統一することにします。</TD>
 * </TR>
 * </TABLE>
 * @version 1.00
 * @since 2008/06/20
 * @author Masatoshi Tsuge
 */
class GgafScene : public GgafElement<GgafScene> {

    friend class GgafGod;
    friend class GgafWorld;
    friend class GgafActor;
    friend class GgafHeadActor;
    friend class GgafLordActor;

protected:

	/** このシーンの管理アクター */
	GgafLordActor* _pLordActor;

	static GgafHeadActor* _s_apHeadActor01[];
	static GgafHeadActor* _s_apHeadActor02[];
public:
	/**
	 * コンストラクタ .
	 * 引数： prm_name シーン名<BR>
	 */
	GgafScene(std::string prm_name);

	/**
	 * デストラクタ .
	 * 自シーンの管理アクターのツリーアクターの解放を行ってから。<BR>
	 * 自ツリーシーンの解放を行います<BR>
	 */
	virtual ~GgafScene();

	/**
	 * 自ツリーシーンの次のフレームへ移る処理 .
	 * ＜OverRide です＞<BR>
	 */
	virtual void nextFrame();

	/**
	 * 自ツリーシーンのフレーム毎の振る舞い処理 .
	 * ＜OverRide です＞<BR>
	 */
	virtual void behave();

	/**
	 * 自ツリーシーンのフレーム毎の判断処理 .
	 * ＜OverRide です＞<BR>
	 */
	virtual void judge();

	/**
	 * 自ツリーシーンのフレーム毎の描画事前処理 .
	 * ＜OverRide です＞<BR>
	 */
	virtual void drawPrior();

	/**
	 * 自ツリーシーンのフレーム毎の描画処理 .
	 * ＜OverRide です＞<BR>
	 */
	virtual void drawMain();

	/**
	 * 自ツリーシーンのフレーム毎の描画事後処理 .
	 * ＜OverRide です＞<BR>
	 */
	virtual void drawTerminate();

	/**
	 * 自ツリーシーンに何かする .
	 * ＜OverRide です＞<BR>
	 */
	virtual void happen(int prm_no);

	/**
	 * 自ツリーシーンに何かする .
	 * ＜OverRide です＞<BR>
	 */
	virtual void finally();

	/**
     * 自ツリーシーンを次フレームから再生する。 .
	 * ＜OverRide です＞<BR>
	 */
	virtual void play();

	/**
     * 自ツリーシーンを直ちに再生する。 .
	 * ＜OverRide です＞<BR>
	 */
	virtual void playImmediately();

	/**
	 * 自ツリーシーンを次フレームから停止する。 .
	 * ＜OverRide です＞<BR>
	 */
	virtual void stop();

	/**
	 * 自ツリーシーンを直ちに停止する。 .
	 * ＜OverRide です＞<BR>
	 */
	virtual void stopImmediately();

	/**
	 * 自ツリーシーンを次フレームから一時停止する。 .
	 * ＜OverRide です＞<BR>
	 */
	virtual void pause();

	/**
	 * 自ツリーシーンを直ちに一時停止する。 .
	 * ＜OverRide です＞<BR>
	 */
	virtual void pauseImmediately();

	/**
     * 自ツリーシーンの一時停止を次フレームから解除。 .
	 * ＜OverRide です＞<BR>
	 */
	virtual void unpause();

	/**
     * 自ツリーシーンの一時停止を直ちに解除。 .
	 * ＜OverRide です＞<BR>
	 */
	virtual void unpauseImmediately();

	/**
	 * 自ツリーシーンを次フレームから非表示する。 .
	 * ＜OverRide です＞<BR>
	 */
	virtual void blind();

	/**
	 * 自ツリーシーンを直ちに非表示する。 .
	 * ＜OverRide です＞<BR>
	 */
	virtual void blindImmediately();

	/**
	 * 自ツリーシーンの非表示を次フレームから解除。 .
	 * ＜OverRide です＞<BR>
	 */
	virtual void unblind();

	/**
	 * 自ツリーシーンの非表示を直ちに解除。 .
	 * ＜OverRide です＞<BR>
	 */
	virtual void unblindImmediately();

	/**
	 * 自ツリーシーンを次フレーム絶命させる。 .
	 * ＜OverRide です＞<BR>
	 */
	virtual void farewell(DWORD prm_dwFrameOffset = 0);

	/**
	 * 自ツリーシーンを絶命させる。 .
	 * ＜OverRide です＞<BR>
	 */
	virtual void cleane(int prm_iNumCleanNode);

	/**
	 * 神様に接見 .
	 * @return	呼ばれて出てきた神様
	 */
	virtual GgafGod* askGod();

	/**
	 * 自シーンの管理者アクターを取得 .
	 * @return	管理者アクター
	 */
	virtual GgafLordActor* getLordActor();

	/**
	 * 自ツリーシーンのアクターに衝突判定を実行 (遅い方。こちらはgetName()のstd::string比較なのでやや遅い。次のメソッドを使う方が良いだー).
	 * 自ツリーシーン全てに対して、各シーンに所属する管理者アクターのサブアクターである GgafHeadActor 全てに対して<BR>
	 * GgafActor#executeBumpChkRoundRobinを実行する。<BR>
	 * @param	prm_actor_kind_name01	判定する対象のGgafHeadActorに登録されているActor種別名
	 * 		    prm_actor_kind_name02	判定される対象のGgafHeadActorに登録されているActor種別名<BR>
	 */
	//virtual void executeBumpChkHeadActors(std::string prm_actor_kind_name01, std::string prm_actor_kind_name02);


	/**
	 * 自ツリーシーンのアクターに衝突判定を実行 （速いほう）.
	 * 自ツリーシーン全てに対して、各シーンに所属する管理者アクターのサブアクターである GgafHeadActor 全てに対して<BR>
	 * GgafActor#executeBumpChkRoundRobinを実行する。<BR>
	 * @param	prm_actorkind01	判定する対象のGgafHeadActorに登録されているActor種別
	 * 		    prm_actorkind01	判定される対象のGgafHeadActorに登録されているActor種別<BR>
	 */
	virtual void executeBumpChkHeadActors(actorkind prm_actorkindmask01, actorkind prm_actorkindmask02);

	/**
	 * 経過フレーム判定。 .
	 * 直前の delay(n) 実行時（結果がtrue/falseに関わらず）のフレーム数からの経過フレーム数に達したか判定する。<BR>
	 * 注意：入れ子で使用した場合はうまく動きません。<BR>
	 * @param	prm_dwFrame_delay	経過フレーム数
	 * @return	bool	true:経過フレーム数に達した/false:達していない
	 */
//	virtual bool delayed(_delay);

	/**
	 * デバッグ用：ツリー構造を表示 .
	 */
	virtual void dump();

	/**
	 * デバッグ用：dump()から使用される .
	 */
	virtual void dump(std::string prm_parent);
};


}
#endif /**GGAFSCENE_H_*/
