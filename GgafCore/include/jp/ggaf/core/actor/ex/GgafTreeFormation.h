#ifndef GGAFCORE_GGAFTREEFORMATION_H_
#define GGAFCORE_GGAFTREEFORMATION_H_
#include "GgafCommonHeader.h"
#include "jp/ggaf/core/actor/ex/GgafFormation.h"

namespace GgafCore {

/**
 * 配下ツリー管理のフォーメーション管理クラス .
 * 編隊メンバーは使い捨てのフォーメーション。
 * 使用する場合は、本クラスを継承し、addFormationMember(GgafActor*) により
 * 編隊メンバーを追加していってください。
 * また、登録のアクターが破壊された場合は、編隊全滅判定のために
 * GgafActor::notifyDestroyedToFormation(); をコールしてください。
 * processFinal()を実装済みですので、オーバーライドする場合は注意して下さい。
 * @version 1.00
 * @since 2008/08/08
 * @author Masatoshi Tsuge
 */
class GgafTreeFormation : public GgafFormation {
private:
    /**
     * 使用不可 .
     * @param prm_pSub
     */
    virtual void addSubLast(GgafCore::GgafActor* prm_pSub) override {
        throwGgafCriticalException("は使用不可です。");
    }

    /** [r]callUpMember()用のカーソル */
    GgafCore::GgafActor* _pIte;
    bool _can_call_up;
    bool _is_addmember_experienced;

public:
    /**
     * コンストラクタ .
     * @param prm_name
     * @param prm_offset_frames_end 子が無くなったときに解放する猶予フレーム
     * @return
     */
    GgafTreeFormation(const char* prm_name, frame prm_offset_frames_end);

    /**
     * サブが無ければ本オブジェクト解放という処理 .
     * 構成メンバーが全て sayonara() した場合、本フォーメーションオブジェクトが自動解放される
     * ようにするために実装済みです。
     * 下位で processFinal() の処理が必要な場合は、
     * オーバーライドして、その処理中での何処かで
     * <code>
     * GgafTreeFormation::processFinal();
     * </code>
     * を呼び出してください、
     */
    virtual void processFinal() override;

    /**
     * 編隊のメンバーを登録します.
     * 編隊を構成するために、本メソッドを実行し、メンバーを予め配下アクターに設定する必要がある。<BR>
     * 最初に登録したアクターが、フォーメーションの種別となるため、同じ種別をaddFormationMember する必要がある。<BR>
     * 内部で自動で inactivateImmed() が実行され、最初は待機状態となる。<BR>
     * 構成メンバーを活動させるには、callUpMember() を使用。<BR>
     * 構成メンバーを活動終了時は、sayonara() を使用。解放対象になる。<BR>
     * 編隊メンバーは使い捨てである。<BR>
     * @param prm_pSub 編隊のメンバーのアクター
     */
    virtual void addFormationMember(GgafCore::GgafActor* prm_pSub);

    /**
     * 登録した編隊のメンバーを順番に取得します.
     * addFormationMember(GgafCore::GgafActor*) により、登録した編隊メンバーを順番に取り出します。
     * 全て編隊メンバーを取得してしまった場合、nullptr を返します。
     * @return 未活動の編隊登録メンバー。又は nullptr、未活動の編隊登録メンバーはもう無い。
     */
    GgafActor* callUpMember();

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
     * GgafTreeFormation::onEnd() を呼び出して下さい。
     */
    virtual void onEnd() override;

    /**
     * 編隊に所属したアクターが全てさよなら(sayonara()が呼び出された)した場合コールバックされるメソッド .
     * 必要に応じて下位でオーバーライドし実装して下さい。
     */
    virtual void onSayonaraAll() override {
    }

    virtual ~GgafTreeFormation();
};

}
#endif /*GGAFCORE_GGAFTREEFORMATION_H_*/
