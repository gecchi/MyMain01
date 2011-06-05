#ifndef DEFAULTMESHEFFECTACTOR_H_
#define DEFAULTMESHEFFECTACTOR_H_
namespace MyStg2nd {

/**
 * プリレンダ用テストアクター .
 * @version 1.00
 * @since 2011/04/18
 * @author Masatoshi Tsuge
 */
class DefaultMeshTestActor : public GgafDx9LibStg::DefaultMeshActor {

public:

    DefaultMeshTestActor(const char* prm_name);

    virtual ~DefaultMeshTestActor();

};

}
#endif /*DEFAULTMESHEFFECTACTOR_H_*/

