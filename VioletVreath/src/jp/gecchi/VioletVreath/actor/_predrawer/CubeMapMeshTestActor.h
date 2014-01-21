#ifndef CUBEMAPMESHEFFECTACTOR_H_
#define CUBEMAPMESHEFFECTACTOR_H_
#include "jp/ggaf/lib/actor/CubeMapMeshActor.h"

namespace VioletVreath {

/**
 * プリロード用テストアクター .
 * @version 1.00
 * @since 2011/04/18
 * @author Masatoshi Tsuge
 */
class CubeMapMeshTestActor : public GgafLib::CubeMapMeshActor {

public:

    CubeMapMeshTestActor(const char* prm_name);

    void onCreateModel() override;

    void initialize() override;

    void onActive() override;

    void processBehavior() override;

    virtual ~CubeMapMeshTestActor();

};

}
#endif /*CUBEMAPMESHEFFECTACTOR_H_*/

