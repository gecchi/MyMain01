﻿#ifndef GGAFDX9POINTSPRITEMODEL_H_
#define GGAFDX9POINTSPRITEMODEL_H_
namespace GgafDx9Core {

/**
 * GgafDx9PointSpriteActor用モデルクラス.
 * @version 1.00
 * @since 2008/02/22
 * @author Masatoshi Tsuge
 */
class GgafDx9PointSpriteModel : public GgafDx9Model {
    friend class GgafDx9ModelManager;

protected:
public:

//    struct VARTEXPARAM {
//        UINT MaterialNo;
//        UINT StartVertex;
//        UINT PrimitiveCount;
//
////        INT BaseVertexIndex;
////        UINT MinIndex;
////        UINT NumVertices;
////        UINT StartIndex;
////        UINT PrimitiveCount;
//    };

    struct VERTEX {
        float x, y, z;    // 頂点座標
        float psize;      // ポイントサイズ
        DWORD color;      // 頂点の色
        float tu, tv;     // テクスチャ座標
    };

    /** 頂点バッファ */
    LPDIRECT3DVERTEXBUFFER9 _pIDirect3DVertexBuffer9;
    /** 頂点情報配列 */
    VERTEX* _paVtxBuffer_org;
    /** 頂点数(=スプライト数) */
    int _vertices_num;
    /** 頂点のFVF */
    static DWORD FVF;
    /** 矩形の頂点合計のサイズ */
    UINT _size_vertices;
    /** 1頂点のサイズ */
    UINT _size_vertex_unit;
    /** オブジェクトの１辺のサイズ(px) */
    float _fSquareSize;
    /** テクスチャの１辺の長さ(px) */
    float _fTexSize;
    /** テクスチャ分割数(１で分割無し。２で４パターン、３で９パターン) */
    int _texture_split_rowcol;


    /**
     * コンストラクタ<BR>
     * @param prm_model_name スプライト定義の識別名。".x"を追加すると定義Xファイル名になる。
     */
    GgafDx9PointSpriteModel(char* prm_model_name);

public:
    /** 全アニメパターン数(0〜) */
//    int _pattno_uvflip_Max;
//    float _fSize_PointSpriteModelWidthPx;
//    float _fSize_PointSpriteModelHeightPx;
//    int _row_texture_split;
//    int _col_texture_split;

    /**
     * GgafDx9PointSpriteModelオブジェクトの描画<BR>
     * @param   prm_pActor_Target 描画するGgafDx9PointSpriteActor
     * @return  HRESULT
     */
    virtual HRESULT draw(GgafDx9DrawableActor* prm_pActor_Target) override;

    virtual void restore() override;

    virtual void onDeviceLost() override;

    virtual void release() override;

    void changeVertexAlpha(int prm_vertex_alpha);

    /**
     * デストラクタ<BR>
     */
    virtual ~GgafDx9PointSpriteModel(); //デストラクタ
};

}
#endif /*GGAFDX9POINTSPRITEMODEL_H_*/
