#ifndef FORMATIONALLAS001_H_
#define FORMATIONALLAS001_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/ggaf/lib/actor/TreeFormation.h"

namespace VioletVreath {

/**
 * 敵機アラス用フォーメーションその１ .
 * @version 1.00
 * @since 2010/06/13
 * @author Masatoshi Tsuge
 */
class FormationAllas001 : public GgafLib::TreeFormation {

public:
    /** アラスの発射弾の借り入れ元Depository資源への接続 */
    DepositoryConnection* pConn_depo_;
    /** 曲線移動の情報資源への接続 */
    GgafDx::CurveManufactureConnection* pConn_pCurveManuf_;
    /** 編隊数(RANK変動) */
    int num_Allas_;
    /** 編隊間隔フレーム(RANK変動) */
    frame interval_frames_;
    /** 移動速度(RANK変動) */
    velo velo_mv_;

public:
    FormationAllas001(const char* prm_name);

    /**
     * 編隊を作成 .
     */
    virtual void initialize() override;

    virtual void onActive() override;

    virtual void processBehavior() override;

    virtual void onDestroyAll(GgafCore::Actor* prm_pActor_last_destroyed) override;

    virtual void onCalledUpAllas(EnemyAllas* prm_pAllas) = 0;

    virtual ~FormationAllas001();
};

}
#endif /*FORMATIONALLAS001_H_*/
