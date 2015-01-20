#ifndef HOSHIBOSHITESTACTOR_H_
#define HOSHIBOSHITESTACTOR_H_
#include "VioletVreath.h"
#include "jp/gecchi/VioletVreath/actor/background/HoshiBoshi/HoshiBoshi.h"

namespace VioletVreath {


/**
 * プリロード用テストアクター .
 * @version 1.00
 * @since 2011/04/18
 * @author Masatoshi Tsuge
 */
class HoshiBoshiTestActor : public HoshiBoshi {

public:
    HoshiBoshiTestActor(const char* prm_name);

    void onActive() override;

    void processBehavior() override;

    void processJudgement() override;

    void processDraw() override;

    virtual ~HoshiBoshiTestActor();
};

}
#endif /*HOSHIBOSHITESTACTOR_H_*/

