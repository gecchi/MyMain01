#ifndef GAMEDEMOSCENE_H_
#define GAMEDEMOSCENE_H_

#define GAMEDEMO_SCENE_PROG_INIT              1
#define GAMEDEMO_SCENE_PROG_BEGIN             2
#define GAMEDEMO_SCENE_PROG_TITLE             3
#define GAMEDEMO_SCENE_PROG_DEMOPLAY          4
#define GAMEDEMO_SCENE_PROG_RANKING           5
#define GAMEDEMO_SCENE_PROG_DECIDE  6

namespace MyStg2nd {


/**
 * ゲームデモシーンクラス .
 * ゲームが行なわれている場面と言っても、ゲームデモが行なわれている場合もありました。
 * @version 1.00
 * @since 2007/11/16
 * @author Masatoshi Tsuge
 */
class GameDemoScene : public GgafDx9LibStg::DefaultScene {

public:

    LabelGecchi16Font* _pStringBoard01;
    LabelGecchi16Font* _pStringBoard02;

    frame _frame_Begin;
    frame _frame_Title;
    frame _frame_Demoplay;
    frame _frame_Ranking;
    frame _frame_Decide;
    frame _frame_End;

    GameDemoScene(const char* prm_name);
    void reset() override;
//    void ready();

    void initialize() override;
    void onActive() override;
    void processBehavior() override;
    void processFinal() override;
    virtual ~GameDemoScene();
};

}
#endif /*GAMEDEMOSCENE_H_*/
