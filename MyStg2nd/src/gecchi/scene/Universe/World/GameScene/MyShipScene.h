#ifndef MYSHIPSCENE_H_
#define MYSHIPSCENE_H_


#ifdef P_MYSHIP_SCENE
    #define P_MYSHIP (P_MYSHIP_SCENE->_pMyShip)
    #define P_MYOPTIONCON (P_MYSHIP_SCENE->_pMyOptionController)
    #define P_VAM (P_MYSHIP_SCENE->_pVamSysCamWorker)
#else
    #error P_GAME_SCENE isnt define
#endif


namespace MyStg2nd {

/**
 * ���@�֘A�V�[�� .
 * @version 1.00
 * @since 2010/10/25
 * @author Masatoshi Tsuge
 */
class MyShipScene : public GgafLib::DefaultScene {

public:
    /** ���@ */
    MyShip* _pMyShip;
    /** ���@�I�v�V������ */
    MyOptionController* _pMyOptionController;
    /** ���@�����G�t�F�N�g */
    EffectMyShipExplosion* _pEffectMyShipExplosion;
    /** VAMSYSTEM �J�������[�N */
    VamSysCamWorker* _pVamSysCamWorker;

    /** ���@���[�^�[ */
    MagicMeter* _pMagicMeter;
    /** �G�l���M�[�o�[ */
    EnagyBar* _pEnagyBar;

    int _zanki;

    MyShipScene(const char* prm_name);
    /**
     * ��������
     */
    void initialize() override;
    void onReset() override;
    void onActive() override;
    void processBehavior() override;

    void onCatchEvent(UINT32 prm_no, void* prm_pSource) override;

    virtual ~MyShipScene();
};

}
#endif /*MYSHIPSCENE_H_*/
