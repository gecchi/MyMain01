#ifndef GGAFDXBOARDSETACTORD_H_
#define GGAFDXBOARDSETACTORD_H_
namespace GgafDxCore {

/**
 * 座標変換済みスプライトアクター.
 * GgafDxTransformedActor を継承し、板ポリゴンにテクスチャを貼り付けた<BR>
 * 擬似スプライト機能を追加し、さらに大量表示時に同一モデルは一括描画を行うように最適化したたアクター。<BR>
 * 単純表示（回転拡大無し）のため高速。スコア表示や、背景等に使用しよう。<BR>
 * ２Ｄゲームだけなら、キャラクタオブジェクトはこのクラス一本でいける。<BR>
 * @version 1.00
 * @since 2009/07/21
 * @author Masatoshi Tsuge
 */
class GgafDxBoardSetActor : public GgafDxDrawableActor {
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
    GgafCore::GgafGroupHead* addSubBone(actorkind prm_kind,
                                         GgafDxGeometricActor* prm_pGeoActor,
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
    GgafCore::GgafGroupHead* addSubBone(GgafDxGeometricActor* prm_pGeoActor,
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
    void rotateWith(GgafDxGeometricActor* prm_pActor) override {
    }

public:
    int _draw_set_num;
    /** モデルオブジェクトへのポインタ */
    GgafDxBoardSetModel* _pBoardSetModel;
    /** エフェクト */
    GgafDxBoardSetEffect* _pBoardSetEffect;
    /** UVフリッパー(パラパラアニメ) */
    GgafDxUvFlipper* _pUvFlipper;

    GgafDxBoardSetActor(const char* prm_name,
                         const char* prm_model_id,
                         const char* prm_effect_id,
                         const char* prm_technique );

    virtual void processDraw() override;


    virtual void processSettlementBehavior() override {
    }

    virtual ~GgafDxBoardSetActor(); //デストラクタ

    virtual void locateAs(GgafDxGeometricActor* prm_pActor) override {
        _X = prm_pActor->_X;
        _Y = prm_pActor->_Y;
    }

    virtual void locateAs(GgafDxGeoElem* prm_pGeoElem) override;

};

}
#endif /*GGAFDXBOARDSETACTORD_H_*/
