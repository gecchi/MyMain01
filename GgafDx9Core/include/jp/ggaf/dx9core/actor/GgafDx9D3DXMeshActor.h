#ifndef GGAFDX9D3DXMESHACTOR_H_
#define GGAFDX9D3DXMESHACTOR_H_
namespace GgafDx9Core {

/**
 * メッシュアクター.
 * GgafDx9UntransformedActor を継承し、Xファイル定義のメッシュ表示機能を<BR>
 * 追加したアクターです<BR>
 */
class GgafDx9D3DXMeshActor : public GgafDx9UntransformedActor {
private:

public:
    /** モデル */
    GgafDx9ModelConnection* _pModelCon;
    GgafDx9D3DXMeshModel* _pD3DXMeshModel;

    GgafDx9D3DXMeshActor(const char* prm_name,
                     const char* prm_model,
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

    virtual ~GgafDx9D3DXMeshActor(); //デストラクタ
};

}
#endif /*GGAFDX9D3DXMESHACTOR_H_*/
