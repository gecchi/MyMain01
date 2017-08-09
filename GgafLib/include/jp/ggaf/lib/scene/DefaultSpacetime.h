#ifndef GGAFLIB_DEFAULTSPACETIME_H_
#define GGAFLIB_DEFAULTSPACETIME_H_
#include "GgafLibCommonHeader.h"
#include "jp/ggaf/dxcore/scene/GgafDxSpacetime.h"

#include "jp/ggaf/core/util/GgafLinearTreeRounder.hpp"
#include "jp/ggaf/lib/actor/camera/DefaultCamera.h"

namespace GgafLib {

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
    GgafCore::GgafLinearTreeRounder<GgafCore::GgafActor, 3>* _pLinearOctreeHitCheckRounder;
    GgafCore::GgafLinearQuadtree* _pLinearQuadtree;
    GgafCore::GgafLinearTreeRounder<GgafCore::GgafActor, 2>* _pLinearQuadtreeHitCheckRounder;
public:
    DefaultSpacetime(const char* prm_name, DefaultCamera* prm_pCamera);

    inline GgafCore::GgafLinearOctree* getLinearOctree() {
        return _pLinearOctree;
    }
    inline GgafCore::GgafLinearTreeRounder<GgafCore::GgafActor, 3>* getLinearOctreeHitCheckRounder() {
        return _pLinearOctreeHitCheckRounder;
    }
    inline GgafCore::GgafLinearQuadtree* getLinearQuadtree() {
        return _pLinearQuadtree;
    }
    inline GgafCore::GgafLinearTreeRounder<GgafCore::GgafActor, 2>* getLinearQuadtreeHitCheckRounder() {
        return _pLinearQuadtreeHitCheckRounder;
    }
    virtual DefaultCamera* getCamera() override { //���ς̖߂�l
        return (DefaultCamera*)_pCamera;
    }

    virtual ~DefaultSpacetime();
};

}
#endif /*GGAFLIB_DEFAULTSPACETIME_H_*/
