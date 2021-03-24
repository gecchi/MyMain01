#ifndef GGAF_DX_SPLINEPROGRAMCONNECTION_H_
#define GGAF_DX_SPLINEPROGRAMCONNECTION_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/core/util/ResourceConnection.hpp"

#include "jp/ggaf/dx/util/spline/SplineSource.h"

namespace GgafDx {

/**
 * SplineSource�����R�l�N�V����.
 * @version 1.00
 * @since 2010/12/14
 * @author Masatoshi Tsuge
 */
class SplineSourceConnection : public GgafCore::ResourceConnection<SplineSource> {

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
#endif /*GGAF_DX_SPLINEPROGRAMCONNECTION_H_*/
