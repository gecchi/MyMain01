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
        _offscreenkind = 0;
        return _offscreenkind;
    }

    /**
     * 使えなくするためにprivateでoverride
     * @return
     */
    bool isOutOfGameSpace() override {
        return false;
    }

    /** */
    float _sx;
    /** */
    float _sy;

public:
    /** モデルオブジェクトへのポインタ */
    GgafDx9BoardModel* _pBoardModel;
    /** エフェクト */
    GgafDx9BoardEffect* _pBoardEffect;
    /** UVフリッパー(パラパラアニメ) */
    GgafDx9UvFlipper* _pUvFlipper;

    GgafDx9BoardActor(const char* prm_name,
                      const char* prm_model_id,
                      const char* prm_effect_id,
                      const char* prm_technique );

    virtual void processDraw() override;

    virtual void setGeometry(int x, int y) {
        _x = x;
        _y = y;
    }

    virtual void setGeometry(int x, int y, int z) override {
        _x = x;
        _y = y;
        _z = z;
    }

    virtual void setGeometry(float x, float y, float z) {
        _x = x;
        _y = y;
        _z = z;
    }

    virtual void setGeometry(GgafDx9GeometricActor* prm_pActor) override {
        _z = prm_pActor->_z;
        _y = prm_pActor->_y;
        _x = prm_pActor->_x;
    }

    virtual ~GgafDx9BoardActor(); //デストラクタ

};

}
#endif /*GGAFDX9BOARDACTORD_H_*/
