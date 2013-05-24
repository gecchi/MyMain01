#ifndef DEFAULTSPRITEEFFECTACTOR_H_
#define DEFAULTSPRITEEFFECTACTOR_H_
#include "jp/ggaf/lib/actor/DefaultSpriteActor.h"

namespace VioletVreath {

/**
 * プリレンダ用テストアクター .
 * @version 1.00
 * @since 2011/04/18
 * @author Masatoshi Tsuge
 */
class DefaultSpriteTestActor : public GgafLib::DefaultSpriteActor {

public:

    DefaultSpriteTestActor(const char* prm_name);

    virtual ~DefaultSpriteTestActor();

};

}
#endif /*DEFAULTSPRITEEFFECTACTOR_H_*/

