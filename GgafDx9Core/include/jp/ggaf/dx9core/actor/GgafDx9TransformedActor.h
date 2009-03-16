#ifndef GGAFDX9TRANSFORMEDACTOR_H_
#define GGAFDX9TRANSFORMEDACTOR_H_
namespace GgafDx9Core {

/**
 * 変換済み座標のアクター.
 * 変換済み座標（x座標、y座標、深度）を持った<BR>
 * アクターです<BR>
 */
class GgafDx9TransformedActor : public GgafDx9BaseActor {

private:

    /**
     * ＜OverRide です＞<BR>
     */
    virtual bool isOffscreen() {
        return false;
    }

public:

    /** マテリアル配列 */
    D3DMATERIAL9* _paD3DMaterial9;

    /** 画面X座標 */
    float _x;
    /** 画面X座標 */
    float _y;
    /** 画面Z座標 */
    float _z;

    GgafDx9TransformedActor(const char* prm_name);


    virtual void processDrawPrior();


    virtual GgafDx9TransformedActor* getPrev() {
        return (GgafDx9TransformedActor*)GgafActor::getPrev();
    }

    virtual GgafDx9TransformedActor* getNext() {
        return (GgafDx9TransformedActor*)GgafActor::getNext();
    }

    virtual ~GgafDx9TransformedActor(); //デストラクタ

};

}
#endif /*GGAFDX9TRANSFORMEDACTOR_H_*/
