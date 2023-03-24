#ifndef GGAF_DX_GEOELEM_H_
#define GGAF_DX_GEOELEM_H_
#include "jp/ggaf/GgafDxCommonHeader.h"
#include "jp/ggaf/core/Object.h"

#include "jp/ggaf/dx/actor/GeometricActor.h"

namespace GgafDx {

/**
 * ç¿ïWèÓïÒç\ë¢ëÃ .
 * @version 1.00
 * @since 2008/12/19
 * @author Masatoshi Tsuge
 */
class GeoElem : public GgafCore::Object {
public:
    coord x;
    coord y;
    coord z;
    angle rx;
    angle ry;
    angle rz;
    GeoElem* _next;

public:
    GeoElem();

    GeoElem(coord prm_x, coord prm_y, coord prm_z);

    GeoElem(coord prm_x, coord prm_y, coord prm_z, angle prm_rx, angle prm_ry, angle prm_rz);

    explicit GeoElem(const GeometricActor* prm_pActor);

    void set(coord prm_x, coord prm_y, coord prm_z, angle prm_rx, angle prm_ry, angle prm_rz);

    void set(coord prm_x, coord prm_y, coord prm_z);

    void set(const GeometricActor* prm_pActor);

    void set(const GeoElem* prm_pGeoElem);

    virtual ~GeoElem();
};

}
#endif /*GGAF_DX_GEOELEM_H_*/
