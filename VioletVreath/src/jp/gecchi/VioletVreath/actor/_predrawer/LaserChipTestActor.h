#ifndef LASERCHIPEFFECTACTOR_H_
#define LASERCHIPEFFECTACTOR_H_
#include "jp/ggaf/lib/actor/laserchip/StraightLaserChip.h"

namespace VioletVreath {

/**
 * プリレンダ用テストアクター .
 * @version 1.00
 * @since 2011/04/18
 * @author Masatoshi Tsuge
 */
class LaserChipTestActor : public GgafLib::StraightLaserChip {

public:

    LaserChipTestActor(const char* prm_name);

    virtual ~LaserChipTestActor();

};

}
#endif /*LASERCHIPEFFECTACTOR_H_*/

