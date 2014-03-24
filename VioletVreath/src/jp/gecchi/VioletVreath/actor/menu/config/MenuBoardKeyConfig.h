#ifndef MENUBOARDKEYCONFIG_H_
#define MENUBOARDKEYCONFIG_H_
#include "jp/gecchi/VioletVreath/actor/menu/MenuBoard.h"

namespace VioletVreath {

/**
 * �L�[�R���t�B�O���j���[ .
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
    };

    int ITEM_INDEX_OK_;
    int ITEM_INDEX_CANCEL_;

    struct VBProperty {
        LabelFix16Font01* pKey;
        LabelFix16Font01* pJoy;
    };
    VBProperty* paVBProperties;
public:
    MenuBoardKeyConfig(const char* prm_name);

    bool condSelectNext() override;
    bool condSelectPrev() override;
    void onRise() override;
    void onDecision(GgafDxCore::GgafDxDrawableActor* prm_pItem, int prm_item_index) override;
    void onCancel(GgafDxCore::GgafDxDrawableActor* prm_pItem, int prm_item_index) override;
    void processBehavior() override;

    virtual ~MenuBoardKeyConfig();
};

}
#endif /*MENUBOARDKEYCONFIG_H_*/
