#ifndef DEFAULTSPRITEMYACTOR_H_
#define DEFAULTSPRITEMYACTOR_H_
namespace MyStg2nd {


class DefaultSpriteMyActor : public GgafDx9LibStg::DefaultSpriteActor {

public:
	DefaultSpriteMyActor(std::string prm_name, std::string prm_model);

	virtual ~DefaultSpriteMyActor();
};

}
#endif /*DEFAULTSPRITEMYACTOR_H_*/

