#ifndef GGAFDX9BOARDSETACTORD_H_
#define GGAFDX9BOARDSETACTORD_H_
namespace GgafDx9Core {

/**
 * 座標変換済みスプライトアクター.
 * GgafDx9TransformedActor を継承し、板ポリゴンにテクスチャを貼り付けた<BR>
 * 擬似スプライト機能を追加したアクター。<BR>
 * 単純表示（回転拡大無し）のため高速。スコア表示や、背景等に使用しよう。<BR>
 * ２Ｄゲームだけなら、オブジェクトはこのクラス一本でいける。<BR>
 */
class GgafDx9BoardSetActor : public GgafDx9DrawableActor {
private:

//    struct VERTEX {
//        float x, y, z; // 頂点座標
//        float tu, tv; // テクスチャ座標
//    };

    /** 内部アニメパターン用カウンター */
    int _pattno_counter;
    /** 内部アニメフレーム用カウンタ */
    int _aniframe_counter;

public:
    int _draw_set_num;
//    char* _technique;
    /** モデルオブジェクトへのポインタ */
    GgafDx9BoardSetModel* _pBoardSetModel;
    /** エフェクト */
    GgafDx9BoardSetEffect* _pBoardSetEffect;

//    /** 矩形の頂点情報 */
//    VERTEX* _paVertex;
//    /** 矩形の頂点合計のサイズ */
//    UINT _size_vertices;
//    /** 1頂点のサイズ */
//    UINT _size_vertex_unit;

    /** パターン番号の上限 */
    int _pattno_top;
    /** パターン番号の下限 */
    int _pattno_bottom;
    /** 現在表示中のアニメパターン番号 */
    int _patteno_now;

    GgafDx9BoardSetActor(const char* prm_name,
                      const char* prm_model,
                      const char* prm_effect,
                      const char* prm_technique );

    /**
     * ＜OverRide です＞<BR>
     */
    virtual void processDrawMain();

    virtual void setPatternNo(int prm_patteno);

//    void setAlpha(float prm_fAlpha) {
//        _fAlpha = prm_fAlpha;
//    }
//
//    float getAlpha() {
//        return _fAlpha;
//    }

    virtual ~GgafDx9BoardSetActor(); //デストラクタ

    //virtual void setCoordinates(float prm_x, float prm_y, float prm_z);


};

}
#endif /*GGAFDX9BOARDSETACTORD_H_*/
