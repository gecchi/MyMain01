#ifndef DEFAULTGOD_H_
#define DEFAULTGOD_H_
#include "jp/ggaf/dxcore/GgafDxGod.h"

#include "jp/ggaf/lib/manager/SplineSourceManager.h"
#include "jp/ggaf/lib/manager/SplineSourceConnection.h"
#include "jp/ggaf/lib/manager/SplineManufactureManager.h"
#include "jp/ggaf/lib/manager/SplineManufactureConnection.h"

#undef P_GOD
#define P_GOD ((GgafLib::DefaultGod*)GgafCore::GgafGod::_pGod)

/**
 * �_���ێ����� SplineManufactureManager �ɐڑ����A�R�l�N�V�������擾�B
 * @param X�F�X�v���C����`���ʕ�����B�v���p�e�B DIR_SPLINE �z���́uX + ".spl"�v�Ƃ����t�@�C�������g�p����
 */
#define connectToSplineManufactureManager(X) ((GgafLib::SplineManufactureConnection*)((P_GOD)->_pSplManufManager->connect((X), this)))

namespace GgafLib {
class DefaultGod : public GgafDxCore::GgafDxGod {

public:
    SplineSourceManager* _pSplSrcManager;
    SplineManufactureManager* _pSplManufManager;

public:
    DefaultGod(HINSTANCE prm_hInstance, HWND prm_pHWndPrimary, HWND prm_pHWndSecondary);
    virtual void clean() override;
    virtual ~DefaultGod();
};

}
#endif /*DEFAULTGOD_H_*/
