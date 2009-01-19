#ifndef DEFAULTMESHENEMYACTOR_H_
#define DEFAULTMESHENEMYACTOR_H_
namespace MyStg2nd {


class DefaultMeshEnemyActor : public GgafDx9LibStg::DefaultMeshActor {

public:
	DefaultMeshEnemyActor(string prm_name, string prm_model);

	virtual ~DefaultMeshEnemyActor();
};

}
#endif /*DEFAULTMESHENEMYACTOR_H_*/

