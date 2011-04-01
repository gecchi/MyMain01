#ifndef COMMONSCENE_H_
#define COMMONSCENE_H_


#ifdef P_GAME_SCENE
    #define P_COMMON_SCENE (P_GAME_SCENE->_pCommonScene)
#else
    #error P_GAME_SCENE isnt define
#endif


namespace MyStg2nd {

/**
 * ���ʃV�[���N���X .
 * 2008/9/8
 */
class CommonScene : public GgafDx9LibStg::DefaultScene {


public:
    /** �ėp���� */
    GgafCore::GgafActorDispatcher* _pDP_EffectExplosion001;
    GgafCore::GgafActorDispatcher* _pDispatcher_EffectTurbo002;
    GgafCore::GgafActorDispatcher* _pDP_MagicPointItem001;


    CommonScene(const char* prm_name);
    /**
     * ��������
     */
    void initialize() override;

    virtual void processBehavior() override;

    virtual ~CommonScene();
};

}
#endif /*COMMONSCENE_H_*/
