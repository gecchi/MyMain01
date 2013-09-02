#ifndef GGAFDXCORE_GGAFDXGEOELEM_H_
#define GGAFDXCORE_GGAFDXGEOELEM_H_
#include "jp/ggaf/core/GgafObject.h"

#include "jp/ggaf/dxcore/actor/GgafDxGeometricActor.h"

namespace GgafDxCore {

/**
 * ç¿ïWèÓïÒç\ë¢ëÃ .
 * @version 1.00
 * @since 2008/12/19
 * @author Masatoshi Tsuge
 */
class GgafDxGeoElem : public GgafCore::GgafObject {
public:
    coord _X;
    coord _Y;
    coord _Z;
    angle _RX;
    angle _RY;
    angle _RZ;
    GgafDxGeoElem* _next;

public:
    GgafDxGeoElem();

    GgafDxGeoElem(coord prm_X, coord prm_Y, coord prm_Z);

    GgafDxGeoElem(coord prm_X, coord prm_Y, coord prm_Z, angle prm_RX, angle prm_RY, angle prm_RZ);

    GgafDxGeoElem(GgafDxGeometricActor* prm_pActor);

    void set(coord prm_X, coord prm_Y, coord prm_Z, angle prm_RX, angle prm_RY, angle prm_RZ);

    void set(coord prm_X, coord prm_Y, coord prm_Z);

    void set(GgafDxGeometricActor* prm_pActor);

    void set(GgafDxGeoElem* prm_pGeoElem);

    virtual ~GgafDxGeoElem();
};

}
#endif /*GGAFDXCORE_GGAFDXGEOELEM_H_*/
