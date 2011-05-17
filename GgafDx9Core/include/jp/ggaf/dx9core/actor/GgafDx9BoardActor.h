#ifndef GGAFDX9BOARDACTORD_H_
#define GGAFDX9BOARDACTORD_H_
namespace GgafDx9Core {

/**
 * 座標変換済みスプライトアクター .
 * GgafDx9TransformedActor を継承し、板ポリゴンにテクスチャを貼り付けた<BR>
 * 擬似スプライト機能を追加したアクター。<BR>
 * 単純表示（回転拡大無し）のため高速。<BR>
 * @version 1.00
 * @since 2008/02/27
 * @author Masatoshi Tsuge
 */
class GgafDx9BoardActor : public GgafDx9DrawableActor {
private:
    /**
     * 使用不可のため、privateでoverride
     * @return
     */
    int isOutOfView() override {
        return 0;
    }

    /**
     * 使用不可のため、privateでoverride
     * @return
     */
    bool isOutOfUniverse() override {
        return false;
    }

    /**
     * 使用不可のため、privateでoverride
     * @return
     */
    GgafCore::GgafGroupActor* addSubBone(actorkind prm_kind,
                                         GgafDx9GeometricActor* prm_pGeoActor,
                                         int prm_X_init_local,
                                         int prm_Y_init_local,
                                         int prm_Z_init_local,
                                         int prm_RX_init_local,
                                         int prm_RZ_init_local,
                                         int prm_RY_init_local) override {
        return NULL;
    }

    /**
     * 使用不可のため、privateでoverride
     * @return
     */
    GgafCore::GgafGroupActor* addSubBone(GgafDx9GeometricActor* prm_pGeoActor,
                                         int prm_X_init_local,
                                         int prm_Y_init_local,
                                         int prm_Z_init_local,
                                         int prm_RX_init_local,
                                         int prm_RZ_init_local,
                                         int prm_RY_init_local) override {
        return NULL;
    }

    /**
     * 使用不可のため、privateでoverride
     * @return
     */
    void changeGeoLocal() override {
    }

    /**
     * 使用不可のため、privateでoverride
     * @return
     */
    void changeGeoFinal() override {
    }

    /**
     * 使用不可のため、privateでoverride
     * @return
     */
    void locateAs(GgafDx9GeoElem* prm_pGgafDx9GeoElem) override {
    }

    /**
     * 使用不可のため、privateでoverride
     * @return
     */
    void rotateWith(GgafDx9GeometricActor* prm_pActor) override {
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
    virtual void locate(float x, float y) {
        _x = x;
        _y = y;
    }

    /**
     * アクターの変換済み座標(左上の点)を設定 .
     * @param x
     * @param y
     * @param z 深度
     */
    virtual void locate(int x, int y, int z) override {
        _x = (float)x;
        _y = (float)y;
        _z = (float)z;
    }

    /**
     * アクターの変換済み座標(左上の点)を設定 .
     * @param x
     * @param y
     * @param z 深度
     */
    virtual void locate(float x, float y, float z) {
        _x = x;
        _y = y;
        _z = z;
    }

    /**
     * アクターの変換済み座標をコピーして設定 .
     * @param prm_pActor
     */
    virtual void locateAs(GgafDx9GeometricActor* prm_pActor) override {
        _z = prm_pActor->_z;
        _y = prm_pActor->_y;
        _x = prm_pActor->_x;
    }

    /**
     * スケールをスケール値で設定します。
     * @param S スケール値(1.0 で 1.0倍)
     */
    virtual void setScale(int S) override {
        _sx = S;
        _sy = S;
        setBoundingSphereRadiusRate((1.0*S)/1000);
    }

    /**
     * スケールを倍率で設定します。
     * 1.0 で 1.0倍。
     * 【注意】setScale と同じ
     * @param prm_rate 倍率
     */
    virtual void setScaleRate(float prm_rate) override {
        _sx = prm_rate;
        _sy = prm_rate;
        setBoundingSphereRadiusRate(prm_rate);
    }

    virtual void processSettlementBehavior() {
    }

    virtual ~GgafDx9BoardActor(); //デストラクタ

};

}
#endif /*GGAFDX9BOARDACTORD_H_*/
