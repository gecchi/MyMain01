#ifndef ROTATIONACTOR_H_
#define ROTATIONACTOR_H_

/**
 * ���[�e�[�V�����A�N�^�[�N���X .
 */
class RotationActor : public GgafDummyActor {

public:
	RotationActor(string prm_name);

	GgafActor* getFreeOne();

	virtual ~RotationActor();
};


#endif /*ROTATIONACTOR_H_*/
