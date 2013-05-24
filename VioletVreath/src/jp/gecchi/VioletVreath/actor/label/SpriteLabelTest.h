#ifndef SPRITELABELTEST_H_
#define SPRITELABELTEST_H_
#include "jp/ggaf/lib/actor/StringSpriteActor.h"

namespace VioletVreath {

/**
 * オリジナル16x16ドットフォントのラベル .
 * @version 1.00
 * @since 2012/05/16
 * @author Masatoshi Tsuge
 */
class SpriteLabelTest : public GgafLib::StringSpriteActor {

public:
    SpriteLabelTest(const char* prm_name);

    virtual void onCreateModel() override;

    virtual void initialize() override;

    virtual void processBehavior() override;

    virtual ~SpriteLabelTest();

};

}
#endif /*SPRITELABELTEST_H_*/
