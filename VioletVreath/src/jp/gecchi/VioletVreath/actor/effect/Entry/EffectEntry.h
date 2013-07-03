#ifndef EFFECTENTRY_H_
#define EFFECTENTRY_H_
#include "jp/ggaf/lib/actor/DefaultMeshSetActor.h"

namespace VioletVreath {

/**
 * �o��G�t�F�N�g��� .
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
     * �����̃A�N�^�[�Ɠ������W���p�� .
     * @param prm_pTarget
     */
    void positionFollow(GgafDxCore::GgafDxGeometricActor* prm_pTarget);

    virtual ~EffectEntry();
};

}
#endif /*EFFECTENTRY_H_*/

