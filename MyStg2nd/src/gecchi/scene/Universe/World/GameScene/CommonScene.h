#ifndef MYSHIPSCENE_H_
#define MYSHIPSCENE_H_
namespace MyStg2nd {

#define pMYSHIP (GameGlobal::_pMyShip)

/**
 * 共通シーンクラス .
 * 2008/9/8
 */
class CommonScene : public GgafDx9LibStg::DefaultScene {

public:
    MyShip* _pMyShip;

    GgafCore::GgafActorDispatcher* _pDispatcher_EnemyShots001;
    GgafCore::GgafActorDispatcher* _pDispatcher_EffectExplosion001;
    GgafCore::GgafActorDispatcher* _pDispatcher_EffectExplosion003;
    GgafCore::GgafActorDispatcher* _pDispatcher_LaserChipDispatcher;
    GgafCore::GgafActorDispatcher* _pDispatcher_EffectTurbo002;



    CommonScene(const char* prm_name);
    /**
     * 初期処理
     */
    void initialize() override;

    virtual void processBehavior() override;

    virtual ~CommonScene();
};

}
#endif /*MYSHIPSCENE_H_*/
