#ifndef WORLD_H_
#define WORLD_H_

//getParent getSub �}�N���B
//���L�}�N���g�p����ɂ́A�V�[���I�u�W�F�N�g�̖��O���A
//�N���X�����疖����"Scene"�Ƃ������������苎�������̂ł��邱�Ƃ��O������ł�
#define getParentScene(X) ((X##Scene*)getParent(#X))
#define getSubScene(X) ((X##Scene*)getSub(#X))


class World : public GgafDx9LibStg::DefaultWorld {


public:
	World(string prm_name);

	/**
	 * ��������
	 */
	void initialize() {};

 	/**
	 * ��OverRide �ł���
	 */
	void processBehavior() {};

 	/**
	 * ��OverRide �ł���
	 */
	void processJudgement() {};

	/**
	 * �J�����𑀍�
	 * ��OverRide �ł���
	 */
	void processDrawPrior();

	virtual ~World();
};

#endif /*WORLD_H_*/
