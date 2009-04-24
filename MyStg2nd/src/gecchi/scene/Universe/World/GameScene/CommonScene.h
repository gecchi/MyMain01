#ifndef MYSHIPSCENE_H_
#define MYSHIPSCENE_H_
namespace MyStg2nd {

class CommonScene : public GgafDx9LibStg::DefaultScene {

public:
    MyShip* _pMyShip;

    GgafDx9LibStg::RotationActor* _pEnemyShots001Rotation;
    GgafDx9LibStg::RotationActor* _pEffectExplosion001Rotation;

    CommonScene(const char* prm_name);
    /**
     * èâä˙èàóù
     */
    void initialize();

    virtual void processBehavior();

    virtual ~CommonScene();
};

}
#endif /*MYSHIPSCENE_H_*/
