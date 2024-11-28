#ifndef EFFECTCONDENSATION001_H_
#define EFFECTCONDENSATION001_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/ggaf/lib/actor/DefaultSpriteSetActor.h"
#include "jp/gecchi/VioletVreath/actor/VvEffectActor.hpp"

namespace VioletVreath {

/**
 * ���ˑO�̗��\���G�t�F�N�g���̂P .
 * @version 1.00
 * @since 2010/03/19
 * @author Masatoshi Tsuge
 */
class EffectCondensation001 : public VvEffectActor<GgafLib::DefaultSpriteSetActor> {

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

