#ifndef UNIVERSE_H_
#define UNIVERSE_H_
namespace MyStg2nd {

//getParent getSub そして キャストマクロ。
//下記マクロ使用するには、オブジェクトの識別名が、
//クラス名の末尾の"...Scene"という文字列を取り去ったものであることが前提条件です
#define getParentScene(X) ((X##Scene*)getParent(#X))
#define getSubScene(X) ((X##Scene*)getSub(#X))
#define getParentActor(X) ((X##Actor*)getParent(#X))
#define getSubActor(X) ((X##Actor*)getSub(#X))


/**
 * この世シーン .
 * まずこの世がありました。<BR>
 * 本クラスは、この世の振る舞い等を実装しています。<BR>
 */
class Universe : public GgafDx9LibStg::DefaultUniverse {

public:

	Universe(const char* prm_name);

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
	 * ＜OverRide です＞
	 */
	void processDrawPrior();

	virtual ~Universe();
};

}
#endif /*UNIVERSE_H_*/
