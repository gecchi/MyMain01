#ifndef MENUBOARDPAUSE_H_
#define MENUBOARDPAUSE_H_

namespace MyStg2nd {

/**
 * ポーズ時メニュー .
 * @version 1.00
 * @since 2011/12/20
 * @author Masatoshi Tsuge
 */
class MenuBoardPause : public MenuBoard {

public:

    /**
     *
     * @param prm_name
     * @param prm_pAmount config済みの AmountGraphオブジェクトの参照
     */
    MenuBoardPause(const char* prm_name);

    bool condMoveCursorNext() override;
    bool condMoveCursorPrev() override;
    bool condMoveCursorExNext() override;
    bool condMoveCursorExPrev() override;
    void onDecision(GgafDxCore::GgafDxDrawableActor* prm_pItem, int prm_item_index) override;

    virtual ~MenuBoardPause();
};

}
#endif /*ENAGYBAR_H_*/

