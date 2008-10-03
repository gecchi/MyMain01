#ifndef GGAFDX9SPRITEACTORD_H_
#define GGAFDX9SPRITEACTORD_H_

#define GGAF_EVENT_NOLOOP_ANIMATION_FINISHED 201

class GgafDx9SpriteActor : public GgafDx9UntransformedActor {

private:

	/** 内部アニメフレーム用カウンタ */
	unsigned int _iCounter_AnimationFrame;


public:
	static const int ORDER_LOOP;
	static const int REVERSE_LOOP;
	static const int OSCILLATE_LOOP;
	static const int ORDER_NOLOOP;
	static const int REVERSE_NOLOOP;
	static const int NOT_ANIMATED;
	GgafDx9SpriteModel* _pSpriteModel;

	/** アニメパターン番号の上限番号 */
	unsigned int _iAnimationPatternNo_Top;
	/** 現在表示中のアニメパターン番号 */
	unsigned int _iAnimationPatternNo_Bottom;
	/** 現在表示中のアニメパターン番号(0～) */
	unsigned int _iAnimationPatternNo_Active;
	/** パターンとパターンの間隔フレーム数 */
	unsigned int _iAnimationFrame_Interval;
	/** アニメ方式 */
	unsigned int _iAnimationMethod;
	/** OSCILLATE_LOOP用の現在のアニメ方向 */
	bool _oscillateAnimationOrderFlg;


	GgafDx9SpriteActor(string prm_name, string prm_spritemodel_name, GgafDx9GeometryMover* prm_pGeoMover, GgafDx9GeometryChecker* prm_pGeoChecker);

 	/**
	 * ＜OverRide です＞<BR>
	 */
	virtual void processDrawMain();

	virtual ~GgafDx9SpriteActor();		//デストラクタ

	/**
	 * アニメーションを次のコマへ進める
	 */
	void nextAnimationFrame();

	/**
	 * アニメーションパターンの範囲を制限する
	 */
	void setAnimationPatternRenge(int prm_iTop, int prm_bottom);

	/**
	 * アニメーション方法を設定する
	 */
	void setAnimationMethod(int prm_iMethodNo, int prm_iInterval);

};


#endif /*GGAFDX9SPRITEACTORD_H_*/
