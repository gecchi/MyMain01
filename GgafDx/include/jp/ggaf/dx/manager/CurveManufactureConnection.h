#ifndef GGAF_DX_CURVEMANUFACTURECONNECTION_H_
#define GGAF_DX_CURVEMANUFACTURECONNECTION_H_
#include "jp/ggaf/GgafDxCommonHeader.h"
#include "jp/ggaf/core/util/ResourceConnection.hpp"

#include "jp/ggaf/dx/util/curve/CurveManufacture.h"

namespace GgafDx {

/**
 * CurveManufacture�����R�l�N�V����.
 * @version 1.00
 * @since 2010/12/14
 * @author Masatoshi Tsuge
 */
class CurveManufactureConnection : public GgafCore::ResourceConnection<CurveManufacture> {

public:
    /**
     * �R���X�g���N�^<BR>
     * @param prm_idstr ���ʖ�
     * @param prm_pResource CurveManufacture�I�u�W�F�N�g
     */
    CurveManufactureConnection(const char* prm_idstr, CurveManufacture* prm_pResource);

    void processReleaseResource(CurveManufacture* prm_pResource);

    virtual ~CurveManufactureConnection() {
    }
};

}
#endif /*GGAF_DX_CURVEMANUFACTURECONNECTION_H_*/
