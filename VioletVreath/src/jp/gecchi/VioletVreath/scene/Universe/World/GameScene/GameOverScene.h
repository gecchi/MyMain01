#ifndef GAMEOVERSCENE_H_
#define GAMEOVERSCENE_H_
namespace VioletVreath {

class GameOverScene : public GgafLib::DefaultScene {

public:
    enum {
        PROG_INIT = 1,
        PROG_DISP    ,
        PROG_FINISH  ,
    };

    LabelGecchi16Font* pLabel01_;
    GameOverScene(const char* prm_name);
    void onReset() override;
    virtual void initialize() override;
    virtual void processBehavior() override;
    virtual ~GameOverScene();
};

}
#endif /*GAMEOVERSCENE_H_*/
