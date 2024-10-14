#ifndef SMPPIEGRAPHSPRITE_H_
#define SMPPIEGRAPHSPRITE_H_
#include "Mogera.h"
#include "jp/ggaf/lib/actor/PieGraphSpriteActor.h"

namespace Mogera {

/**
 * �e�X�g�L�����N�^ .
 * @version 1.00
 * @since 2011/02/16
 * @author Masatoshi Tsuge
 */
class SmpPieGraphSprite : public GgafLib::PieGraphSpriteActor {

public:
    /**
     * �R���X�g���N�^
     * @param prm_name
     * @return
     */
    SmpPieGraphSprite(const char* prm_name);

    /**
     * �L�����̏������� .
     */
    void initialize() override;

    /**
     * �L�����̐U�镑������ .
     */
    void processBehavior() override;

    void onHit(const GgafCore::Checker* prm_pOtherChecker, const GgafCore::Actor* prm_pOtherActor);

    virtual ~SmpPieGraphSprite();
};

}
#endif /*SMPPIEGRAPHSPRITE_H_*/

