#ifndef SHOT001_H_
#define SHOT001_H_
#include "VioletVreath.h"
#include "jp/gecchi/VioletVreath/actor/VvEnemyActor.hpp"
#include "jp/ggaf/lib/actor/DefaultMassMeshActor.h"

namespace VioletVreath {

/**
 * 汎用弾001(小) .
 * 破壊可能で等速直線移動<BR>
 * @version 1.00
 * @since 2009/12/28
 * @author Masatoshi Tsuge
 */
class Shot001 : public VvEnemyActor<GgafLib::DefaultMassMeshActor> {

public:
    /** 移動スプラインプログラム */
    GgafDx::SplineLeader* pVecDriverLeader_;
    /** スプライン定義資源への接続 */
    GgafDx::SplineManufactureConnection* pSplManufConn_;
public:
    Shot001(const char* prm_name);

    void initialize() override;

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;

    void onInactive() override;

    void onHit(const GgafCore::Actor* prm_pOtherActor) override;

    virtual ~Shot001();
};

}
#endif /*SHOT001_H_*/

