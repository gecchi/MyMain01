#ifndef GGAF_DX_CURVEMANUFACTUREMANAGER_H_
#define GGAF_DX_CURVEMANUFACTUREMANAGER_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/core/util/ResourceManager.hpp"

namespace GgafDx {

/**
 * CurveManufacture �Ǘ��N���X .
 * �����ς� CurveManufacture �I�u�W�F�N�g��o�^���Ă����A�g���܂킵�܂��B
 * @version 1.00
 * @since 2010/12/14
 * @author Masatoshi Tsuge
 */
class CurveManufactureManager : public GgafCore::ResourceManager<CurveManufacture> {

public:

    /**
     * �R���X�g���N�^
     * @param prm_manager_name �}�l�[�W������
     */
    CurveManufactureManager(const char* prm_manager_name);

    CurveManufacture* processCreateResource(const char* prm_idstr, void* prm_pConnector) override;

    GgafCore::ResourceConnection<CurveManufacture>* processCreateConnection(const char* prm_idstr, CurveManufacture* prm_pResource) override;

    virtual ~CurveManufactureManager() {
    }
};

}
#endif /*GGAF_DX_CURVEMANUFACTUREMANAGER_H_*/
