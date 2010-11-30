#ifndef GAMEOVERSCENE_H_
#define GAMEOVERSCENE_H_

#define GAMEOVER_SCENE_PROG_INIT   1
#define GAMEOVER_SCENE_PROG_DISP   2
#define GAMEOVER_SCENE_PROG_FINISH    5



namespace MyStg2nd {

class GameOverScene : public GgafDx9LibStg::DefaultScene {

public:
    LabelGecchi16Font* _pStringBoard01;
    GameOverScene(const char* prm_name);
    void processReset() override;
    virtual void initialize() override;
    virtual void processBehavior() override;
    virtual void processFinal() override;
    virtual ~GameOverScene();
};

}
#endif /*GAMEOVERSCENE_H_*/
