#ifndef LABELSCENESYMBOL_H_
#define LABELSCENESYMBOL_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/ggaf/lib/actor/FontBoardActor.h"

namespace VioletVreath {

/**
 * シーン名表示用ラベル .
 * @version 1.00
 * @since 2012/10/30
 * @author Masatoshi Tsuge
 */
class LabelSceneSymbol : public GgafLib::FontBoardActor {

public:
    LabelSceneSymbol(const char* prm_name);

    virtual void onCreateModel() override;

    virtual void initialize() override;

    virtual void processBehavior() override;

    virtual ~LabelSceneSymbol();

};

}
#endif /*LABELSCENESYMBOL_H_*/
