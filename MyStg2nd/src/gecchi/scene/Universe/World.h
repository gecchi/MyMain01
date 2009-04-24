#ifndef WORLD_H_
#define WORLD_H_
namespace MyStg2nd {

//getParent getSub そして キャストマクロ。
//下記マクロ使用するには、オブジェクトの識別名が、
//クラス名の末尾の"...Scene"という文字列を取り去ったものであることが前提条件です
#define getParentScene(X) ((X##Scene*)getParent(#X))
#define getSubScene(X) ((X##Scene*)getSub(#X))
#define getParentActor(X) ((X##Actor*)getParent(#X))
#define getSubActor(X) ((X##Actor*)getSub(#X))

/**
 * 世界クラス
 * この世にゲームが行なわれている世界がありました。
 */
class World : public GgafDx9LibStg::DefaultScene {


public:

	World(const char* prm_name);

	/**
	 * 初期処理
	 */
	void initialize();

 	/**
	 * ＜OverRide です＞
	 */
	void processBehavior();

 	/**
	 * ＜OverRide です＞
	 */
	void processJudgement();

	/**
	 * カメラを操作
	 * ＜OverRide です＞
	 */
	void processDrawPrior();

	virtual ~World();
};

}
#endif /*WORLD_H_*/
