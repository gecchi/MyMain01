#ifndef SPLINELINEMANAGER_H_
#define SPLINELINEMANAGER_H_
#include "VioletVreath.h"
#include "jp/ggaf/lib/manager/SplineSourceManager.h"

namespace VioletVreath {

/**
 * Spline �Ǘ��N���X .
 * �����ς� SplineLine �I�u�W�F�N�g��o�^���Ă����A�g���܂킵�܂��B
 * @version 1.00
 * @since 2010/05/31
 * @author Masatoshi Tsuge
 */
class SplineSourceManagerEx : public GgafLib::SplineSourceManager {

public:
    /**
     * �R���X�g���N�^
     * @param prm_manager_name �}�l�[�W������
     */
    SplineSourceManagerEx(const char* prm_manager_name);

    virtual GgafLib::SplineSource* processCreateResource(const char* prm_idstr, void* prm_pConnector) override;

    virtual ~SplineSourceManagerEx() {
    }
};

}
#endif /*SPLINELINEMANAGER_H_*/
