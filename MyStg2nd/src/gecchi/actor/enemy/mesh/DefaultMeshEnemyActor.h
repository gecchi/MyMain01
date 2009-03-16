#ifndef DEFAULTMESHENEMYACTOR_H_
#define DEFAULTMESHENEMYACTOR_H_
namespace MyStg2nd {

class DefaultMeshEnemyActor : public GgafDx9LibStg::DefaultMeshActor {

public:
    DefaultMeshEnemyActor(const char* prm_name, const char* prm_model, const char* prm_technique);

    virtual ~DefaultMeshEnemyActor();
};

}
#endif /*DEFAULTMESHENEMYACTOR_H_*/

