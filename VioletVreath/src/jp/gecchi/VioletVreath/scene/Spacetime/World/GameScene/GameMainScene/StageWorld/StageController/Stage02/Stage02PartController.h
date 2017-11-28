#ifndef STAGE02PARTCONTROLLER_H_
#define STAGE02PARTCONTROLLER_H_
#include "VioletVreath.h"
#include "jp/gecchi/VioletVreath/scene/Spacetime/World/GameScene/GameMainScene/StageWorld/StageController/Stage/StagePartController.h"

namespace VioletVreath {

HASHVAL(EVENT_STG02_01_WAS_BROKEN);
HASHVAL(EVENT_STG02_02_WAS_BROKEN);
HASHVAL(EVENT_STG02_03_WAS_BROKEN);
HASHVAL(EVENT_STG02_CLIMAX_WAS_BROKEN);

/**
 * ステージ１コントローラー .
 * @version 1.00
 * @since 2010/08/18
 * @author Masatoshi Tsuge
 */
class Stage02PartController : public StagePartController {

    GgafDxCore::GgafDxBgm* bgm_st1_;

public:
    frame frame_prog_fainal_;

public:
    Stage02PartController(const char* prm_name);
    /**
     * 初期処理
     */
    void initialize() override;

    virtual void processBehavior() override;

    virtual void onCatchEvent(hashval prm_no, void* prm_pSource) override;

    virtual ~Stage02PartController();
};

}
#endif /*STAGE02PARTCONTROLLER_H_*/
