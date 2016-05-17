#ifndef GGAFDXCORE_GGAFDXMASSMODEL_H_
#define GGAFDXCORE_GGAFDXMASSMODEL_H_
#include "GgafDxCommonHeader.h"
#include "jp/ggaf/dxcore/model/GgafDxModel.h"

namespace GgafDxCore {

#define GGAFDXMASS_MAX_INSTACE_NUM 512

/**
 * Massメッシュモデルクラス(GgafDxMeshActor用) .
 * @version 1.00
 * @since 2016/02/26
 * @author Masatoshi Tsuge
 */
class GgafDxMassModel : public GgafDxModel {
    friend class GgafDxModelManager;

public:
    /**
     * 頂点レイアウト（インスタンス）情報
     */
    class VertexInstaceDataInfo {
    public:
        /** インスタンスデータの頂点レイアウト配列 */
        D3DVERTEXELEMENT9* paElement;
        /** インスタンスデータの頂点レイアウトの要素数 */
        int element_num;
        /** インスタンスデータの１頂点のサイズ */
        UINT size_vertex_unit_instacedata;
        /** デバイスに流し込むインスタンスデータが存在する先頭アドレス */
        void* pInstancedata;
        VertexInstaceDataInfo() {
            paElement = nullptr;
            element_num = 0;
            size_vertex_unit_instacedata = 0;
            pInstancedata = nullptr;
        }
        ~VertexInstaceDataInfo() {
            GGAF_DELETEARR_NULLABLE(paElement);
        }
    };

    /**
     * 頂点レイアウト（モデル）情報
     */
    class VertexModelInfo {
    public:
        /** モデル頂点レイアウト */
        D3DVERTEXELEMENT9* paElement;
        /** モデル頂点レイアウトの要素数 */
        int element_num;
        VertexModelInfo() {
            paElement = nullptr;
            element_num = 0;
        }
        ~VertexModelInfo() {
            GGAF_DELETEARR_NULLABLE(paElement);
        }
    };

    /** デバイスの頂点バッファ（モデル） */
    LPDIRECT3DVERTEXBUFFER9 _pVertexBuffer_model;
    /** デバイスの頂点バッファ（インスタンス：ワールド変換行列情報、マテリアルカラー情報） */
    LPDIRECT3DVERTEXBUFFER9 _pVertexBuffer_instacedata;
    /** デバイスのインデックスバッファ */
    LPDIRECT3DINDEXBUFFER9 _pIndexBuffer;
    /** デバイスのシェーダー入力頂点フォーマット */
    LPDIRECT3DVERTEXDECLARATION9 _pVertexDeclaration;

    /** １頂点のサイズ（モデル） */
    UINT _size_vertex_unit_model;
    /** １頂点のサイズ（インスタンス） */
    UINT _size_vertex_unit_instacedata;
    /** １モデル頂点サイズ計 */
    UINT _size_vertices_model;
    /** モデル頂点数 */
    UINT _nVertices;
    /** モデル面の数 */
    UINT _nFaces;
    /** 頂点バッファ（インスタンスデータ）に流し込むデータ配列の先頭アドレス */
    void* _pInstancedata;
    /**
     * 頂点レイアウト（モデル）情報取得コールバック関数 .
     * @param prm なにかしらのパラメータ
     * @param out_info 頂点レイアウト（モデル）情報が設定される
     */
    void (*_pFunc_getVertexModel)(void* prm, VertexModelInfo* out_info);
    /**
     * 頂点レイアウト（インスタンスデータ）情報取得コールバック関数 .
     * @param prm なにかしらのパラメータ
     * @param out_info 頂点レイアウト（インスタンス）情報が設定される
     */
    void (*_pFunc_getVertexInstaceData)(void* prm, VertexInstaceDataInfo* out_info);

public:
    /**
     * コンストラクタ .
     * @param prm_model_name スプライト定義の識別名。".x"を追加すると定義Xファイル名になる。
     */
    GgafDxMassModel(const char* prm_model_name);

    /**
     * 頂点レイアウト（インスタンスデータ）情報取得コールバック関数を登録する .
     * Modelクラスのコンストラクタ等で呼び出し、登録してください。
     * @param prm_pFunc_getVertexInstaceData 頂点レイアウト（インスタンスデータ）情報取得コールバック関数
     */
    inline void registerCallback_VertexInstaceDataInfo(void (*prm_pFunc_getVertexInstaceData)(void*, VertexInstaceDataInfo*)) {
#ifdef MY_DEBUG
        if (_pFunc_getVertexInstaceData && _pFunc_getVertexInstaceData != prm_pFunc_getVertexInstaceData) {
            throwGgafCriticalException("既に頂点レイアウトは作成済みにもかかわらず、別の定義関数を設定しようとしました。(1)");
        }
#endif
        _pFunc_getVertexInstaceData = prm_pFunc_getVertexInstaceData;
        if (_pFunc_getVertexInstaceData && _pFunc_getVertexModel) {
            if (_pVertexBuffer_instacedata == nullptr) {
                createVertexElements();
            }
        }
    }
    /**
     * 頂点レイアウト（モデル）情報取得コールバック関数を登録する .
     * Actorクラスのコンストラクタ等で呼び出し、登録してください。
     * @param prm_pFunc_getVertexModel  頂点レイアウト（モデルデータ）情報取得コールバック関数
     */
    inline void registerCallback_VertexModelInfo(void (*prm_pFunc_getVertexModel)(void*, VertexModelInfo*)) {
#ifdef MY_DEBUG
        if (_pFunc_getVertexModel && _pFunc_getVertexModel != prm_pFunc_getVertexModel) {
            throwGgafCriticalException("既に頂点レイアウトは作成済みにもかかわらず、別の定義関数を設定しようとしました。(2)");
        }
#endif
        _pFunc_getVertexModel = prm_pFunc_getVertexModel;
        if (_pFunc_getVertexInstaceData && _pFunc_getVertexModel) {
            if (_pVertexBuffer_instacedata == nullptr) {
                createVertexElements();
            }
        }
    }

    /**
     * モデルの頂点レイアウト、頂点インスタンスデータの作成 .
     */
    void createVertexElements();

    virtual void resetStreamSourceFreq();

    virtual void onDeviceLost() override;

    virtual void release() override;


    /**
     * デストラクタ<BR>
     */
    virtual ~GgafDxMassModel(); //デストラクタ
};

}
#endif /*GGAFDXCORE_GGAFDXMESHSETMODEL_H_*/
