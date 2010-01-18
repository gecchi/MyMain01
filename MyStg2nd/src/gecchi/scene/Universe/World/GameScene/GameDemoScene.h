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
 */
class GameDemoScene : public GgafDx9LibStg::DefaultScene {

public:

    GgafDx9Core::GgafDx9StringBoardActor* _pStringBoard01;
    GgafDx9Core::GgafDx9StringBoardActor* _pStringBoard02;

    DWORD _dwFrame_Begin;
    DWORD _dwFrame_Title;
    DWORD _dwFrame_Demoplay;
    DWORD _dwFrame_Ranking;
    DWORD _dwFrame_Decide;
    DWORD _dwFrame_End;

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
