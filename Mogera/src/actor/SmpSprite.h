#ifndef SMPSPRITE_H_
#define SMPSPRITE_H_
#include "Mogera.h"
#include "jp/ggaf/lib/actor/DefaultFramedSpriteActor.h"

namespace Mogera {

/**
 * �e�X�g�L�����N�^ .
 * @version 1.00
 * @since 2011/02/16
 * @author Masatoshi Tsuge
 */
class SmpSprite : public GgafLib::DefaultFramedSpriteActor {

public:
    /**
     * �R���X�g���N�^
     * @param prm_name
     * @return
     */
    SmpSprite(const char* prm_name);

    /**
     * �L�����̏������� .
     */
    void initialize() override;

    /**
     * �L�����̐U�镑������ .
     */
    void processBehavior() override;

    void onHit(const GgafCore::Actor* prm_pOtherActor);

    virtual ~SmpSprite();
};

}
#endif /*SMPSPRITE_H_*/

