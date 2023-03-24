#ifndef PLANET001ATMOSPHERE_H_
#define PLANET001ATMOSPHERE_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"
#include "jp/ggaf/lib/actor/DefaultMeshActor.h"

namespace VioletVreath {

/**
 * òfêØ001ÇÃëÂãCåó .
 * @version 1.00
 * @since 2012/02/23
 * @author Masatoshi Tsuge
 */
class Planet001Atmosphere : public GgafLib::DefaultMeshActor {

public:
    Planet001Atmosphere(const char* prm_name);

    virtual void onCreateModel() override;

    virtual void initialize() override;

    virtual void processBehavior() override;

    virtual int isOutOfView() override {
        return 0;
    }

    virtual bool isOutOfSpacetime() const override {
        return false;
    }

    virtual ~Planet001Atmosphere();

};

}
#endif /*PLANET001ATMOSPHERE_H_*/

