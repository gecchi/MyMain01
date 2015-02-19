#ifndef GGAFDXCORE_GGAFDXD3DXMESHMODEL_H_
#define GGAFDXCORE_GGAFDXD3DXMESHMODEL_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/dxcore/model/GgafDxModel.h"

#include <d3dx9.h>

namespace GgafDxCore {

/**
 * メッシュモデルクラス(GgafDxD3DXActor用).
 * GgafDxD3DXMeshModel は D3DXLoadMeshFromX を使用して、Xファイルからモデルデータを読み込み、<BR>
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
class GgafDxD3DXMeshModel : public GgafDxModel {
    friend class GgafDxModelManager;

public:
    /** メッシュ(インスタンスはモデル毎） */
    LPD3DXMESH _pID3DXMesh;
    /** D3DXLoadMeshFromXのオプション */
    DWORD _dwOptions;

public:
    /**
     * コンストラクタ<BR>
     * @param prm_model モデルの識別名。".x"を追加すると定義Xファイル名になる。
     * @param prm_dwOptions D3DXLoadMeshFromXのオプション
     * @return
     */
    GgafDxD3DXMeshModel(char* prm_model, DWORD prm_dwOptions);

    virtual HRESULT draw(GgafDxFigureActor* prm_pActor_target, int prm_draw_set_num = 1) override;

    virtual void restore() override;

    virtual void onDeviceLost() override;

    void release() override;

    /**
     * デストラクタ<BR>
     * deleteするのはGgafDxD3DXMeshModelManagerである<BR>
     */
    virtual ~GgafDxD3DXMeshModel(); //デストラクタ

};

}
#endif /*GGAFDXCORE_GGAFDXD3DXMESHMODEL_H_*/
