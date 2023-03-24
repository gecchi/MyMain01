#ifndef LABELFONT8X16_H_
#define LABELFONT8X16_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/ggaf/lib/actor/FontBoardActor.h"

namespace VioletVreath {

/**
 * 8x16ドットFIXフォントのラベル .
 * @version 1.00
 * @since 2018/10/04
 * @author Masatoshi Tsuge
 */
class LabelFont8x16 : public GgafLib::FontBoardActor {

public:
    LabelFont8x16(const char* prm_name);

    virtual void onCreateModel() override;

    virtual void initialize() override;

    virtual void processBehavior() override;

    virtual ~LabelFont8x16();

};

}
#endif /*LABELFONT8X16_H_*/
