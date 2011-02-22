#ifndef GGAFDX9PUPPETEER_H_
#define GGAFDX9PUPPETEER_H_
namespace GgafDx9Core {

/**
 * 操り人形遣い .
 * @version 1.00
 * @since 2011/02/22
 * @author Masatoshi Tsuge
 */
class GgafDx9Puppeteer : public GgafCore::GgafObject {
private:

public:
    /** 操られる者 */
    GgafDx9DynaD3DXMeshActor* _pPuppet;

    /**
     * コンストラクタ .
     * @param prm_pActor 操られる者
     * @return
     */
    GgafDx9Puppeteer(GgafDx9DynaD3DXMeshActor* prm_pPuppet);


    virtual ~GgafDx9Puppeteer();



    /**
     * アニメーションを1フレーム分進行させる .
     * 本メソッドを、processBehavior() 等で毎フレーム呼び出す必要があります。<BR>
     * 呼び出すことで、setFlipMethod()で設定した方法に応じて<BR>
     * アクティブなパターン番号(_pattno_uvflip_now)が内部で切り替わります。<BR>
     */
    virtual void behave();


};

}
#endif /*GGAFDX9PUPPETEER_H_*/
