#ifndef GGAFLIB_SPLINEMANUFACTURECONNECTION_H_
#define GGAFLIB_SPLINEMANUFACTURECONNECTION_H_
#include "GgafLibCommonHeader.h"
#include "jp/ggaf/core/util/GgafResourceConnection.hpp"

#include "jp/ggaf/lib/util/spline/SplineManufacture.h"

namespace GgafLib {

/**
 * SplineManufacture�����R�l�N�V����.
 * @version 1.00
 * @since 2010/12/14
 * @author Masatoshi Tsuge
 */
class SplineManufactureConnection : public GgafCore::GgafResourceConnection<SplineManufacture> {

public:
    /**
     * �R���X�g���N�^<BR>
     * @param prm_idstr ���ʖ�
     * @param prm_pResource SplineManufacture�I�u�W�F�N�g
     */
    SplineManufactureConnection(char* prm_idstr, SplineManufacture* prm_pResource);

    void processReleaseResource(SplineManufacture* prm_pResource);

    virtual ~SplineManufactureConnection() {
    }
};

}
#endif /*GGAFLIB_SPLINEMANUFACTURECONNECTION_H_*/
