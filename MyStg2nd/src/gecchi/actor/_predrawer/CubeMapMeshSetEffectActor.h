#ifndef CUBEMAPMESHSETEFFECTACTOR_H_
#define CUBEMAPMESHSETEFFECTACTOR_H_
namespace MyStg2nd {

/**
 * プリレンダ用テストアクター .
 * @version 1.00
 * @since 2011/04/18
 * @author Masatoshi Tsuge
 */
class CubeMapMeshSetEffectActor : public GgafDx9LibStg::CubeMapMeshSetActor {

public:

    CubeMapMeshSetEffectActor(const char* prm_name);

    virtual ~CubeMapMeshSetEffectActor();

};

}
#endif /*CUBEMAPMESHSETEFFECTACTOR_H_*/

