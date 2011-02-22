#ifndef GGAFDX9MARIONNETTISTE_H_
#define GGAFDX9MARIONNETTISTE_H_
namespace GgafDx9Core {

/**
 * テクスチャUVフリッパー.
 * テクスチャをパラパラアニメが如く切り替える事を簡単に行うために
 * 作成したクラス。
 * @version 1.00
 * @since 2010/02/16
 * @author Masatoshi Tsuge
 */
class GgafDx9Marionnettiste : public GgafCore::GgafObject {
private:

public:
    GgafDx9GeometricActor* _pActor;

    GgafDx9Marionnettiste(GgafDx9GeometricActor* prm_pActor);


    virtual ~GgafDx9Marionnettiste();



    /**
     * アニメーションを1フレーム分進行させる .
     * 本メソッドを、processBehavior() 等で毎フレーム呼び出す必要があります。<BR>
     * 呼び出すことで、setFlipMethod()で設定した方法に応じて<BR>
     * アクティブなパターン番号(_pattno_uvflip_now)が内部で切り替わります。<BR>
     */
    virtual void behave();


};

}
#endif /*GGAFDX9SPRITEMESHACTOR_H_*/
