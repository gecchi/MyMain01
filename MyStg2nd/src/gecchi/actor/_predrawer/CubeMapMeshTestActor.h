#ifndef CUBEMAPMESHEFFECTACTOR_H_
#define CUBEMAPMESHEFFECTACTOR_H_
namespace MyStg2nd {


/**
 * プリレンダ用テストアクター .
 * @version 1.00
 * @since 2011/04/18
 * @author Masatoshi Tsuge
 */
class CubeMapMeshTestActor : public GgafDx9LibStg::CubeMapMeshActor {

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

