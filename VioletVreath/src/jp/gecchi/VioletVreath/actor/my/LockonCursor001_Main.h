#ifndef LOCKONCURSOR001MAIN_H_
#define LOCKONCURSOR001MAIN_H_
#include "VioletVreath.h"
#include "jp/gecchi/VioletVreath/actor/my/LockonCursor001.h"

namespace VioletVreath {

/**
 * ���b�N�I��
 * @version 1.00
 * @since 2010/01/28
 * @author Masatoshi Tsuge
 */
class LockonCursor001_Main : public LockonCursor001 {

public:
    LockonCursor001_Main(const char* prm_name);

    void initialize() override;

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;

    void onInactive() override;

    void releaseLockon() override;

    void lockon(GgafDxGeometricActor* prm_pTarget) override;

    virtual ~LockonCursor001_Main();
};

}
#endif /*LOCKONCURSOR001MAIN_H_*/

