#ifndef GGAFLIB_DEFAULTSPACETIME_H_
#define GGAFLIB_DEFAULTSPACETIME_H_
#include "GgafLibCommonHeader.h"
#include "jp/ggaf/dxcore/scene/GgafDxSpacetime.h"

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
    GgafCore::GgafLinearOctreeForActor* _pLinearOctree;

public:
    DefaultSpacetime(const char* prm_name, DefaultCamera* prm_pCamera);

    inline GgafCore::GgafLinearOctreeForActor* getLinearOctree() const {
        return _pLinearOctree;
    }
    virtual DefaultCamera* getCamera() override { //���ς̖߂�l
        return (DefaultCamera*)_pCamera;
    }

    virtual ~DefaultSpacetime();
};

}
#endif /*GGAFLIB_DEFAULTSPACETIME_H_*/
