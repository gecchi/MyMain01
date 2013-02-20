#ifndef MENUBOARDKEYCONFIG_H_
#define MENUBOARDKEYCONFIG_H_

namespace VioletVreath {

/**
 * キーコンフィグメニュー .
 * @version 1.00
 * @since 2013/02/18
 * @author Masatoshi Tsuge
 */
class MenuBoardKeyConfig : public MenuBoard {

public:
    enum {
        ITEM_MAIN_SHOT = 0,
        ITEM_SUB_SHOT  ,
        ITEM_TURBO     ,
        ITEM_CONTROLL  ,
        ITEM_MAGIC     ,
        ITEM_VAM       ,
        ITEM_PAUSE     ,
        ITEM_KEY_UP    ,
        ITEM_KEY_DOWN  ,
        ITEM_KEY_LEFT  ,
        ITEM_KEY_LIGHT ,
    };

    int ITEM_INDEX_OK_;
    int ITEM_INDEX_CANCEL_;

    LabelGecchi16Font** papDispKey_;
    LabelGecchi16Font** papDispJoy_;

    struct VBProperty {
        std::string key;
        std::string joy;
    };

    VBProperty* paVBProperties;
public:
    MenuBoardKeyConfig(const char* prm_name);

    bool condMoveCursorNext() override;
    bool condMoveCursorPrev() override;
    void onDecision(GgafDxCore::GgafDxDrawableActor* prm_pItem, int prm_item_index) override;
    void onCancel(GgafDxCore::GgafDxDrawableActor* prm_pItem, int prm_item_index) override;
    void processBehavior() override;

    virtual ~MenuBoardKeyConfig();
};

}
#endif /*MENUBOARDKEYCONFIG_H_*/

