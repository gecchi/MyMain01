#ifndef GAMEBEGINNINGSCENE_H_
#define GAMEBEGINNINGSCENE_H_


#define GAMEBEGINNING_PROG_INIT   1
#define GAMEBEGINNING_PROG_BEGIN  2
#define GAMEBEGINNING_PROG_OPE    3
#define GAMEBEGINNING_PROG_DECIDE 4
#define GAMEBEGINNING_PROG_END    5

namespace MyStg2nd {

class GameBeginningScene : public GgafDx9LibStg::DefaultScene {

public:
    GgafDx9LibStg::FontBoardActor* _pFontBoard01;
    GgafDx9LibStg::FontBoardActor* _pFontBoard02;

    DWORD _dwFrame_Begin;
    DWORD _dwFrame_Ope;
    DWORD _dwFrame_Decide;
    DWORD _dwFrame_End;

    int _selected_stage;

    GameBeginningScene(const char* prm_name);
    void reset();
    void ready();

    virtual void initialize();
    virtual void processBehavior();
    virtual void processFinal();
    virtual ~GameBeginningScene();
};

}
#endif /*GAMEDEMOSCENE_H_*/
