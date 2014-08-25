#ifndef VIEWPOINT_H_
#define VIEWPOINT_H_
#include "VioletVreath.h"
#include "jp/ggaf/dxcore/actor/GgafDxCameraViewPoint.h"

namespace VioletVreath {

/**
 * 視点.
 * @version 1.00
 * @since 2013/12/05
 * @author Masatoshi Tsuge
 */
class ViewPoint : public GgafDxCore::GgafDxCameraViewPoint {
public:
    /** 平行移動支援 */
    GgafDxCore::GgafDxAxesMover* pAxsMver_;

public:
    ViewPoint(const char* prm_name);

    virtual void initialize() override;

    virtual void processBehavior() override;

    void slideMvTo(coord tx, coord ty, coord tz, frame t);
    void slideMvTo(GgafDxCore::GgafDxGeometricActor* pTarget, frame t);

    virtual ~ViewPoint(); //デストラクタ
};

}
#endif /*VIEWPOINT_H_*/
