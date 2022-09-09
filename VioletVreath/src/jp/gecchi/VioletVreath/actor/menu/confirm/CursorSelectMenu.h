#ifndef CURSORSELECTMENU_H_
#define CURSORSELECTMENU_H_
#include "VioletVreath.h"
#include "jp/ggaf/lib/actor/DefaultBoardActor.h"

namespace VioletVreath {

/**
 * �I�����j���[�J�[�\���i�쐬���j
 * @version 1.00
 * @since 2022/08/04
 * @author Masatoshi Tsuge
 */
class CursorSelectMenu : public GgafLib::DefaultBoardActor {

public:
    CursorSelectMenu(const char* prm_name);

    void initialize() override;

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;

    virtual ~CursorSelectMenu();
};

}
#endif /*CURSORSELECTMENU_H_*/

