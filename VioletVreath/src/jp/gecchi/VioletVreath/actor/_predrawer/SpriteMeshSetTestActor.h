#ifndef SPRITEMESHSETEFFECTACTOR_H_
#define SPRITEMESHSETEFFECTACTOR_H_
#include "jp/ggaf/lib/actor/SpriteMeshSetActor.h"

namespace VioletVreath {

/**
 * プリロード用テストアクター .
 * @version 1.00
 * @since 2011/04/18
 * @author Masatoshi Tsuge
 */
class SpriteMeshSetTestActor : public GgafLib::SpriteMeshSetActor {

public:

    SpriteMeshSetTestActor(const char* prm_name);

    virtual ~SpriteMeshSetTestActor();

};

}
#endif /*SPRITEMESHSETEFFECTACTOR_H_*/

