﻿#ifndef GGAFDX9BOARDSETACTORD_H_
#define GGAFDX9BOARDSETACTORD_H_
namespace GgafDx9Core {

/**
 * 座標変換済みスプライトアクター.
 * GgafDx9TransformedActor を継承し、板ポリゴンにテクスチャを貼り付けた<BR>
 * 擬似スプライト機能を追加し、さらに大量表示に最適化したたアクター。<BR>
 * 単純表示（回転拡大無し）のため高速。スコア表示や、背景等に使用しよう。<BR>
 * ２Ｄゲームだけなら、オブジェクトはこのクラス一本でいける。<BR>
 * @version 1.00
 * @since 2009/07/21
 * @author Masatoshi Tsuge
 */
class GgafDx9BoardSetActor : public GgafDx9DrawableActor {
private:

    /**
     * 使えなくするためにprivateでoverride
     * @return
     */
    virtual int isOffscreen() {
        return 0;
    }
    /**
     * 使えなくするためにprivateでoverride
     * @return
     */
    virtual bool isOutOfGameSpace() {
        return false;
    }


public:
    int _draw_set_num;
    /** モデルオブジェクトへのポインタ */
    GgafDx9BoardSetModel* _pBoardSetModel;
    /** エフェクト */
    GgafDx9BoardSetEffect* _pBoardSetEffect;
    /** UVフリッパー(パラパラアニメ) */
    GgafDx9UvFlipper* _pUvFlipper;

    GgafDx9BoardSetActor(const char* prm_name,
                         const char* prm_model_id,
                         const char* prm_effect_id,
                         const char* prm_technique );

    /**
     * ＜OverRide です＞<BR>
     */
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

    virtual ~GgafDx9BoardSetActor(); //デストラクタ

};

}
#endif /*GGAFDX9BOARDSETACTORD_H_*/
