#ifndef DEFAULTD3DXANIMESHEFFECTACTOR_H_
#define DEFAULTD3DXANIMESHEFFECTACTOR_H_
namespace MyStg2nd {

/**
 * プリレンダ用テストアクター .
 * @version 1.00
 * @since 2011/04/18
 * @author Masatoshi Tsuge
 */
class DefaultD3DXAniMeshEffectActor : public GgafDx9LibStg::DefaultD3DXAniMeshActor {

public:

    DefaultD3DXAniMeshEffectActor(const char* prm_name);

    virtual ~DefaultD3DXAniMeshEffectActor();

};

}
#endif /*DEFAULTD3DXANIMESHEFFECTACTOR_H_*/

