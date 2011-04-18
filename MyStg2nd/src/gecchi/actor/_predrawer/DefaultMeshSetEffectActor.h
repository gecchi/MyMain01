#ifndef DEFAULTMESHSETEFFECTACTOR_H_
#define DEFAULTMESHSETEFFECTACTOR_H_
namespace MyStg2nd {

/**
 * プリレンダ用テストアクター .
 * @version 1.00
 * @since 2011/04/18
 * @author Masatoshi Tsuge
 */
class DefaultMeshSetEffectActor : public GgafDx9LibStg::DefaultMeshSetActor {

public:

    DefaultMeshSetEffectActor(const char* prm_name);

    virtual ~DefaultMeshSetEffectActor();

};

}
#endif /*DEFAULTMESHSETEFFECTACTOR_H_*/

