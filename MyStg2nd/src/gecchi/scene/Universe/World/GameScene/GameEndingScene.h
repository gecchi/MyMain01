#ifndef GAMEENDINGSCENE_H_
#define GAMEENDINGSCENE_H_
namespace MyStg2nd {

class GameEndingScene : public GgafDx9LibStg::DefaultScene {

public:

    GameEndingScene(const char* prm_name);
    void onReset() override;
    void ready();
    virtual void initialize() override;
    virtual void processBehavior() override;
    virtual void processFinal() override;
    virtual ~GameEndingScene();
};

}
#endif /*GAMEENDINGSCENE_H_*/
