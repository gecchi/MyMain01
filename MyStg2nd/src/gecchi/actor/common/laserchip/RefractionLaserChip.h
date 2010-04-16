﻿#ifndef REFRACTIONLASERCHIP_H_
#define REFRACTIONLASERCHIP_H_
namespace MyStg2nd {

/**
 * 屈折レーザー用ポリラインのチップ .
 * 屈折レーザーと表現しているが、
 * 正確には発射座標固定、移動方向は先頭チップが決める、押し出し形レーザーというべきか。
 * ところてん方式レーザーと言うべきか、そんな感じ。
 * @version 1.00
 * @since 2010/01/19
 * @author Masatoshi Tsuge
 */
class RefractionLaserChip : public LaserChip {
    friend class LaserChipDispatcher;

private:
    DWORD _frame_refraction_enter;
    DWORD _frame_refraction_outer;
    bool _isRefracting;
    int _cnt_refraction;
public:
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

    int _num_refraction;
    DWORD _frame_refraction_interval;
    DWORD _frame_standstill;


    RefractionLaserChip(const char* prm_name, const char* prm_model);

    void setParam(int prm_num_refraction, DWORD prm_frame_refraction_interval, DWORD prm_frame_standstill) {
        _num_refraction = prm_num_refraction;
        _frame_refraction_interval = _frame_refraction_interval;
        _frame_standstill = prm_frame_standstill;
    }

    virtual void initialize() override;

    /**
     * レーザーチップ座標計算等処理 .
     * 独自設定したい場合、継承して別クラスを作成し、オーバーライドしてください。
     * その際 は、本クラスの processBehavior() メソッドも呼び出してください。
     */
    virtual void processBehavior() override;

    /**
     * 屈折レーザーの先頭チップの動きを実装する .
     * 本当の先頭チップの場合はもちろんコールバックされるが、
     * にわか先頭チップ（ちぎれて急に先頭になったチップ）の場合もコールバックされます。
     */
    virtual void onRefraction(int prm_num_refraction)=0;

    /**
     * レーザーチップ判定等処理 .
     * 独自設定したい場合、継承して別クラスを作成し、オーバーライドしてください。
     * その際 は、本クラスの processJudgement() メソッドも呼び出してください。
     * 実は本メソッドで、GgafDx9GeometricActor::updateWorldMatrix_Mv(this, _matWorld) を呼び出しており、
     * このタイミングでワールド変換行列が確定しますので、オーバーライドの際は最後に RefractionLaserChip::processJudgement(); と
     * したほうが良いでしょう。
     */
    virtual void processJudgement() override;

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


    //virtual void initializeRefraction(GgafDx9Core::GgafDx9GeometricActor* prm_pActor_Target);

    virtual ~RefractionLaserChip();

};

}
#endif /*HOMINGLASERCHIP_H_*/

