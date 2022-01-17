#ifndef GGAF_LIB_DEFAULTGOD_H_
#define GGAF_LIB_DEFAULTGOD_H_
#include "GgafLibCommonHeader.h"
#include "jp/ggaf/dx/God.h"

#include "jp/ggaf/dx/manager/CurveSourceManager.h"
#include "jp/ggaf/dx/manager/CurveSourceConnection.h"
#include "jp/ggaf/dx/manager/CurveManufactureManager.h"
#include "jp/ggaf/dx/manager/CurveManufactureConnection.h"
#include "jp/ggaf/lib/manager/DefaultEffectManager.h"
#include "jp/ggaf/lib/manager/DefaultModelManager.h"
#include "jp/ggaf/lib/scene/DefaultSpacetime.h"

#undef pGOD
#define pGOD ((GgafLib::DefaultGod*)GgafCore::God::ask())

namespace GgafLib {
class DefaultGod : public GgafDx::God {

public:
    DefaultGod();
    virtual HRESULT initDevice() override;

    virtual DefaultSpacetime* getSpacetime() override {  //‹¤•Ï‚Ì–ß‚è’l
        return (DefaultSpacetime*)_pSpacetime;
    }

    virtual void clean() override;
    virtual DefaultEffectManager* createEffectManager() override;  //‹¤•Ï‚Ì–ß‚è’l
    virtual DefaultModelManager* createModelManager() override;  //‹¤•Ï‚Ì–ß‚è’l
    virtual ~DefaultGod();
};

}
#endif /*GGAF_LIB_DEFAULTGOD_H_*/
