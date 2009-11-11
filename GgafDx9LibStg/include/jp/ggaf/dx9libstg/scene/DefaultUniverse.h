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

    GgafCore::GgafLinearOctree* _pLinearOctree;

    DefaultUniverse(const char* prm_name);

    virtual void nextFrame();
    /**
     * 8分木ルート空間更新
     * GgafDx9Camera::processBehavior()
     * ルート空間を決める「カメラ座標移動」 より後、かつ
     * GgafDx9GeometricActor::processPreJudgement() の _pChecker->updateHitArea();
     * 「オブジェクトの所属空間更新」 よりも前に実行する必要がある。
     * ルート空間更新実行の場所を変えるときは上記に注意を払うこと
     */
    virtual void processJudgement();

    virtual ~DefaultUniverse();
};

}
#endif /*DEFAULTUNIVERSE_H_*/
