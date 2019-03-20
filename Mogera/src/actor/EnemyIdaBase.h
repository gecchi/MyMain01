#ifndef ENEMYIDABASE_H_
#define ENEMYIDABASE_H_
#include "Mogera.h"

#include <iostream>
#include <fstream>
#include "jp/ggaf/lib/actor/DefaultMeshSetActor.h"
#include "jp/ggaf/core/util/LinkedListRing.hpp"

namespace Mogera {

/**
 * 敵機イーダの基盤 .
 * @version 1.00
 * @since 2013/06/18
 * @author Masatoshi Tsuge
 */
class EnemyIdaBase : public GgafLib::DefaultMeshSetActor {

public:
    GgafLib::SplineManufactureConnection* pConn_pSplManuf_;
    GgafLib::SplineLeader* pKurokoLeader_;
    GgafCore::LinkedListRing<EnemyIda> _list_child;
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
    virtual void onCatchEvent(hashval prm_no, void* prm_pSource) override;
    virtual ~EnemyIdaBase();
};
}
#endif /*ENEMYIDABASE_H_*/

