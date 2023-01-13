#ifndef ENEMYIDABASE_H_
#define ENEMYIDABASE_H_
#include "Mogera.h"

#include <iostream>
#include <fstream>
#include "jp/ggaf/lib/actor/DefaultMeshSetActor.h"
#include "jp/ggaf/core/util/RingLinkedList.hpp"

namespace Mogera {

/**
 * 敵機イーダの基盤 .
 * @version 1.00
 * @since 2013/06/18
 * @author Masatoshi Tsuge
 */
class EnemyIdaBase : public GgafLib::DefaultMeshSetActor {

public:
    GgafDx::CurveManufactureConnection* pConn_pCurveManuf_;
    GgafDx::VehicleLeader* pVehicleLeader_;
    GgafCore::RingLinkedList<EnemyIda> _list_child;
    std::ofstream* pOs_;
    /**
     * コンストラクタ
     * @param prm_name
     * @return
     */
    EnemyIdaBase(const char* prm_name);
    virtual void initialize() override;
    virtual void onActive() override;
    virtual void processBehavior() override;
    virtual void processJudgement() override;
    virtual void onInactive() override;
    virtual void onCatchEvent(eventval prm_event_val, void* prm_pSource) override;
    virtual ~EnemyIdaBase();
};
}
#endif /*ENEMYIDABASE_H_*/

