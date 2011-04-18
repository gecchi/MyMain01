#ifndef CUBEMAPMORPHMESHEFFECTACTOR_H_
#define CUBEMAPMORPHMESHEFFECTACTOR_H_
namespace MyStg2nd {

/**
 * プリレンダ用テストアクター .
 * @version 1.00
 * @since 2011/04/18
 * @author Masatoshi Tsuge
 */
class CubeMapMorphMeshEffectActor : public GgafDx9LibStg::CubeMapMorphMeshActor {

public:

    CubeMapMorphMeshEffectActor(const char* prm_name);

    virtual ~CubeMapMorphMeshEffectActor();

};

}
#endif /*CUBEMAPMORPHMESHEFFECTACTOR_H_*/

