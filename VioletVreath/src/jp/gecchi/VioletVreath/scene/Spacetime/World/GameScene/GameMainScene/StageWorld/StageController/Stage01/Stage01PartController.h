#ifndef STAGE01PARTCONTROLLER_H_
#define STAGE01PARTCONTROLLER_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "../Stage/StagePartController.h"

namespace VioletVreath {

DECLARE_EVENT_VAL(EVENT_STAGE01_PART_01_WAS_FINISHED);
DECLARE_EVENT_VAL(EVENT_STAGE01_PART_02_WAS_FINISHED);
DECLARE_EVENT_VAL(EVENT_STAGE01_PART_03_WAS_FINISHED);
DECLARE_EVENT_VAL(EVENT_STAGE01_PART_WALL_WAS_FINISHED);
DECLARE_EVENT_VAL(EVENT_STAGE01_PART_CLIMAX_WAS_FINISHED);

/**
 * ステージ１コントローラー .
 * @version 1.00
 * @since 2018/09/18
 * @author Masatoshi Tsuge
 */
class Stage01PartController : public StagePartController {

public:
    Stage01PartController(const char* prm_name);
    /**
     * 初期処理
     */
    void initialize() override;

    virtual void processBehavior() override;

    virtual void onCatchEvent(eventval prm_event_val, void* prm_pSource) override;

    virtual ~Stage01PartController();
};

}
#endif /*STAGE01PARTCONTROLLER_H_*/
