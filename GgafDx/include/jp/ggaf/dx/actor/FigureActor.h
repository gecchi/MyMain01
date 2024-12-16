#ifndef GGAF_DX_FIGUREACTOR_H_
#define GGAF_DX_FIGUREACTOR_H_
#include "jp/ggaf/GgafDxCommonHeader.h"
#include "jp/ggaf/dx/actor/GeometricActor.h"

#include "jp/ggaf/dx/manager/ModelManager.h"
#include "jp/ggaf/dx/manager/EffectManager.h"

namespace GgafDx {

/**
 * 画面に描画を行うアクターの抽象クラス .
 * GeometricActor に モデル、エフェクト、マテリアルなどを保持し、<BR>
 * 描画関連メソッドを定義<BR>
 * @version 1.00
 * @since 2009/06/10
 * @author Masatoshi Tsuge
 */
class FigureActor : public GeometricActor {
private:
    /**
     * draw()の使用禁止 .
     * 世界(Spacetime)が全ての描画を行う仕組みになりました。
     * Spacetime::draw() を参照せよ。
     * ノードツリー用 draw メソッドを下位で使えないようにするためprivateで実装。
     */
    void draw() override {}

protected:
    /** [r]現在有効なモデル資源接続 */
    ModelConnection* _pModelCon;
    /** [r]現在有効なモデル資源 */
    Model* _pModel;

    /** [r]モデル資源接続リスト */
    std::vector<ModelConnection*> _lstModelCon;
    /** [r]モデル資源リスト */
    std::vector<Model*> _lstModel;

    std::map<std::string, int> _mapModel;

    /** [r]エフェクト資源接続 */
    EffectConnection* const _pEffectCon;
    /** [r]エフェクト資源 */
    Effect* const _pEffect;
    /** [r]一時テクニック名 */
    char* _temp_technique;
    /** [r]一時テクニック名ハッシュ値 */
    hashval _hash_temp_technique;
    /** [r]一時テクニック終了フレーム */
    frame _frame_of_behaving_temp_technique_end;
    /** [r]αフェーディング支援 */
    AlphaFader* _pAlphaFader;
    /** [r]カラリストさん */
    Colorist* _pColorist;
public:
    /** [r/w]描画時、Zバッファを考慮して描画を行うか否か。true:考慮する／false:Zバッファを無視して描画  */
    bool _use_zbuffer_drawing;
    /** [r/w]描画時、Zバッファへ書き込みを行うか否か。true:Zバッファへ深度を書き込む／false:Zバッファへは何も書き込まない */
    bool _zbuffer_write_enable;

    /** [r]直近の描画時に使用されたテクニック名のハッシュコード */
    static hashval _hash_technique_last_draw;

    /** [r]同一描画レベルの次のアクター */
    FigureActor* _pNextRenderActor;
    /** [r/w]カリング有り表示の場合 true */
    bool _cull_enable;
    /** [r/w]カリング有り表示の場合のカリング方向 D3DCULL_CCW(default) or D3DCULL_CW */
    DWORD _cull_mode;
    DWORD _cull_mode_default;
    /** [r]現在描画に使用しているシェーダーテクニック名 */
    char* _technique;
    /** [r]現在描画に使用しているのシェーダーテクニックのハッシュコード */
    hashval _hash_technique;
    /** [r/w]現在のマテリアル別カラー(TODO:Diffuse のみ使用） */
    D3DMATERIAL9* _paMaterial;

    /** [r]現在の描画深度 */
    int _now_drawdepth;
    /** [r/w]特別な固定描画深度(負の数の場合は無効) _now_drawdepth より優先でこの深度が適用される */
    int _specal_render_depth_index;
    /** [r]一時テクニック適用中の場合 true */
    bool _is_temp_technique;

public:
    /**
     * コンストラクタ .
     * ModelManager::processCreateResource() 及び
     * EffectManager::processCreateResource()
     * の説明も参照すべし。
     * @param prm_name アクター名称（任意）
     * @param prm_model モデル定義名
     * @param prm_model_type モデルタイプ
     * @param prm_effect_id エフェクト定義名
     * @param prm_effect_type エフェクトタイプ
     * @param prm_technique エフェクトのテクニック
     */
    FigureActor(const char* prm_name,
                const char* prm_model,
                const char prm_model_type,
                const char* prm_effect_id,
                const char prm_effect_type,
                const char* prm_technique);

    virtual FigureActor* getPrev() const override {  //共変の戻り値
        return (FigureActor*)GgafCore::Actor::getPrev();
    }

    virtual FigureActor* getNext() const override {  //共変の戻り値
        return (FigureActor*)GgafCore::Actor::getNext();
    }

    /**
     * αフェーディング支援オブジェクトを取得 .
     * @return αフェーディング支援オブジェクト
     */
    AlphaFader* getAlphaFader();

    /**
     * カラリストさんを取得 .
     * @return カラリストさん
     */
    Colorist* getColorist();

    /**
     * シェーダーのテクニックを変更する .
     * 随時可能。
     * @param prm_technique テクニック名
     */
    virtual void changeEffectTechnique(const char* prm_technique);

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
    virtual void changeEffectTechniqueMoment(const char* prm_technique, frame prm_frame);

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
     * 特別な描画深度順序を強制する。 .
     * 0以上指定場合、描画深度指定にこの値が使用される。
     * 負の数の指定場合、自動設定に戻る（_specal_render_depth_indexのデフォルトは-1)
     * @param prm_drawdepth 描画深度順序
     */
    void setSpecialRenderDepthIndex(int prm_drawdepth);

    /**
     * 特別な描画深度指定を解除する .
     */
    void resetSpecialRenderDepthIndex();

    /**
     * 特別な最前面描画深度の順序を強制する。(0, 1, 2, 3, … 10 で指定) .
     * 通常の段階レンダリングよりも、前面に位置する特別な描画深度が5段階用意されている。
     * （この段階数は CONFIG::RENDER_DEPTH_INDEXS_NUM_EX_NEAR で変更可）
     * この前面に位置する特別な描画深度に登録を強制する。
     * @param prm_near_index 0(最前面の中でも最も手前) ～ 4(最前面の中でも最も背面)
     */
    void setSpecialRenderDepthNear(int prm_near_index);

    /**
     * 特別な最背面描画深度の順序を強制する。(0, -1, -2, -3, … -10 で指定) .
     * 通常の段階レンダリングよりも、背面に位置する特別な描画深度が5段階用意されている。
     * （この段階数は CONFIG::RENDER_DEPTH_INDEXS_NUM_EX_FAR で変更可）
     *  この背面面に位置する特別な描画深度に登録を強制する。
     * @param prm_far_index 0(最背面の中でも最も背面) ～ -4(最背面の中でも最も手前)
     */
    void setSpecialRenderDepthFar(int prm_far_index);

    /**
     * 共通の描画事前処理 .
     * 描画を行うにあたっての重要な事前処理を行ないます。
     * ・onCreateModel() の呼び出し
     * ・段階レンダリングの深度計算
     * ・一時テクニック考慮
     * オーバーライド非推奨。
     * オーバーライドする場合は、
     * FigureActor::processPreDraw() をメソッド内で呼び出すか、
     * 或いは自前で同等の処理を実装するか、問題ないか考慮してください。
     * TODO:private virtual にするべきか否か？。fainal が欲しい
     */
    virtual void processPreDraw() override;

    /**
     * 本アクターの描画時のマテリアルアルファ値設定 .
     * 1.0 以上の場合カリングがON、<br>
     * 1.0 より小さな場合、カリングがOFF、<br>
     * という機能もあわせ持つ。<br>
     * @param prm_alpha アクターのマテリアルアルファ値
     */
    virtual void setAlpha(float prm_alpha);

    /**
     * 本アクターの描画時のマテリアルアルファ値を加算する .
     * @param prm_alpha 加算するマテリアルアルファ値
     */
    virtual void addAlpha(float prm_alpha);

    /**
     * 本アクターの描画時のマテリアルアルファ値を取得 .
     * @return アクターの現在のアルファ値
     */
    virtual float getAlpha() const {
        return _paMaterial[0].Diffuse.a;
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
    virtual float getMaterialRed();
    virtual float getMaterialGreen();
    virtual float getMaterialBlue();

    /**
     * 本アクターの描画時のマテリアルカラーを設定。 .
     * @param prm_rgb
     */
    virtual void setMaterialColor(const GgafCore::Rgb* prm_rgb);

    /**
     * マテリアルカラーをモデル読み込み時の状態にリセット。
     */
    virtual void resetMaterialColor();

    /**
     * モデル資源（現在有効となっているもの）を取得 .
     * @return 現在有効なモデル資源
     */
    inline Model* getModel() const {
        return _pModel;
    }

    /**
     * モデル資源を１つ生成して追加する。 .
     * 初めて本メソッドを実行すると、内部リストに保持され、そのモデル資源が有効になります。
     * ２回目以降の実行は、生成したモデル資源を内部リストの末尾に追加します。（有効になりません）
     * @param prm_model モデル定義名
     */
    virtual void addModel(const char* prm_model);

    /**
     * モデル資源を切り替える（表示が切り替わります） .
     * @param prm_model_index モデル資源保持リストのインデックス。
     *                        最初の   addModel() に切り替え => 0 を設定
     *                        ２回目の addModel() に切り替え => 1 を設定
     *                        ３回目の addModel() に切り替え => 2 を設定
     *                         …
     */
    virtual void changeModelByIndex(int prm_model_index);

    virtual void changeModel(const char* prm_model);

    virtual void changeDefaultModel();

    /**
     * アクターのエフェクトを取得 .
     * @return エフェクト
     */
    virtual Effect* getEffect() const {
        return _pEffect;
    }

    /**
     * カリング描画するかどうか。
     * @param prm_bool true:カリング描画あり(default) / false:カリング無し、裏面も描画
     */
    inline void setCullingDraw(bool prm_bool) {
        _cull_enable = prm_bool;
        if (_cull_enable) {
            _cull_mode = _cull_mode_default;
        } else {
            _cull_mode = D3DCULL_NONE;
        }
    }

    inline void setCullingMode(DWORD prm__cull_mode) {
        _cull_mode_default = prm__cull_mode;
        _cull_mode = _cull_mode_default;
    }

    /**
     * 描画時Zバッファを考慮するか .
     * @param prm_bool true:考慮する(default) / false:無視する
     */
    inline void useZBufferDrawing(bool prm_bool) {
        _use_zbuffer_drawing = prm_bool;
    }

    /**
     * 描画時Zバッファを書き込むか .
     * @param prm_bool true:書き込む(default) / false:書き込まない
     */
    inline void setZBufferWriteEnable(bool prm_bool) {
        _zbuffer_write_enable = prm_bool;
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

    virtual ~FigureActor();
};

}
#endif /*GGAF_DX_FIGUREACTOR_H_*/
