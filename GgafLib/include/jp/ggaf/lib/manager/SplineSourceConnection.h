#ifndef GGAFLIB_SPLINEPROGRAMCONNECTION_H_
#define GGAFLIB_SPLINEPROGRAMCONNECTION_H_
#include "GgafLibCommonHeader.h"
#include "jp/ggaf/core/util/GgafResourceConnection.hpp"

#include "jp/ggaf/lib/util/spline/SplineSource.h"

namespace GgafLib {

/**
 * SplineSource�����R�l�N�V����.
 * @version 1.00
 * @since 2010/12/14
 * @author Masatoshi Tsuge
 */
class SplineSourceConnection : public GgafCore::GgafResourceConnection<SplineSource> {

public:
    /**
     * �R���X�g���N�^<BR>
     * @param prm_idstr ���ʖ�
     * @param prm_pResource SplineSource�I�u�W�F�N�g
     */
    SplineSourceConnection(const char* prm_idstr, SplineSource* prm_pResource);

    void processReleaseResource(SplineSource* prm_pResource);

    virtual ~SplineSourceConnection() {
    }
};

}
#endif /*GGAFLIB_SPLINEPROGRAMCONNECTION_H_*/
