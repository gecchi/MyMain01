#ifndef NAMEENTRYSCENE_H_
#define NAMEENTRYSCENE_H_
namespace VioletVreath {

/**
 * ネームエントリー .
 * @version 1.00
 * @since 2012/10/04
 * @author Masatoshi Tsuge
 */
class NameEntryScene : public GgafLib::DefaultScene {

public:
    enum {
        PROG_INIT = 1,
        PROG_DISP    ,
        PROG_INPUT   ,
        PROG_FINISH  ,
    };

    LabelGecchi16Font* pLabel01_;
    MenuBoardNameEntry* pMenu_;
    NameEntryScene(const char* prm_name);
    void onReset() override;
    virtual void initialize() override;
    virtual void processBehavior() override;
    virtual ~NameEntryScene();
};

}
#endif /*GAMEOVERSCENE_H_*/
