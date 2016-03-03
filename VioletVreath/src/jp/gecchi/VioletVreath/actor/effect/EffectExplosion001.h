#ifndef EFFECTEXPLOSION001_H_
#define EFFECTEXPLOSION001_H_
#include "VioletVreath.h"
#include "jp/ggaf/lib/actor/DefaultMassSpriteActor.h"

namespace VioletVreath {

/**
 * �����G�t�F�N�g�X�v���C�g001
 * @version 1.00
 * @since 2006/01/10
 * @author Masatoshi Tsuge
 */
class EffectExplosion001 : public GgafLib::DefaultMassSpriteActor {

public:
    /** �g��k���x���I�u�W�F�N�g */
    GgafDxCore::GgafDxScaler* pScaler_;

public:
    EffectExplosion001(const char* prm_name);

    void initialize() override;

    void processBehavior() override;

    void onActive() override;

    void onInactive() override;

    void processJudgement() override;

    virtual ~EffectExplosion001();
};

}
#endif /*EFFECTEXPLOSION001_H_*/

