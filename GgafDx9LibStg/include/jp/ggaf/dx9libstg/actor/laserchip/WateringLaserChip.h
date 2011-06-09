#ifndef CURVELASERCHIP_H_
#define CURVELASERCHIP_H_
namespace GgafDx9LibStg {

/**
 * 水撒きレーザー用ポリラインのチップ .
 * 水撒きレーザーなどと表現しているが、正確には<BR>
 * ・発射座標任意（発射元座標が移動可能）<BR>
 * ・各チップの移動方向、速度共に固定<BR>
 * ・しかし、隣接するチップとチップが手を取り合い、チップ間に当たり判定が発生<BR>
 * というべきか、グラディウスＶのディレクションレーザー(TYPE2)と言うべきか、そんな感じ。<BR>
 * @version 1.00
 * @since 2009/08/27
 * @author Masatoshi Tsuge
 */
class WateringLaserChip : public LaserChip {
    friend class LaserChipDispatcher;
public:
    int _tmpX, _tmpY, _tmpZ;
    WateringLaserChip(const char* prm_name, const char* prm_model);

    virtual void initialize() override;

    /**
     * レーザーチップ座標計算等処理 .
     * 独自設定したい場合、継承して別クラスを作成し、オーバーライドしてください。
     * その際 は、本クラスの processBehavior() メソッドも呼び出してください。
     */
    virtual void processBehavior() override;


    virtual void processSettlementBehavior() override;

    /**
     * レーザーチップ判定等処理 .
     * 独自設定したい場合、継承して別クラスを作成し、オーバーライドしてください。
     * その際 は、本クラスの processJudgement() メソッドも呼び出してください。
     * 実は本メソッドで、GgafDx9GeometricActor::updateWorldMatrix_Mv(this, _matWorld) を呼び出しており、
     * このタイミングでワールド変換行列が確定しますので、オーバーライドの際は最後に WateringLaserChip::processJudgement(); と
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

    virtual ~WateringLaserChip();

};

}
#endif /*CURVELASERCHIP_H_*/

