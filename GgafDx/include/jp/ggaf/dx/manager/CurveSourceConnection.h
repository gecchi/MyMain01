#ifndef GGAF_DX_CURVEPROGRAMCONNECTION_H_
#define GGAF_DX_CURVEPROGRAMCONNECTION_H_
#include "jp/ggaf/GgafDxCommonHeader.h"
#include "jp/ggaf/core/util/ResourceConnection.hpp"

#include "jp/ggaf/dx/util/curve/CurveSource.h"

namespace GgafDx {

/**
 * CurveSource�����R�l�N�V����.
 * @version 1.00
 * @since 2010/12/14
 * @author Masatoshi Tsuge
 */
class CurveSourceConnection : public GgafCore::ResourceConnection<CurveSource> {

public:
    /**
     * �R���X�g���N�^<BR>
     * @param prm_idstr ���ʖ�
     * @param prm_pResource CurveSource�I�u�W�F�N�g
     */
    CurveSourceConnection(const char* prm_idstr, CurveSource* prm_pResource);

    void processReleaseResource(CurveSource* prm_pResource);

    virtual ~CurveSourceConnection() {
    }
};

}
#endif /*GGAF_DX_CURVEPROGRAMCONNECTION_H_*/
