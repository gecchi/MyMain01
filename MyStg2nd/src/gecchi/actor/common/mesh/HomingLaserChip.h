#ifndef HOMINGLASERCHIP_H_
#define HOMINGLASERCHIP_H_
namespace MyStg2nd {

class HomingLaserChip : public LaserChip {
    friend class LaserChipDispatcher;



public:
    /** 先導チップ（本当の先頭チップ）フラグ */
    bool _is_leader; //本当の先頭チップとは、レーザー移動中にちぎれて発生するにわか先頭チップでは無いという意味。
    int _begining_X;
    int _begining_Y;
    int _begining_Z;
    GgafDx9Core::angle _begining_RX;
    GgafDx9Core::angle _begining_RY;
    GgafDx9Core::angle _begining_RZ;
    int _prev_X;
    int _prev_Y;
    int _prev_Z;
    GgafDx9Core::angle _prev_RX;
    GgafDx9Core::angle _prev_RY;
    GgafDx9Core::angle _prev_RZ;

    HomingLaserChip(const char* prm_name, const char* prm_model);

    virtual void initialize();

    /**
     * レーザーチップ座標計算等処理 .
     * 独自設定したい場合、継承して別クラスを作成し、オーバーライドしてください。
     * その際 は、本クラスの processBehavior() メソッドも呼び出してください。
     */
    virtual void processBehavior();

    /**
     * ホーミングレーザーの先頭チップの動きを実装する .
     * 本当の先頭チップの場合はもちろんコールバックされるが、
     * にわか先頭チップ（ちぎれて急に先頭になったチップ）の場合もコールバックされます。
     */
    virtual void processBehaviorHeadChip() {}

    /**
     * レーザーチップ判定等処理 .
     * 独自設定したい場合、継承して別クラスを作成し、オーバーライドしてください。
     * その際 は、本クラスの processJudgement() メソッドも呼び出してください。
     * 実は本メソッドで、GgafDx9GeometricActor::updateWorldMatrix_Mv(this, _matWorld) を呼び出しており、
     * このタイミングでワールド変換行列が確定しますので、オーバーライドの際は最後に HomingLaserChip::processJudgement(); と
     * したほうが良いでしょう。
     */
    virtual void processJudgement();

    /**
     * レーザーチップ出現時処理 .
     * 独自設定したい場合、継承して別クラスを作成し、オーバーライドしてください。
     * その際 は、本クラスの onActive() メソッドも呼び出してください。
     */
    virtual void onActive();

    /**
     * レーザーチップ消失時処理 .
     * 独自設定したい場合、継承して別クラスを作成し、オーバーライドしてください。
     * その際 は、本クラスの onInactive() メソッドも呼び出してください。
     */
    virtual void onInactive();


    //virtual void initializeHoming(GgafDx9Core::GgafDx9GeometricActor* prm_pActor_Target);

    virtual ~HomingLaserChip();

};

}
#endif /*HOMINGLASERCHIP_H_*/

