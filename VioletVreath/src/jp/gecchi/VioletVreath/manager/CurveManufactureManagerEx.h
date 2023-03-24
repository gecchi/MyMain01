#ifndef CURVEMANUFACTUREMANAGEREX_H_
#define CURVEMANUFACTUREMANAGEREX_H_
#include "jp/gecchi/VioletVreath/VioletVreath.h"

#include "jp/ggaf/dx/manager/CurveManufactureManager.h"

namespace VioletVreath {
/**
 * VioletVreath�p CurveManufacture �Ǘ��N���X .
 * @version 1.00
 * @since 2018/08/21
 * @author Masatoshi Tsuge
 */
class CurveManufactureManagerEx : public GgafDx::CurveManufactureManager {

public:
    /**
     * �R���X�g���N�^
     * @param prm_manager_name �}�l�[�W������
     */
    CurveManufactureManagerEx(const char* prm_manager_name);

    GgafDx::CurveManufacture* processCreateResource(const char* prm_idstr, void* prm_pConnector) override;

    virtual ~CurveManufactureManagerEx() {
    }
};

}
#endif /*CURVEMANUFACTUREMANAGEREX_H_*/
