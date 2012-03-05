#ifndef GAMEPRETITLESCENE_H_
#define GAMEPRETITLESCENE_H_
namespace VioletVreath {

/**
 * タイトルシーンクラス .
 * @version 1.00
 * @since 2010/11/15
 * @author Masatoshi Tsuge
 */
class GamePreTitleScene : public GgafLib::DefaultScene {

public:
    enum {
        PROG_INIT = 1,
        PROG_EXEC    ,
        PROG_FINISH  ,
    };


    LabelGecchi16Font* pStringBoard01_;
    LabelGecchi16Font* pStringBoard02_;
    TitleBoard* pTitleBoard_;
    GamePreTitleScene(const char* prm_name);
    void onReset() override;
    void initialize() override;
    void onActive() override;
    void processBehavior() override;
    virtual ~GamePreTitleScene();
};

}
#endif /*GAMEPRETITLESCENE_H_*/
