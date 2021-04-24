#ifndef CURVELINEMANAGER_H_
#define CURVELINEMANAGER_H_
#include "VioletVreath.h"
#include "jp/ggaf/dx/manager/CurveSourceManager.h"

namespace VioletVreath {

/**
 * VioletVreath�p Curve �Ǘ��N���X .
 * @version 1.00
 * @since 2018/08/10
 * @author Masatoshi Tsuge
 */
class CurveSourceManagerEx : public GgafDx::CurveSourceManager {

public:
    /**
     * �R���X�g���N�^
     * @param prm_manager_name �}�l�[�W������
     */
    CurveSourceManagerEx(const char* prm_manager_name);

    virtual GgafDx::CurveSource* processCreateResource(const char* prm_idstr, void* prm_pConnector) override;

    virtual ~CurveSourceManagerEx() {
    }
};

}
#endif /*CURVELINEMANAGER_H_*/
