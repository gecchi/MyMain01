#ifndef DEFAULTPRIMITIVEENEMYACTOR_H_
#define DEFAULTPRIMITIVEENEMYACTOR_H_
namespace MyStg2nd {

class DefaultPrimitiveEnemyActor : public GgafDx9LibStg::DefaultMeshActor {

public:
    DefaultPrimitiveEnemyActor(const char* prm_name, const char* prm_model, const char* prm_technique);

    virtual ~DefaultPrimitiveEnemyActor();
};

}
#endif /*DEFAULTPRIMITIVEENEMYACTOR_H_*/

