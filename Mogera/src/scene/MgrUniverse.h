#ifndef MGRUNIVERSE_H_
#define MGRUNIVERSE_H_
#include "jp/ggaf/lib/scene/DefaultUniverse.h"

#include "actor/MgrCamera.h"
#ifdef P_GOD
    #undef P_UNIVERSE
    #define P_UNIVERSE ((Mogera::MgrUniverse*)(P_GOD->_pUniverse))
    #ifdef P_CAM
        #undef P_CAM
    #endif
    #define P_CAM ((Mogera::MgrCamera*)(P_UNIVERSE->_pCamera))
#else
    #error P_UNIVERSE isnt define
#endif

namespace Mogera {

/**
 * �u���̐��v�̐��` .
 * GgafLib::DefaultUniverse ���p�����u���̐��v�N���X���쐬���ĉ������B
 * @version 1.00
 * @since 2012/02/16
 * @author Masatoshi Tsuge
 */
class MgrUniverse : public GgafLib::DefaultUniverse {

public:
    MgrWorld* pWorld_;

public:
    /**
     * �R���X�g���N�^ .
     * @param prm_name ����
     * @param prm_pCam �J�����I�u�W�F�N�g
     */
    MgrUniverse(const char* prm_name, MgrCamera* prm_pCam);

    /**
     * �u���̐��v�̏������� .
     */
    void initialize() override;

    /**
     * �u���̐��v�̐U�镑������ .
     */
    void processBehavior() override;

    virtual ~MgrUniverse();
};

}
#endif /*MGRUNIVERSE_H_*/
