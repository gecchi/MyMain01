#ifndef DEFAULTMESHEFFECTACTOR_H_
#define DEFAULTMESHEFFECTACTOR_H_
#include "jp/ggaf/lib/actor/DefaultMeshActor.h"

namespace VioletVreath {

/**
 * プリロード用テストアクター .
 * @version 1.00
 * @since 2011/04/18
 * @author Masatoshi Tsuge
 */
class DefaultMeshTestActor : public GgafLib::DefaultMeshActor {

public:

    DefaultMeshTestActor(const char* prm_name);

    virtual ~DefaultMeshTestActor();

};

}
#endif /*DEFAULTMESHEFFECTACTOR_H_*/

