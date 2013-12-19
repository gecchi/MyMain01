#ifndef GGAFDXCORE_GGAFDXKUROKOHELPERA_H_
#define GGAFDXCORE_GGAFDXKUROKOHELPERA_H_
#include "jp/ggaf/core/GgafObject.h"
#include "jp/ggaf/dxcore/util/GgafDxAccelerator.hpp"

namespace GgafDxCore {

/**
 * 黒衣の助手A .
 * 師匠(黒衣)の補佐を行います。
 * @version 1.00
 * @since 2013/12/05
 * @author Masatoshi Tsuge
 */
class GgafDxKurokoHelperA : public GgafCore::GgafObject {

public:
    /** [r]師匠 */
    GgafDxKuroko* _pMaster;
    GgafDxAccelerator<int> _smthMv;
public:
    /**
     * コンストラクタ<BR>
     * @param   prm_pMaster  師匠
     */
    GgafDxKurokoHelperA(GgafDxKuroko* prm_pMaster);


    /**
     * なめらかな移動速度を変化させるシークエンスを実行(時間・距離指定、速度変動) .
     * 移動に費やされる時間(Te)を3つのセクションに分け、次のような速度制御を自動的に行う。<BR>
     * ・時間 0     〜 時間 p1*Te まで ・・・ 現在の速度からトップスピードまで加速(or減速)移動<BR>
     * ・時間 p1*Te 〜 時間 p2*Te まで ・・・ トップスピードで等速移動<BR>
     * ・時間 p2*Te 〜 時間 Te    まで ・・・ トップスピードから最終スピードへ減速(or加速)移動<BR>
     * ※下図参照<BR>
     * <pre>
     *
     *    速度(v)
     *     ^
     *     |
     *     |                         V0:現時点の速度
     *     |                         Ve:最終速度
     *     |                          D:目標移動距離
     *   Vt|....___________          Te:目標時間（フレーム数）
     *     |   /:         :＼        p1:トップスピードに達する時刻となるような、Teに対する割合(0.0〜1.0)
     *   Ve|../.:.........:..＼      p2:減速を開始時刻となるような、Teに対する割合(0.0〜1.0)
     *     | /  :         :    |     Vt:距離・時間から導きだされるトップスピード
     *     |/   :         :    |
     *   V0|    :    D    :    |
     *     |    :         :    |
     *   --+----+---------+----+-----> 時間(t:フレーム)
     *   0 |  p1*Te     p2*Te  Te
     *
     * </pre>
     * 最終スピード(Ve)、目標移動距離(D)、到達目標時間(Te)、及び p1, p2 を指定する。<BR>
     * トップスピード(Vt)は内部で自動計算し決定される。<BR>
     * @param prm_target_distance 目標直線移動距離(D)
     * @param prm_target_frames 費やす時間(Te)(フレーム数を指定、負の数は不可)
     * @param prm_p1 トップスピードに達する時刻となるような、Teに対する割合(p1)
     * @param prm_p2 減速を開始時刻となるような、Teに対する割合(p2)
     * @param prm_end_velo 最終スピード(Ve)
     * @param prm_endacc_flg true:目標移動距離に達した際に加速度を０に強制設定/false:加速度はそのままにしておく
     */
    void slideMvByDt(coord prm_target_distance, int prm_target_frames,
                     float prm_p1, float prm_p2, velo prm_end_velo,
                     bool prm_endacc_flg);

    /**
     * なめらかな移動速度を変化させるシークエンスを実行(速度・距離指定、時間変動) .
     * 移動距離を3つのセクション(d1,d2,d3)に分け、次のような速度制御を自動的に行う。<BR>
     * ・距離 0     〜 距離 d1       まで ・・・ 現在の速度からトップスピードまで加速(or減速)移動<BR>
     * ・距離 d1    〜 距離 d1+d2    まで ・・・ トップスピードで等速移動<BR>
     * ・距離 d1+d2 〜 距離 d1+d2+d3 まで ・・・ トップスピードから最終スピードへ減速(or加速)移動<BR>
     * ※下図参照<BR>
     * <pre>
     *    速度(v)
     *     ^
     *     |                         V0:現時点の速度
     *     |                         Vt:トップスピード
     *     |                         Ve:最終速度
     *     |         D=d1+d2+d3       D:目標移動距離(D=d1+d2+d3)
     *   Vt|....___________          p1:トップスピードに達する距離となるような、距離(D)に対する割合
     *     |   /|         |＼            つまり    d1 = D*p1 となるような p1 (0.0〜1.0)
     *   Ve|../.|.........|..＼      p2:減速を開始距離となるような、距離(D)に対する割合
     *     | /  |         |    |         つまり d1+d2 = D*p2 となるような p2 (0.0〜1.0)
     *     |/   |         |    |     Te:費やされる必要時間（フレーム数）
     *   V0| d1 |    d2   | d3 |
     *     |    |         |    |
     *   --+----+---------+----+-----> 時間(t:フレーム)
     *   0 |                  Te
     *
     * </pre>
     * トップスピード(Vt)、最終スピード(Ve)、目標移動距離(D)、及び p1, p2 を指定する。<BR>
     * 費やされる時間(Te)は内部で自動計し決定される。<BR>
     * <BR>
     * @param prm_top_velo トップスピード(Vt)
     * @param prm_target_distance 目標直線移動距離(D)
     * @param prm_p1 トップスピードに達する距離となるような、距離(D)に対する割合。(d1 = D*prm_p1)
     * @param prm_p2 減速を開始距離となるような、距離(D)に対する割合 (d1+d2 = D*p2)
     * @param prm_end_velo 最終スピード(Ve)
     * @param prm_endacc_flg true:目標時間に達した際に加速度を０に強制設定/false:加速度はそのままにしておく
     */
    void slideMvByVd(velo prm_top_velo, coord prm_target_distance,
                     float prm_p1, float prm_p2, velo prm_end_velo,
                     bool prm_endacc_flg);
    bool isSlidingMv() {
        return _smthMv._prm._flg;
    }

    void stopSlidingMv() {
        _smthMv._prm._flg = false;
    }

    bool isJustFinishSlidingMv() {
        if (_smthMv._prm._flg == false && _smthMv._prm._progress != -1) {
            return true;
        } else {
            return false;
        }
    }
   /**
     * 黒衣の助手が振る舞う .
     * 助手が、師匠にいろいろ設定を行いますので、師匠が振る舞う(behave())前に実行しましょう。
     */
    virtual void behave();

    virtual ~GgafDxKurokoHelperA();
};

}
#endif /*GGAFDXCORE_GGAFDXKUROKOHELPERA_H_*/

