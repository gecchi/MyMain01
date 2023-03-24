#ifndef HORIZON001_H_
#define HORIZON001_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/ggaf/lib/actor/DefaultMeshActor.h"

namespace VioletVreath {

/**
 * ínïΩê¸001 .
 * @version 1.00
 * @since 2013/07/30
 * @author Masatoshi Tsuge
 */
class Horizon001 : public GgafLib::DefaultMeshActor {

    coord chip_width_;
public:
    Horizon001(const char* prm_name);

    virtual void onCreateModel() override;

    virtual void initialize() override;

    virtual void processBehavior() override;

    virtual int isOutOfView() override {
        return 0;
    }

    virtual bool isOutOfSpacetime() const override {
        return false;
    }

    virtual ~Horizon001();

};

}
#endif /*HORIZON001_H_*/

