#ifndef EFFECTCONDENSATION001_H_
#define EFFECTCONDENSATION001_H_
#include "VioletVreath.h"
#include "jp/ggaf/lib/actor/DefaultSpriteSetActor.h"

namespace VioletVreath {

/**
 * ���ˑO�̗��\���G�t�F�N�g���̂P .
 * @version 1.00
 * @since 2010/03/19
 * @author Masatoshi Tsuge
 */
class EffectCondensation001 : public GgafLib::DefaultSpriteSetActor {

public:
    /** �g��k���x���I�u�W�F�N�g */
    GgafDxCore::GgafDxScaler* pScaler_;

public:
    EffectCondensation001(const char* prm_name);

    void initialize() override;

    void processBehavior() override;

    void onActive() override;

    void onInactive() override;

    void processJudgement() override;

    virtual ~EffectCondensation001();
};

}
#endif /*EFFECTCONDENSATION001_H_*/

