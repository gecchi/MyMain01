#ifndef GGAFDX9PRIMITIVEACTOR_H_
#define GGAFDX9PRIMITIVEACTOR_H_
namespace GgafDx9Core {

/**
 * メッシュアクター.
 * GgafDx9UntransformedActor を継承し、Xファイル定義のメッシュ表示機能を<BR>
 * 追加したアクターです<BR>
 */
class GgafDx9PrimitiveActor : public GgafDx9UntransformedActor {
private:

public:
    /** モデル */
    GgafDx9ModelConnection* _pModelCon;
    GgafDx9PrimitiveModel* _pPrimitiveModel;

    GgafDx9PrimitiveActor(const char* prm_name,
                     const char* prm_meshmodel_name,
                     GgafDx9GeometryMover* prm_pGeoMover,
                     GgafDx9GeometryChecker* prm_pGeoChecker);

    /**
     * ＜OverRide です＞<BR>
     */
    virtual void processDrawMain();

    /**
     * α設定.
     * ＜オーバーライト＞
     * @param prm_fAlpha
     */
    void setAlpha(float prm_fAlpha);

    virtual ~GgafDx9PrimitiveActor(); //デストラクタ
};

}
#endif /*GGAFDX9PRIMITIVEACTOR_H_*/
