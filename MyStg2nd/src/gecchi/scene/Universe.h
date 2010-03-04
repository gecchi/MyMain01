#ifndef UNIVERSE_H_
#define UNIVERSE_H_
namespace MyStg2nd {

//getParent getSub ������ �L���X�g�}�N���B
//���L�}�N���g�p����ɂ́A�I�u�W�F�N�g�̎��ʖ����A
//�N���X���̖�����"...Scene"�Ƃ������������苎�������̂ł��邱�Ƃ��O������ł�
#define getParentScene(X) ((X##Scene*)getParent(#X))
#define getSubScene(X) ((X##Scene*)getSub(#X))
#define getParentActor(X) ((X##Actor*)getParent(#X))
#define getSubActor(X) ((X##Actor*)getSub(#X))

#define pWORLD (((Universe*)(GgafGod::_pGod->_pUniverse))->_pWorld)
/**
 * ���̐��V�[�� .
 * �܂����̐�������܂����B<BR>
 * �{�N���X�́A���̐��̐U�镑�������������Ă��܂��B<BR>
 */
class Universe : public GgafDx9LibStg::DefaultUniverse {

public:

    World* _pWorld;

    Universe(const char* prm_name);

    /**
     * ��������
     */
    void initialize() override;

     /**
     * ��OverRide �ł���
     */
    void processBehavior() override;

     /**
     * ��OverRide �ł���
     */
    void processJudgement() override;

    virtual ~Universe();
};

}
#endif /*UNIVERSE_H_*/
