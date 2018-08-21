#ifndef SPLINEMANUFACTUREMANAGEREX_H_
#define SPLINEMANUFACTUREMANAGEREX_H_
#include "VioletVreath.h"

#include "jp/ggaf/lib/manager/SplineManufactureManager.h"

namespace VioletVreath {
/**
 * VioletVreath�p SplineManufacture �Ǘ��N���X .
 * @version 1.00
 * @since 2018/08/21
 * @author Masatoshi Tsuge
 */
class SplineManufactureManagerEx : public GgafLib::SplineManufactureManager {

public:
    /**
     * �R���X�g���N�^
     * @param prm_manager_name �}�l�[�W������
     */
    SplineManufactureManagerEx(const char* prm_manager_name);

    GgafLib::SplineManufacture* processCreateResource(const char* prm_idstr, void* prm_pConnector) override;

    virtual ~SplineManufactureManagerEx() {
    }
};

}
#endif /*SPLINEMANUFACTUREMANAGEREX_H_*/
