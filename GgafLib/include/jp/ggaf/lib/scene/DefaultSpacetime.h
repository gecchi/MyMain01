#ifndef GGAF_LIB_DEFAULTSPACETIME_H_
#define GGAF_LIB_DEFAULTSPACETIME_H_
#include "GgafLibCommonHeader.h"
#include "jp/ggaf/dx/scene/Spacetime.h"

#include "jp/ggaf/lib/LibConfig.h"
#include "jp/ggaf/core/util/LinearTreeRounder.hpp"
#include "jp/ggaf/lib/actor/camera/DefaultCamera.h"


namespace GgafLib {

typedef GgafCore::LinearTreeRounder<GgafCore::Actor, 3> OctreeRounder;
typedef GgafCore::LinearTreeRounder<GgafCore::Actor, 2> QuadtreeRounder;

typedef GgafCore::LinearTreeRounder<GgafCore::Actor, 2> QuadtreeRounder_b;
/**
 * �u���̐��v�N���X�C���^�[�t�F�C�X.
 * GgafDx::Spacetime ���p�����������̃C���^�[�t�F�[�X�ł��B<BR>
 * ggaf ���C�u�����𗘗p����ꍇ�A�{�N���X���p���������������̐��N���X���K�v�ł��B<BR>
 * (��DefaultWorld)
 * @version 1.00
 * @since 2008/07/30
 * @author Masatoshi Tsuge
 */
class DefaultSpacetime : public GgafDx::Spacetime {
    virtual void processFinal() override;

public:
    GgafCore::LinearOctree* _pLinearOctree;
    OctreeRounder* _pLinearOctreeHitCheckRounder;
    GgafCore::LinearQuadtree* _pLinearQuadtree;
    QuadtreeRounder* _pLinearQuadtreeHitCheckRounder;

    GgafCore::LinearQuadtree* _pLinearQuadtree_b;
    QuadtreeRounder_b* _pLinearQuadtreeHitCheckRounder_b;

public:
    DefaultSpacetime(const char* prm_name, DefaultCamera* prm_pCamera);

    inline GgafCore::LinearOctree* getLinearOctree() {
#ifdef MY_DEBUG
        if (_pLinearOctree == nullptr) {
            throwCriticalException("DefaultSpacetime::getLinearOctree() �����؂͍쐬����Ă��܂���B\n"
                    "IS_HIT_CHECK_3D �v���p�e�B true �ɂ��Ă��������B\n"
                    "���݂�IS_HIT_CHECK_3D="<<CONFIG::IS_HIT_CHECK_3D );
        }
#endif
        return _pLinearOctree;
    }

    inline OctreeRounder* getLinearOctreeHitCheckRounder() {
#ifdef MY_DEBUG
        if (_pLinearOctreeHitCheckRounder == nullptr) {
            throwCriticalException("DefaultSpacetime::getLinearOctreeHitCheckRounder() �����؂͍쐬����Ă��܂���B\n"
                    "IS_HIT_CHECK_3D �v���p�e�B true �ɂ��Ă��������B\n"
                    "���݂�IS_HIT_CHECK_3D="<<CONFIG::IS_HIT_CHECK_3D );
        }
#endif
        return _pLinearOctreeHitCheckRounder;
    }

    inline GgafCore::LinearQuadtree* getLinearQuadtree() {
#ifdef MY_DEBUG
        if (_pLinearQuadtree == nullptr) {
            throwCriticalException("DefaultSpacetime::getLinearQuadtree() �l���؂͍쐬����Ă��܂���B IS_HIT_CHECK_2D �v���p�e�B true �ɂ��Ă��������B���݂�IS_HIT_CHECK_2D="<<CONFIG::IS_HIT_CHECK_2D );
        }
#endif
        return _pLinearQuadtree;
    }

    inline QuadtreeRounder* getLinearQuadtreeHitCheckRounder() {
#ifdef MY_DEBUG
        if (_pLinearQuadtreeHitCheckRounder == nullptr) {
            throwCriticalException("DefaultSpacetime::_pLinearQuadtreeHitCheckRounder() �l���؂͍쐬����Ă��܂���B IS_HIT_CHECK_2D �v���p�e�B true �ɂ��Ă��������B���݂�IS_HIT_CHECK_2D="<<CONFIG::IS_HIT_CHECK_2D );
        }
#endif
        return _pLinearQuadtreeHitCheckRounder;
    }

    inline GgafCore::LinearQuadtree* getLinearQuadtree_b() {
#ifdef MY_DEBUG
        if (_pLinearQuadtree_b == nullptr) {
            throwCriticalException("DefaultSpacetime::getLinearQuadtree_b() �l���؂͍쐬����Ă��܂���B");
        }
#endif
        return _pLinearQuadtree_b;
    }

    inline QuadtreeRounder* getLinearQuadtreeHitCheckRounder_b() {
#ifdef MY_DEBUG
        if (_pLinearQuadtreeHitCheckRounder_b == nullptr) {
            throwCriticalException("DefaultSpacetime::_pLinearQuadtreeHitCheckRounder_b() �l���؂͍쐬����Ă��܂���B");
        }
#endif
        return _pLinearQuadtreeHitCheckRounder_b;
    }

    virtual void executeWorldHitCheck(kind_t prm_kind_groupA, kind_t prm_kind_groupB);

    virtual void executeViewHitCheck(kind_t prm_kind_groupA, kind_t prm_kind_groupB);


    virtual DefaultCamera* getCamera() override { //���ς̖߂�l
        return (DefaultCamera*)_pCamera;
    }

    virtual ~DefaultSpacetime();
};

}
#endif /*GGAF_LIB_DEFAULTSPACETIME_H_*/
