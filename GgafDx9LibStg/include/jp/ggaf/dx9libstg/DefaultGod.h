#ifndef DEFAULTGOD_H_
#define DEFAULTGOD_H_

namespace GgafDx9LibStg {

#define getSplineSourceManager() ((P_GOD)->_pSplineSourceManager)

class DefaultGod : public GgafDx9Core::GgafDx9God {

public:
    SplineSourceManager* _pSplineSourceManager;
    SplineManufactureManager* _pSplineManufactureManager;

    DefaultGod(HINSTANCE prm_hInstance, HWND prm_pHWndPrimary, HWND prm_pHWndSecondary);
    virtual void clean() override;
    virtual ~DefaultGod();
};

}
#endif /*DEFAULTGOD_H_*/
