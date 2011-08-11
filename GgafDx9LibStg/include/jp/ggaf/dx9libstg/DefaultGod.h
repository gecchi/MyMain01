#ifndef DEFAULTGOD_H_
#define DEFAULTGOD_H_


#define connectSplineSourceManager(X)      ((GgafDx9LibStg::SplineSourceConnection*)((P_GOD)->_pSplSourceManager->connect(X)))
#define connectSplineManufactureManager(X) ((GgafDx9LibStg::SplineManufactureConnection*)((P_GOD)->_pSplManufManager->connect(X)))


namespace GgafDx9LibStg {
class DefaultGod : public GgafDx9Core::GgafDx9God {

public:
    SplineSourceManager* _pSplSourceManager;
    SplineManufactureManager* _pSplManufManager;

    DefaultGod(HINSTANCE prm_hInstance, HWND prm_pHWndPrimary, HWND prm_pHWndSecondary);
    virtual void clean() override;
    virtual ~DefaultGod();
};

}
#endif /*DEFAULTGOD_H_*/
