#ifndef CURVELASERCHIP_H_
#define CURVELASERCHIP_H_
namespace MyStg2nd {

class CurveLaserChip : public LaserChip {
    friend class CurveLaserChipDispatcher;
public:
////    D3DXHANDLE _hKind, _hX, _hY, _hZ, _hRevPosZ;
//    D3DXHANDLE _ahKind[8];
////    D3DXHANDLE _ahRevPosZ[8];
//    D3DXHANDLE _ahMatWorld_front[8];
//
//    D3DXHANDLE _h_cnt_vertec;
//
//    /** チップの頂点バッファをシェーダーでレンダリングする際にZ座標に-1を乗ずるかどうかのフラグ */
//    int _rev_pos_Z;
//    /** チップの頂点バッファをシェーダーでレンダリングする際にZ座標を2で割るかどうかのフラグ */
//    int _div_pos_Z;
//
////    virtual void processPreDraw() {
////        GgafDx9Core::GgafDx9MeshSetActor::processPreDraw();
////    }
//
//
//
////    void processAfterDraw();
//
//
//
//    GgafDx9LibStg::StgChecker* _pStgChecker;
//
//    /** 一つ前方のレーザーチップ */
//    CurveLaserChip* _pChip_front;
//    /** 一つ後方のレーザーチップ */
//    CurveLaserChip* _pChip_behind;
//    /** レーザーテクスチャ種別  1:末尾 2:中間 3:先頭 （末尾かつ先頭は末尾が優先） */
//    int _chip_kind;
//
//    /** 自身のWorld変換行列 */
//    D3DXMATRIX _matWorld;
//    /** 一つ前方のWorld変換行列 */
//    D3DXMATRIX _matWorld_front;
//    /** 自身を管理してるアクター発送者 */
//    CurveLaserChipDispatcher* _pDispatcher;



    CurveLaserChip(const char* prm_name, const char* prm_model);

    virtual void initialize();

    virtual void processBehavior();

    virtual void processJudgement();

    virtual void onActive();

    virtual void onInactive();

    virtual ~CurveLaserChip();

};

}
#endif /*CURVELASERCHIP_H_*/

