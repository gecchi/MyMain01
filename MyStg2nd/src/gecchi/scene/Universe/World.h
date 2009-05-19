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
 * 世界シーンクラス .
 * この世に、とある世界がありました。<BR>
 * 本クラスは、世界の振る舞い等を実装しています。<BR>
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

	virtual ~World();
};

}
#endif /*WORLD_H_*/
