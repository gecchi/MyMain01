#ifndef VVSPACETIME_H_
#define VVSPACETIME_H_
#include "VioletVrain.h"
#include "jp/ggaf/lib/scene/DefaultSpacetime.h"

#include "actor/camera/VvCamera.h"

namespace VioletVrain {

/**
 * �u���̐��v�̐��` .
 * GgafLib::DefaultSpacetime ���p�����u���̐��v�N���X���쐬���ĉ������B
 * @version 1.00
 * @since 2012/02/16
 * @author Masatoshi Tsuge
 */
class VvSpacetime : public GgafLib::DefaultSpacetime {

public:
    VvWorld* pWorld_;

public:
    /**
     * �R���X�g���N�^ .
     * @param prm_name ����
     * @param prm_pCam �J�����I�u�W�F�N�g
     */
    VvSpacetime(const char* prm_name, VvCamera* prm_pCam);

    /**
     * �u���̐��v�̏������� .
     */
    void initialize() override;

    /**
     * �u���̐��v�̐U�镑������ .
     */
    void processBehavior() override;

    VvCamera* getCamera() override { //���ς̖߂�l
        return (VvCamera*)_pCamera;
    }
    VvWorld* getWorld() {
        return pWorld_;
    }
    virtual ~VvSpacetime();
};

}
#endif /*VVSPACETIME_H_*/
