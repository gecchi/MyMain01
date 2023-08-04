#ifndef FORMATIONALLAS002_H_
#define FORMATIONALLAS002_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/gecchi/VioletVreath/actor/VvFormationActor.hpp"
#include "jp/ggaf/lib/actor/TreeFormation.h"

namespace VioletVreath {

/**
 * 敵機リス用フォーメーションその１ .
 * @version 1.00
 * @since 2010/06/13
 * @author Masatoshi Tsuge
 */
class FormationAllas002 : public VvFormationActor<GgafLib::TreeFormation> {
    /** リスの発射弾の借り入れ元Depository資源への接続 */
    DepositoryConnection* pConn_depo_;
    /** 曲線移動の情報資源への接続 */
    GgafDx::CurveManufactureConnection* pConn_pCurveManuf_;

public:
    /** 編隊数(RANK変動) */
    int num_Allas_;
    /** 編隊間隔フレーム(RANK変動) */
    frame interval_frames_;
    /** 移動速度(RANK変動) */
    velo velo_mv_;

public:
    FormationAllas002(const char* prm_name);

    /**
     * 編隊を作成 .
     */
    virtual void initialize() override {
    }
    virtual void onActive() override;

    virtual ~FormationAllas002();
};

}
#endif /*FORMATIONALLAS002_H_*/
