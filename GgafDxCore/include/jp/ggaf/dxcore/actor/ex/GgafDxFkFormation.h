#ifndef GGAFDXCORE_GGAFDXFKFORMATION_H_
#define GGAFDXCORE_GGAFDXFKFORMATION_H_
#include "jp/ggaf/core/actor/ex/GgafFormation.h"

namespace GgafDxCore {

/**
 * 配下ツリー管理のフォーメーション管理クラス .
 * 編隊メンバーは使い捨てのフォーメーション。
 * 使用する場合は、本クラスを継承し、addFormationMember(GgafActor*) により
 * 編隊メンバーを追加していってください。
 * processFinal()を実装済みですので、オーバーライドする場合は注意して下さい。
 * @version 1.00
 * @since 2008/08/08
 * @author Masatoshi Tsuge
 */
class GgafDxFkFormation : public GgafCore::GgafFormation {
private:
    /**
     * 使用不可 .
     * @param prm_pSub
     */
    virtual void addSubLast(GgafCore::GgafActor* prm_pSub) override {
        throwGgafCriticalException("GgafDxFkFormation::addSubLast は使用不可です。");
    }

    /** [r]callUpMember()用のカーソル */
    GgafCore::GgafActor* _pIte;
    bool _can_call_up;
public:
    /**
     * コンストラクタ .
     * @param prm_name
     * @param prm_offset_frames_end 子が無くなったときに解放する猶予フレーム
     * @return
     */
    GgafDxFkFormation(const char* prm_name, frame prm_offset_frames_end);

    /**
     * サブが無ければ本オブジェクト解放という処理 .
     * 構成メンバーが全て sayonara() した場合、本フォーメーションオブジェクトが自動解放される
     * ようにするために実装済みです。
     * 下位で processFinal() の処理が必要な場合は、
     * オーバーライドして、その処理中での何処かで
     * <code>
     * GgafDxFkFormation::processFinal();
     * </code>
     * を呼び出してください、
     */
    virtual void processFinal() override;

    /**
     * FKのベースを設定 .
     * ＜メモ＞
     * 複数可。移動制御用ダミーなどを想定。
     * もちろん実アクターでも良い。その場合本フォーメーションオブジェクトの種別を１つするため、
     * ２つ目以降は追加同じ種別である必要がある。
     * ベースのFKの追加するアクターの種別は、内部でaddSubGroupAsFkを使用し、団長が挟まっているので、
     * ここで追加するベースと同じ種別であるかどうかを気にする必要がない。
     * @param prm_pFkBase
     */
    virtual void registerFormationFkBase(GgafDxGeometricActor* prm_pFkBase);

    virtual GgafDxGeometricActor* getFkBase() {
        return (GgafDxGeometricActor*)(getSubFirst());
    }

    /**
     * 編隊のメンバーを登録。姿勢をフォワードキネマティクスで設定する。
     * 編隊を構成するために、本メソッドを実行し、メンバーを予め配下アクターに設定する必要がある。<BR>
     * 最初に登録したアクターが、フォーメーションの種別となるため、同じ種別をaddFormationMember する必要がある。<BR>
     * 構成メンバーを活動させるには、callUpMember() を使用。<BR>
     * 構成メンバーを活動終了時は、sayonara() を使用。解放対象になる。<BR>
     * 編隊メンバーは使い捨てである。<BR>
     * 内部的には、引数 prm_fkbase_index 番目のサブアクターをベースとし、そのベースアクターが addSubGroupAsFk により
     * prm_pMemberを配下に登録します。<BR>
     * <BR>
     * 引数の編隊メンバーアクターは、次の２つのメソッドの使用が可能となります。 <BR>
     * _x,_y,_z,_rx,_ry,_rz をローカル（thisからの相対）に切り替える・・・changeGeoLocal()<BR>
     * _x,_y,_z,_rx,_ry,_rz 絶対座標に切り替える                    ・・・changeGeoFinal()<BR>
     * 【注意】<BR>
     * 黒衣(_pKuroko) は、ローカル座標系でのみ使用可能となります。<BR>
     * 従属アクターprocessBehavior() の処理を抜ける前には、changeGeoFinal() で絶対座標に戻しておく必要があります。<BR>
     * @param prm_pMember 従属させるアクター
     * @param prm_x_init_local  従属アクターのローカル(this)位置からのX座標位置
     * @param prm_y_init_local  従属アクターのローカル(this)位置からのY座標位置
     * @param prm_z_init_local  従属アクターのローカル(this)位置からのZ座標位置
     * @param prm_rx_init_local 従属アクターのローカル(this)回転からのX軸回転値
     * @param prm_ry_init_local 従属アクターのローカル(this)回転からのY軸回転値
     * @param prm_rz_init_local 従属アクターのローカル(this)回転からのZ軸回転値
     */
    virtual void addFormationMember(GgafDxGeometricActor* prm_pMember,
                                    int prm_x_init_local,
                                    int prm_y_init_local,
                                    int prm_z_init_local,
                                    int prm_rx_init_local,
                                    int prm_ry_init_local,
                                    int prm_rz_init_local);

    /**
     * 登録した編隊のメンバーを順番に取得します.
     * addSubLast(GgafCore::GgafActor*) により、登録した編隊メンバーを順番に取り出します。
     * 全て編隊メンバーを取得してしまった場合、nullptr を返します。
     * @return 未活動の編隊登録メンバー。又は nullptr、未活動の編隊登録メンバーはもう無い。
     */
    GgafDxGeometricActor* callUpMember();

    /**
     * callUpMember() 可能な場合 true
     * @return true:未活動の編隊登録メンバーが未だ存在/false:もう存在しない。
     */
    inline bool canCallUp() {
        return _can_call_up;
    }

    /**
     * メンバーが残っていれば解放します。
     * 継承してオーバーライドする場合は、処理内で
     * GgafDxFkFormation::onEnd() を呼び出して下さい。
     */
    virtual void onEnd() override;

    /**
     * 編隊に所属したアクターが全てさよなら(sayonara()が呼び出された)した場合コールバックされるメソッド .
     * 必要に応じて下位でオーバーライドし実装して下さい。
     */
    virtual void onSayonaraAll() override {
    }

    virtual ~GgafDxFkFormation();
};

}
#endif /*GGAFDXCORE_GGAFDXFKFORMATION_H_*/
