#ifndef LOCKONCURSOR001SUB_H_
#define LOCKONCURSOR001SUB_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/gecchi/VioletVreath/actor/my/LockonCursor001.h"

namespace VioletVreath {

/**
 * ÉçÉbÉNÉIÉì
 * @version 1.00
 * @since 2010/01/28
 * @author Masatoshi Tsuge
 */
class LockonCursor001_Sub : public LockonCursor001 {

public:
    LockonCursor001_Main* pLockonCursor001_Main_;

    LockonCursor001_Sub(const char* prm_name);

    void initialize() override;

    void processBehavior() override;

    void onActive() override;

    void onInactive() override;

    void processJudgement() override;

    void releaseLockon() override;

    void lockon(GgafDx::GeometricActor* prm_pTarget)  override;

    virtual ~LockonCursor001_Sub();
};

}
#endif /*LOCKONCURSOR001SUB_H_*/

