#ifndef GGAF_LIB_DEFAULTGOD_H_
#define GGAF_LIB_DEFAULTGOD_H_
#include "GgafLibCommonHeader.h"
#include "jp/ggaf/dx/God.h"

#include "jp/ggaf/lib/manager/SplineSourceManager.h"
#include "jp/ggaf/lib/manager/SplineSourceConnection.h"
#include "jp/ggaf/lib/manager/SplineManufactureManager.h"
#include "jp/ggaf/lib/manager/SplineManufactureConnection.h"
#include "jp/ggaf/lib/manager/DefaultEffectManager.h"
#include "jp/ggaf/lib/scene/DefaultSpacetime.h"

#undef pGOD
#define pGOD ((GgafLib::DefaultGod*)GgafCore::God::ask())

/**
 * 神が保持する SplineManufactureManager に接続し、コネクションを取得。
 * @param X：スプライン定義識別文字列。プロパティ DIR_SPLINE 配下の「X + ".spl"」というファイル名を使用する
 * "FormationOebius002,1" の意味。読み込むファイル=FormationOebius002.spl
 * 1 は採用するスプラインのインデックス(0～)をあらわす。
 * SPLINE=mobius1.dat,mobius3.dat,mobius5.dat
 * 定義されていた場合 1=mobius3.dat のデータを採用
 */
#define connectToSplineManufactureManager(X) ((GgafLib::SplineManufactureConnection*)((pGOD)->_pSplManufManager->connect((X), this)))

/**
 * 神が保持する SplineSourceManager に接続し、コネクションを取得。
 * X：識別文字列（SplineSourceManager::processCreateResource(const char* prm_idstr, void* prm_pConnector) の prm_idstr に渡る)
 */
#define connectToSplineSourceManager(X)   ((GgafLib::SplineSourceConnection*)((pGOD)->_pSplSrcManager->connect((X), this)))

namespace GgafLib {
class DefaultGod : public GgafDx::God {

public:
    SplineSourceManager* _pSplSrcManager;
    SplineManufactureManager* _pSplManufManager;

public:
    DefaultGod();
    virtual HRESULT initDevice() override;

    virtual DefaultSpacetime* getSpacetime() override {  //共変の戻り値
        return (DefaultSpacetime*)_pSpacetime;
    }

    virtual void clean() override;
    virtual DefaultEffectManager* createEffectManager() override;  //共変の戻り値

    virtual SplineSourceManager* createSplineSourceManager();
    virtual SplineManufactureManager* createSplineManufactureManager();

    virtual ~DefaultGod();
};

}
#endif /*GGAF_LIB_DEFAULTGOD_H_*/
