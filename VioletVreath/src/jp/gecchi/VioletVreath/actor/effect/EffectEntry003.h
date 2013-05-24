#ifndef EFFECTENTRANCE003_H_
#define EFFECTENTRANCE003_H_
#include "jp/ggaf/lib/actor/DefaultMeshSetActor.h"

namespace VioletVreath {

/**
 * 登場エフェクト、その3 .
 * @version 1.00
 * @since 2012/07/18
 * @author Masatoshi Tsuge
 */
class EffectEntry003 : public GgafLib::DefaultMeshSetActor {

    enum {
        PROG_INIT ,
        PROG_IN   ,
        PROG_STAY ,
        PROG_OUT  ,
    };

public:
    EffectEntry003(const char* prm_name);

    void initialize() override;

    void processBehavior() override;

    void onActive() override;

    void onInactive() override;

    void processJudgement() override;

    virtual ~EffectEntry003();
};

}
#endif /*EFFECTENTRANCE003_H_*/

