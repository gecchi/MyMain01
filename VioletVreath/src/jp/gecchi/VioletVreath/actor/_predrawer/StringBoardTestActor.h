#ifndef STRINGBOARDEFFECTACTOR_H_
#define STRINGBOARDEFFECTACTOR_H_
#include "jp/ggaf/lib/actor/StringBoardActor.h"

namespace VioletVreath {

/**
 * プリロード用テストアクター .
 * @version 1.00
 * @since 2011/04/18
 * @author Masatoshi Tsuge
 */
class StringBoardTestActor : public GgafLib::StringBoardActor {

public:
    StringBoardTestActor(const char* prm_name);

    virtual void processBehavior() override;

    virtual ~StringBoardTestActor();

};

}
#endif /*LABELGECCHI8FONT_H_*/
