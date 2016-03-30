#ifndef MGRCAMERAVIEWPOINT_H_
#define MGRCAMERAVIEWPOINT_H_
#include "Mogera.h"
#include "jp/ggaf/lib/actor/camera/DefaultCameraViewPoint.h"

namespace Mogera {

/**
 * ���_.
 * @version 1.00
 * @since 2013/12/05
 * @author Masatoshi Tsuge
 */
class MgrCameraViewPoint : public GgafLib::DefaultCameraViewPoint {

public:
    MgrCameraViewPoint(const char* prm_name);

    virtual ~MgrCameraViewPoint(); //�f�X�g���N�^
};

}
#endif /*MGRCAMERAVIEWPOINT_H_*/
