#ifndef VVVUNIVERSE_H_
#define VVVUNIVERSE_H_
#include "VVViewer.h"
#include "jp/ggaf/lib/scene/DefaultUniverse.h"

#include "actor/VvvCamera.h"

namespace VVViewer {

/**
 * VVViewer�̂��̐�
 * @version 1.00
 * @since 2012/06/05
 * @author Masatoshi Tsuge
 */
class VvvUniverse : public GgafLib::DefaultUniverse {

public:
    VvvWorld* pWorld_;

    /**
     * �R���X�g���N�^ .
     * @param prm_name ����
     * @param prm_pCam �J�����I�u�W�F�N�g
     */
    VvvUniverse(const char* prm_name, VvvCamera* prm_pCam);

    /**
     * �u���̐��v�̏������� .
     */
    void initialize() override;

    /**
     * �u���̐��v�̐U�镑������ .
     */
    void processBehavior() override {}

    virtual VvvCamera* getCamera() override { //���ς̖߂�l
        return (VvvCamera*)_pCamera;
    }

    virtual ~VvvUniverse();
};

}
#endif /*VVVUNIVERSE_H_*/
