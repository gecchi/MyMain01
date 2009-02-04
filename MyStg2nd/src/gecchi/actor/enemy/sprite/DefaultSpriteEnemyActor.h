#ifndef DEFAULTSPRITEENEMYACTOR_H_
#define DEFAULTSPRITEENEMYACTOR_H_
namespace MyStg2nd {


class DefaultSpriteEnemyActor : public GgafDx9LibStg::DefaultSpriteActor {

public:
	DefaultSpriteEnemyActor(char* prm_name, char* prm_model);

	virtual ~DefaultSpriteEnemyActor();
};

}
#endif /*DEFAULTSPRITEENEMYACTOR_H_*/

