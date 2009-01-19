#ifndef GGAFWORLD_H_
#define GGAFWORLD_H_
namespace GgafCore {


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

	GgafWorld(string prm_name);

	/**
	 * 初期処理<BR>
	 */
	void initialize() {};

	/**
	 * フレーム毎の振る舞い<BR>
	 */
	virtual void processBehavior() {};

	/**
	 * フレーム毎の判定処理<BR>
	 */
	virtual void processJudgement() {};

	/**
	 * フレーム毎の描画事前処理<BR>
	 */
	virtual void processDrawPrior() {};

	/**
	 * フレーム毎の描画処理<BR>
	 */
	virtual void drawMain() {};

	/**
	 * フレーム毎の描画処理<BR>
	 */
	virtual void processDrawMain() {};

	/**
	 * フレーム毎の描画事後処理<BR>
	 */
	virtual void processDrawTerminate() {};

	/**
	 * 何かの処理<BR>
	 * @param prm_no 何かを表す数値
	 */
	virtual void processHappen(int prm_no) {};

	/**
	 * 最終処理<BR>
	 */
	virtual void processFinal() {};


	virtual ~GgafWorld();
};


}
#endif /*GGAFWORLD_H_*/
