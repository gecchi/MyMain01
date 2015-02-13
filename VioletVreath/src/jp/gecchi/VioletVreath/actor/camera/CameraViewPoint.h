#ifndef CAMERAVIEWPOINT_H_
#define CAMERAVIEWPOINT_H_
#include "VioletVreath.h"
#include "jp/ggaf/lib/actor/camera/DefaultCameraViewPoint.h"

namespace VioletVreath {

/**
 * ���_.
 * @version 1.00
 * @since 2013/12/05
 * @author Masatoshi Tsuge
 */
class CameraViewPoint : public GgafLib::DefaultCameraViewPoint {
public:
    /** ���s�ړ��x�� */
    GgafDxCore::GgafDxAxesMover* pAxsMver_;

public:
    CameraViewPoint(const char* prm_name);

    virtual void initialize() override;

    virtual void processBehavior() override;

    void slideMvTo(coord tx, coord ty, coord tz, frame t);
    void slideMvTo(GgafDxCore::GgafDxGeometricActor* pTarget, frame t);

    virtual ~CameraViewPoint(); //�f�X�g���N�^
};

}
#endif /*CAMERAVIEWPOINT_H_*/
