#ifndef GGAF_DX_BOARDSETACTORD_H_
#define GGAF_DX_BOARDSETACTORD_H_
#include "jp/ggaf/GgafDxCommonHeader.h"
#include "jp/ggaf/dx/actor/FigureActor.h"
#include "jp/ggaf/dx/actor/interface/IAlignAbleActor.h"

namespace GgafDx {

/**
 * 2D表示用板ポリアクター. (複数同時表示時用) .
 * BoardActorに、同一モデルは一括描画を行うように最適化したたアクター。<BR>
 * 頂点バッファに複数の板ポリ頂点を挿入し、一気に描画する仕様。<BR>
 * 数十個の同一モデル板ポリであれば、頂点バッファが固定の為、MassBoardActor より本アクターの方が効率が良い<BR>
 * 但し、回転機能はなし、拡大縮小機能もなし。<BR>
 * 単純表示のため高速。背景等に使用したい。<BR>
 * @version 1.00
 * @since 2009/07/21
 * @author Masatoshi Tsuge
 */
class BoardSetActor : public FigureActor , public IAlignAbleActor {
private:

    /**
     * 使用不可のため、privateでoverride
     * @return
     */
    void appendChildAsFk(GeometricActor* prm_pGeoActor,
                          int prm_x_init_local,
                          int prm_y_init_local,
                          int prm_z_init_local,
                          int prm_rx_init_local,
                          int prm_ry_init_local,
                          int prm_rz_init_local) override {
        throwCriticalException("使用不可です。");
    }

    void setFaceAngAs(const GeoElem* prm_pActor) override {
        throwCriticalException("使用不可です。");
    }
    void setFaceAngAs(const GeometricActor* prm_pActor) override {
        throwCriticalException("使用不可です。");
    }
    void setScale(scale S) override {
        throwCriticalException("使用不可です。");
    }
    void setScale(scale SX, scale SY) override {
        throwCriticalException("使用不可です。");
    }
    void setScale(scale SX, scale SY, scale SZ) override {
        throwCriticalException("使用不可です。");
    }
    void setScaleR(float prm_rate) override {
        throwCriticalException("使用不可です。");
    }
    void setScaleR(float prm_x_rate, float prm_y_rate, float prm_z_rate) override {
        throwCriticalException("使用不可です。");
    }
    void setScaleR(float prm_x_rate, float prm_y_rate) override {
        throwCriticalException("使用不可です。");
    }
    void addScale(scale dS) override {
        throwCriticalException("使用不可です。");
    }
    void addScaleX(scale dsx) override {
        throwCriticalException("使用不可です。");
    }
    void addScaleY(scale dsy) override {
        throwCriticalException("使用不可です。");
    }
    void addScaleZ(scale dsz) override {
        throwCriticalException("使用不可です。");
    }

public:
    /** [r]モデルオブジェクトへのポインタ */
    BoardSetModel* _pBoardSetModel;
    /** [r]エフェクト */
    BoardSetEffect* const _pBoardSetEffect;
    /** [r]UVフリッパー(パラパラアニメ) */
    UvFlipper* const _pUvFlipper;
    /** [r]幅(px) */
    pixcoord _width_px;
    /** [r]高さ(px) */
    pixcoord _height_px;
    /** [r]幅(px)の半分 */
    pixcoord _harf_width_px;
    /** [r]高さ(px)の半分 */
    pixcoord _harf_height_px;

public:
    /**
     * コンストラクタ .
     * @param prm_name アクター名称（デバッグログで表示、なんでも良い）
     * @param prm_model モデル定義名、末尾に ".sprx" をつけたモデル定義ファイルが読み込まれる。
     * @param prm_effect_id エフェクト定義名。末尾に ".fx" をつけてエフェクトファイル名になること。
     * @param prm_technique エフェクトのテクニック名
     * @return
     */
    BoardSetActor(const char* prm_name,
                  const char* prm_model,
                  const char* prm_effect_id,
                  const char* prm_technique ,
                  CollisionChecker* prm_pChecker = nullptr);

    virtual void processDraw() override;

    virtual void setPositionAt(const GeometricActor* prm_pActor) override;

    virtual void setPositionAt(const GeoElem* prm_pGeoElem) override;

    inline UvFlipper* getUvFlipper() {
        return _pUvFlipper;
    }

    int isOutOfView() override {
        return 0;
    }

    bool isOutOfSpacetime() const override {
        return false;
    }

    /**
     * モデル資源(MeshModel)を切り替える（表示が切り替わります） .
     * @param prm_model_index モデル資源保持リストのインデックス。
     *                        最初の   addModel() に切り替え => 0 を設定
     *                        ２回目の addModel() に切り替え => 1 を設定
     *                        ３回目の addModel() に切り替え => 2 を設定
     *                         …
     */
    virtual void changeModelByIndex(int prm_model_index) override;

    virtual ~BoardSetActor();

};

}
#endif /*GGAF_DX_BOARDSETACTORD_H_*/
