#ifndef GGAF_LIB_DEFAULTCARETAKER_H_
#define GGAF_LIB_DEFAULTCARETAKER_H_
#include "jp/ggaf/GgafLibCommonHeader.h"
#include "jp/ggaf/dx/Caretaker.h"

#include "jp/ggaf/dx/manager/CurveSourceManager.h"
#include "jp/ggaf/dx/manager/CurveSourceConnection.h"
#include "jp/ggaf/dx/manager/CurveManufactureManager.h"
#include "jp/ggaf/dx/manager/CurveManufactureConnection.h"
#include "jp/ggaf/lib/manager/DefaultEffectManager.h"
#include "jp/ggaf/lib/manager/DefaultModelManager.h"
#include "jp/ggaf/lib/scene/DefaultSpacetime.h"

#undef pCARETAKER
#define pCARETAKER ((GgafLib::DefaultCaretaker*)GgafCore::Caretaker::ask())

namespace GgafLib {
class DefaultCaretaker : public GgafDx::Caretaker {

public:
    DefaultCaretaker();
    virtual HRESULT initDevice() override;

    virtual DefaultSpacetime* getSpacetime() override {  //‹¤•Ï‚Ì–ß‚è’l
        return (DefaultSpacetime*)_pSpacetime;
    }

    virtual void clean() override;
    virtual DefaultEffectManager* createEffectManager() override;  //‹¤•Ï‚Ì–ß‚è’l
    virtual DefaultModelManager* createModelManager() override;  //‹¤•Ï‚Ì–ß‚è’l
    virtual ~DefaultCaretaker();
};

}
#endif /*GGAF_LIB_DEFAULTCARETAKER_H_*/
