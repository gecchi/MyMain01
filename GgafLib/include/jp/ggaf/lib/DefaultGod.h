#ifndef DEFAULTGOD_H_
#define DEFAULTGOD_H_


//#define connectSplineSourceManager(X)      ((GgafLib::SplineSourceConnection*)((P_GOD)->_pSplSrcManager->connect(X)))
#define connectSplineManufactureManager(X) ((GgafLib::SplineManufactureConnection*)((P_GOD)->_pSplManufManager->connect(X)))


namespace GgafLib {
class DefaultGod : public GgafDxCore::GgafDxGod {

public:
    SplineSourceManager* _pSplSrcManager;
    SplineManufactureManager* _pSplManufManager;

    DefaultGod(HINSTANCE prm_hInstance, HWND prm_pHWndPrimary, HWND prm_pHWndSecondary);
    virtual void clean() override;
    virtual ~DefaultGod();
};

}
#endif /*DEFAULTGOD_H_*/
