#ifndef VVVCAMERA_H_
#define VVVCAMERA_H_
#include "jp/ggaf/lib/actor/DefaultCamera.h"

namespace VVViewer {

/**
 * VVViewerฬJ .
 * @version 1.00
 * @since 2012/06/05
 * @author Masatoshi Tsuge
 */
class VvvCamera : public GgafLib::DefaultCamera {
public:
    /** ฝsฺฎx */
    GgafDxCore::GgafDxAxesMover* pAxMver_;
    /** ฿ฬ่A */
    GgafDxCore::GgafDxKurokoAsstA* pKurokoAsstA_;
public:
    VvvCamera(const char* prm_name);
    GgafDxCore::GgafDxCameraViewPoint* createViewPoint() override;
    void processBehavior() override;
    virtual ~VvvCamera();
};

}
#endif /*VVVCAMERAH_*/
