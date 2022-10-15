#ifndef WORLD_H_
#define WORLD_H_
#include "VioletVreath.h"

#include "jp/ggaf/lib/scene/DefaultScene.h"
#include "jp/gecchi/VioletVreath/scene/VvScene.hpp"
#include "jp/gecchi/VioletVreath/Caretaker.h"

namespace VioletVreath {

#define pMOUSEPOINTER (pCARETAKER->getSpacetime()->getWorld()->pMousePointer_)

/**
 * 世界シーンクラス .
 * アプリ上の「この世(Spacetime)」の一つ下の階層に位置します。<BR>
 */
class World : public VvScene<GgafLib::DefaultScene> {

public:
    MousePointer* pMousePointer_;

    bool is_create_GameScene_;
    char aBufDebug_[128];
    LabelGecchi16Font* pLabel_aster_;
    LabelGecchi16Font* pLabel_title_;
    LabelGecchi16Font* pLabel_debug_;
    LabelGecchi16Font* pLabel_resolution1_;
    LabelGecchi16Font* pLabel_resolution2_;
    LabelGecchi8Font*  pLabel_warn1_;
    LabelGecchi8Font*  pLabel_warn2_;
    LabelGecchi8Font*  pLabel_warn_dual_view_;

    int need_reboot_;
    int need_reboot_prev_;
    LabelGecchi16Font* pLabel_need_reboot_;
    PreDrawScene* pPreDrawScene_;
    GameScene* pGameScene_;

    frame hide_cursor_cnt_;
    bool is_show_cursor_;
public:
    World(const char* prm_name);

    /**
     * 初期処理
     */
    void initialize() override;

    void processBehavior() override;

    void showCursor(bool prm_bool) {
        if (prm_bool) {
            if (is_show_cursor_) {
                return;
            } else {
                is_show_cursor_ = prm_bool;
                while (ShowCursor(TRUE) < 0) {}
            }
        } else {
            if (!is_show_cursor_) {
                return;
            } else {
                is_show_cursor_ = prm_bool;
                while (ShowCursor(FALSE) >= 0) {}
            }
        }
    }
    virtual ~World();
};

}
#endif /*WORLD_H_*/
