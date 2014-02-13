#ifndef TEKI002_H_
#define TEKI002_H_
#include "jp/ggaf/lib/actor/DefaultMeshActor.h"

namespace Mogera {

/**
 * �e�X�g�G�L�����N�^ .
 * @version 1.00
 * @since 2013/08/30
 * @author Masatoshi Tsuge
 */
class Teki002 : public GgafLib::DefaultMeshActor {

public:
    GgafDxCore::GgafDxAxesMover* pAxMvr_;
    /** �g��k���x���I�u�W�F�N�g */
    GgafDxCore::GgafDxScaler* pScaler_;

    angle angRz_Target_;
    angle angRy_Target_;
    /**
     * �R���X�g���N�^
     * @param prm_name
     * @return
     */
    Teki002(const char* prm_name);

    /**
     * �L�����̏������� .
     */
    void initialize() override;

    /**
     * �L�����̐U�镑������ .
     */
    void processBehavior() override;

    virtual ~Teki002();
};

}
#endif /*TEKI002_H_*/

