#ifndef CUBEMAPMESHSETEFFECTACTOR_H_
#define CUBEMAPMESHSETEFFECTACTOR_H_
#include "jp/ggaf/lib/actor/CubeMapMeshSetActor.h"

namespace VioletVreath {

/**
 * プリレンダ用テストアクター .
 * @version 1.00
 * @since 2011/04/18
 * @author Masatoshi Tsuge
 */
class CubeMapMeshSetTestActor : public GgafLib::CubeMapMeshSetActor {

public:
    CubeMapMeshSetTestActor(const char* prm_name);

    void onCreateModel() override;

    void initialize() override;

    void onActive() override;

    void processBehavior() override;

    virtual ~CubeMapMeshSetTestActor();

};

}
#endif /*CUBEMAPMESHSETEFFECTACTOR_H_*/

