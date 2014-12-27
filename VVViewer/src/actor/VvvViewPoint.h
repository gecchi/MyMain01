#ifndef VVVCAMERAUPVECTOR_H_
#define VVVCAMERAUPVECTOR_H_
#include "VVViewer.h"

#include "jp/ggaf/lib/actor/DefaultCameraViewPoint.h"

namespace VVViewer {

/**
 * ���_.
 * @version 1.00
 * @since 2014/12/22
 * @author Masatoshi Tsuge
 */
class VvvViewPoint : public GgafLib::DefaultCameraViewPoint {
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
#endif /*VVVCAMERAUPVECTOR_H_*/
