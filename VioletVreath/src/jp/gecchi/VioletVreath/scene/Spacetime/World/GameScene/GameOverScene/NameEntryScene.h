#ifndef NAMEENTRYSCENE_H_
#define NAMEENTRYSCENE_H_
#include "VioletVreath.h"

#include "jp/gecchi/VioletVreath/scene/VvScene.hpp"
#include "jp/ggaf/lib/scene/DefaultScene.h"

namespace VioletVreath {

/**
 * �l�[���G���g���[ .
 * @version 1.00
 * @since 2012/10/04
 * @author Masatoshi Tsuge
 */
class NameEntryScene : public VvScene<GgafLib::DefaultScene> {

public:
    WorldBoundNameEntry* pWorldBound_;

    LabelGecchi16Font* pLabel01_;

    SpriteLabelGecchi32Font* pLabelInputedName_;
    SpriteLabelGecchi32Font* pLabelSelectedChar_;

    MenuBoardNameEntry* pNameEntryBoard_;
    std::string inputed_name_;

public:
    NameEntryScene(const char* prm_name);
    void onReset() override;
    virtual void initialize() override;
    virtual void processBehavior() override;
    virtual void onCatchEvent(hashval prm_no, void* prm_pSource) override;
    virtual ~NameEntryScene();
};

}
#endif /*GAMEOVERSCENE_H_*/
