#ifndef GGAFLIB_DEFAULTGOD_H_
#define GGAFLIB_DEFAULTGOD_H_
#include "GgafLibCommonHeader.h"
#include "jp/ggaf/dxcore/GgafDxGod.h"

#include "jp/ggaf/lib/manager/SplineSourceManager.h"
#include "jp/ggaf/lib/manager/SplineSourceConnection.h"
#include "jp/ggaf/lib/manager/SplineManufactureManager.h"
#include "jp/ggaf/lib/manager/SplineManufactureConnection.h"
#include "jp/ggaf/lib/manager/DefaultEffectManager.h"
#include "jp/ggaf/lib/scene/DefaultSpacetime.h"

#undef pGOD
#define pGOD ((GgafLib::DefaultGod*)GgafCore::GgafGod::ask())

/**
 * �_���ێ����� SplineManufactureManager �ɐڑ����A�R�l�N�V�������擾�B
 * @param X�F�X�v���C����`���ʕ�����B�v���p�e�B DIR_SPLINE �z���́uX + ".spl"�v�Ƃ����t�@�C�������g�p����
 */
#define connectToSplineManufactureManager(X) ((GgafLib::SplineManufactureConnection*)((pGOD)->_pSplManufManager->connect((X), this)))

namespace GgafLib {
class DefaultGod : public GgafDxCore::GgafDxGod {

public:
    SplineSourceManager* _pSplSrcManager;
    SplineManufactureManager* _pSplManufManager;

public:
    DefaultGod();
    virtual HRESULT initDevice() override;

    virtual DefaultSpacetime* getSpacetime() override {  //���ς̖߂�l
        return (DefaultSpacetime*)_pSpacetime;
    }

    virtual void clean() override;
    virtual DefaultEffectManager* createEffectManager() override;  //���ς̖߂�l
    virtual ~DefaultGod();
};

}
#endif /*GGAFLIB_DEFAULTGOD_H_*/
