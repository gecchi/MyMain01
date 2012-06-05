#ifndef SMPUNIVERSE_H_
#define SMPUNIVERSE_H_

#ifdef P_UNIVERSE
    #ifdef P_CAM
        #undef P_CAM
    #endif
    #define P_CAM ((VVViewer::VvvCamera*)(P_UNIVERSE->_pCamera))
#else
    #error P_UNIVERSE isnt define
#endif

namespace VVViewer {

/**
 * VVViewerのこの世
 * @version 1.00
 * @since 2012/06/05
 * @author Masatoshi Tsuge
 */
class VvvUniverse : public GgafLib::DefaultUniverse {

public:
    VvvWorld* pWorld_;

    /**
     * コンストラクタ .
     * @param prm_name 名称
     * @param prm_pCam カメラオブジェクト
     */
    VvvUniverse(const char* prm_name, VvvCamera* prm_pCam);

    /**
     * 「この世」の初期処理 .
     */
    void initialize() override;

    /**
     * 「この世」の振る舞い処理 .
     */
    void processBehavior() override {}

    virtual ~VvvUniverse();
};

}
#endif /*SMPUNIVERSE_H_*/
