#ifndef GAMEOVERSCENE_H_
#define GAMEOVERSCENE_H_
namespace MyStg2nd {

class GameOverScene : public GgafLib::DefaultScene {

public:
    enum {
        PROG_INIT = 1,
        PROG_DISP    ,
        PROG_FINISH  ,
    };

    LabelGecchi16Font* _pStringBoard01;
    GameOverScene(const char* prm_name);
    void onReset() override;
    virtual void initialize() override;
    virtual void processBehavior() override;
    virtual ~GameOverScene();
};

}
#endif /*GAMEOVERSCENE_H_*/
