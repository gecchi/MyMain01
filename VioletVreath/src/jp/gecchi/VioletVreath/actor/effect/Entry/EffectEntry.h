#ifndef EFFECTENTRY_H_
#define EFFECTENTRY_H_
#include "jp/ggaf/lib/actor/DefaultMeshSetActor.h"

namespace VioletVreath {

/**
 * 登場エフェクト基底 .
 * @version 1.00
 * @since 2013/06/28
 * @author Masatoshi Tsuge
 */
class EffectEntry : public GgafLib::DefaultMeshSetActor {
public:
    GgafDxCore::GgafDxGeometricActor* pTarget_;

public:
    EffectEntry(const char* prm_name, const char* prm_model);

    virtual void onInactive() override;
    virtual void processBehavior() override;
    virtual void processJudgement() override;

    /**
     * 引数のアクターと同じ座標を継続 .
     * @param prm_pTarget
     */
    void positionFollow(GgafDxCore::GgafDxGeometricActor* prm_pTarget);

    virtual ~EffectEntry();
};

}
#endif /*EFFECTENTRY_H_*/

