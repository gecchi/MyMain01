#ifndef GGAFDXCORE_GGAFDXGEOELEM_H_
#define GGAFDXCORE_GGAFDXGEOELEM_H_
#include "GgafDxCommonHeader.h"
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
    coord x;
    coord y;
    coord z;
    angle rx;
    angle ry;
    angle rz;
    GgafDxGeoElem* _next;

public:
    GgafDxGeoElem();

    GgafDxGeoElem(coord prm_x, coord prm_y, coord prm_z);

    GgafDxGeoElem(coord prm_x, coord prm_y, coord prm_z, angle prm_rx, angle prm_ry, angle prm_rz);

    explicit GgafDxGeoElem(const GgafDxGeometricActor* prm_pActor);

    void set(coord prm_x, coord prm_y, coord prm_z, angle prm_rx, angle prm_ry, angle prm_rz);

    void set(coord prm_x, coord prm_y, coord prm_z);

    void set(const GgafDxGeometricActor* prm_pActor);

    void set(const GgafDxGeoElem* prm_pGeoElem);

    virtual ~GgafDxGeoElem();
};

}
#endif /*GGAFDXCORE_GGAFDXGEOELEM_H_*/
