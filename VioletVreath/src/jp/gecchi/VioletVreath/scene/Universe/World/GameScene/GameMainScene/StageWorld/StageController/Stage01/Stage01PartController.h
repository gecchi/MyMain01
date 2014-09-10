#ifndef STAGE01PARTCONTROLLER_H_
#define STAGE01PARTCONTROLLER_H_
#include "VioletVreath.h"
#include "jp/gecchi/VioletVreath/scene/Universe/World/GameScene/GameMainScene/StageWorld/StageController/Stage/StagePartController.h"

namespace VioletVreath {

HASHVAL(EVENT_STG01_01_WAS_BROKEN);
HASHVAL(EVENT_STG01_02_WAS_BROKEN);
HASHVAL(EVENT_STG01_03_WAS_BROKEN);
HASHVAL(EVENT_STG01_WALLED_WAS_BROKEN);
HASHVAL(EVENT_STG01_CLIMAX_WAS_BROKEN);


/**
 * ステージ１コントローラー .
 * @version 1.00
 * @since 2010/08/18
 * @author Masatoshi Tsuge
 */
class Stage01PartController : public StagePartController {

public:
    enum {
        PROG_INIT   ,
        PROG_FAINAL ,
        PROG_BANPEI,
    };

public:
    Stage01PartController(const char* prm_name);
    /**
     * 初期処理
     */
    void initialize() override;

    virtual void processBehavior() override;

    virtual void onCatchEvent(hashval prm_no, void* prm_pSource) override;

    virtual ~Stage01PartController();
};

}
#endif /*STAGE01PARTCONTROLLER_H_*/
