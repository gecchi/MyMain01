#ifndef HOSHIBOSHI_H_
#define HOSHIBOSHI_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/ggaf/dx/actor/PointSpriteActor.h"
#include "jp/ggaf/lib/actor/WorldBoundActor.h"

namespace VioletVreath {

//#define RENDER_DEPTH_INDEX_HOSHIBOSHI (RENDER_DEPTH_INDEX_WORLDBOUND-1)

/**
 * 星々ポイントスプライト基底 .
 * 星々の頂点(スプライト)座標群は、XYZ軸座標 -1.0～1.0 範囲内に集約して作成されていることが前提。<BR>
 * X軸、Y軸、Z軸移動させても、星々の頂点(スプライト)座標はローテートさせ、スクロールしていように見える効果を出す<br>
 * また、基準アクター(自機等)の周りで星星を滑らかに非表示する効果も出す。<br>
 * @version 1.00
 * @since 2010/02/28
 * @author Masatoshi Tsuge
 */
class HoshiBoshi : public GgafDx::PointSpriteActor {

public:
    float far_rate_;

    coord space_distance_;

    GgafDx::GeometricActor* pCriteria_;

    static coord CAM_ZF_;

public:
    HoshiBoshi(const char* prm_name, const char* prm_model);

    static bool initStatic(HoshiBoshi* prm_pHoshiBoshi);

    /**
     * 星々の広がりの拡大倍率を設定 .
     * 星々はDIRECTX距離-1.0～1.0（-10px～10px)に収まっている前提で、
     * 1.0を設定すると、現在のカメラから見える最遠の距離(zf) を使用し、 -zf ～ zf を一辺の長さとする立方体に、
     * モデルの星々の頂点(スプライト)座標群の座標範囲(XYZ軸座標 -1.0～1.0）と一致させる。
     * @param prm_far_rate 広がりの拡大倍率
     */
    void setFarRate(float prm_far_rate);

    inline float getFarRate() {
        return far_rate_;
    }
    /**
     * 基準アクターを設定 .
     * 設定されたアクターの周りは、星々は滑らかに非表示（アルファで透明）となる。
     * @param prm_pCriteria 基準アクター
     */
    void setCriteriaActor(GgafDx::GeometricActor* prm_pCriteria);

    virtual void onCreateModel() override {
    }

    virtual void initialize() override;

    virtual void processSettlementBehavior() override;

    virtual void processJudgement() override;

    virtual void processDraw() override;

    virtual void onCatchEvent(eventval prm_event_val, void* prm_pSource) override {
    }

    virtual void onHit(const GgafCore::Actor* prm_pOtherActor) override {
    }

    virtual void drawHitArea() override;

    virtual int isOutOfView() override;

    virtual bool isOutOfSpacetime() const override;



    virtual ~HoshiBoshi();



    static void setWorldMatrix_HoshiBoshi(const GgafDx::GeometricActor* prm_pActor, D3DXMATRIX& out_matWorld);
};

}
#endif /*HOSHIBOSHI_H_*/

