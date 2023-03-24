#ifndef FORMATIONRIS001_H_
#define FORMATIONRIS001_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/ggaf/lib/actor/TreeFormation.h"

namespace VioletVreath {

/**
 * 敵機リス用フォーメーションその１ .
 * @version 1.00
 * @since 2009/12/25
 * @author Masatoshi Tsuge
 */
class FormationRis001 : public GgafLib::TreeFormation {
    /** リスの発射弾の借り入れ元Depository資源への接続 */
    DepositoryConnection* pConn_depo_;
    /** 曲線移動の情報資源への接続 */
    GgafDx::CurveSourceConnection* pCurveSrcConnection_;
    GgafDx::CurveManufacture* pManufacture_;
public:

    /** 編隊数(RANK変動) */
    int num_Ris_;
    /** 編隊間隔フレーム(RANK変動) */
    frame interval_frames_;
    /** 移動速度(RANK変動) */
    velo velo_mv_;

public:
    FormationRis001(const char* prm_name);

    void initialize() override;

    void onActive() override;

    void processBehavior() override;

    void onDestroyAll(GgafCore::Actor* prm_pActor_last_destroyed) override;

    virtual ~FormationRis001();
};

}
#endif /*FORMATIONRIS001_H_*/
