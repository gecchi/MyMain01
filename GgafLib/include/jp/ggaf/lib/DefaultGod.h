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
 * �_���ێ����� SplineManufactureManager �ɐڑ����A�R�l�N�V�������擾�B
 * @param X�F�X�v���C����`���ʕ�����B�v���p�e�B DIR_SPLINE �z���́uX + ".spl"�v�Ƃ����t�@�C�������g�p����
 * "FormationOebius002,1" �̈Ӗ��B�ǂݍ��ރt�@�C��=FormationOebius002.spl
 * 1 �͍̗p����X�v���C���̃C���f�b�N�X(0�`)������킷�B
 * SPLINE=mobius1.dat,mobius3.dat,mobius5.dat
 * ��`����Ă����ꍇ 1=mobius3.dat �̃f�[�^���̗p
 */
#define connectToSplineManufactureManager(X) ((GgafLib::SplineManufactureConnection*)((pGOD)->_pSplManufManager->connect((X), this)))

/**
 * �_���ێ����� SplineSourceManager �ɐڑ����A�R�l�N�V�������擾�B
 * X�F���ʕ�����iSplineSourceManager::processCreateResource(const char* prm_idstr, void* prm_pConnector) �� prm_idstr �ɓn��)
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

    virtual DefaultSpacetime* getSpacetime() override {  //���ς̖߂�l
        return (DefaultSpacetime*)_pSpacetime;
    }

    virtual void clean() override;
    virtual DefaultEffectManager* createEffectManager() override;  //���ς̖߂�l

    virtual SplineSourceManager* createSplineSourceManager();
    virtual SplineManufactureManager* createSplineManufactureManager();

    virtual ~DefaultGod();
};

}
#endif /*GGAF_LIB_DEFAULTGOD_H_*/
