#ifndef CUBEMAPMORPHMESHEFFECTACTOR_H_
#define CUBEMAPMORPHMESHEFFECTACTOR_H_
#include "jp/ggaf/lib/actor/CubeMapMorphMeshActor.h"

namespace VioletVreath {

/**
 * �v�����[�h�p�e�X�g�A�N�^�[ .
 * @version 1.00
 * @since 2011/04/18
 * @author Masatoshi Tsuge
 */
class CubeMapMorphMeshTestActor : public GgafLib::CubeMapMorphMeshActor {

public:

    CubeMapMorphMeshTestActor(const char* prm_name);

    void onCreateModel() override;

    void initialize() override;

    void onActive() override;

    void processBehavior() override;

    virtual ~CubeMapMorphMeshTestActor();

};

}
#endif /*CUBEMAPMORPHMESHEFFECTACTOR_H_*/

