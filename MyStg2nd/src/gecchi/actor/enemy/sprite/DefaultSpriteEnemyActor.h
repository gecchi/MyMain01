#ifndef DEFAULTSPRITEENEMYACTOR_H_
#define DEFAULTSPRITEENEMYACTOR_H_
namespace MyStg2nd {


class DefaultSpriteEnemyActor : public GgafDx9LibStg::DefaultSpriteActor {

public:
	DefaultSpriteEnemyActor(std::string prm_name, std::string prm_model);

	virtual ~DefaultSpriteEnemyActor();
};

}
#endif /*DEFAULTSPRITEENEMYACTOR_H_*/

