#ifndef STAGEDEBUGPARTCONTROLLER_H_
#define STAGEDEBUGPARTCONTROLLER_H_
#include "VioletVreath.h"
#include "../Stage/StagePartController.h"

namespace VioletVreath {

DECLARE_HASHVAL(EVENT_STAGEDEBUG_PART_01_WAS_FINISHED);
DECLARE_HASHVAL(EVENT_STAGEDEBUG_PART_02_WAS_FINISHED);
DECLARE_HASHVAL(EVENT_STAGEDEBUG_PART_03_WAS_FINISHED);
DECLARE_HASHVAL(EVENT_STAGEDEBUG_PART_WALL_WAS_FINISHED);
DECLARE_HASHVAL(EVENT_STAGEDEBUG_PART_CLIMAX_WAS_FINISHED);

/**
 * ステージ１コントローラー .
 * @version 1.00
 * @since 2018/09/18
 * @author Masatoshi Tsuge
 */
class StageDebugPartController : public StagePartController {

public:
    StageDebugPartController(const char* prm_name);
    /**
     * 初期処理
     */
    void initialize() override;

    virtual void processBehavior() override;

    virtual void onCatchEvent(hashval prm_no, void* prm_pSource) override;

    virtual ~StageDebugPartController();
};

}
#endif /*STAGEDEBUGPARTCONTROLLER_H_*/
