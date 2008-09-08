#ifndef ROTATIONACTOR_H_
#define ROTATIONACTOR_H_

/**
 * ローテーションアクタークラス .
 */
class RotationActor : public GgafDummyActor {

public:
	RotationActor(string prm_name);

	GgafActor* getFreeOne();

	virtual ~RotationActor();
};


#endif /*ROTATIONACTOR_H_*/
