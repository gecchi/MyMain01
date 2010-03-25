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
    /**
     * 使えなくするためにprivateでoverride
     * @return
     */
    int isOffscreen() override {
        return 0;
    }

    /**
     * 使えなくするためにprivateでoverride
     * @return
     */
    bool isOutOfGameSpace() override {
        return false;
    }


public:
    /** [r]モデルオブジェクトへのポインタ */
    GgafDx9BoardModel* _pBoardModel;
    /** [r]エフェクト */
    GgafDx9BoardEffect* _pBoardEffect;
    /** [r]UVフリッパー(パラパラアニメ) */
    GgafDx9UvFlipper* _pUvFlipper;
    /** [r/w]変換済み座標X軸拡大率(1.0で等倍) */
    float _sx;
    /** [r/w]変換済み座標Y軸拡大率(1.0で等倍) */
    float _sy;

    GgafDx9BoardActor(const char* prm_name,
                      const char* prm_model_id,
                      const char* prm_effect_id,
                      const char* prm_technique );

    virtual void processDraw() override;

    /**
     * アクターの変換済み座標(左上の点)を設定 .
     * z は変化なし
     * @param x
     * @param y
     */
    virtual void setGeometry(float x, float y) {
        _x = x;
        _y = y;
    }

    /**
     * アクターの変換済み座標(左上の点)を設定 .
     * @param x
     * @param y
     * @param z 深度
     */
    virtual void setGeometry(int x, int y, int z) override {
        _x = x;
        _y = y;
        _z = z;
    }

    /**
     * アクターの変換済み座標(左上の点)を設定 .
     * @param x
     * @param y
     * @param z 深度
     */
    virtual void setGeometry(float x, float y, float z) {
        _x = x;
        _y = y;
        _z = z;
    }

    /**
     * アクターの変換済み座標をコピーして設定 .
     * @param prm_pActor
     */
    virtual void setGeometry(GgafDx9GeometricActor* prm_pActor) override {
        _z = prm_pActor->_z;
        _y = prm_pActor->_y;
        _x = prm_pActor->_x;
    }

    virtual ~GgafDx9BoardActor(); //デストラクタ

};

}
#endif /*GGAFDX9BOARDACTORD_H_*/
