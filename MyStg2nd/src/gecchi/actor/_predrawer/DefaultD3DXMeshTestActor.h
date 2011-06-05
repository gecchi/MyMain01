#ifndef DEFAULTD3DXMESHEFFECTACTOR_H_
#define DEFAULTD3DXMESHEFFECTACTOR_H_
namespace MyStg2nd {

/**
 * プリレンダ用テストアクター .
 * @version 1.00
 * @since 2011/04/18
 * @author Masatoshi Tsuge
 */
class DefaultD3DXMeshTestActor : public GgafDx9LibStg::DefaultD3DXMeshActor {

public:

    DefaultD3DXMeshTestActor(const char* prm_name);

    virtual ~DefaultD3DXMeshTestActor();

};

}
#endif /*DEFAULTD3DXMESHEFFECTACTOR_H_*/

