#ifndef GGAFLIB_DEFAULTUNIVERSE_H_
#define GGAFLIB_DEFAULTUNIVERSE_H_
#include "jp/ggaf/dxcore/scene/GgafDxUniverse.h"

#include "jp/ggaf/lib/DefaultGod.h"
#include "jp/ggaf/lib/actor/DefaultCamera.h"

#ifdef P_GOD
    #undef P_UNIVERSE
    #define P_UNIVERSE ((GgafLib::DefaultUniverse*)(P_GOD->_pUniverse))
    #undef P_CAM
    #define P_CAM ((GgafLib::DefaultCamera*)(P_UNIVERSE->_pCamera))
#else
    #undef P_UNIVERSE
    #undef P_CAM
#endif

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

    virtual ~DefaultUniverse();
};

}
#endif /*GGAFLIB_DEFAULTUNIVERSE_H_*/
