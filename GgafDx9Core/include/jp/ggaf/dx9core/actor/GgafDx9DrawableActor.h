#ifndef GGAFDX9DRAWABLEACTOR_H_
#define GGAFDX9DRAWABLEACTOR_H_
namespace GgafDx9Core {

/**
 * 画面に描画を行う座標未変換アクターの抽象クラス .
 * GgafDx9GeometricActor に モデル、エフェクト、マテリアルなどを保持し、<BR>
 * 描画関連メソッドを追加<BR>
 * @version 1.00
 * @since 2009/06/10
 * @author Masatoshi Tsuge
 */
class GgafDx9DrawableActor : public GgafDx9GeometricActor {

private:

public:
    /** 同一描画レベルの次のアクター */
    GgafDx9DrawableActor* _pNext_TheSameDrawDepthLevel;


    /** α (0.0 <= _fAlpha <= 1.0) */
    float _fAlpha;

    char* _technique;
    /** マテリアル配列 */
    D3DMATERIAL9* _paD3DMaterial9;
    /** モデル資源接続 */
    GgafDx9ModelConnection* _pGgafDx9ModelCon;
    /** モデル資源 */
    GgafDx9Model* _pGgafDx9Model;
    /** エフェクト資源接続 */
    GgafDx9EffectConnection* _pGgafDx9EffectCon;
    /** エフェクト資源 */
    GgafDx9Effect* _pGgafDx9Effect;
    /** SE資源接続 */
    GgafDx9SeConnection* _pSeCon;
    /** SE資源 */
    GgafDx9Se* _pSe;
    /** SE資源接続 */
    GgafDx9SeConnection* _pSeCon2;
    /** SE資源 */
    GgafDx9Se* _pSe2;



    /**
     * コンストラクタ<BR>
     * @param	prm_name 識別名
     */
    GgafDx9DrawableActor(const char* prm_name,
                         const char* prm_model,
                         const char* prm_effect,
                         const char* prm_technique,
                         GgafDx9Checker* prm_pChecker);

    GgafDx9DrawableActor(const char* prm_name,
                         const char* prm_model_id,
                         const char* prm_model_type,
                         const char* prm_effect_id,
                         const char* prm_effect_type,
                         const char* prm_technique,
                         GgafDx9Checker* prm_pChecker);

    virtual GgafDx9DrawableActor* getPrev() {
        return (GgafDx9DrawableActor*)GgafActor::getPrev();
    }

    virtual GgafDx9DrawableActor* getNext() {
        return (GgafDx9DrawableActor*)GgafActor::getNext();
    }


    /**
     * _Zの値により、大まかにレンダリング順序を設定する。
     * 任意の優先順位でレンダリングしたい場合は、このメソッドをオーバーライドし
     * GgafUniverse::_apAlphaActorList_DrawDepthLevel[n] の好きな n に addSubLast(this) を行って下さい。
     * 但し 0 ≦ n ＜ MAX_DRAW_DEPTH_LEVEL
     * TODO:private virtual にするべきか否か？。fainal が欲しい
     */
    virtual void processPreDraw();

    virtual void processAfterDraw();


    virtual void drawHitArea() {};

    virtual void setAlpha(float prm_fAlpha) {
        _fAlpha = prm_fAlpha;
    }

    virtual void addAlpha(float prm_fAlpha) {
        _fAlpha += prm_fAlpha;
    }

    virtual float getAlpha() {
        return _fAlpha;
    }

    virtual void setMaterialColor(float r, float g, float b);

    virtual void resetMaterialColor();

    void useSe1(char* prm_se_name, unsigned int prm_cannel = 0);

    void playSe1();

    void useSe2(char* prm_se_name, unsigned int prm_cannel = 0);

    void playSe2();


    virtual ~GgafDx9DrawableActor(); //デストラクタ
};

}
#endif /*GGAFDX9DRAWABLEACTOR_H_*/
