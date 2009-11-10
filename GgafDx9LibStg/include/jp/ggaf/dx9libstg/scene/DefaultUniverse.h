#ifndef DEFAULTUNIVERSE_H_
#define DEFAULTUNIVERSE_H_
namespace GgafDx9LibStg {

/**
 * 「この世」クラスインターフェイス.
 * GgafDx9Core::GgafDx9Universe を継承しただけのインターフェースです。<BR>
 * Ggafライブラリを利用する場合、本クラスを継承し実装したこの世クラスが必要です。<BR>
 */
class DefaultUniverse : public GgafDx9Core::GgafDx9Universe {

public:

    GgafCore::GgafLinearOctree<StgChecker>* _pLinearOctree;

    DefaultUniverse(const char* prm_name);

    virtual void nextFrame();

    virtual ~DefaultUniverse();
};

}
#endif /*DEFAULTUNIVERSE_H_*/
