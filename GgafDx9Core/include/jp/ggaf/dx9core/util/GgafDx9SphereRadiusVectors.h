#ifndef GGAFDX9SPHERERADIUSVECTORS_H_
#define GGAFDX9SPHERERADIUSVECTORS_H_
namespace GgafDx9Core {

/**
 * 方向ベクトル構造体.
 * 各要素の単位は、10000倍の整数で保持されます。<BR>
 * ＜例＞<BR>
 * 単位ベクトル(0.6583, 0.1132, 0.744) は<BR>
 * SR_VECTORでは、(6583, 1132, 7440) です<BR>
 */
struct SR_VECTOR {
    unsigned __int16 x;
    unsigned __int16 z;
    unsigned __int16 y;
};

/**
 * ソート可能方向ベクトルクラス.
 * SR_VECTOR(方向ベクトル)に大小の値をつけ、比較を可能にしたメンバをもつクラス。<BR>
 * 大小の値の強さは、y要素 ＞ z要素 ＞ x要素 の順です。<BR>
 */
class COMPARE_ABLE_SR_VECTOR : public GgafCore::GgafObject {
public:
    unsigned __int64 num_yzx;
    SR_VECTOR vec;
    COMPARE_ABLE_SR_VECTOR() : GgafObject() {
    }
    /**
     * 単位ベクトルを設定する。<BR>
     * @param prm_x 単位方向ベクトルX要素（長さ1 が 10000)
     * @param prm_y 単位方向ベクトルY要素（長さ1 が 10000)
     * @param prm_z 単位方向ベクトルZ要素（長さ1 が 10000)
     */
    void set(unsigned __int16 prm_x, unsigned __int16 prm_y, unsigned __int16 prm_z) {
        vec.x = prm_x;
        vec.y = prm_y;
        vec.z = prm_z;
        num_yzx = (prm_y * 65536LL * 65536LL ) +
        (prm_z * 65536LL ) +
        (prm_x );
    }
};

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
    /** 1/8球分のソート可能方向ベクトル配列(要素数は900*900) */
    static COMPARE_ABLE_SR_VECTOR _sr[];

    GgafDx9SphereRadiusVectors();

    /**
     * 引数のX,Y,Z方向ベクトルから、相当するZ軸回転とY軸回転の近時を求める。
     * 但し、X,Y,Z は全て正でなくてはならない
     * @param prm_x 単位方向ベクトルX要素（長さ1 が 10000)
     * @param prm_y 単位方向ベクトルY要素（長さ1 が 10000)
     * @param prm_z 単位方向ベクトルZ要素（長さ1 が 10000)
     * @param out_angRotZ Z軸回転値（単位s_ang）
     * @param out_angRotY Y軸回転値（単位s_ang）
     */
    void getRotAngleClosely(unsigned __int16 prm_x,
                            unsigned __int16 prm_y,
                            unsigned __int16 prm_z,
                            s_ang& out_angRotZ,
                            s_ang& out_angRotY,
                            int s = 25);

    /**
     * 引数のZ軸回転とY軸回転の値から、相当する単位方向ベクトルの近時を求める。
     * 但し、結果の方向ベクトルの各要素(X,Y,Z)が正の値になるような引数しか受け付けない。
     * @param prm_angRotY Z軸回転値（単位s_ang）
     * @param prm_angRotZ Y軸回転値（単位s_ang）
     * @param out_x 単位方向ベクトルX要素（長さ1 が 10000)
     * @param out_y 単位方向ベクトルY要素（長さ1 が 10000)
     * @param out_z 単位方向ベクトルZ要素（長さ1 が 10000)
     * @param 精度 (デフォルト=25 25段階バイナリーサーチするという意味）
     */
    void getVectorClosely(s_ang prm_angRotY,
                          s_ang prm_angRotZ,
                          unsigned __int16& out_x,
                          unsigned __int16& out_y,
                          unsigned __int16& out_z
                          );


    virtual ~GgafDx9SphereRadiusVectors();
};




}
#endif /*GGAFDX9SPHERERADIUSVECTORS_H_*/

