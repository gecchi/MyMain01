#ifndef SPRITELABELGECCHI32FONT_H_
#define SPRITELABELGECCHI32FONT_H_
#include "jp/ggaf/lib/actor/StringSpriteActor.h"

namespace VioletVreath {

/**
 * オリジナル32x32ドットフォントのスプライト文字 .
 * @version 1.00
 * @since 2012/05/16
 * @author Masatoshi Tsuge
 */
class SpriteLabelGecchi32Font : public GgafLib::StringSpriteActor {

public:
    /** フィードイン・フェードアウト支援 */
    GgafDxCore::GgafDxAlphaFader* pAFader_;

public:
    SpriteLabelGecchi32Font(const char* prm_name);

    virtual void onCreateModel() override;

    virtual void initialize() override;

    virtual void processBehavior() override;

    virtual ~SpriteLabelGecchi32Font();

};

}
#endif /*SPRITELABELTEST_H_*/
