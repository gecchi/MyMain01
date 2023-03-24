#ifndef MGRCAMERAUPVECTOR_H_
#define MGRCAMERAUPVECTOR_H_
#include "Mogera.h"
#include "jp/ggaf/lib/actor/camera/DefaultCameraUpVector.h"

namespace Mogera {

/**
 * �J�����̏�̈ʒu�x�N�g�� .
 * @version 1.00
 * @since 2014/12/24
 * @author Masatoshi Tsuge
 */
class MgrCameraUpVector : public GgafLib::DefaultCameraUpVector {

public:
    MgrCameraUpVector(const char* prm_name);

    virtual ~MgrCameraUpVector();
};


}
#endif /*MGRCAMERAUPVECTOR_H_*/
