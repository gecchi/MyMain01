#ifndef PLANET001ATMOSPHERE_H_
#define PLANET001ATMOSPHERE_H_
#include "VioletVreath.h"
#include "jp/ggaf/lib/actor/DefaultMeshActor.h"

namespace VioletVreath {

/**
 * �f��001�̑�C�� .
 * @version 1.00
 * @since 2012/02/23
 * @author Masatoshi Tsuge
 */
class Planet001Atmosphere : public GgafLib::DefaultMeshActor {

public:
    /** �g��k���x���I�u�W�F�N�g */
    GgafDxCore::GgafDxScaler* pScaler_;

public:
    Planet001Atmosphere(const char* prm_name);

    virtual void onCreateModel() override;

    virtual void initialize() override;

    virtual void processBehavior() override;

    virtual int isOutOfView() override {
        return 0;
    }

    virtual bool isOutOfUniverse() const override {
        return false;
    }

    virtual ~Planet001Atmosphere();

};

}
#endif /*PLANET001ATMOSPHERE_H_*/

