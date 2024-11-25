#ifndef GGAF_DX_MORPHERASSISTANT_H_
#define GGAF_DX_MORPHERASSISTANT_H_
#include "jp/ggaf/GgafDxCommonHeader.h"
#include "jp/ggaf/core/Object.h"
#include "jp/ggaf/core/util/TrapezoidalVeloValue.hpp"

namespace GgafDx {

template<class T>
class Morpher;

/**
 * モーファーの助手 .
 * @version 1.00
 * @since 2013/12/06
 * @author Masatoshi Tsuge
 */
template<class T>
class MorpherAssistant : public GgafCore::Object {
    friend class Morpher<T>;

private:
    /** [r]師匠 */
    Morpher<T>* _pMaster;
    /** [r]重み加速器 */
    GgafCore::TrapezoidalVeloValue<float>* _pa_smthMph;
    /** [r]モーフターゲット数(利用頻度が高いので、モデルからコピーして保持) */
    int _target_num;

    /**
     * モーファーの助手が振る舞う .
     * 師匠が振る舞う(behave())時に、自動で呼び出されるので気にしないでよいです。
     */
    virtual void behave();

public:
    /**
     * コンストラクタ<BR>
     * @param   prm_pMaster  師匠
     */
    explicit MorpherAssistant(Morpher<T>* prm_pMaster);


    /**
     * 軸回転方角を滑らかに回転するシークエンスを実行(角距離指定、時間指定、角速度変動) .
     * 角回転移動に費やされる時間(Te)を3つのセクションに分け、次のような角速度制御を自動的に行う。<BR>
     * ・時間 0     ～ 時間 p1*Te まで ・・・ 現在の角速度からトップ角速度まで回転速度を加速<BR>
     * ・時間 p1*Te ～ 時間 p2*Te まで ・・・ トップスピードで等速角速度で等速回転<BR>
     * ・時間 p2*Te ～ 時間 Te    まで ・・・ トップスピードから最終角速度へ回転速度を減速<BR>
     * ※下図参照<BR>
     * <pre>
     *
     *    角速度(ω)
     *     ^
     *     |                         θ:目標移動角（距離）    ・・・引数 prm_distance
     *     |                        ω0:現時点の角速度        ・・・_angvelo_face[prm_axis]
     *     |                        ωt:トップ角速度          ・・・変動、計算される
     *     |                        ωe:最終速度              ・・・引数 prm_end_angvelo
     *  ωt|....___________          Te:目標時間（フレーム数）・・・引数 prm_target_frames
     *     |   /:         :＼        p1:トップ角速度に達する時刻となるような、Teに対する割合・・・引数 prm_p1
     *  ωe|../.:.........:..＼      p2:回転の減速を開始する時刻となるような、Teに対する割合・・・引数 prm_p2
     *     | /  :         :    |
     *     |/   :         :    |
     *  ω0|    :    θ   :    |
     *     |    :         :    |
     *   --+----+---------+----+-----> 時間(t:フレーム)
     *   0 |  p1*Te     p2*Te  Te
     *
     * </pre>
     * @param prm_axis 回転方角軸(AXIS_X or AXIS_Y or AXIS_Z)
     * @param prm_distance 目標角距離(θ)（正負により回転方向有り。正：TURN_COUNTERCLOCKWISE、負：TURN_CLOCKWISE）
     * @param prm_target_frames 費やす時間(Te)(フレーム数を指定、負の数は不可)
     * @param prm_p1 トップスピードに達する時刻となるような、Teに対する割合(p1)
     * @param prm_p2 減速を開始時刻となるような、Teに対する割合(p2)
     * @param prm_end_angvelo 目標到達時の最終角速度(ωe) （内部で正負がprm_distanceの正負に合わせられる）
     * @param prm_zero_acc_end_flg true:目標移動距離に達した際に角加速度を０に強制設定/false:角加速度はそのままにしておく
     */
    void morphByDt(int prm_target_mesh_no,
                   float prm_target_distance, int prm_target_frames,
                   float prm_p1, float prm_p2, float prm_end_velo,
                   bool prm_zero_acc_end_flg = true);
    /**
     * 目標の軸回転方角(Z軸)へ滑らかに回転するシークエンスを実行(速度・距離指定、時間変動) .
     * 移動距離を3つのセクション(θ1,θ2,θ3)に分け、次のような角速度制御を自動的に行う。<BR>
     * ・距離角 0       ～ 距離角 θ1         まで ・・・ 現在のθ速度からトップスピードまで角加速(or減速)回転<BR>
     * ・距離角 θ1     ～ 距離角 θ1+θ2     まで ・・・ トップスピードで等速角回転<BR>
     * ・距離角 θ1+θ2 ～ 距離角 θ1+θ2+θ3 まで ・・・ トップスピードから最終スピードへ角減速(or加速)回転<BR>
     * ※下図参照<BR>
     * <pre>
     *    角速度(ω)
     *     ^
     *     |                        ω0:現時点の角速度
     *     |                        ωt:トップ角速度
     *     |                        ωe:最終角速度
     *     |       θ=θ1+θ2+θ3    θ:目標回転距離角
     *  ωt|....___________          p1:トップ角速度に達する角距離となるような、θに対する割合
     *     |   /|         |＼            つまり     θ1 = θ*p1 となるような p1 (0.0～1.0)
     *  ωe|../.|.........|..＼      p2:減速を開始距離となるような、θ対する割合
     *     | /  |         |    |         つまり θ1+θ2 = θ*p2 となるような p2 (0.0～1.0)
     *     |/   |         |    |     Te:費やされる必要時間（フレーム数）
     *  ω0|θ1 |   θ2   |θ3 |
     *     |    |         |    |
     *   --+----+---------+----+-----> 時間(t:フレーム)
     *   0 |                  Te
     *
     * </pre>
     * トップスピード(ωt)、最終スピード(ωe)、目標回転距離角(θ)、及び p1, p2 を指定する。<BR>
     * 費やされる時間(Te)は内部で自動計し決定される。<BR>
     * <BR>
     * @param prm_axis 回転方角軸(AXIS_X or AXIS_Y or AXIS_Z)
     * @param prm_top_angvelo トップ角速度(ωt)
     * @param prm_distance 目標角距離(θ)（正負により回転方向有り。正：TURN_COUNTERCLOCKWISE、負：TURN_CLOCKWISE）
     * @param prm_p1 トップスピードに達する距離となるような、回転距離角(θ)に対する割合。(θ1 = θ*prm_p1)
     * @param prm_p2 角回転の減速を開始角となるような、回転距離角(θ)に対する割合 (θ1+θ2 = θ*p2)
     * @param prm_end_angvelo 最終角速度(ωe)
     * @param prm_zero_acc_end_flg true:目標時間に達した際に角加速度を０に強制設定/false:角加速度はそのままにしておく
     */
    void morphByVd(int prm_target_mesh_no,
                   float prm_top_velo, float prm_target_distance,
                   float prm_p1, float prm_p2, float prm_end_velo,
                   bool prm_zero_acc_end_flg = true);

    virtual ~MorpherAssistant();
};

template<class T>
MorpherAssistant<T>::MorpherAssistant(Morpher<T>* prm_pMaster) : GgafCore::Object(),
        _pMaster(prm_pMaster) {
    _target_num = prm_pMaster->_pActor->_pMorphMeshModel->_morph_target_num;

    _pa_smthMph = NEW GgafCore::TrapezoidalVeloValue<float>[_target_num+1];
    for (int i = 1; i <= _target_num; i++) {
        _pa_smthMph[i]._t_velo = _pMaster->_velo[i];
        _pa_smthMph[i]._t_acce = _pMaster->_acce[i];
    }
}

template<class T>
void MorpherAssistant<T>::behave() {
    GgafCore::TrapezoidalVeloValue<float>* pSmthMph = _pa_smthMph;
    GgafCore::ValueTransitioner<float, (MAX_MORPH_TARGET+1)>::Parameter* p = _pMaster->_parameter;
    for (int i = 1; i <= _target_num; i++) {
        if (pSmthMph->isTransitioning()) {
            pSmthMph->behave();
            p->_velo = pSmthMph->_t_velo - pSmthMph->_t_acce;
            p->_acce = pSmthMph->_t_acce;
        }
        ++pSmthMph;
        ++p;
    }
}

template<class T>
void MorpherAssistant<T>::morphByDt(int prm_target_mesh_no,
                                        float prm_target_distance, int prm_target_frames,
                                        float prm_p1, float prm_p2, float prm_end_velo,
                                        bool prm_zero_acc_end_flg) {
    _pa_smthMph[prm_target_mesh_no]._t_value = 0;
    _pa_smthMph[prm_target_mesh_no]._t_velo = _pMaster->_velo[prm_target_mesh_no];
    _pa_smthMph[prm_target_mesh_no]._t_acce = _pMaster->_acce[prm_target_mesh_no];
    _pa_smthMph[prm_target_mesh_no].moveByDt(prm_target_distance, prm_target_frames,
                                                   prm_p1,prm_p2,prm_end_velo,
                                                   prm_zero_acc_end_flg);
}

template<class T>
void MorpherAssistant<T>::morphByVd(int prm_target_mesh_no,
                                        float prm_top_velo, float prm_target_distance,
                                        float prm_p1, float prm_p2, float prm_end_velo,
                                        bool prm_zero_acc_end_flg) {
    _pa_smthMph[prm_target_mesh_no]._t_value = 0;
    _pa_smthMph[prm_target_mesh_no]._t_velo = _pMaster->_velo[prm_target_mesh_no];
    _pa_smthMph[prm_target_mesh_no]._t_acce = _pMaster->_acce[prm_target_mesh_no];
    _pa_smthMph[prm_target_mesh_no].moveByVd(prm_top_velo, prm_target_distance,
                                                   prm_p1,prm_p2,prm_end_velo,
                                                   prm_zero_acc_end_flg);
}

template<class T>
MorpherAssistant<T>::~MorpherAssistant() {
    GGAF_DELETEARR(_pa_smthMph);
}

}
#endif /*GGAF_DX_MORPHE2RASSISTANT_H_*/

