#ifndef MGRUNIVERSE_H_
#define MGRUNIVERSE_H_
#include "Mogera.h"
#include "jp/ggaf/lib/scene/DefaultUniverse.h"

#include "actor/camera/MgrCamera.h"

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

    MgrCameraWorker* pActiveCamWorker_;
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

    virtual MgrCamera* getCamera() override { //���ς̖߂�l
        return (MgrCamera*)_pCamera;
    }

    virtual ~MgrUniverse();
};

}
#endif /*MGRUNIVERSE_H_*/
