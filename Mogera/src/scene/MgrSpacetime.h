#ifndef MGRSPACETIME_H_
#define MGRSPACETIME_H_
#include "Mogera.h"
#include "jp/ggaf/lib/scene/DefaultSpacetime.h"

#include "actor/camera/MgrCamera.h"

namespace Mogera {

/**
 * �u���̐��v�̐��` .
 * GgafLib::DefaultSpacetime ���p�����u���̐��v�N���X���쐬���ĉ������B
 * @version 1.00
 * @since 2012/02/16
 * @author Masatoshi Tsuge
 */
class MgrSpacetime : public GgafLib::DefaultSpacetime {

public:
    MgrWorld* pWorld_;

    MgrCameraWorker* pActiveCamWorker_;
public:
    /**
     * �R���X�g���N�^ .
     * @param prm_name ����
     * @param prm_pCam �J�����I�u�W�F�N�g
     */
    MgrSpacetime(const char* prm_name, MgrCamera* prm_pCam);

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

    virtual ~MgrSpacetime();
};

}
#endif /*MGRSPACETIME_H_*/
