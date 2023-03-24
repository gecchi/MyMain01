#ifndef SPRITEFONT32X64_H_
#define SPRITEFONT32X64_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/ggaf/lib/actor/FontSpriteActor.h"

namespace VioletVreath {

/**
 * 32x64ドットフォントのスプライト文字 .
 * @version 1.00
 * @since 2018/10/04
 * @author Masatoshi Tsuge
 */
class SpriteFont32x64 : public GgafLib::FontSpriteActor {

public:
    SpriteFont32x64(const char* prm_name);

    virtual void onCreateModel() override;

    virtual void initialize() override;

    virtual void processBehavior() override;

    virtual ~SpriteFont32x64();

};

}
#endif /*SPRITEFONT32X64_H_*/
