#ifndef GAMEENDINGSCENE_H_
#define GAMEENDINGSCENE_H_
namespace MyStg2nd {

class GameEndingScene : public GgafLib::DefaultScene {

public:
    enum {
        PROG_INIT = 1,
        PROG_BEGIN   ,
        PROG_OPE     ,
        PROG_DECIDE  ,
        PROG_END     ,
    };

    GameEndingScene(const char* prm_name);
    void onReset() override;
    void ready();
    virtual void initialize() override;
    virtual void processBehavior() override;
    virtual ~GameEndingScene();
};

}
#endif /*GAMEENDINGSCENE_H_*/
