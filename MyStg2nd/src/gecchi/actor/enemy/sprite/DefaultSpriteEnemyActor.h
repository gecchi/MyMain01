#ifndef DEFAULTSPRITEENEMYACTOR_H_
#define DEFAULTSPRITEENEMYACTOR_H_
namespace MyStg2nd {


class DefaultSpriteEnemyActor : public GgafDx9LibStg::DefaultSpriteSetActor {

public:
    DefaultSpriteEnemyActor(const char* prm_name, const char* prm_model);

    virtual ~DefaultSpriteEnemyActor();
};

}
#endif /*DEFAULTSPRITEENEMYACTOR_H_*/

