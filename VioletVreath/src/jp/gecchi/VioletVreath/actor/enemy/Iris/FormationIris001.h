#ifndef FORMATIONIRIS001_H_
#define FORMATIONIRIS001_H_
#include "jp/ggaf/lib/actor/TreeFormation.h"

namespace VioletVreath {

/**
 * 敵機イリス用フォーメーションその１ .
 * @version 1.00
 * @since 2009/12/25
 * @author Masatoshi Tsuge
 */
class FormationIris001 : public GgafLib::TreeFormation {
    /** イリスの発射弾の借り入れ元Depository資源への接続 */
    DepositoryConnection* pDepoConnection_;
    /** スプライン定義資源への接続 */
    SplineLineConnection* pSplLineConnection_;

public:
    /** 編隊数(RANK変動) */
    int num_Iris_;
    /** 編隊間隔フレーム(RANK変動) */
    frame interval_frames_;
    /** 移動速度(RANK変動) */
    velo velo_mv_;

public:
    FormationIris001(const char* prm_name);

    void initialize() override;

    void onActive() override;

    void processBehavior() override;

    void onDestroyAll(GgafCore::GgafActor* prm_pActor_last_destroyed) override;

    virtual ~FormationIris001();
};

}
#endif /*FORMATIONIRIS001_H_*/
