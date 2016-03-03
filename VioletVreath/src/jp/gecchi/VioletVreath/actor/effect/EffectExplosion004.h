#ifndef EFFECTEXPLOSION004_H_
#define EFFECTEXPLOSION004_H_
#include "VioletVreath.h"
#include "jp/ggaf/lib/actor/DefaultMassSpriteActor.h"

namespace VioletVreath {

/**
 * �����G�t�F�N�g�X�v���C�g004
 * �g�[���X�p������
 * @version 1.00
 * @since 2012/10/19
 * @author Masatoshi Tsuge
 */
class EffectExplosion004 : public GgafLib::DefaultMassSpriteActor {

public:
    /** �g��k���x���I�u�W�F�N�g */
    GgafDxCore::GgafDxScaler* pScaler_;

public:
    EffectExplosion004(const char* prm_name);

    void initialize() override;

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;

    virtual ~EffectExplosion004();
};

}
#endif /*EFFECTEXPLOSION004_H_*/

