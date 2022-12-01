#ifndef VVVSPACETIME_H_
#define VVVSPACETIME_H_
#include "VVViewer.h"
#include "jp/ggaf/lib/scene/DefaultSpacetime.h"

#include "actor/VvvCamera.h"

namespace VVViewer {

/**
 * VVViewer�̂��̐�
 * @version 1.00
 * @since 2012/06/05
 * @author Masatoshi Tsuge
 */
class VvvSpacetime : public GgafLib::DefaultSpacetime {

public:
    VvvWorld* pWorld_;

    /**
     * �R���X�g���N�^ .
     * @param prm_name ����
     * @param prm_pCam �J�����I�u�W�F�N�g
     */
    VvvSpacetime(const char* prm_name, VvvCamera* prm_pCam);

    /**
     * �u���̐��v�̏������� .
     */
    void initialize() override;

    /**
     * �u���̐��v�̐U�镑������ .
     */
    void processBehavior() override;

    virtual VvvCamera* getCamera() override { //���ς̖߂�l
        return (VvvCamera*)_pCamera;
    }

    virtual ~VvvSpacetime();
};

}
#endif /*VVVSPACETIME_H_*/
