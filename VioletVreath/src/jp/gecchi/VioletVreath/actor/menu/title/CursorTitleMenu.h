#ifndef CURSORTITLEMENU_H_
#define CURSORTITLEMENU_H_


namespace VioletVreath {

/**
 * ÉJÅ[É\ÉãÇªÇÃÇP .
 * @version 1.00
 * @since 2011/04/07
 * @author Masatoshi Tsuge
 */
class CursorTitleMenu : public GgafLib::DefaultBoardActor {

public:
    CursorTitleMenu(const char* prm_name);

    void initialize() override;

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;

    virtual ~CursorTitleMenu();
};

}
#endif /*CURSORTITLEMENU_H_*/

