#ifndef CURVELASERCHIP_H_
#define CURVELASERCHIP_H_
namespace GgafLib {

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
    friend class LaserChipDepository;

public:
    int _tmpX, _tmpY, _tmpZ;

public:
    WateringLaserChip(const char* prm_name, const char* prm_model, GgafCore::GgafStatus* prm_pStat=nullptr);

    virtual void onCreateModel() override {}

    virtual void initialize() override {}

    /**
     * レーザーチップ出現時処理 .
     * 独自設定したい場合、継承して別クラスを作成し、オーバーライドしてください。
     * その際 は、本クラスの onActive() メソッドも呼び出してください。
     */
    virtual void onActive() override;

    /**
     * レーザーチップ座標計算等処理 .
     * 独自設定したい場合、継承して別クラスを作成し、オーバーライドしてください。
     * その際 は、本クラスの processBehavior() メソッドも呼び出してください。
     */
    virtual void processBehavior() override;

    virtual void processJudgement() override {}

    virtual void processSettlementBehavior() override;

    virtual void onCatchEvent(hashval prm_no, void* prm_pSource) override {}

    virtual ~WateringLaserChip();

};

}
#endif /*CURVELASERCHIP_H_*/

