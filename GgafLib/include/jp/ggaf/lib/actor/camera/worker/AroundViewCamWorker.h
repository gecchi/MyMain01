#ifndef GGAF_LIB_AROUNDVIEWCAMWORKER_H_
#define GGAF_LIB_AROUNDVIEWCAMWORKER_H_
#include "jp/ggaf/GgafLibCommonHeader.h"
#include "CameraWorker.h"
#include "jp/ggaf/lib/DefaultCaretaker.h"

namespace GgafLib {

/**
 * 一時停止時のカメラマン .
 * @version 1.00
 * @since 2010/10/25
 * @author Masatoshi Tsuge
 */
class AroundViewCamWorker : public CameraWorker {

public:
    int _cd;
    bool _mdz_flg;
    double _mdz_vx, _mdz_vy, _mdz_vz, _mdz_t;
    int _mdz_total;
    bool _isPressed0,_isPressed1, _isPressed2;
    bool _onScreen;
    HWND _hWnd_last;
public:
    AroundViewCamWorker(const char* prm_name, DefaultCamera* prm_pCamera,
                       frame prm_slide_frames = 60, double prm_slide_p1 = 0.3, double prm_slide_p2 = 0.7);


    virtual void initialize() override;

    virtual void onActive() override;
    virtual void processBehavior() override;

    virtual void processJudgement() override {
    }


    virtual ~AroundViewCamWorker();
};

}
#endif /*GGAF_LIB_AROUNDVIEWCAMWORKER_H_*/
