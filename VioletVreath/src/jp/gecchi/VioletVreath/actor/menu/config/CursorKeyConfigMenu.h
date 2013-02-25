#ifndef CURSORKEYCONFIGMENU_H_
#define CURSORKEYCONFIGMENU_H_


namespace VioletVreath {

/**
 * キーコンフィグのカーソル .
 * @version 1.00
 * @since 2013/02/18
 * @author Masatoshi Tsuge
 */
class CursorKeyConfigMenu : public GgafLib::DefaultBoardActor {

public:
    CursorKeyConfigMenu(const char* prm_name);

    void initialize() override;

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;

    virtual ~CursorKeyConfigMenu();
};

}
#endif /*CURSORKEYCONFIGMENU_H_*/

