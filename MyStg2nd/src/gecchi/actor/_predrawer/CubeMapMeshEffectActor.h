#ifndef CUBEMAPMESHEFFECTACTOR_H_
#define CUBEMAPMESHEFFECTACTOR_H_
namespace MyStg2nd {


/**
 * プリレンダ用テストアクター .
 * @version 1.00
 * @since 2011/04/18
 * @author Masatoshi Tsuge
 */
class CubeMapMeshEffectActor : public GgafDx9LibStg::CubeMapMeshActor {

public:

    CubeMapMeshEffectActor(const char* prm_name);

    void onCreateModel() override;

    void initialize() override;

    void onActive() override;

    void processBehavior() override;

    virtual ~CubeMapMeshEffectActor();

};

}
#endif /*CUBEMAPMESHEFFECTACTOR_H_*/

