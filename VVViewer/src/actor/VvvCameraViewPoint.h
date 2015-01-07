#ifndef VVVCAMERAVIEWPOINT_H_
#define VVVCAMERAVIEWPOINT_H_
#include "VVViewer.h"

#include "jp/ggaf/lib/actor/DefaultCameraViewPoint.h"

namespace VVViewer {

/**
 * ���_.
 * @version 1.00
 * @since 2014/12/22
 * @author Masatoshi Tsuge
 */
class VvvCameraViewPoint : public GgafLib::DefaultCameraViewPoint {
public:
    /** ���s�ړ��x�� */
    GgafDxCore::GgafDxAxesMover* pAxsMver_;

public:
    VvvCameraViewPoint(const char* prm_name);

    virtual void processBehavior() override;

    void slideMvTo(coord tx, coord ty, coord tz, frame t);
    void slideMvTo(GgafDxCore::GgafDxGeometricActor* pTarget, frame t);

    virtual ~VvvCameraViewPoint(); //�f�X�g���N�^
};


}
#endif /*VVVCAMERAVIEWPOINT_H_*/
