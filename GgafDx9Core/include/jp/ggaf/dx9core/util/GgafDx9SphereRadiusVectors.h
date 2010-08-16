#ifndef GGAFDX9SPHERERADIUSVECTORS_H_
#define GGAFDX9SPHERERADIUSVECTORS_H_
namespace GgafDx9Core {





/**
 * 単位球と、単位ベクトルの関係を保持するクラスです。 .
 * 方向ベクトルからZ軸回転角とY軸回転角、逆にZ軸回転角とY軸回転角から方向ベクトルの相互変換を可能とするために設計。<BR>
 * 但し保持されている範囲は単位球の、x≧0 y≧0 z≧0 の範囲の方向ベクトルだけです。（1/8球分のみ）<BR>
 * 【補足】<BR>
 * 保持しているベクトルの各要(X,Y,Z)の単位(unsigned __int16)は、長さ1 が 10000 に相当する整数になっています。<BR>
 * 角度の単位（s_ang）は、1度 が 10 に相当します。直角は 900 になります。angle値(1度が1000)と混在しないように注意<BR>
 */
class GgafDx9SphereRadiusVectors : public GgafCore::GgafObject {
public:

    /**
     * ソート可能方向ベクトルクラス.
     * SR_VECTOR(方向ベクトル)に大小の値をつけ、比較を可能にしたメンバをもつクラス。<BR>
     * 大小の値の強さは、y要素 ＞ z要素 ＞ x要素 の順です。<BR>
     */
    class COMPARE_ABLE_SR_VECTOR : public GgafCore::GgafObject {
    public:

        /**
         * COMPARE_ABLE_SR_VECTOR用の方向ベクトル構造体.
         * 各要素の単位は、1000000倍の整数で保持されます。<BR>
         * ＜例＞<BR>
         * 単位ベクトル(0.658301, 0.1132, 0.744) は<BR>
         * SR_VECTORでは、(658301, 113200, 744000) です<BR>
         */
        struct SR_VECTOR {
            UINT32 x;
            UINT32 z;
            UINT32 y;
        };


        UINT64 num_yzx;
        SR_VECTOR vec;
        COMPARE_ABLE_SR_VECTOR() : GgafObject() {
        }
        /**
         * 単位ベクトルを設定する。<BR>
         * @param prm_x 単位方向ベクトルX要素（長さ1 が 1000000)
         * @param prm_y 単位方向ベクトルY要素（長さ1 が 1000000)
         * @param prm_z 単位方向ベクトルZ要素（長さ1 が 1000000)
         */
        void set(UINT32 prm_x, UINT32 prm_y, UINT32 prm_z) {
            vec.x = prm_x;
            vec.y = prm_y;
            vec.z = prm_z;
            num_yzx = (prm_y * 1000000LL * 1000000LL ) +
            (prm_z * 1000000LL ) +
            (prm_x );

            //_TRACE_(prm_x<<","<<prm_y<<","<<prm_z<<"  num_yzx="<<(num_yzx));
            //1048575LL = &b11111111111111111111 (20bit)
        }
    };





    /** 作成目的の 1/8球分のソート可能方向ベクトル配列(要素数は900*900) */
    //COMPARE_ABLE_SR_VECTOR _sr[];
    COMPARE_ABLE_SR_VECTOR _sr[(S_ANG90 + 1) * (S_ANG90 + 1)];
    GgafDx9SphereRadiusVectors();

    /**
     * 引数のX,Y,Z方向ベクトルから、相当するZ軸回転とY軸回転の近時を求める。
     * 但し、X,Y,Z は全て正でなくてはならない
     * @param prm_x 単位方向ベクトルX要素（長さ1 が 1000000) > 0
     * @param prm_y 単位方向ベクトルY要素（長さ1 が 1000000) > 0
     * @param prm_z 単位方向ベクトルZ要素（長さ1 が 1000000) > 0
     * @param out_angFaceZ Z軸回転値（ 回転値0は、方向ベクトル(1,0,0)。方向ベクトル(0,0,1)を向いて反時計回り。）（単位s_ang）
     * @param out_angFaceY_rev 時計周りY軸回転値（回転値0は、同じく方向ベクトル(1,0,0)。方向ベクトル(0,1,0)を向いて時計回り）（単位s_ang）
     * @param s 計算回数（精度）。回数が多いほど正確になる。
     */
    void getFaceAngClosely(UINT32 prm_x,
                           UINT32 prm_y,
                           UINT32 prm_z,
                           s_ang& out_angFaceZ,
                           s_ang& out_angFaceY_rev,
                           int s = 25);

    /**
     * 引数のZ軸回転とY軸回転の値から、相当する単位方向ベクトルの近時を求める .
     * 但し、結果の方向ベクトルの各要素(X,Y,Z)が正の値になるような引数しか受け付けない。<BR>
     * 戻り値はUINT32で符号無しのため、intと演算する時は気をつけよ<BR>
     * @param prm_angFaceY_rev Z軸回転値（ 回転値0は、方向ベクトル(1,0,0)。方向ベクトル(0,0,1)を向いて反時計回り。）（単位s_ang）
     * @param prm_angFaceZ 時計周りY軸回転値（回転値0は、同じく方向ベクトル(1,0,0)。方向ベクトル(0,1,0)を向いて時計回り）（単位s_ang）
     * @param out_x 単位方向ベクトルX要素（長さ1 が 1000000) > 0
     * @param out_y 単位方向ベクトルY要素（長さ1 が 1000000) > 0
     * @param out_z 単位方向ベクトルZ要素（長さ1 が 1000000) > 0
     */
    void getVectorClosely(s_ang prm_angFaceY_rev,
                          s_ang prm_angFaceZ,
                          UINT32& out_x,
                          UINT32& out_y,
                          UINT32& out_z
                          );


    virtual ~GgafDx9SphereRadiusVectors();
};




}
#endif /*GGAFDX9SPHERERADIUSVECTORS_H_*/

