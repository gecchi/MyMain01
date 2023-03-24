#ifndef HOSHIBOSHIRANKUP_H_
#define HOSHIBOSHIRANKUP_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/gecchi/VioletVreath/actor/background/HoshiBoshi/HoshiBoshi.h"

namespace VioletVreath {

/**
 * ランクアップステージの星々 .
 * @version 1.00
 * @since 2011/10/18
 * @author Masatoshi Tsuge
 */
class HoshiBoshiRankUp : public HoshiBoshi {

public:
    HoshiBoshiRankUp(const char* prm_name);

    void initialize() override;

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;

    virtual ~HoshiBoshiRankUp();



};

}
#endif /*HOSHIBOSHITRANSIT_H_*/

