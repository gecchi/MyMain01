#ifndef DEFAULTUNIVERSE_H_
#define DEFAULTUNIVERSE_H_

#ifdef P_UNIVERSE
    #define P_CAM ((GgafDx9LibStg::DefaultCamera*)(P_UNIVERSE->_pCamera))
#else
    #error P_UNIVERSE isnt define
#endif

namespace GgafDx9LibStg {

/**
 * 「この世」クラスインターフェイス.
 * GgafDx9Core::GgafDx9Universe を継承しただけのインターフェースです。<BR>
 * Ggafライブラリを利用する場合、本クラスを継承し実装したこの世クラスが必要です。<BR>
 * (旧DefaultWorld)
 * @version 1.00
 * @since 2008/07/30
 * @author Masatoshi Tsuge
 */
class DefaultUniverse : public GgafDx9Core::GgafDx9Universe {

public:

    LinearOctreeForActor* _pLinearOctree;

    DefaultUniverse(const char* prm_name, GgafDx9Core::GgafDx9Camera* prm_pCamera);


    virtual void processFinal() override;

    virtual ~DefaultUniverse();
};

}
#endif /*DEFAULTUNIVERSE_H_*/
