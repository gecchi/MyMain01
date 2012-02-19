#ifndef DEFAULTUNIVERSE_H_
#define DEFAULTUNIVERSE_H_

#ifdef P_UNIVERSE
    #ifdef P_CAM
        #undef P_CAM
    #endif
    #define P_CAM ((GgafLib::DefaultCamera*)(P_UNIVERSE->_pCamera))
#else
    #error P_UNIVERSE isnt define
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

    DefaultUniverse(const char* prm_name, DefaultCamera* prm_pCamera);

    virtual ~DefaultUniverse();
};

}
#endif /*DEFAULTUNIVERSE_H_*/
