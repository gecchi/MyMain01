#ifndef SPLINELINEMANAGER_H_
#define SPLINELINEMANAGER_H_
#include "VioletVreath.h"
#include "jp/ggaf/dx/manager/SplineSourceManager.h"

namespace VioletVreath {

/**
 * VioletVreath�p Spline �Ǘ��N���X .
 * @version 1.00
 * @since 2018/08/10
 * @author Masatoshi Tsuge
 */
class SplineSourceManagerEx : public GgafDx::SplineSourceManager {

public:
    /**
     * �R���X�g���N�^
     * @param prm_manager_name �}�l�[�W������
     */
    SplineSourceManagerEx(const char* prm_manager_name);

    virtual GgafDx::SplineSource* processCreateResource(const char* prm_idstr, void* prm_pConnector) override;

    virtual ~SplineSourceManagerEx() {
    }
};

}
#endif /*SPLINELINEMANAGER_H_*/
