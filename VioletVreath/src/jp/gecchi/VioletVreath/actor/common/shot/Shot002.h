#ifndef SHOT002_H_
#define SHOT002_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/gecchi/VioletVreath/actor/VvEnemyActor.hpp"
#include "jp/ggaf/lib/actor/DefaultMassMeshActor.h"

namespace VioletVreath {

/**
 * 汎用弾002(小) .
 * 破壊可能で等速直線移動後、自機へ方向転換<BR>
 * @version 1.00
 * @since 2009/12/28
 * @author Masatoshi Tsuge
 */
class Shot002 : public VvEnemyActor<GgafLib::DefaultMassMeshActor> {

public:
    Shot002(const char* prm_name);

    void initialize() override;

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;

    virtual ~Shot002();
};

}
#endif /*SHOT002_H_*/

