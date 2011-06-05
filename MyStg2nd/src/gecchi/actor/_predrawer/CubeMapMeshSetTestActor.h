#ifndef CUBEMAPMESHSETEFFECTACTOR_H_
#define CUBEMAPMESHSETEFFECTACTOR_H_
namespace MyStg2nd {

/**
 * プリレンダ用テストアクター .
 * @version 1.00
 * @since 2011/04/18
 * @author Masatoshi Tsuge
 */
class CubeMapMeshSetTestActor : public GgafDx9LibStg::CubeMapMeshSetActor {

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

