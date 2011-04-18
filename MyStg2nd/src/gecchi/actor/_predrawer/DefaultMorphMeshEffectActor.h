#ifndef DEFAULTMORPHMESHEFFECTACTOR_H_
#define DEFAULTMORPHMESHEFFECTACTOR_H_
namespace MyStg2nd {

/**
 * プリレンダ用テストアクター .
 * @version 1.00
 * @since 2011/04/18
 * @author Masatoshi Tsuge
 */
class DefaultMorphMeshEffectActor : public GgafDx9LibStg::DefaultMorphMeshActor {

public:

    DefaultMorphMeshEffectActor(const char* prm_name);

    virtual ~DefaultMorphMeshEffectActor();

};

}
#endif /*DEFAULTMESHEFFECTACTOR_H_*/

