#ifndef GGAF_DX_SPLINEMANUFACTUREMANAGER_H_
#define GGAF_DX_SPLINEMANUFACTUREMANAGER_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/core/util/ResourceManager.hpp"

namespace GgafDx {
/**
 * SplineManufacture �Ǘ��N���X .
 * �����ς� SplineManufacture �I�u�W�F�N�g��o�^���Ă����A�g���܂킵�܂��B
 * @version 1.00
 * @since 2010/12/14
 * @author Masatoshi Tsuge
 */
class SplineManufactureManager : public GgafCore::ResourceManager<SplineManufacture> {

public:
    /**
     * �R���X�g���N�^
     * @param prm_manager_name �}�l�[�W������
     */
    SplineManufactureManager(const char* prm_manager_name);

    SplineManufacture* processCreateResource(const char* prm_idstr, void* prm_pConnector) override;

    GgafCore::ResourceConnection<SplineManufacture>* processCreateConnection(const char* prm_idstr, SplineManufacture* prm_pResource) override;

    virtual ~SplineManufactureManager() {
    }
};

}
#endif /*GGAF_DX_SPLINEMANUFACTUREMANAGER_H_*/
