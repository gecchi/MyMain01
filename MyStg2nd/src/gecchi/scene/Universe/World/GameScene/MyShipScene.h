#ifndef MYSHIPSCENE_H_
#define MYSHIPSCENE_H_


#ifdef P_GAME_SCENE
    #define P_MYSHIP_SCENE (P_GAME_SCENE->_pMyShipScene)
    #define P_MYSHIP (P_MYSHIP_SCENE->_pMyShip)
    #define P_MYOPTIONCON (P_MYSHIP_SCENE->_pMyOptionController)
    #define P_VAM (P_MYSHIP_SCENE->_pVamSysCamWorker)
#else
    #error P_GAME_SCENE isnt define
#endif

#define MYSHIPSCENE_SCENE_PROG_INIT     1
#define MYSHIPSCENE_SCENE_PROG_BEGIN    2
#define MYSHIPSCENE_SCENE_PROG_PLAY     3
#define MYSHIPSCENE_SCENE_PROG_DESTROY  4
#define MYSHIPSCENE_SCENE_PROG_END      5


namespace MyStg2nd {

/**
 * ���ʃV�[���N���X .
 * 2008/9/8
 */
class MyShipScene : public GgafDx9LibStg::DefaultScene {

public:
    /** ���@ */
    MyShip* _pMyShip;
    /** ���@�I�v�V������ */
    MyOptionController* _pMyOptionController;
    /** ���@�����G�t�F�N�g */
    EffectMyShipExplosion* _pEffectMyShipExplosion;
    /** VAMSYSTEM �J�������[�N */
    VamSysCamWorker* _pVamSysCamWorker;
    int _zanki;

    MyShipScene(const char* prm_name);
    /**
     * ��������
     */
    void initialize() override;
    void reset() override;
    void onActive() override;
    void processBehavior() override;

    void onCatchEvent(UINT32 prm_no, void* prm_pSource) override;

    virtual ~MyShipScene();
};

}
#endif /*MYSHIPSCENE_H_*/
