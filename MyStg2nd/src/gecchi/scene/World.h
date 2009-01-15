#ifndef WORLD_H_
#define WORLD_H_

//getParent getSub マクロ。
//下記マクロ使用するには、シーンオブジェクトの名前が、
//クラス名から末尾の"Scene"という文字列を取り去ったものであることが前提条件です
#define getParentScene(X) ((X##Scene*)getParent(#X))
#define getSubScene(X) ((X##Scene*)getSub(#X))


class World : public GgafDx9LibStg::DefaultWorld {


public:
	World(string prm_name);

	/**
	 * 初期処理
	 */
	void initialize() {};

 	/**
	 * ＜OverRide です＞
	 */
	void processBehavior() {};

 	/**
	 * ＜OverRide です＞
	 */
	void processJudgement() {};

	/**
	 * カメラを操作
	 * ＜OverRide です＞
	 */
	void processDrawPrior();

	virtual ~World();
};

#endif /*WORLD_H_*/
