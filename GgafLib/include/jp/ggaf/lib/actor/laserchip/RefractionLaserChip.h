#ifndef GGAF_LIB_REFRACTIONLASERCHIP_H_
#define GGAF_LIB_REFRACTIONLASERCHIP_H_
#include "GgafLibCommonHeader.h"
#include "jp/ggaf/lib/actor/laserchip/LaserChip.h"

namespace GgafLib {

/**
 * 反射（屈折）レーザー用ポリラインのチップ .
 * 反射（屈折）レーザーなどどと表現しているが、正確には <BR>
 * ・発射座標固定（発射元座標は通常は移動不可） <BR>
 * ・移動方向、速度は先頭チップがのみが決め、残りチップは単に追従する<BR>
 * ・移動方向は直進、但し一定間隔で移動方向が変化 <BR>
 * と言うべきか、ダライアスのボスの多段レーザーと言うべきか、そんな感じ。<BR>
 * デポジトリ登録前にconfig()で設定してください。<BR>
 * 先頭チップは  GgafDx::VecVehicle#behave() で移動します。<BR>
 * dispatch() したら、初期座標と VecVehicle（速度・方向）を設定して下さい。<BR>
 * @version 1.00
 * @since 2010/01/19
 * @author Masatoshi Tsuge
 */
class RefractionLaserChip : public LaserChip {
    friend class LaserChipDepository;

private:
    /** [r](次回の)屈折開始フレーム */
    frame _frame_refraction_enter;
    /** [r]屈折終了フレーム */
    frame _frame_refraction_out;
    /** [r]今まさに屈折中（移動していない）の場合true */
    bool _is_refracting;
    /** [r]現在の屈折回数 */
    int _cnt_refraction;

    int _begining_x;
    int _begining_y;
    int _begining_z;
    angle _begining_rx;
    angle _begining_ry;
    angle _begining_rz;
    angle _begining_rz_mv;
    angle _begining_ry_mv;
    velo _begining_velo_mv;
    int _prev_x;
    int _prev_y;
    int _prev_z;
    angle _prev_rx;
    angle _prev_ry;
    angle _prev_rz;
    angle _prev_rz_mv;
    angle _prev_ry_mv;
    velo _prev_velo_mv;

    bool _prev_is_refracting;
    GgafDx::FigureActor* _prev_pRefractionEffect;

    /** 屈折エフェクトアクターのデポジトリ（シーン所属済みであること） */
    GgafCore::ActorDepository* _pDepo_refraction_effect;
    GgafDx::FigureActor* _pRefractionEffect;
    /** 屈折終了までのフレーム数 */
    frame _refraction_end_frames;
public:
    /** 先導チップ（本当の先頭チップ）フラグ */
    bool _is_leader; //本当の先頭チップとは、レーザー移動中にちぎれて発生するにわか先頭チップでは無いという意味。;
    /** [r]最終的な屈折回数 */
    int _num_refraction;
    /** [r]直進開始(屈折終了)～直進～直進終了(屈折開始)、のフレーム数(>= 1) */
    frame _frame_between_refraction;
    /** [r]屈折時(直進終了(屈折開始)～停止～直進開始(屈折終了))の停滞貯めフレーム数(>= 1) */
    frame _frame_standstill_refraction;
    /** [r]発射開始座標固定か否か(true:固定、呼び元の座標等を上書きして、最初の[0]の座標に強制上書き/false:非固定。スクロールシーン配下等の場合は false が良い */
    bool _is_fix_begin_pos;

public:
    RefractionLaserChip(const char* prm_name, const char* prm_model);

    /**
     * リフレクションレーザーを定義 .
     * @param prm_num_refraction 何回屈折するか
     * @param prm_frame_between_refraction 直進開始(屈折終了)～直進～直進終了(屈折開始)、のフレーム数(>= 1)
     * @param prm_frame_standstill_refraction 屈折時(直進終了(屈折開始)～停止～直進開始(屈折終了))の停滞貯めフレーム数(>= 1)
     * @param prm_is_fix_beginning_pos true:レーザー発射元は、先頭レーザーチップの座標に固定される。／false:それぞれのレーザーチップの座標に依存
     * @param prm_pDepo_refraction_effect 屈折時のエフェクトアクターのデポジトリ(無しの場合はnullptr)
     */
    virtual void config(int prm_num_refraction,
                        frame prm_frame_between_refraction,
                        frame prm_frame_standstill_refraction,
                        bool prm_is_fix_begin_pos,
                        GgafCore::ActorDepository* prm_pDepo_refraction_effect);

    virtual void onCreateModel() override {}

    virtual void initialize() override {}

    /**
     * レーザーチップ座標計算等処理 .
     * 独自設定したい場合、継承して別クラスを作成し、オーバーライドしてください。
     * その際、本クラスの processBehavior() メソッドも呼び出してください。
     * 内部処理は、
     * 先頭チップは、GgafDx::VecVehicle#behave() を実行により移動を行います。
     * 屈折中は GgafDx::VecVehicle#behave() による移動は行いません。
     * 先頭以外のチップ以外は、先頭チップに追従するという処理を行います。
     */
    virtual void processBehavior() override;

    virtual void processJudgement() override {}

    virtual void onCatchEvent(eventval prm_event_val, void* prm_pSource) override {}

    /**
     * 先頭チップのレーザーの直進終了～屈折開始時の処理 .
     * 先頭チップのみコールバックされます。<BR>
     * @param prm_num_refraction 屈折カウント(何回目の屈折開始か)(0～)
     */
    virtual void onRefractionInto(int prm_num_refraction) = 0;

    /**
     * 先頭チップのレーザーのため後屈折後終了～直進開始時の処理 .
     * 先頭チップのみコールバックされます。<BR>
     * 実際には存在しない0回目の屈折終了からスタートする。<BR>
     * 0回目の屈折終了は onActive() 時にコールバックされます。<BR>
     * オーバーライドし、屈折後の次の移動方向と速度を力車Aに設定する実装を
     * 行ってください。<BR>
     * @param prm_num_refraction 屈折カウント(何回目の屈折終了か)(0～)
     */
    virtual void onRefractionOutOf(int prm_num_refraction) = 0;

    /**
     * レーザーチップ出現時処理 .
     * 独自設定したい場合、継承して別クラスを作成し、オーバーライドしてください。
     * その際 は、本クラスの onActive() メソッドも呼び出してください。
     */
    virtual void onActive() override;

    /**
     * レーザーチップ消失時処理 .
     * 独自設定したい場合、継承して別クラスを作成し、オーバーライドしてください。
     * その際 は、本クラスの onInactive() メソッドも呼び出してください。
     */
    virtual void onInactive() override;

    /**
     * 屈折レーザー開始～終了までのフレーム数を得る .
     * @return 屈折レーザー開始～終了までのフレーム数
     */
    inline frame getRefractionFinishFrames() {
        return _refraction_end_frames;
    }

    virtual ~RefractionLaserChip();

};

}
#endif /*GGAF_LIB_HOMINGLASERCHIP_H_*/

