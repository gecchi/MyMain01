#ifndef HOSHIBOSHI_H_
#define HOSHIBOSHI_H_
#include "VioletVreath.h"
#include "jp/ggaf/dxcore/actor/GgafDxPointSpriteActor.h"

namespace VioletVreath {

/**
 * 星々ポイントスプライト基底 .
 * 星々の頂点(スプライト)座標群は、XYZ軸座標 -1.0～1.0 範囲内に集約して作成されていることが前提。<BR>
 * X軸、Y軸、Z軸移動させても、星々の頂点(スプライト)座標はローテートさせ、スクロールしていように見える効果を出す<br>
 * また、基準アクター(自機等)の周りで星星を滑らかに非表示する効果も出す。<br>
 * @version 1.00
 * @since 2010/02/28
 * @author Masatoshi Tsuge
 */
class HoshiBoshi : public GgafDxCore::GgafDxPointSpriteActor {

public:


    float far_rate_;
    coord space_distance_;
    GgafDxCore::GgafDxGeometricActor* pCriteria_;

    static D3DXHANDLE h_fX_MyShip_;
    static D3DXHANDLE h_fY_MyShip_;
    static D3DXHANDLE h_fZ_MyShip_;
    static D3DXHANDLE h_far_rate_;
    static coord CAM_ZF_;

    static bool is_init_;

public:
    HoshiBoshi(const char* prm_name, const char* prm_model_id);

    /**
     * 星々の広がりの拡大倍率を設定 .
     * 1.0を設定すると、現在のカメラから見える範囲(XYZ軸座標 -zf ～ zf)を、
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
    void setCriteriaActor(GgafDxCore::GgafDxGeometricActor* prm_pCriteria);

    virtual void onCreateModel() override {
    }

    virtual void initialize() override;

    virtual void processSettlementBehavior() override;

    virtual void processJudgement() override;

    virtual void processDraw() override;

    virtual void onCatchEvent(hashval prm_no, void* prm_pSource) override {
    }

    virtual void onHit(GgafCore::GgafActor* prm_pOtherActor) override {
    }

    virtual void drawHitArea() override;

    virtual int isOutOfView() override;

    virtual bool isOutOfUniverse() const override;



    virtual ~HoshiBoshi();



    static void setWorldMatrix_HoshiBoshi(const GgafDxGeometricActor* prm_pActor, D3DXMATRIX& out_matWorld);
};

}
#endif /*HOSHIBOSHI_H_*/

