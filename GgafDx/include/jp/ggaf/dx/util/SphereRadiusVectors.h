#ifndef GGAF_DX_SPHERERADIUSVECTORS_H_
#define GGAF_DX_SPHERERADIUSVECTORS_H_
#include "jp/ggaf/GgafDxCommonHeader.h"
#include "jp/ggaf/core/Object.h"

#include <map>

namespace GgafDx {

#define SR_AC (1)

/**
 * 単位球と、単位ベクトルの座標のマッピング .
 * 方向ベクトルからZ軸回転角とY軸回転角、逆にZ軸回転角とY軸回転角から方向ベクトルの相互変換を可能とするために設計。<BR>
 * 但し保持されている範囲は単位球の、x≧0 y≧0 z≧0 の範囲の方向ベクトルだけです。（1/8球分のみ）<BR>
 * 【補足】<BR>
 * 保持しているベクトルの各要(X,Y,Z)の単位(uint32_t)は、長さ1 が 10000000 に相当する整数になっています。<BR>
 * 角度の単位（s_ang）は、弧度法 1度 が 10 に相当します。直角は 900 になります。
 * angle値(弧度法1度が1000)と混在しないように注意<BR>
 */
class SphereRadiusVectors : public GgafCore::Object {
public:
    struct SrVec {
        uint32_t x;
        uint32_t z;
        uint32_t y;
    };

    struct RzRy {
        s_ang s_rz;
        s_ang s_ry;
    };

    SrVec _sr_vec[(D90SANG*SR_AC + 1)][(D90SANG*SR_AC +1)];
    std::map<uint32_t, std::map<uint32_t, RzRy> > _vy_vz_2_rz_ry_rev;

public:
    SphereRadiusVectors();

    /**
     * 引数のX,Y,Z方向ベクトルから、相当するZ軸回転とY軸回転の近似を求める。
     * 但し、X,Y,Z は全て正でなくてはならない
     * @param prm_x 単位方向ベクトルX要素（長さ 1 が 10000000) > 0
     * @param prm_y 単位方向ベクトルY要素（長さ 1 が 10000000) > 0
     * @param prm_z 単位方向ベクトルZ要素（長さ 1 が 10000000) > 0
     * @param out_faceZ Z軸回転値（ 回転値0は、方向ベクトル(1,0,0)。方向ベクトル(0,0,1)を向いて反時計回り。）（単位s_ang）
     * @param out_faceY_rev 時計周りY軸回転値（回転値0は、同じく方向ベクトル(1,0,0)。方向ベクトル(0,1,0)を向いて時計回り）（単位s_ang）
     */
    void getFaceAngClosely(uint32_t prm_x,
                           uint32_t prm_y,
                           uint32_t prm_z,
                           angle& out_faceZ,
                           angle& out_faceY_rev);

    /**
     * 引数のZ軸回転とY軸回転の値から、相当する単位方向ベクトルの近似を求める .
     * 但し、結果の方向ベクトルの各要素(X,Y,Z)が正の値になるような引数しか受け付けない。<BR>
     * 戻り値はuint32_tで符号無しのため、intと演算する時は気をつけよ<BR>
     * @param prm_faceZ Z軸回転値（ 回転値0は、方向ベクトル(1,0,0)。方向ベクトル(0,0,1)を向いて反時計回り。）（単位s_ang）
     * @param prm_faceY_rev 時計周りY軸回転値（回転値0は、同じく方向ベクトル(1,0,0)。方向ベクトル(0,1,0)を向いて時計回り）（単位s_ang）
     * @param out_x 単位方向ベクトルX要素（長さ 1 が 10000000) > 0
     * @param out_y 単位方向ベクトルY要素（長さ 1 が 10000000) > 0
     * @param out_z 単位方向ベクトルZ要素（長さ 1 が 10000000) > 0
     */
    inline void getVectorClosely(angle prm_faceZ,
                                 angle prm_faceY_rev,
                                 uint32_t& out_x,
                                 uint32_t& out_y,
                                 uint32_t& out_z ) {
        SrVec* pV = &(_sr_vec[(s_ang)(prm_faceZ/(1.0*SANG_RATE/SR_AC))][(s_ang)(prm_faceY_rev/(1.0*SANG_RATE/SR_AC))]);
        out_x = pV->x;
        out_y = pV->y;
        out_z = pV->z;
    }

    virtual ~SphereRadiusVectors();
};

}
#endif /*GGAF_DX_SPHERERADIUSVECTORS_H_*/

