#ifndef DEFAULTPRIMITIVEENEMYACTOR_H_
#define DEFAULTPRIMITIVEENEMYACTOR_H_
namespace MyStg2nd {

class DefaultPrimitiveEnemyActor : public GgafDx9LibStg::DefaultPrimitiveActor {

public:
    DefaultPrimitiveEnemyActor(const char* prm_name, const char* prm_model, const char* prm_effect);

    virtual ~DefaultPrimitiveEnemyActor();
};

}
#endif /*DEFAULTPRIMITIVEENEMYACTOR_H_*/

