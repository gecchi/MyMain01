#ifndef GAMEOVERSCENE_H_
#define GAMEOVERSCENE_H_

#define GAMEOVER_PROG_INIT   1
#define GAMEOVER_PROG_BEGIN  2
#define GAMEOVER_PROG_OPE    3
#define GAMEOVER_PROG_DECIDE 4
#define GAMEOVER_PROG_END    5



namespace MyStg2nd {

class GameOverScene : public GgafDx9LibStg::DefaultScene {

public:

    GameOverScene(const char* prm_name);
    void reset();
    void ready();
   virtual void initialize() override;
    virtual void processBehavior() override;
    virtual void processFinal() override;
    virtual ~GameOverScene();
};

}
#endif /*GAMEOVERSCENE_H_*/
