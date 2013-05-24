#ifndef STAGE01_01_H_
#define STAGE01_01_H_
#include "jp/ggaf/lib/scene/DefaultScene.h"

namespace VioletVreath {

/**
 * ƒXƒe[ƒW‚P|‚P .
 * @version 1.00
 * @since 2010/08/18
 * @author Masatoshi Tsuge
 */
class Stage01_01 : public GgafLib::DefaultScene {


public:
    Stage01_01(const char* prm_name);
    /**
     * ‰Šúˆ—
     */
    void initialize() override;

    virtual void processBehavior() override;

    virtual ~Stage01_01();
};

}
#endif /*STAGE01_01_H_*/
