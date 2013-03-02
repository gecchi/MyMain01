#ifndef MENUBOARDCONFIRM_H_
#define MENUBOARDCONFIRM_H_


namespace VioletVreath {

/**
 * 初期選択[OK]の確認メニュー .
 * @version 1.00
 * @since 2011/12/27
 * @author Masatoshi Tsuge
 */
class MenuBoardConfirm : public MenuBoard {

public:
    enum {
        ITEM_OK = 0 ,
        ITEM_CANCEL ,
    };

public:
    MenuBoardConfirm(const char* prm_name);

    bool condSelectNext() override;
    bool condSelectPrev() override;
    bool condSelectExNext() override;
    bool condSelectrExPrev() override;

    void onRisen() override;

    void onDecision(GgafDxCore::GgafDxDrawableActor* prm_pItem, int prm_item_index) override;
    void onCancel(GgafDxCore::GgafDxDrawableActor* prm_pItem, int prm_item_index) override;

    bool wasDecidedOk();
    bool wasDecidedCancel();

    virtual ~MenuBoardConfirm();
};

}
#endif /*MENUBOARDCONFIRM_H_*/

