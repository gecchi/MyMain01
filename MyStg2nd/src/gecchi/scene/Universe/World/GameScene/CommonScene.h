#ifndef COMMONSCENE_H_
#define COMMONSCENE_H_


#ifdef pGAMESCENE
    #define pCOMMON_SCENE (pGAMESCENE->_pCommonScene)
#else
    #error pGAMESCENE isnt define
#endif


namespace MyStg2nd {

/**
 * ���ʃV�[���N���X .
 * 2008/9/8
 */
class CommonScene : public GgafDx9LibStg::DefaultScene {

public:

    GgafCore::GgafActorDispatcher* _pDispatcher_EnemyShots001;
    GgafCore::GgafActorDispatcher* _pDispatcher_EffectExplosion001;
    GgafCore::GgafActorDispatcher* _pDispatcher_EffectExplosion003;
    GgafCore::GgafActorDispatcher* _pDispatcher_LaserChipDispatcher;
    GgafCore::GgafActorDispatcher* _pDispatcher_EffectTurbo002;



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
