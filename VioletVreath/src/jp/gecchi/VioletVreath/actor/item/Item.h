#ifndef ITEM_H_
#define ITEM_H_
#include "VioletVreath.h"
#include "jp/ggaf/lib/actor/DefaultMassMeshActor.h"

namespace VioletVreath {

/**
 * �A�C�e�� .
 * @version 1.00
 * @since 2011/02/04
 * @author Masatoshi Tsuge
 */
class Item : public GgafLib::DefaultMassMeshActor {

public:
    TractorMagic* pTractorMagic_;

public:
    Item(const char* prm_name, const char* prm_model, GgafCore::Status* prm_pStat);

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

