#ifndef GGAF_DX_MASSMODEL_H_
#define GGAF_DX_MASSMODEL_H_
#include "jp/ggaf/GgafDxCommonHeader.h"
#include "jp/ggaf/dx/model/Model.h"

namespace GgafDx {

#define GGAFDXMASS_MAX_INSTANCE_NUM 512

/**
 * Massモデル基底クラス .
 * @version 1.00
 * @since 2016/02/26
 * @author Masatoshi Tsuge
 */
class MassModel : public Model {
    friend class ModelManager;

public:
    /**
     * 頂点レイアウト（インスタンス）情報
     */
    class VertexInstanceDataInfo {
    public:
        /** インスタンスデータの頂点レイアウト配列 */
        D3DVERTEXELEMENT9* paElement;
        /** インスタンスデータの頂点レイアウトの要素数 */
        int element_num;
        /** インスタンスデータの１頂点のサイズ */
        UINT size_vertex_unit_instancedata;
        /** デバイスに流し込むインスタンスデータが存在する先頭アドレス */
        void* pInstancedata;
        VertexInstanceDataInfo() {
            paElement = nullptr;
            element_num = 0;
            size_vertex_unit_instancedata = 0;
            pInstancedata = nullptr;
        }
        ~VertexInstanceDataInfo() {
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
    LPDIRECT3DVERTEXBUFFER9 _paVertexBuffer_model;
    /** デバイスの頂点バッファ（インスタンス：ワールド変換行列情報、マテリアルカラー情報） */
    LPDIRECT3DVERTEXBUFFER9 _paVertexBuffer_instancedata;
    /** デバイスのインデックスバッファ */
    LPDIRECT3DINDEXBUFFER9 _paIndexBuffer;
    /** デバイスのシェーダー入力頂点フォーマット */
    LPDIRECT3DVERTEXDECLARATION9 _pVertexDeclaration;

    /** １頂点のサイズ（モデル） */
    UINT _size_vertex_unit_model;
    /** １頂点のサイズ（インスタンス） */
    UINT _size_vertex_unit_instancedata;
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
    void (*_pFunc_getVertexInstanceData)(void* prm, VertexInstanceDataInfo* out_info);

public:
    /**
     * コンストラクタ .
     * @param prm_model_id スプライト定義の識別名。".x"を追加すると定義Xファイル名になる。
     */
    MassModel(const char* prm_model_id);

    /**
     * 頂点レイアウト（インスタンスデータ）情報取得コールバック関数を登録する .
     * Modelクラスのコンストラクタ等で呼び出し、登録してください。
     * @param prm_pFunc_getVertexInstanceData 頂点レイアウト（インスタンスデータ）情報取得コールバック関数
     */
    inline void registerCallback_VertexInstanceDataInfo(void (*prm_pFunc_getVertexInstanceData)(void*, VertexInstanceDataInfo*)) {
        _TRACE3_("_model_id=" << _model_id << " start");
#ifdef MY_DEBUG
        if (_pFunc_getVertexInstanceData && _pFunc_getVertexInstanceData != prm_pFunc_getVertexInstanceData) {
            throwCriticalException("既に頂点レイアウトは作成済みにもかかわらず、別の定義関数を設定しようとしました。(1)");
        }
#endif
        _pFunc_getVertexInstanceData = prm_pFunc_getVertexInstanceData;
        if (_pFunc_getVertexInstanceData && _pFunc_getVertexModel) {
            if (_paVertexBuffer_instancedata == nullptr) {
                createVertexElements();
            }
        }
        _TRACE3_("_model_id=" << _model_id << " end");
    }
    /**
     * 頂点レイアウト（モデル）情報取得コールバック関数を登録する .
     * Actorクラスのコンストラクタ等で呼び出し、登録してください。
     * @param prm_pFunc_getVertexModel  頂点レイアウト（モデルデータ）情報取得コールバック関数
     */
    inline void registerCallback_VertexModelInfo(void (*prm_pFunc_getVertexModel)(void*, VertexModelInfo*)) {
        _TRACE3_("_model_id=" << _model_id << " start");
#ifdef MY_DEBUG
        if (_pFunc_getVertexModel && _pFunc_getVertexModel != prm_pFunc_getVertexModel) {
            throwCriticalException("既に頂点レイアウトは作成済みにもかかわらず、別の定義関数を設定しようとしました。(2)");
        }
#endif
        _pFunc_getVertexModel = prm_pFunc_getVertexModel;
        if (_pFunc_getVertexInstanceData && _pFunc_getVertexModel) {
            if (_paVertexBuffer_instancedata == nullptr) {
                createVertexElements();
            }
        }
        _TRACE3_("_model_id=" << _model_id << " end");
    }

    /**
     * モデルの頂点レイアウト、頂点インスタンスデータの作成 .
     */
    void createVertexElements();

    virtual void resetStreamSourceFreq();

    virtual void onDeviceLost() override;

    virtual void release() override;

    virtual void restore() override;
    /**
     * デストラクタ<BR>
     */
    virtual ~MassModel();
};

}
#endif /*GGAF_DX_MESHSETMODEL_H_*/
