#ifndef DEFAULTSPRITESETEFFECTACTOR_H_
#define DEFAULTSPRITESETEFFECTACTOR_H_
#include "jp/ggaf/lib/actor/DefaultSpriteSetActor.h"

namespace VioletVreath {

/**
 * プリレンダ用テストアクター .
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

