#ifndef HGRSPACETIME_H_
#define HGRSPACETIME_H_
#include "Hogera.h"
#include "jp/ggaf/lib/scene/DefaultSpacetime.h"

#include "actor/camera/HgrCamera.h"

namespace Hogera {

/**
 * �u���̐��v�̐��` .
 * GgafLib::DefaultSpacetime ���p�����u���̐��v�N���X���쐬���ĉ������B
 * @version 1.00
 * @since 2012/02/16
 * @author Masatoshi Tsuge
 */
class HgrSpacetime : public GgafLib::DefaultSpacetime {

public:
    HgrWorld* pWorld_;

public:
    /**
     * �R���X�g���N�^ .
     * @param prm_name ����
     * @param prm_pCam �J�����I�u�W�F�N�g
     */
    HgrSpacetime(const char* prm_name, HgrCamera* prm_pCam);

    /**
     * �u���̐��v�̏������� .
     */
    void initialize() override;

    /**
     * �u���̐��v�̐U�镑������ .
     */
    void processBehavior() override;

    HgrCamera* getCamera() override { //���ς̖߂�l
        return (HgrCamera*)_pCamera;
    }
    HgrWorld* getWorld() {
        return pWorld_;
    }
    virtual ~HgrSpacetime();
};

}
#endif /*HGRSPACETIME_H_*/
