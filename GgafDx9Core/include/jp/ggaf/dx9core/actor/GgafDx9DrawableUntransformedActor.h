#ifndef GGAFDX9DRAWABLEUNTRANSFORMEDACTOR_H_
#define GGAFDX9DRAWABLEUNTRANSFORMEDACTOR_H_
namespace GgafDx9Core {

/**
 * 画面に描画を行う座標未変換アクターの抽象クラス
 * GgafDx9DrawableUntransformedActor に描画関連の モデル、エフェクト、マテリアルなどを保持<BR>
 */
class GgafDx9DrawableUntransformedActor : public GgafDx9UntransformedActor {

private:

public:

    /** α (0.0 <= _fAlpha <= 1.0) */
    float _fAlpha;


    /**
     * コンストラクタ<BR>
     * @param	prm_name 識別名
     */
    GgafDx9DrawableUntransformedActor(const char* prm_name,
                              GgafDx9Checker* prm_pChecker);

    virtual GgafDx9DrawableUntransformedActor* getPrev() {
        return (GgafDx9DrawableUntransformedActor*)GgafActor::getPrev();
    }

    virtual GgafDx9DrawableUntransformedActor* getNext() {
        return (GgafDx9DrawableUntransformedActor*)GgafActor::getNext();
    }


    /**
     * _Zの値により、大まかにレンダリング順序を設定する。
     * 任意の優先順位でレンダリングしたい場合は、このメソッドをオーバーライドし
     * GgafUniverse::_apAlphaActorList_DrawDepthLevel[n] の好きな n に addSubLast(this) を行って下さい。
     * 但し 0 ≦ n ＜ MAX_DRAW_DEPTH_LEVEL
     * TODO:private virtual にするべきか否か？。fainal が欲しい
     */
    virtual void processDrawPrior();

    virtual void setAlpha(float prm_fAlpha) {
        _fAlpha = prm_fAlpha;
    }

    virtual void addAlpha(float prm_fAlpha) {
        _fAlpha += prm_fAlpha;
    }

    virtual float getAlpha() {
        return _fAlpha;
    }


    virtual ~GgafDx9DrawableUntransformedActor(); //デストラクタ
};

}
#endif /*GGAFDX9DRAWABLEUNTRANSFORMEDACTOR_H_*/
