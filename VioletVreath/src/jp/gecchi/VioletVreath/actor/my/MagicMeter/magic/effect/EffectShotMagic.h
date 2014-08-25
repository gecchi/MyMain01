#ifndef EFFECTSHOTMAGIC_H_
#define EFFECTSHOTMAGIC_H_
#include "VioletVreath.h"
#include "jp/ggaf/lib/actor/DefaultSpriteActor.h"

namespace VioletVreath {

/**
 * �V���b�g���@�̃G�t�F�N�g .
 * @version 1.00
 * @since 2014/04/07
 * @author Masatoshi Tsuge
 */
class EffectShotMagic : public GgafLib::DefaultSpriteActor {

public:
    /** �g��k���x���I�u�W�F�N�g */
    GgafDxCore::GgafDxScaler* pScaler_;

    GgafDxCore::GgafDxColorist* pColorist_;
public:
    EffectShotMagic(const char* prm_name);

    void initialize() override;

    void processBehavior() override;

    void onActive() override;

    void onInactive() override;

    void processJudgement() override;

    virtual ~EffectShotMagic();
};

}
#endif /*EFFECTSHOTMAGIC_H_*/

