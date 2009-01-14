#ifndef GGAFDX9SPRITEACTORD_H_
#define GGAFDX9SPRITEACTORD_H_

#define GGAF_EVENT_NOLOOP_ANIMATION_FINISHED 201
enum GgafDx9AnimationMethod {
	ORDER_LOOP,
	REVERSE_LOOP,
	OSCILLATE_LOOP,
	ORDER_NOLOOP,
	REVERSE_NOLOOP,
	NOT_ANIMATED
};


class GgafDx9SpriteActor : virtual public GgafDx9UntransformedActor {

private:

	/** 内部アニメフレーム用カウンタ */
	unsigned int _iCounter_AnimationFrame;


public:
	/** モデルオブジェクトへのポインタ */
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
	GgafDx9AnimationMethod _animation_method;
	/** OSCILLATE_LOOP用の現在のアニメ方向 */
	bool _oscillateAnimationOrderFlg;

	/** ビルボード要否 */
	bool _isBillboarding;

	GgafDx9SpriteActor(int prm_type, string prm_name, string prm_spritemodel_name, GgafDx9GeometryMover* prm_pGeoMover, GgafDx9GeometryChecker* prm_pGeoChecker);

 	/**
	 * ＜OverRide です＞<BR>
	 */
	virtual void processDrawMain();

	virtual ~GgafDx9SpriteActor();		//デストラクタ

	/**
	 * アニメーションを次のコマへ進める .
	 * アニメーションを行いたい場合メソッドを、processBehavior() 等で毎フレーム呼び出す必要があります。<BR>
	 */
	void nextAnimationFrame();


	/**
	 * アニメーションパターンを設定する .
	 * @param prm_iAnimationPatternNo アニメーションパターン番号
	 */
	void setActivAnimationPattern(int prm_iAnimationPatternNo);

	/**
	 * アニメーションパターンの範囲を制限する .
	 * @param prm_iTop上限のアニメーションパターン番号
	 * @param prm_bottom 下限のアニメーションパターン番号
	 */
	void setAnimationPatternRenge(int prm_iTop, int prm_bottom);

	/**
	 * アニメーション方法を設定する.
	 * @param prm_method アニメーション方法定数
	 * @param prm_iInterval アニメーション間隔フレーム（default=1)
	 */
	void setAnimationMethod(GgafDx9AnimationMethod prm_method, int prm_iInterval);

	/**
	 * 半透明度合いを設定 .
	 * @param prm_fAlpha<BR>
	 */
	void setAlpha(float prm_fAlpha) {
		_fAlpha = prm_fAlpha;
	}

	/**
	 * 現在の半透明度合いを取得 .
	 * @return マテリアルα反射値<BR>
	 */
	float getAlpha() {
		return _fAlpha;
	}

	/**
	 * ビルボード有効 .
	 * （デフォルトは無効です）<BR>
	 */
	void enableBillboarding() {
		_isBillboarding = true;
	}

	/**
	 * ビルボード無効 .
	 * （デフォルトは無効です）<BR>
	 */
	void disableBillboarding() {
		_isBillboarding = false;
	}
};


#endif /*GGAFDX9SPRITEACTORD_H_*/
