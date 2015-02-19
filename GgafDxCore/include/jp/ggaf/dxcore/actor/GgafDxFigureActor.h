#ifndef GGAFDXCORE_GGAFDXFIGUREACTOR_H_
#define GGAFDXCORE_GGAFDXFIGUREACTOR_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/dxcore/actor/GgafDxGeometricActor.h"

namespace GgafDxCore {

/**
 * 画面に描画を行うアクターの抽象クラス .
 * GgafDxGeometricActor に モデル、エフェクト、マテリアルなどを保持し、<BR>
 * 描画関連メソッドを定義<BR>
 * @version 1.00
 * @since 2009/06/10
 * @author Masatoshi Tsuge
 */
class GgafDxFigureActor : public GgafDxGeometricActor {
private:
    /**
     * draw()の使用禁止 .
     * 世界(GgafDxUniverse)が全ての描画を行う仕組みになりました。
     * GgafDxUniverse::draw() を参照せよ。
     * ノードツリー用 draw メソッドを下位で使えないようにするためprivateで実装。
     */
    void draw() override {}

protected:
    /** [r]モデル資源接続 */
    GgafDxModelConnection* const _pModelCon;
    /** [r]モデル資源 */
    GgafDxModel* const _pModel;
    /** [r]エフェクト資源接続 */
    GgafDxEffectConnection* const _pEffectCon;
    /** [r]エフェクト資源 */
    GgafDxEffect* const _pEffect;
    /** [r]一時テクニック名 */
    char* _temp_technique;
    /** [r]一時テクニック名ハッシュ値 */
    hashval _hash_temp_technique;
    /** [r]一時テクニック終了フレーム */
    frame _frame_of_behaving_temp_technique_end;

public:
    /** [r/w]描画時、Zバッファを考慮して描画を行うか否か。true:考慮する／false:Zバッファを無視して描画  */
    bool _zenable;
    /** [r/w]描画時、Zバッファへ書き込みを行うか否か。true:Zバッファへ深度を書き込む／false:Zバッファへは何も書き込まない */
    bool _zwriteenable;

    /** [r]直近の描画時に使用されたテクニック名のハッシュコード */
    static hashval _hash_technique_last_draw;

    /** [r]同一描画レベルの次のアクター */
    GgafDxFigureActor* _pNextActor_in_draw_depth_level;
    /** [r/w]現在のマテリアルのα値 (0.0 <= _alpha <= 1.0) */
    float _alpha;
    /** [r]現在描画に使用しているシェーダーテクニック名 */
    char* _technique;
    /** [r]現在描画に使用しているのシェーダーテクニックのハッシュコード */
    hashval _hash_technique;
    /** [r/w]現在のマテリアル別カラー */
    D3DMATERIAL9* _paMaterial;

    /** [r/w]現在の描画深度 */
    int _now_drawdepth;
    /** [r/w]特別な固定描画深度、-1でなければ _now_drawdepth より優先でこの深度が適用される */
    int _specal_drawdepth;
    /** [r]一時テクニック適用中の場合 true */
    bool _is_temp_technique;


public:
    /**
     * コンストラクタ .
     * @param prm_name モデル名称（任意）
     * @param prm_model モデル識別キー文字列
     * @param prm_effect エフェクト識別キー文字列
     * @param prm_technique エフェクトのテクニック
     * @param prm_pStat 使用するステータスオブジェクト(使用しない時 nullptrでよい)
     * @param prm_pStat 使用するステータスオブジェクト(使用しない時 nullptrでよい)
     * @param prm_pChecker 使用するチェッカーオブジェクト（チェッカー未使用時はnullptrでよい）
     */
    GgafDxFigureActor(const char* prm_name,
                      const char* prm_model,
                      const char* prm_effect,
                      const char* prm_technique,
                      GgafCore::GgafStatus* prm_pStat,
                      GgafDxChecker* prm_pChecker);

    /**
     * コンストラクタ .
     * GgafDxModelManager::processCreateResource() 及び
     * GgafDxEffectManager::processCreateResource()
     * の説明も参照すべし。
     * @param prm_name アクター名称（任意）
     * @param prm_model_id モデル定義名
     * @param prm_model_type モデルタイプ
     * @param prm_effect_id エフェクト定義名
     * @param prm_effect_type エフェクトタイプ
     * @param prm_technique エフェクトのテクニック
     * @param prm_pStat 使用するステータスオブジェクト(使用しない時 nullptrでよい)
     * @param prm_pChecker 使用するチェッカーオブジェクト（チェッカー未使用時はnullptrでよい）
     */
    GgafDxFigureActor(const char* prm_name,
                      const char* prm_model_id,
                      const char* prm_model_type,
                      const char* prm_effect_id,
                      const char* prm_effect_type,
                      const char* prm_technique,
                      GgafCore::GgafStatus* prm_pStat,
                      GgafDxChecker* prm_pChecker);

    virtual GgafDxFigureActor* getPrev() const override {  //共変の戻り値
        return (GgafDxFigureActor*)GgafActor::getPrev();
    }

    virtual GgafDxFigureActor* getNext() const  override {  //共変の戻り値
        return (GgafDxFigureActor*)GgafActor::getNext();
    }

    /**
     * シェーダーのテクニックを変更する .
     * 随時可能。
     * @param prm_technique テクニック名
     */
    void changeEffectTechnique(const char* prm_technique);

    /**
     * シェーダーのテクニックを一時的に変更する .
     * 既に一時テクニック使用時は無視される。但し、
     * 既に一時テクニック使用中に強制的に一時テクニックを変更したい場合次のようにできる。
     * <code>
     * if (_is_temp_technique == false) {
     *     changeEffectTechnique("変更したいテクニック名");
     * }
     * </code>
     * @param prm_technique テクニック名
     * @param prm_frame 変更テクニックの継続フレーム数
     */
    void changeEffectTechniqueInterim(const char* prm_technique, frame prm_frame);

    /**
     * ピカっと光る。
     * @param prm_frame 光る時間
     */
    virtual void effectFlush(frame prm_frame = MAX_FRAME);

    /**
     * 加算合成エフェクト .
     * @param prm_frame
     */
    virtual void effectBlendOne(frame prm_frame = MAX_FRAME);

    /**
     * 標準エフェクトに戻す .
     */
    virtual void effectDefault();

    /**
     * 特別な描画深度を強制する。 .
     * 0以上指定場合、描画深度指定にこの値が使用される。
     * 負の数の指定場合、自動設定に戻る（_specal_drawdepthのデフォルトは-1)
     * @param prm_drawdepth
     */
    void setSpecialDrawDepth(int prm_drawdepth);

    /**
     * 共通の描画事前処理 .
     * 描画を行うにあたっての重要な事前処理を行ないます。
     * ・onCreateModel() の呼び出し
     * ・段階レンダリングの深度計算
     * ・一時テクニック考慮
     * オーバーライド非推奨。
     * オーバーライドする場合は、
     * GgafDxFigureActor::processPreDraw() をメソッド内で呼び出すか、
     * 或いは自前で同等の処理を実装するか、問題ないか考慮してください。
     * TODO:private virtual にするべきか否か？。fainal が欲しい
     */
    virtual void processPreDraw() override;

    /**
     * 共通の描画事後処理 .
     * 俺デバッグモード (MY_DEBUG が 1)の場合は
     * 当たり判定領域を描画する。
     * (といっても drawHitArea() をコールするだけ)
     */
    virtual void processAfterDraw() override;

    /**
     * 当たり判定領域を描画 .
     * 実際の処理は下位クラスに任せる。
     */
    virtual void drawHitArea() {};

    /**
     * 本アクターの描画時のマテリアルアルファ値設定 .
     * 1.0 以上の場合カリングがON、<br>
     * 1.0 より小さな場合、カリングがOFF、<br>
     * という機能もあわせ持つ。<br>
     * @param prm_alpha アクターのマテリアルアルファ値
     */
    virtual void setAlpha(float prm_alpha) {
        _alpha = prm_alpha;
    }

    /**
     * 本アクターの描画時のマテリアルアルファ値を加算する .
     * @param prm_alpha 加算するマテリアルアルファ値
     */
    virtual void addAlpha(float prm_alpha) {
        _alpha += prm_alpha;
    }

    /**
     * 本アクターの描画時のマテリアルアルファ値を取得 .
     * @return アクターの現在のアルファ値
     */
    virtual float getAlpha() const {
        return _alpha;
    }

    /**
     * 本アクターの描画時のマテリアルカラーを設定。 .
     * キャラクタ全体に色を重ねる効果を得る。<br>
     * 実装方法は、下位に依存。<br>
     * したがって本メソッドによる「マテリアルカラー」の意味は、<br>
     * 「DirectXのマテリアル」の意味と一致しないかもしれない。<br>
     * @param r Red強度(0.0 ～ 1.0)
     * @param g Green強度(0.0 ～ 1.0)
     * @param b Blue強度(0.0 ～ 1.0)
     */
    virtual void setMaterialColor(float r, float g, float b);

    virtual void setMaterialRed(float r);
    virtual void setMaterialGreen(float g);
    virtual void setMaterialBlue(float b);

    /**
     * 本アクターの描画時のマテリアルカラーを設定。 .
     * @param prm_rgb
     */
    virtual void setMaterialColor(const GgafCore::GgafRgb* prm_rgb);

    /**
     * マテリアルカラーをモデル読み込み時の状態にリセット。
     */
    virtual void resetMaterialColor();

    inline GgafDxModel* getModel() const {
        return _pModel;
    }

    virtual GgafDxEffect* getEffect() const {
        return _pEffect;
    }

    /**
     * 描画時Zバッファを考慮するか .
     * @param prm_bool true:考慮する(default) / false:無視する
     */
    void setZEnable(bool prm_bool) {
        _zenable = prm_bool;
    }

    /**
     * 描画時Zバッファを書き込むか .
     * @param prm_bool true:書き込む(default) / false:書き込まない
     */
    void setZWriteEnable(bool prm_bool) {
        _zwriteenable = prm_bool;
    }

    /**
     * モデルが生成された時の処理 .
     * モデルオブジェクトが new された場合に１回だけ呼び出します。
     * モデル単位で設定したい処理をオーバーライドして下さい。
     */
    virtual void onCreateModel() = 0;

    /**
     * 画面内に表示されているか判定 .
     * @return 0(false):Viewport範囲内
     *         1       :Viewport視錐台の上平面より上で範囲外
     *         2       :Viewport視錐台の下平面より下で範囲外
     *         3       :Viewport視錐台の左平面より左で範囲外
     *         4       :Viewport視錐台の右平面より右で範囲外
     *         5       :Viewport視錐台の手前平面より手前で範囲外
     *         6       :Viewport視錐台の奥平面より奥で範囲外
     *         ※判定優先順位順に並んでいます。（例：1 かつ 4 は 1 が返ります）
     */
    virtual int isOutOfView() override;

    virtual ~GgafDxFigureActor(); //デストラクタ
};

}
#endif /*GGAFDXCORE_GGAFDXFIGUREACTOR_H_*/
