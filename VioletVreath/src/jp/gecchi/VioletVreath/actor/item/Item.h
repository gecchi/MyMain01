#ifndef ITEM_H_
#define ITEM_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/gecchi/VioletVreath/actor/VvItemActor.hpp"
#include "jp/ggaf/lib/actor/DefaultMassMeshActor.h"

namespace VioletVreath {

/**
 * ƒAƒCƒeƒ€ .
 * @version 1.00
 * @since 2011/02/04
 * @author Masatoshi Tsuge
 */
class Item : public VvItemActor<GgafLib::DefaultMassMeshActor> {

public:
    TractorMagic* pTractorMagic_;

public:
    Item(const char* prm_name, const char* prm_model, void* prm_pFuncStatusReset);

  TractorMagic* getTractorMagic();

    virtual void initialize() override;

    virtual void onReset() override;

    virtual void onActive() override;

    virtual void processBehavior() override;

    virtual void processJudgement() override;

    virtual void onInactive() override;

    virtual ~Item();
};

}
#endif /*ITEM_H_*/

