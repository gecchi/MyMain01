#ifndef DEFAULTSPRITEENEMYACTOR_H_
#define DEFAULTSPRITEENEMYACTOR_H_
namespace MyStg2nd {


class DefaultSpriteEnemyActor : public GgafDx9LibStg::DefaultSpriteActor {

public:
	DefaultSpriteEnemyActor(const char* prm_name, const char* prm_model, const char* prm_technique);

	virtual ~DefaultSpriteEnemyActor();
};

}
#endif /*DEFAULTSPRITEENEMYACTOR_H_*/

