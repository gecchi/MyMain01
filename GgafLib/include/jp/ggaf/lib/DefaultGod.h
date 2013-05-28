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
 * 神が保持する SplineManufactureManager に接続し、コネクションを取得。
 * @param X：スプライン定義識別文字列。プロパティ DIR_SPLINE 配下の「X + ".spl"」というファイル名を使用する
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
