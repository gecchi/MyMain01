#ifndef GGAFLIB_DEFAULTSPACETIME_H_
#define GGAFLIB_DEFAULTSPACETIME_H_
#include "GgafLibCommonHeader.h"
#include "jp/ggaf/dxcore/scene/GgafDxSpacetime.h"

#include "jp/ggaf/lib/GgafLibConfig.h"
#include "jp/ggaf/core/util/GgafLinearTreeRounder.hpp"
#include "jp/ggaf/lib/actor/camera/DefaultCamera.h"


namespace GgafLib {

typedef GgafCore::GgafLinearTreeRounder<GgafCore::GgafActor, 3> OctreeRounder;
typedef GgafCore::GgafLinearTreeRounder<GgafCore::GgafActor, 2> QuadtreeRounder;

/**
 * �u���̐��v�N���X�C���^�[�t�F�C�X.
 * GgafDxCore::GgafDxSpacetime ���p�����������̃C���^�[�t�F�[�X�ł��B<BR>
 * Ggaf���C�u�����𗘗p����ꍇ�A�{�N���X���p���������������̐��N���X���K�v�ł��B<BR>
 * (��DefaultWorld)
 * @version 1.00
 * @since 2008/07/30
 * @author Masatoshi Tsuge
 */
class DefaultSpacetime : public GgafDxCore::GgafDxSpacetime {
    virtual void processFinal() override;

public:
    GgafCore::GgafLinearOctree* _pLinearOctree;
    OctreeRounder* _pLinearOctreeHitCheckRounder;
    GgafCore::GgafLinearQuadtree* _pLinearQuadtree;
    QuadtreeRounder* _pLinearQuadtreeHitCheckRounder;
public:
    DefaultSpacetime(const char* prm_name, DefaultCamera* prm_pCamera);

    inline GgafCore::GgafLinearOctree* getLinearOctree() {
#ifdef MY_DEBUG
        if (_pLinearOctree == nullptr) {
            throwGgafCriticalException("DefaultSpacetime::getLinearOctree() �����؂͍쐬����Ă��܂���B\n"
                    "IS_HIT_CHECK_3D �v���p�e�B true �ɂ��Ă��������B\n"
                    "���݂�IS_HIT_CHECK_3D="<<CONFIG::IS_HIT_CHECK_3D );
        }
#endif
        return _pLinearOctree;
    }

    inline OctreeRounder* getLinearOctreeHitCheckRounder() {
#ifdef MY_DEBUG
        if (_pLinearOctreeHitCheckRounder == nullptr) {
            throwGgafCriticalException("DefaultSpacetime::getLinearOctreeHitCheckRounder() �����؂͍쐬����Ă��܂���B\n"
                    "IS_HIT_CHECK_3D �v���p�e�B true �ɂ��Ă��������B\n"
                    "���݂�IS_HIT_CHECK_3D="<<CONFIG::IS_HIT_CHECK_3D );
        }
#endif
        return _pLinearOctreeHitCheckRounder;
    }

    inline GgafCore::GgafLinearQuadtree* getLinearQuadtree() {
#ifdef MY_DEBUG
        if (_pLinearQuadtree == nullptr) {
            throwGgafCriticalException("DefaultSpacetime::getLinearQuadtree() �l���؂͍쐬����Ă��܂���B IS_HIT_CHECK_2D �v���p�e�B true �ɂ��Ă��������B���݂�IS_HIT_CHECK_2D="<<CONFIG::IS_HIT_CHECK_2D );
        }
#endif
        return _pLinearQuadtree;
    }

    inline QuadtreeRounder* getLinearQuadtreeHitCheckRounder() {
#ifdef MY_DEBUG
        if (_pLinearQuadtreeHitCheckRounder == nullptr) {
            throwGgafCriticalException("DefaultSpacetime::_pLinearQuadtreeHitCheckRounder() �l���؂͍쐬����Ă��܂���B IS_HIT_CHECK_2D �v���p�e�B true �ɂ��Ă��������B���݂�IS_HIT_CHECK_2D="<<CONFIG::IS_HIT_CHECK_2D );
        }
#endif
        return _pLinearQuadtreeHitCheckRounder;
    }
    virtual DefaultCamera* getCamera() override { //���ς̖߂�l
        return (DefaultCamera*)_pCamera;
    }

    virtual ~DefaultSpacetime();
};

}
#endif /*GGAFLIB_DEFAULTSPACETIME_H_*/
