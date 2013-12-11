#ifndef SPRITELABELGECCHI32FONT_H_
#define SPRITELABELGECCHI32FONT_H_
#include "jp/ggaf/lib/actor/StringSpriteActor.h"

namespace VioletVreath {

/**
 * �I���W�i��32x32�h�b�g�t�H���g�̃X�v���C�g���� .
 * @version 1.00
 * @since 2012/05/16
 * @author Masatoshi Tsuge
 */
class SpriteLabelGecchi32Font : public GgafLib::StringSpriteActor {

public:
    /** �t�B�[�h�C���E�t�F�[�h�A�E�g�x�� */
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
