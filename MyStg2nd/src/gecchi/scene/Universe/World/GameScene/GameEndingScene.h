#ifndef GAMEENDINGSCENE_H_
#define GAMEENDINGSCENE_H_

#define GAMEENDING_SCENE_PROG_INIT   1
#define GAMEENDING_SCENE_PROG_BEGIN  2
#define GAMEENDING_SCENE_PROG_OPE    3
#define GAMEENDING_SCENE_PROG_DECIDE 4
#define GAMEENDING_SCENE_PROG_END    5



namespace MyStg2nd {

class GameEndingScene : public GgafDx9LibStg::DefaultScene {

public:

    GameEndingScene(const char* prm_name);
    void reset();
    void ready();
   virtual void initialize() override;
    virtual void processBehavior() override;
    virtual void processFinal() override;
    virtual ~GameEndingScene();
};

}
#endif /*GAMEENDINGSCENE_H_*/
