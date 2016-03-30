#ifndef VVVCAMERAVIEWPOINT_H_
#define VVVCAMERAVIEWPOINT_H_
#include "VVViewer.h"

#include "jp/ggaf/lib/actor/camera/DefaultCameraViewPoint.h"

namespace VVViewer {

/**
 * ���_.
 * @version 1.00
 * @since 2014/12/22
 * @author Masatoshi Tsuge
 */
class VvvCameraViewPoint : public GgafLib::DefaultCameraViewPoint {

public:
    VvvCameraViewPoint(const char* prm_name);

    virtual ~VvvCameraViewPoint(); //�f�X�g���N�^
};


}
#endif /*VVVCAMERAVIEWPOINT_H_*/
