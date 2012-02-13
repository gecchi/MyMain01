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

namespace VioletVreath {

/**
 * ���@�֘A�V�[�� .
 * @version 1.00
 * @since 2010/10/25
 * @author Masatoshi Tsuge
 */
class MyShipScene : public GgafLib::DefaultScene {

public:
    enum {
        PROG_INIT = 1,
        PROG_BEGIN   ,
        PROG_PLAY    ,
        PROG_DESTROY ,
        PROG_END
    };

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

    int _zanki;

    MyShipScene(const char* prm_name);
    /**
     * ��������
     */
    void initialize() override;
    void onReset() override;
    void onActive() override;
    void processBehavior() override;

    void onCatchEvent(hashval prm_no, void* prm_pSource) override;

    virtual ~MyShipScene();
};

}
#endif /*MYSHIPSCENE_H_*/
