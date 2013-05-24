#ifndef STRINGSPRITEACTOR_H_
#define STRINGSPRITEACTOR_H_
#include "jp/ggaf/dxcore/actor/ex/GgafDxStringSpriteActor.h"

namespace GgafLib {

/**
 * ç¿ïWñ¢ïœä∑î¬É|Éäï∂éöï\é¶
 * @version 1.00
 * @since 2012/05/16
 * @author Masatoshi Tsuge
 */
class StringSpriteActor : public GgafDxCore::GgafDxStringSpriteActor {

public:
    StringSpriteActor(const char* prm_name, const char* prm_model, GgafCore::GgafStatus* prm_pStat=nullptr);

    virtual void onCreateModel() override {
        GgafDxCore::GgafDxStringSpriteActor::onCreateModel();
    }

    virtual void initialize() override {
    }

    virtual void onActive() override {
    }

    virtual void processBehavior() override {
    }

    virtual void processJudgement() override {
    }

    virtual void onCatchEvent(hashval prm_no, void* prm_pSource) override {
    }

    virtual void onInactive() override {
    }

    virtual ~StringSpriteActor();

};

}
#endif /*STRINGSPRITEACTOR_H_*/
