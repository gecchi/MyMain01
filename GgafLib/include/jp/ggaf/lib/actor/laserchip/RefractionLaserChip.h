#ifndef REFRACTIONLASERCHIP_H_
#define REFRACTIONLASERCHIP_H_

namespace GgafLib {

/**
 * 反射（屈折）レーザー用ポリラインのチップ .
 * 反射（屈折）レーザーなどどと表現しているが、正確には <BR>
 * ・発射座標固定（発射元座標が移動不可） <BR>
 * ・移動方向、速度は先頭チップがのみが決め、残りチップは単に追従する<BR>
 * ・移動方向は直進、但し一定間隔で移動方向が変化 <BR>
 * と言うべきか、ダライアスのボスの多段レーザーと言うべきか、そんな感じ。
 * @version 1.00
 * @since 2010/01/19
 * @author Masatoshi Tsuge
 */
class RefractionLaserChip : public LaserChip {
    friend class LaserChipDepository;

private:
    frame _frame_refraction_enter;
    frame _frame_refraction_out;
    bool _is_refracting;
    int _cnt_refraction;

    /** 先導チップ（本当の先頭チップ）フラグ */
    bool _is_leader; //本当の先頭チップとは、レーザー移動中にちぎれて発生するにわか先頭チップでは無いという意味。;
    int _begining_X;
    int _begining_Y;
    int _begining_Z;
    angle _begining_RX;
    angle _begining_RY;
    angle _begining_RZ;
    int _prev_X;
    int _prev_Y;
    int _prev_Z;
    angle _prev_RX;
    angle _prev_RY;
    angle _prev_RZ;

    bool _prev_is_refracting;
    GgafDxCore::GgafDxDrawableActor* _prev_pRefractionEffect;
    int _num_refraction;
    frame _frame_between_refraction;
    frame _frame_standstill_refraction;

    /** 屈折エフェクトアクターのデポジトリ（シーン所属済みであること） */
    GgafCore::GgafActorDepository* _pDispatche_RefractionEffect;
    GgafDxCore::GgafDxDrawableActor* _pRefractionEffect;

public:
    RefractionLaserChip(const char* prm_name, const char* prm_model, GgafCore::GgafStatus* prm_pStat=NULL);

    /**
     * リフレクションレーザーを定義 .
     * @param prm_num_refraction 何回屈折するか
     * @param prm_frame_between_refraction 直進開始(屈折終了)～直進～直進終了(屈折開始)、のフレーム数(>= 1)
     * @param prm_frame_standstill_refraction 屈折時(直進終了(屈折開始)～停止～直進開始(屈折終了))の停滞貯めフレーム数(>= 1)
     * @param prm_pDispatche_RefractionEffect 屈折時のエフェクトアクターのデポジトリ(無しの場合はNULL)
     */
    virtual void config(int prm_num_refraction,
                        frame prm_frame_between_refraction,
                        frame prm_frame_standstill_refraction,
                        GgafCore::GgafActorDepository* prm_pDispatche_RefractionEffect);

    virtual void onCreateModel() override {}

    virtual void initialize() override {}

    /**
     * レーザーチップ座標計算等処理 .
     * 独自設定したい場合、継承して別クラスを作成し、オーバーライドしてください。
     * その際 は、本クラスの processBehavior() メソッドも呼び出してください。
     */
    virtual void processBehavior() override;

    virtual void processJudgement() override {}

    virtual void processSettlementBehavior() override;

    virtual void onCatchEvent(hashval prm_no, void* prm_pSource) override {}

    /**
     * 先頭チップのレーザーの直進終了～屈折開始時の処理 .
     * @param prm_num_refraction 屈折カウント(何回目の屈折開始か)(0～)
     */
    virtual void onRefractionBegin(int prm_num_refraction) = 0;

    /**
     * 先頭チップのレーザーのため後屈折後終了～直進開始時の処理 .
     * 実際には存在しない0回目の屈折終了からスタートする。
     * @param prm_num_refraction 屈折カウント(何回目の屈折終了か)(0～)
     */
    virtual void onRefractionFinish(int prm_num_refraction) = 0;

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

    virtual ~RefractionLaserChip();

};

}
#endif /*HOMINGLASERCHIP_H_*/

