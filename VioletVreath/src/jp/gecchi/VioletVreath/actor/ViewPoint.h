#ifndef VIEWPOINT_H_
#define VIEWPOINT_H_
#include "jp/ggaf/dxcore/actor/GgafDxCameraViewPoint.h"

namespace VioletVreath {

/**
 * ���_.
 * @version 1.00
 * @since 2013/12/05
 * @author Masatoshi Tsuge
 */
class ViewPoint : public GgafDxCore::GgafDxCameraViewPoint {
public:
    /** ���s�ړ��x�� */
    GgafDxCore::GgafDxAxesMover* pAxMver_;
    /** ���߂̏���A */
    GgafDxCore::GgafDxKurokoAsstA* pKurokoAsstA_;

public:
    ViewPoint(const char* prm_name);

    virtual void initialize() override;

    virtual void processBehavior() override;

    virtual ~ViewPoint(); //�f�X�g���N�^
};

}
#endif /*VIEWPOINT_H_*/
