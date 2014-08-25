#ifndef LABELGECCHI8FONT_H_
#define LABELGECCHI8FONT_H_
#include "VioletVreath.h"
#include "jp/ggaf/lib/actor/StringBoardActor.h"

namespace VioletVreath {

/**
 * �I���W�i��8x8�h�b�g�t�H���g�̃��x�� .
 * @version 1.00
 * @since 2010/06/23
 * @author Masatoshi Tsuge
 */
class LabelGecchi8Font : public GgafLib::StringBoardActor {

public:
    LabelGecchi8Font(const char* prm_name);

    virtual void processBehavior() override;

    virtual ~LabelGecchi8Font();

};

}
#endif /*LABELGECCHI8FONT_H_*/
