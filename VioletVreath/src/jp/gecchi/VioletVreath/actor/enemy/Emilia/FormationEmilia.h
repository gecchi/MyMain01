#ifndef FORMATIONASSALIA_H_
#define FORMATIONASSALIA_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/ggaf/lib/actor/DefaultGeometricActor.h"

namespace VioletVreath {

/**
 * エミリア群 .
 * @version 1.00
 * @since 2012/01/12
 * @author Masatoshi Tsuge
 */
class FormationEmilia : public GgafLib::DefaultGeometricActor {

public:
    /** プリロード用 */
    DepositoryConnection* pConn_depo_Fragment3_;
    /** プリロード用 */
    DepositoryConnection* pConn_depo_Fragment2_;
    /** プリロード用 */
    DepositoryConnection* pConn_depo_Fragment_;
    /** エミリア借り入れ元Depository資源への接続 */
    DepositoryConnection* pConn_depo_Emilia_;

    /** 編隊メンバーの出現間隔フレーム(RANK変動) */
    frame R_interval_frames_;
    /** 分裂数(RANK変動) */
    int R_num_;
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

    virtual void processBehavior() override;

    void appearFragment(EnemyEmiliaBase* prm_pOrg);
    void appearFragment2(EnemyEmiliaBase* prm_pOrg);
    void appearFragment3(EnemyEmiliaBase* prm_pOrg);

    virtual ~FormationEmilia();
};

}
#endif /*FORMATIONUNOMIA_H_*/
