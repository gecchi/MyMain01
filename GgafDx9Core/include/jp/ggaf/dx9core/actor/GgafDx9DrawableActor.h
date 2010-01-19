#ifndef GGAFDX9DRAWABLEACTOR_H_
#define GGAFDX9DRAWABLEACTOR_H_
namespace GgafDx9Core {

/**
 * 画面に描画を行うアクターの抽象クラス .
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
    char* _technique_temp;
    DWORD _frame_temp_technique;
    unsigned int _hash_technique;
    unsigned int _hash_technique_temp;
    bool _is_temp_technique;

    static unsigned int _hash_technique_last_draw;

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


    /**
     * コンストラクタ .
     * @param prm_name モデル名称（任意）
     * @param prm_model モデル識別キー文字列
     * @param prm_effect エフェクト識別キー文字列
     * @param prm_technique エフェクトのテクニック
     * @param prm_pChecker 使用するチェッカーオブジェクト（チェッカー未使用時はNULLでよい）
     */
    GgafDx9DrawableActor(const char* prm_name,
                         const char* prm_model,
                         const char* prm_effect,
                         const char* prm_technique,
                         GgafDx9Checker* prm_pChecker);

    /**
     * コンストラクタ .
     * GgafDx9ModelManager::processCreateResource() 及び
     * GgafDx9EffectManager::processCreateResource()
     * の説明も参照すべし。
     * @param prm_name アクター名称（任意）
     * @param prm_model_id モデル定義名
     * @param prm_model_type モデルタイプ
     * @param prm_effect_id エフェクト定義名
     * @param prm_effect_type エフェクトタイプ
     * @param prm_technique エフェクトのテクニック
     * @param prm_pChecker 使用するチェッカーオブジェクト（チェッカー未使用時はNULLでよい）
     */
    GgafDx9DrawableActor(const char* prm_name,
                         const char* prm_model_id,
                         const char* prm_model_type,
                         const char* prm_effect_id,
                         const char* prm_effect_type,
                         const char* prm_technique,
                         GgafDx9Checker* prm_pChecker);

    virtual GgafDx9DrawableActor* getPrev() override {
        return (GgafDx9DrawableActor*)GgafActor::getPrev();
    }

    virtual GgafDx9DrawableActor* getNext() override {
        return (GgafDx9DrawableActor*)GgafActor::getNext();
    }

    /**
     * テクニックを変更する .
     * 随時可能。
     * @param prm_technique テクニック名
     */
    void setTechnique(char* prm_technique) {
        _hash_technique = GgafCore::GgafUtil::easy_hash(prm_technique);
        strcpy(_technique, prm_technique);
    }

    void setTechniqueTemporarily(char* prm_technique, DWORD prm_frame) {
        if (_is_temp_technique == false) { //すでに一時テクニック使用時は無視
            //元々のテクニックを退避
            _hash_technique_temp = _hash_technique;
            strcpy(_technique_temp, _technique);
            //テクニック変更
            _frame_temp_technique = _frame_of_active + prm_frame; //変更満期フレーム
            _hash_technique = GgafCore::GgafUtil::easy_hash(prm_technique);
            strcpy(_technique, prm_technique);
            _is_temp_technique = true;
        }
    }

    /**
     * 共通の描画事前処理 .
     * 段階レンダリングを実現するために、自身の深度に応じて
     * GgafDx9Universe::_apAlphaActorList_DrawDepthLevel[] または  GgafDx9Universe::_pActors_DrawMaxDrawDepth に
     * 自身を登録する。
     * TODO:private virtual にするべきか否か？。fainal が欲しい
     */
    virtual void processPreDraw() override;

    /**
     * 共通の描画事後処理 .
     * 俺デバッグモード (<code>#define MY_DEBUG 1</code>)の場合は
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
     * アクターのアルファ設定 .
     * @param prm_fAlpha
     */
    virtual void setAlpha(float prm_fAlpha) {
        _fAlpha = prm_fAlpha;
    }

    /**
     * アクターのアルファ加算 .
     * @param prm_fAlpha
     */
    virtual void addAlpha(float prm_fAlpha) {
        _fAlpha += prm_fAlpha;
    }

    /**
     * アクターの現在のアルファ値 .
     * @return
     */
    virtual float getAlpha() {
        return _fAlpha;
    }

    /**
     * マテリアルカラーを設定。
     * キャラクタ全体に色を重ねる。
     * 本メソッドによるマテリアルカラーとは、いわゆる「DirectXのマテリアル」の意味とは範囲が異なる。
     * @param r
     * @param g
     * @param b
     */
    virtual void setMaterialColor(float r, float g, float b);

    /**
     * マテリアルカラーを初期状態にリセット。
     */
    virtual void resetMaterialColor();

    /** SE資源接続 */
    GgafDx9SeConnection** _papSeCon;
    /** SE資源 */
    GgafDx9Se** _papSe;

    /** SE資源接続 */
    GgafDx9SeConnection* _pSeCon;
    /** SE資源 */
    GgafDx9Se* _pSe;
    /** SE資源接続 */
    GgafDx9SeConnection* _pSeCon2;
    /** SE資源 */
    GgafDx9Se* _pSe2;

    void useSe(int prm_id, char* prm_se_name, int prm_cannel = 1) ;

    void playSe(int prm_id);

    void useSe1(char* prm_se_name, int prm_cannel = 0);

    void playSe1();

    void useSe2(char* prm_se_name, int prm_cannel = 0);

    void playSe2();


    virtual ~GgafDx9DrawableActor(); //デストラクタ
};

}
#endif /*GGAFDX9DRAWABLEACTOR_H_*/
