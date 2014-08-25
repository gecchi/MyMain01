#ifndef DEFAULTMESHSETEFFECTACTOR_H_
#define DEFAULTMESHSETEFFECTACTOR_H_
#include "VioletVreath.h"
#include "jp/ggaf/lib/actor/DefaultMeshSetActor.h"

namespace VioletVreath {

/**
 * プリロード用テストアクター .
 * @version 1.00
 * @since 2011/04/18
 * @author Masatoshi Tsuge
 */
class DefaultMeshSetTestActor : public GgafLib::DefaultMeshSetActor {

public:

    DefaultMeshSetTestActor(const char* prm_name);

    virtual ~DefaultMeshSetTestActor();

};

}
#endif /*DEFAULTMESHSETEFFECTACTOR_H_*/

