#ifndef MGRCAMERAVIEWPOINT_H_
#define MGRCAMERAVIEWPOINT_H_
#include "Mogera.h"
#include "jp/ggaf/lib/actor/DefaultCameraViewPoint.h"

namespace Mogera {

/**
 * ���_.
 * @version 1.00
 * @since 2013/12/05
 * @author Masatoshi Tsuge
 */
class MgrCameraViewPoint : public GgafLib::DefaultCameraViewPoint {
public:
    /** ���s�ړ��x�� */
    GgafDxCore::GgafDxAxesMover* pAxsMver_;

public:
    MgrCameraViewPoint(const char* prm_name);

    virtual void initialize() override;

    virtual void processBehavior() override;

    void slideMvTo(coord tx, coord ty, coord tz, frame t);
    void slideMvTo(GgafDxCore::GgafDxGeometricActor* pTarget, frame t);

    virtual ~MgrCameraViewPoint(); //�f�X�g���N�^
};

}
#endif /*MGRCAMERAVIEWPOINT_H_*/
