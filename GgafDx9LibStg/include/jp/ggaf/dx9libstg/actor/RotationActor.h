#ifndef ROTATIONACTOR_H_
#define ROTATIONACTOR_H_

/**
 * ローテーションアクタークラス .
 * 自機のショットなど、画面上にキャラクタ数MAX制限付で表示したい場合等に有効。
 */
class RotationActor : public GgafDummyActor {

public:

	RotationActor(string prm_name);

	void initialize() {};

	void processBehavior() {};

	void processJudgement() {};

	void processDrawPrior() {};

	void processDrawMain() {};

	void processDrawTerminate() {};

	void processHappen(int prm_no) {};

	void processFinal() {};

 	void processOnHit(GgafActor* prm_pActor_Opponent) {};

	/**
	 * 子アクターのを先頭から検索し、最初に出会った play 可能なアクターを取得.
	 * 取得できた場合、そのアクターを返すと同時に 連結リストの最後に移動される。<BR>
	 * 空きが無い場合 NULL を返す。<BR>
	 * @return play 可能な Actor
	 */
	GgafActor* get();

	virtual ~RotationActor();
};

#endif /*ROTATIONACTOR_H_*/
