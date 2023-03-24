#ifndef MYTORPEDOTAIL_H_
#define MYTORPEDOTAIL_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/ggaf/lib/actor/laserchip/HomingLaserChip.h"

namespace VioletVreath {

/**
 * 魚雷の移動軌跡エフェクト .
 * @version 1.00
 * @since 2010/09/21
 * @author Masatoshi Tsuge
 */
class MyTorpedoTail : public GgafLib::HomingLaserChip {

public:
    /** [r]軌跡を描く元の魚雷オブジェクト */
    MyTorpedo* pTorpedo_;

public:
    /**
     *
     * @param prm_name
     * @param prm_pTorpedo 軌跡を描く元の魚雷オブジェクト
     * @return
     */
    MyTorpedoTail(const char* prm_name, MyTorpedo* prm_pTorpedo);

    void initialize() override;

    void onInactive() override;

    void onActive() override;

    /**
     * 先頭チップの動きを定義 .
     */
    void processBehaviorHeadChip() override;

    void processJudgement() override;

    virtual ~MyTorpedoTail();

};

}
#endif /*MYTORPEDOTAIL_H_*/

