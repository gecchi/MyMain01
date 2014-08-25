#ifndef EFFECTWORMHOLE_H_
#define EFFECTWORMHOLE_H_
#include "VioletVreath.h"
#include "jp/ggaf/lib/actor/DefaultMorphMeshActor.h"

namespace VioletVreath {

/**
 * ���[���z�[��(�G�o���̍���)�G�t�F�N�g�A���N���X .
 * @version 1.00
 * @since 2011/02/02
 * @author Masatoshi Tsuge
 */
class EffectWormhole : public GgafLib::DefaultMorphMeshActor {

public:
    /** �g��k���x���I�u�W�F�N�g */
    GgafDxCore::GgafDxScaler* pScaler_;

public:
    EffectWormhole(const char* prm_name, const char* prm_model_id);

    void initialize() override;

    void processBehavior() override;

    void onActive() override;

    void onInactive() override;

    void processJudgement() override;

    virtual ~EffectWormhole();
};

}
#endif /*EFFECTWORMHOLE_H_*/

