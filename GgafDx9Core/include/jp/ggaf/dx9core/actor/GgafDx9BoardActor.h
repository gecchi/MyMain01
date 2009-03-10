#ifndef GGAFDX9BOARDACTORD_H_
#define GGAFDX9BOARDACTORD_H_
namespace GgafDx9Core {

/**
 * 座標変換済みスプライトアクター.
 * GgafDx9TransformedActor を継承し、板ポリゴンにテクスチャを貼り付けた<BR>
 * 擬似スプライト機能を追加したアクターです<BR>
 */
class GgafDx9BoardActor : public GgafDx9TransformedActor {
private:

    struct VERTEX {
        float x, y, z; // 頂点座標
        float tu, tv; // テクスチャ座標
    };

    /** 内部アニメパターン用カウンター */
    int _pattno_counter;
    /** 内部アニメフレーム用カウンタ */
    int _aniframe_counter;

public:
    /** モデルオブジェクトへのポインタ */
    GgafDx9ModelConnection* _pModelCon;
    GgafDx9BoardModel* _pBoardModel;
    /** エフェクト */
    GgafDx9EffectConnection* _pEffectCon;
    GgafDx9BoardEffect* _pBoardEffect;

    /** キャラ全体のα */
    float _fAlpha;

    /** 矩形の頂点情報 */
    VERTEX* _paVertex;
    /** 矩形の頂点合計のサイズ */
    UINT _size_vertecs;
    /** 1頂点のサイズ */
    UINT _size_vertec_unit;

    /** アニメパターン番号の上限番号 */
    int _pattno_top;
    /** 現在表示中のアニメパターン番号 */
    int _pattno_bottom;
    /** 現在表示中のアニメパターン番号 */
    int _patteno_now;

    GgafDx9BoardActor(const char* prm_name, const char* prm_spritemodel_name);

    /**
     * ＜OverRide です＞<BR>
     */
    virtual void processDrawMain();

    virtual void setPatternNo(int prm_patteno);

    void setAlpha(float prm_fAlpha) {
        _fAlpha = prm_fAlpha;
    }

    float getAlpha() {
        return _fAlpha;
    }

    virtual ~GgafDx9BoardActor(); //デストラクタ

    //virtual void setCoordinates(float prm_x, float prm_y, float prm_z);


};

}
#endif /*GGAFDX9BOARDACTORD_H_*/
