#ifndef DEFAULTSPRITESETEFFECTACTOR_H_
#define DEFAULTSPRITESETEFFECTACTOR_H_
#include "VioletVreath.h"
#include "jp/ggaf/lib/actor/DefaultSpriteSetActor.h"

namespace VioletVreath {

/**
 * プリロード用テストアクター .
 * @version 1.00
 * @since 2011/04/18
 * @author Masatoshi Tsuge
 */
class DefaultSpriteSetTestActor : public GgafLib::DefaultSpriteSetActor {

public:

    DefaultSpriteSetTestActor(const char* prm_name);

    virtual ~DefaultSpriteSetTestActor();

};

}
#endif /*DEFAULTSPRITESETEFFECTACTOR_H_*/

