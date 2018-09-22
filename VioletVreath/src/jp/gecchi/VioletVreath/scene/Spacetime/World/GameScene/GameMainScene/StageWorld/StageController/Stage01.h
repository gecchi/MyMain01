#ifndef STAGE01_H_
#define STAGE01_H_
#include "VioletVreath.h"
#include "Stage.h"

namespace VioletVreath {

DECLARE_HASHVAL(EVENT_STAGE01_PART_CTRLER_WAS_END);

/**
 * �X�e�[�W01 .
 * @version 1.00
 * @since 2018/09/08
 * @author Masatoshi Tsuge
 */
class Stage01 : public Stage {

public:
    WorldBound001* pWorldBound_;
    HoshiBoshi001* pHoshiBoshi_;

    Planet001* pPlanet_;
    Horizon001* pHorizon_;

    LabelGecchi16Font* pMessage_;

public:
    Stage01(const char* prm_name);
    /**
     * ��������
     */
    virtual void initialize() override;
    virtual void processBehavior() override;
    virtual void processJudgement() override;
    virtual void onCatchEvent(hashval prm_no, void* prm_pSource) override;
    virtual ~Stage01();
};

}
#endif /*STAGE01_H_*/
