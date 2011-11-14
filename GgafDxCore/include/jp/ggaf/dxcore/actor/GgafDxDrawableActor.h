#ifndef GGAFDXDRAWABLEACTOR_H_
#define GGAFDXDRAWABLEACTOR_H_
namespace GgafDxCore {

/**
 * 画面に描画を行うアクターの抽象クラス .
 * GgafDxGeometricActor に モデル、エフェクト、マテリアルなどを保持し、<BR>
 * 描画関連メソッドを定義<BR>
 * @version 1.00
 * @since 2009/06/10
 * @author Masatoshi Tsuge
 */
class GgafDxDrawableActor : public GgafDxGeometricActor {

private:
    /** [r]一時テクニック名 */
    char* _temp_technique;
    /** [r]一時テクニック名ハッシュ値 */
    unsigned int _hash_temp_technique;
    /** [r]一時テクニック終了フレーム */
    frame _frame_of_behaving_temp_technique_end;
    /** [r]一時テクニック適用中の場合 true */
    bool _is_temp_technique;
    /** モデル資源接続 */
    GgafDxModelConnection* _pModelCon;
    /** エフェクト資源接続 */
    GgafDxEffectConnection* _pEffectCon;


    /**
     * draw()の使用禁止 .
     * 世界(GgafDxUniverse)が全ての描画を行う仕組みになりました。
     * GgafDxUniverse::draw() を参照せよ。
     * ノードツリー用 draw メソッドを下位で使えないようにするためprivateで実装。
     */
    void draw() override {}

public:
    /** [r/w]描画時、Zバッファを考慮して描画を行うか否か。true:考慮する／false:Zバッファを無視して描画  */
    bool _zenable;
    /** [r/w]描画時、Zバッファへ書き込みを行うか否か。true:Zバッファへ深度を書き込む／false:Zバッファへは何も書き込まない */
    bool _zwriteenable;

    /** 直近の描画時に使用されたテクニック名のハッシュコード */
    static unsigned int _hash_technique_last_draw;

    /** [r]同一描画レベルの次のアクター */
    GgafDxDrawableActor* _pNext_TheSameDrawDepthLevel;
    /** [r]現在のマテリアルのα値 (0.0 <= _fAlpha <= 1.0) */
    float _fAlpha;
    /** [r]現在描画に使用しているシェーダーテクニック名 */
    char* _technique;
    /** [r]現在描画に使用しているのシェーダーテクニックのハッシュコード */
    unsigned int _hash_technique;
    /** [r]現在のマテリアルカラー */
    D3DMATERIAL9* _paMaterial;
    /** [r]モデル資源 */
    GgafDxModel* _pModel;
    /** [r]エフェクト資源 */
    GgafDxEffect* _pEffect;
    /** [r]現在の描画深度 */
    int _now_drawdepth;
    /** [r]特別な固定描画深度、-1でなければ _now_drawdepth より優先でこの深度が適用される */
    int _specal_drawdepth;

    GgafDxAlphaFader* _pFader;

    /**
     * コンストラクタ .
     * @param prm_name モデル名称（任意）
     * @param prm_model モデル識別キー文字列
     * @param prm_effect エフェクト識別キー文字列
     * @param prm_technique エフェクトのテクニック
     * @param prm_pStat 使用するステータスオブジェクト(使用しない時 NULLでよい)
     * @param prm_pStat 使用するステータスオブジェクト(使用しない時 NULLでよい)
     * @param prm_pChecker 使用するチェッカーオブジェクト（チェッカー未使用時はNULLでよい）
     */
    GgafDxDrawableActor(const char* prm_name,
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
     * @param prm_pStat 使用するステータスオブジェクト(使用しない時 NULLでよい)
     * @param prm_pChecker 使用するチェッカーオブジェクト（チェッカー未使用時はNULLでよい）
     */
    GgafDxDrawableActor(const char* prm_name,
                         const char* prm_model_id,
                         const char* prm_model_type,
                         const char* prm_effect_id,
                         const char* prm_effect_type,
                         const char* prm_technique,
                         GgafCore::GgafStatus* prm_pStat,
                         GgafDxChecker* prm_pChecker);

    virtual GgafDxDrawableActor* getPrev() override {
        return (GgafDxDrawableActor*)GgafActor::getPrev();
    }

    virtual GgafDxDrawableActor* getNext() override {
        return (GgafDxDrawableActor*)GgafActor::getNext();
    }

    /**
     * シェーダーのテクニックを変更する .
     * 随時可能。
     * @param prm_technique テクニック名
     */
    void changeEffectTechnique(const char* prm_technique) {
        _hash_technique = GgafCore::GgafUtil::easy_hash(prm_technique);
        strcpy(_technique, prm_technique);
    }

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
    void changeEffectTechniqueInterim(const char* prm_technique, frame prm_frame) {
        if (_is_temp_technique == false) { //すでに一時テクニック使用時は無視
            //元々のテクニックを退避
            _hash_temp_technique = _hash_technique;
            strcpy(_temp_technique, _technique);
            //テクニック変更
            _frame_of_behaving_temp_technique_end = _frame_of_behaving + prm_frame; //変更満期フレーム
            _hash_technique = GgafCore::GgafUtil::easy_hash(prm_technique);
            strcpy(_technique, prm_technique);
            _is_temp_technique = true;
        }
    }

    /**
     * 特別な描画深度を強制する。 .
     * 0以上指定場合、描画深度指定にこの値が使用される。
     * 負の数の指定場合、自動設定に戻る（_specal_drawdepthのデフォルトは-1)
     * @param prm_drawdepth
     */
    void setSpecialDrawDepth(int prm_drawdepth) {
        if (prm_drawdepth > MAX_DRAW_DEPTH_LEVEL) {
            _specal_drawdepth = MAX_DRAW_DEPTH_LEVEL;
        } else {
            _specal_drawdepth = prm_drawdepth;
        }
    }

    /**
     * 共通の描画事前処理 .
     * 描画を行うにあたっての重要な事前処理を行ないます。
     * ・onCreateModel() の呼び出し
     * ・段階レンダリングの深度計算
     * ・一時テクニック考慮
     * オーバーライド非推奨。
     * オーバーライドする場合は、
     * GgafDxDrawableActor::processPreDraw() をメソッド内で呼び出すか、
     * 或いは自前で同等の処理を実装するか、問題ないか考慮してください。
     * TODO:private virtual にするべきか否か？。fainal が欲しい
     */
    virtual void processPreDraw() override;

    /**
     * 共通の描画事後処理 .
     * 俺デバッグモード (<pre><code>#define MY_DEBUG 1</code></pre>)の場合は
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
     * @param prm_fAlpha アクターのマテリアルアルファ値
     */
    virtual void setAlpha(float prm_fAlpha) {
        _fAlpha = prm_fAlpha;
    }

    /**
     * 本アクターの描画時のマテリアルアルファ値を加算する .
     * @param prm_fAlpha 加算するマテリアルアルファ値
     */
    virtual void addAlpha(float prm_fAlpha) {
        _fAlpha += prm_fAlpha;
    }

    /**
     * 本アクターの描画時のマテリアルアルファ値を取得 .
     * @return アクターの現在のアルファ値
     */
    virtual float getAlpha() {
        return _fAlpha;
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

    /**
     * マテリアルカラーをモデル読み込み時の状態にリセット。
     */
    virtual void resetMaterialColor();

    virtual GgafDxModel* getModel() {
        return _pModel;
    }

    virtual GgafDxEffect* getEffect() {
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

    virtual ~GgafDxDrawableActor(); //デストラクタ
};

}
#endif /*GGAFDXDRAWABLEACTOR_H_*/
