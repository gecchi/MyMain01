#ifndef LABELFONT16X32_H_
#define LABELFONT16X32_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/ggaf/lib/actor/FontBoardActor.h"

namespace VioletVreath {

/**
 * 16x32ドットFIXフォントのラベル .
 * @version 1.00
 * @since 2018/10/04
 * @author Masatoshi Tsuge
 */
class LabelFont16x32 : public GgafLib::FontBoardActor {

public:
    LabelFont16x32(const char* prm_name);

    virtual void onCreateModel() override;

    virtual void initialize() override;

    virtual void processBehavior() override;

    virtual ~LabelFont16x32();

};

}
#endif /*LABELFONT16X32_H_*/
