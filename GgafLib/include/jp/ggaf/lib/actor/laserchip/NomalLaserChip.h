#ifndef GGAFLIB_NOMALLASERCHIP_H_
#define GGAFLIB_NOMALLASERCHIP_H_
#include "GgafLibCommonHeader.h"
#include "jp/ggaf/lib/actor/laserchip/LaserChip.h"

namespace GgafLib {

/**
 * 普通のレーザー用ポリラインのチップ .
 * @version 1.00
 * @since 2015/04/02
 * @author Masatoshi Tsuge
 */
class NomalLaserChip : public LaserChip {
    friend class LaserChipDepository;

public:
    NomalLaserChip(const char* prm_name, const char* prm_model, GgafCore::GgafStatus* prm_pStat=nullptr);

    virtual void onCreateModel() override {}

    virtual void initialize() override {}

    virtual void processBehavior() override {}

    virtual void processJudgement() override {}

    virtual void processSettlementBehavior() override;

    virtual void onCatchEvent(hashval prm_no, void* prm_pSource) override {}

    virtual ~NomalLaserChip();

};

}
#endif /*GGAFLIB_NOMALLASERCHIP_H_*/

