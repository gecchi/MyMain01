#ifndef GGAFWORLD_H_
#define GGAFWORLD_H_

#define MAX_DEPTH_LEVEL 2028
/**
 * 世界の基底クラス .
 * 本プログラムで言う『世界』とは、全てのシーン(GgafSceneオブジェクト)の頂点に位置する特別なシーンです。<BR>
 * 少なくとも１つは世界をnewしなければいけません。<BR>
 * @version 1.00
 * @since 2008/06/20
 * @auther Masatoshi Tsuge
 */
 class GgafWorld : public GgafMainScene {
    friend class GgafGod;
    friend class GgafScene;

public:
	/** アクター順序レンダリングのための遠さのレベルグループ */
    static GgafActor* _apActorDrawDepthLevel_first[];
	/** アクター順序レンダリングのための遠さのレベルグループ別最終アクター */
    static GgafActor* _apActorDrawDepthLevel_last[];


	GgafWorld(string prm_name);

	/**
	 * 初期処理<BR>
	 */
	void initialize() {};

	/**
	 * フレーム毎の振る舞い<BR>
	 */
	void processBehavior() {};

	/**
	 * フレーム毎の判定処理<BR>
	 */
	void processJudgement() {};

	/**
	 * フレーム毎の描画事前処理<BR>
	 */
	void processDrawPrior() {};

	/**
	 * フレーム毎の描画処理<BR>
	 */
	void drawMain();

	/**
	 * フレーム毎の描画処理<BR>
	 */
	void processDrawMain() {};

	/**
	 * フレーム毎の描画事後処理<BR>
	 */
	void processDrawTerminate() {};

	/**
	 * 何かの処理<BR>
	 * @param prm_no 何かを表す数値
	 */
	void processHappen(int prm_no) {};

	/**
	 * 最終処理<BR>
	 */
	void processFinal() {};

	/**
	 * 描画レベル（順序）を登録
	 * @param prm_iDrawDepthLevel レベル
	 * @param prm_pActor アクター
	 */
	static void setDrawDepthLevel(int prm_iDrawDepthLevel, GgafActor* prm_pActor);

	virtual ~GgafWorld();
};


#endif /*GGAFWORLD_H_*/
