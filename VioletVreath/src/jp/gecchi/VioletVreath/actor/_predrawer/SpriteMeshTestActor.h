#ifndef SPRITEMESHEFFECTACTOR_H_
#define SPRITEMESHEFFECTACTOR_H_
#include "jp/ggaf/lib/actor/SpriteMeshActor.h"

namespace VioletVreath {

/**
 * プリレンダ用テストアクター .
 * @version 1.00
 * @since 2011/04/18
 * @author Masatoshi Tsuge
 */
class SpriteMeshTestActor : public GgafLib::SpriteMeshActor {

public:

    SpriteMeshTestActor(const char* prm_name);

    virtual ~SpriteMeshTestActor();

};

}
#endif /*SPRITEMESHEFFECTACTOR_H_*/

