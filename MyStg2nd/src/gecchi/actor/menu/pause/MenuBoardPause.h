#ifndef MENUBOARDPAUSE_H_
#define MENUBOARDPAUSE_H_
namespace MyStg2nd {

/**
 * ポーズ時メニュー .
 * @version 1.00
 * @since 2011/12/20
 * @author Masatoshi Tsuge
 */
class MenuBoardPause :
    public DefaultBoardSetMenu {

public:

    /**
     *
     * @param prm_name
     * @param prm_pAmount config済みの AmountGraphオブジェクトの参照
     */
    MenuBoardPause(const char* prm_name);

    bool condCursorNext() override;
    bool condCursorPrev() override;
    bool condCursorExNext() override;
    bool condCursorExPrev() override;
    bool condCursorCancel() override;
    void moveCursor() override;

    void initialize() override;

    void onReset() override;

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;

    void onInactive() override;


    virtual ~MenuBoardPause();
};

}
#endif /*ENAGYBAR_H_*/

