#ifndef VECEYEACTOR_H_
#define VECEYEACTOR_H_
#include "VVViewer.h"
#include "jp/ggaf/lib/actor/DefaultMeshActor.h"

namespace VVViewer {

/**
 * �e�X�g�G�L�����N�^ .
 * @version 1.00
 * @since 2014/12/15
 * @author Masatoshi Tsuge
 */
class VecEyeActor : public GgafLib::DefaultMeshActor {

public:
    int _hx;
    int _hy;
    int _hz;

    int _hx_prev;
    int _hy_prev;
    int _hz_prev;

    /**
     * �R���X�g���N�^
     * @param prm_name
     * @return
     */
    VecEyeActor(const char* prm_name);

    /**
     * �L�����̏������� .
     */
    void initialize() override;

    /**
     * �L�����̐U�镑������ .
     */
    void processBehavior() override;

    virtual ~VecEyeActor();
};

}
#endif /*VECEYEACTOR_H_*/

