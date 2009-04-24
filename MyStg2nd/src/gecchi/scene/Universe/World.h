#ifndef WORLD_H_
#define WORLD_H_
namespace MyStg2nd {

//getParent getSub ������ �L���X�g�}�N���B
//���L�}�N���g�p����ɂ́A�I�u�W�F�N�g�̎��ʖ����A
//�N���X���̖�����"...Scene"�Ƃ������������苎�������̂ł��邱�Ƃ��O������ł�
#define getParentScene(X) ((X##Scene*)getParent(#X))
#define getSubScene(X) ((X##Scene*)getSub(#X))
#define getParentActor(X) ((X##Actor*)getParent(#X))
#define getSubActor(X) ((X##Actor*)getSub(#X))

/**
 * ���E�N���X
 * ���̐��ɃQ�[�����s�Ȃ��Ă��鐢�E������܂����B
 */
class World : public GgafDx9LibStg::DefaultScene {


public:

	World(const char* prm_name);

	/**
	 * ��������
	 */
	void initialize();

 	/**
	 * ��OverRide �ł���
	 */
	void processBehavior();

 	/**
	 * ��OverRide �ł���
	 */
	void processJudgement();

	/**
	 * �J�����𑀍�
	 * ��OverRide �ł���
	 */
	void processDrawPrior();

	virtual ~World();
};

}
#endif /*WORLD_H_*/
