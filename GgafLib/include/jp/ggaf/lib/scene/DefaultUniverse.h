#ifndef GGAFLIB_DEFAULTUNIVERSE_H_
#define GGAFLIB_DEFAULTUNIVERSE_H_
#include "GgafLibCommonHeader.h"
#include "jp/ggaf/dxcore/scene/GgafDxUniverse.h"

#include "jp/ggaf/lib/actor/camera/DefaultCamera.h"

namespace GgafLib {

/**
 * �u���̐��v�N���X�C���^�[�t�F�C�X.
 * GgafDxCore::GgafDxUniverse ���p�����������̃C���^�[�t�F�[�X�ł��B<BR>
 * Ggaf���C�u�����𗘗p����ꍇ�A�{�N���X���p���������������̐��N���X���K�v�ł��B<BR>
 * (��DefaultWorld)
 * @version 1.00
 * @since 2008/07/30
 * @author Masatoshi Tsuge
 */
class DefaultUniverse : public GgafDxCore::GgafDxUniverse {
    virtual void processFinal() override;

public:
    LinearOctreeForActor* _pLinearOctree;

public:
    DefaultUniverse(const char* prm_name, DefaultCamera* prm_pCamera);

    inline LinearOctreeForActor* getLinearOctree() {
        return _pLinearOctree;
    }
    virtual DefaultCamera* getCamera() override { //���ς̖߂�l
        return (DefaultCamera*)_pCamera;
    }

    virtual ~DefaultUniverse();
};

}
#endif /*GGAFLIB_DEFAULTUNIVERSE_H_*/
