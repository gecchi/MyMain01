#ifndef GGAF_DX_D3DXMESHMODEL_H_
#define GGAF_DX_D3DXMESHMODEL_H_
#include "jp/ggaf/GgafDxCommonHeader.h"
#include "jp/ggaf/dx/model/Model.h"

#include <d3dx9.h>
#ifdef __GNUG__
    #undef __in
    #undef __out
#endif


namespace GgafDx {

/**
 * メッシュモデルクラス(D3DXActor用).
 * D3DXMeshModel は D3DXLoadMeshFromX を使用して、Xファイルからモデルデータを読み込み、<BR>
 * 描画する機能を持った静的モデル用のクラスです。
 * ＜長所＞
 * ・D3DXLoadMeshFromX を使用して読み込むため、複雑なXファイルでも問題なく読みこみ描画できる。
 * ・法線優先。モデリングツールで作ったとおりの見た目になる。
 * ＜短所＞
 * ・他のモデルクラス郡に比べて、速度面で劣る。読み込んで DrawSubset() するだけ。
 * @version 1.00
 * @since 2008/02/22
 * @author Masatoshi Tsuge
 */
class D3DXMeshModel : public Model {
    friend class ModelManager;

public:
    /** メッシュ(インスタンスはモデル毎） */
    LPD3DXMESH _pID3DXMesh;
    /** D3DXLoadMeshFromXのオプション */
    DWORD _dwOptions;

public:
    /**
     * コンストラクタ<BR>
     * @param prm_model モデルの識別名。".modelx"を追加するとモデル定義ファイル名になる。
     * @param prm_dwOptions D3DXLoadMeshFromXのオプション
     * @return
     */
    D3DXMeshModel(const char* prm_model, DWORD prm_dwOptions);

    virtual HRESULT draw(FigureActor* prm_pActor_target, int prm_draw_set_num = 1, void* prm_pPrm = nullptr) override;

    virtual void restore() override;

    virtual void onDeviceLost() override;

    void release() override;

    /**
     * デストラクタ<BR>
     * deleteするのはD3DXMeshModelManagerである<BR>
     */
    virtual ~D3DXMeshModel();

};

}
#endif /*GGAF_DX_D3DXMESHMODEL_H_*/
