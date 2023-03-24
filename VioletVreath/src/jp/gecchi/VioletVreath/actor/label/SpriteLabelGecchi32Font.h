#ifndef SPRITELABELGECCHI32FONT_H_
#define SPRITELABELGECCHI32FONT_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/ggaf/lib/actor/FontSpriteActor.h"

namespace VioletVreath {

/**
 * �I���W�i��32x32�h�b�g�t�H���g�̃X�v���C�g���� .
 * @version 1.00
 * @since 2012/05/16
 * @author Masatoshi Tsuge
 */
class SpriteLabelGecchi32Font : public GgafLib::FontSpriteActor {

public:
    SpriteLabelGecchi32Font(const char* prm_name);

    virtual void onCreateModel() override;

    virtual void initialize() override;

    virtual void processBehavior() override;

    virtual ~SpriteLabelGecchi32Font();

};

}
#endif /*SPRITELABELTEST_H_*/
