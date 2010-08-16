#ifndef GAMEDEMOSCENE_H_
#define GAMEDEMOSCENE_H_

#define GAMEDEMO_PROG_INIT              1
#define GAMEDEMO_PROG_BEGIN             2
#define GAMEDEMO_PROG_TITLE             3
#define GAMEDEMO_PROG_DEMOPLAY          4
#define GAMEDEMO_PROG_RANKING           5
#define GAMEDEMO_PROG_DECIDE  6
#define GAMEDEMO_PROG_END     7

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

    UINT32 _frame_Begin;
    UINT32 _frame_Title;
    UINT32 _frame_Demoplay;
    UINT32 _frame_Ranking;
    UINT32 _frame_Decide;
    UINT32 _frame_End;

    GameDemoScene(const char* prm_name);
    void reset();
    void ready();

    void initialize() override;
    virtual void processBehavior() override;
    virtual void processFinal() override;
    virtual ~GameDemoScene();
};

}
#endif /*GAMEDEMOSCENE_H_*/
