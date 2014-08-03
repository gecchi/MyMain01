#ifndef FORMATIONASSALIA_H_
#define FORMATIONASSALIA_H_
#include "jp/ggaf/lib/actor/DepositoryFormation.h"

namespace VioletVreath {

/**
 * エミリア群 .
 * @version 1.00
 * @since 2012/01/12
 * @author Masatoshi Tsuge
 */
class FormationEmilia : public GgafLib::DepositoryFormation {

public:
    /** エミリア借り入れ元Depository資源への接続 */
    DepositoryConnection* pDepoConn_Emilia_;
    /** エミリア断片借り入れ元Depository資源への接続 */
    DepositoryConnection* pDepoConn_Fragment_;
    /** エミリア断片の断片借り入れ元Depository資源への接続 */
    DepositoryConnection* pDepoConn_Fragment_2_;
    /** エミリア断片の断片借り入れ元Depository資源への接続 */
    DepositoryConnection* pDepoConn_Fragment_3_;

    /** 編隊メンバーの出現間隔フレーム(RANK変動) */
    frame R_interval_frames_;
    /** 編隊メンバーの初期移動速度(RANK変動) */
    velo R_mv_velo_;

public:
    /**
     * コンストラクタ .
     * @param prm_name
     */
    FormationEmilia(const char* prm_name);

    void updateRankParameter();

    virtual void initialize() override;

    virtual void onActive() override;

//    virtual void processOnActiveEmilia(EnemyEmilia* pEnemyEmilia, int col) = 0;

    virtual void onDestroyAll(GgafCore::GgafActor* prm_pActor_last_destroyed) override;

    virtual void processBehavior() override;

    virtual ~FormationEmilia();
};

}
#endif /*FORMATIONUNOMIA_H_*/
