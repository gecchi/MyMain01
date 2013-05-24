#ifndef DEFAULTMORPHMESHEFFECTACTOR_H_
#define DEFAULTMORPHMESHEFFECTACTOR_H_
#include "jp/ggaf/lib/actor/DefaultMorphMeshActor.h"

namespace VioletVreath {

/**
 * プリレンダ用テストアクター .
 * @version 1.00
 * @since 2011/04/18
 * @author Masatoshi Tsuge
 */
class DefaultMorphMeshTestActor : public GgafLib::DefaultMorphMeshActor {

public:

    DefaultMorphMeshTestActor(const char* prm_name);

    virtual ~DefaultMorphMeshTestActor();

};

}
#endif /*DEFAULTMESHEFFECTACTOR_H_*/

