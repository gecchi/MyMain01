#ifndef CUBEMAPMORPHMESHEFFECTACTOR_H_
#define CUBEMAPMORPHMESHEFFECTACTOR_H_
namespace MyStg2nd {

/**
 * プリレンダ用テストアクター .
 * @version 1.00
 * @since 2011/04/18
 * @author Masatoshi Tsuge
 */
class CubeMapMorphMeshTestActor : public GgafDx9LibStg::CubeMapMorphMeshActor {

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

