#ifndef MYSHIPSCENE_H_
#define MYSHIPSCENE_H_
namespace MyStg2nd {

/**
 * �Q�[���V�[���̋��ʃV�[���N���X .
 */
class CommonScene : public GgafDx9LibStg::DefaultScene {

public:
    MyShip* _pMyShip;

    GgafDx9LibStg::ActorDispatcher* _pDispatcher_EnemyShots001;
    GgafDx9LibStg::ActorDispatcher* _pDispatcher_EffectExplosion001;

    GgafDx9LibStg::ActorDispatcher* _pDispatcher_Shot001;

    CommonScene(const char* prm_name);
    /**
     * ��������
     */
    void initialize();

    virtual void processBehavior();

    virtual ~CommonScene();
};

}
#endif /*MYSHIPSCENE_H_*/
