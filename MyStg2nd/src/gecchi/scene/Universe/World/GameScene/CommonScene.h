#ifndef MYSHIPSCENE_H_
#define MYSHIPSCENE_H_
namespace MyStg2nd {

/**
 * ゲームシーンの共通シーンクラス .
 */
class CommonScene : public GgafDx9LibStg::DefaultScene {

public:
    MyShip* _pMyShip;

    GgafDx9LibStg::RotationActor* _pEnemyShots001Rotation;
    GgafDx9LibStg::RotationActor* _pEffectExplosion001Rotation;

    CommonScene(const char* prm_name);
    /**
     * 初期処理
     */
    void initialize();

    virtual void processBehavior();

    virtual ~CommonScene();
};

}
#endif /*MYSHIPSCENE_H_*/
