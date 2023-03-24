#ifndef LABELFONT32X64_H_
#define LABELFONT32X64_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/ggaf/lib/actor/FontBoardActor.h"

namespace VioletVreath {

/**
 * 32x64ドットFIXフォントのラベル .
 * @version 1.00
 * @since 2018/10/04
 * @author Masatoshi Tsuge
 */
class LabelFont32x64 : public GgafLib::FontBoardActor {

public:
    LabelFont32x64(const char* prm_name);

    virtual void onCreateModel() override;

    virtual void initialize() override;

    virtual void processBehavior() override;

    virtual ~LabelFont32x64();

};

}
#endif /*LABELFONT32X64_H_*/
