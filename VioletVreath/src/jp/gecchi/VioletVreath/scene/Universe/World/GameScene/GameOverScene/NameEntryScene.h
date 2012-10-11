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
        PROG_PRE_DISP ,
        PROG_INPUT    ,
        PROG_DONE_DISP,
        PROG_FINISH   ,
    };

    LabelGecchi16Font* pLabel01_;

    LabelGecchi32Font* pLabelInputedName_;
    LabelGecchi32Font* pLabelSelectedChar_;

    MenuBoardNameEntry* pNameEntryBoard_;
    std::string inputed_name_;
    NameEntryScene(const char* prm_name);
    void onReset() override;
    virtual void initialize() override;
    virtual void processBehavior() override;
    virtual void onCatchEvent(hashval prm_no, void* prm_pSource) override;
    virtual ~NameEntryScene();
};

}
#endif /*GAMEOVERSCENE_H_*/
