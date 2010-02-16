#ifndef GGAFDX9BOARDACTORD_H_
#define GGAFDX9BOARDACTORD_H_
namespace GgafDx9Core {

/**
 * 座標変換済みスプライトアクター.
 * GgafDx9TransformedActor を継承し、板ポリゴンにテクスチャを貼り付けた<BR>
 * 擬似スプライト機能を追加したアクター。<BR>
 * 単純表示（回転拡大無し）のため高速。スコア表示や、背景等に使用しよう。<BR>
 * ２Ｄゲームだけなら、オブジェクトはこのクラス一本でいける。<BR>
 * @version 1.00
 * @since 2008/02/27
 * @author Masatoshi Tsuge
 */
class GgafDx9BoardActor : public GgafDx9DrawableActor {
private:

//    struct VERTEX {
//        float x, y, z; // 頂点座標
//        float tu, tv; // テクスチャ座標
//    };

    virtual int isOffscreen() {
        _offscreenkind = 0;
        return _offscreenkind;
    }
    virtual bool isOutOfGameSpace() {
        return false;
    }

    /** */
    float _sx;
    /** */
    float _sy;

//    /** 内部アニメパターン用カウンター */
//    int _pattno_counter;
//    /** 内部アニメフレーム用カウンタ */
//    int _frame_counter_uvflip;

public:
    /** モデルオブジェクトへのポインタ */
    GgafDx9BoardModel* _pBoardModel;
    /** エフェクト */
    GgafDx9BoardEffect* _pBoardEffect;
    /** UVフリッパー(パラパラアニメ) */
    GgafDx9UvFlipper* _pUvFlipper;

//    /** 矩形の頂点情報 */
//    VERTEX* _paVertex;
//    /** 矩形の頂点合計のサイズ */
//    UINT _size_vertices;
//    /** 1頂点のサイズ */
//    UINT _size_vertex_unit;
//
//    /** パターン番号の上限 */
//    int _pattno_top;
//    /** パターン番号の下限 */
//    int _pattno_bottom;
//    /** 現在表示中のアニメパターン番号 */
//    int _patteno_now;

    GgafDx9BoardActor(const char* prm_name,
                      const char* prm_model_id,
                      const char* prm_effect_id,
                      const char* prm_technique );

    /**
     * ＜OverRide です＞<BR>
     */
    virtual void processDraw() override;;

    virtual void setGeometry(int x, int y) {
        _x = x;
        _y = y;
    }

    virtual void setGeometry(int x, int y, int z) {
        _x = x;
        _y = y;
        _z = z;
    }

    virtual void setGeometry(float x, float y, float z) {
        _x = x;
        _y = y;
        _z = z;
    }

    virtual void setGeometry(GgafDx9GeometricActor* prm_pActor) {
        _z = prm_pActor->_z;
        _y = prm_pActor->_y;
        _x = prm_pActor->_x;
    }
//    virtual void setPatternNo(int prm_patteno);

//    void setAlpha(float prm_fAlpha) {
//        _fAlpha = prm_fAlpha;
//    }
//
//    float getAlpha() {
//        return _fAlpha;
//    }

    virtual ~GgafDx9BoardActor(); //デストラクタ

    //virtual void setCoordinates(float prm_x, float prm_y, float prm_z);


};

}
#endif /*GGAFDX9BOARDACTORD_H_*/
