#ifndef STRINGBOARDACTOR_H_
#define STRINGBOARDACTOR_H_
#include "jp/ggaf/dxcore/actor/ex/GgafDxStringBoardActor.h"

namespace GgafLib {

/**
 * ç¿ïWïœä∑çœÇ›î¬É|Éäï∂éöï\é¶
 * @version 1.00
 * @since 2010/06/23
 * @author Masatoshi Tsuge
 */
class StringBoardActor : public GgafDxCore::GgafDxStringBoardActor {

public:
    StringBoardActor(const char* prm_name, const char* prm_model, GgafCore::GgafStatus* prm_pStat=nullptr);

    virtual void onCreateModel() override {
        GgafDxCore::GgafDxStringBoardActor::onCreateModel();
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

    virtual ~StringBoardActor();

};

}
#endif /*STRINGBOARDACTOR_H_*/
