#ifndef VVVVIEWPOINT_H_
#define VVVVIEWPOINT_H_
#include "VVViewer.h"
#include "jp/ggaf/dxcore/actor/GgafDxCameraViewPoint.h"

namespace VVViewer {

/**
 * ���_.
 * @version 1.00
 * @since 2013/12/05
 * @author Masatoshi Tsuge
 */
class VvvViewPoint : public GgafDxCore::GgafDxCameraViewPoint {
public:
    /** ���s�ړ��x�� */
    GgafDxCore::GgafDxAxesMover* pAxsMver_;

public:
    VvvViewPoint(const char* prm_name);

    virtual void processBehavior() override;

    void slideMvTo(coord tx, coord ty, coord tz, frame t);
    void slideMvTo(GgafDxCore::GgafDxGeometricActor* pTarget, frame t);

    virtual ~VvvViewPoint(); //�f�X�g���N�^
};


}
#endif /*VVVVIEWPOINT_H_*/
