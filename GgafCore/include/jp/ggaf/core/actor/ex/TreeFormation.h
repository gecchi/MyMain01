#ifndef GGAF_CORE_TREEFORMATION_H_
#define GGAF_CORE_TREEFORMATION_H_
#include "jp/ggaf/GgafCommonHeader.h"
#include "jp/ggaf/core/actor/ex/Formation.h"

namespace GgafCore {

/**
 * 配下ツリー管理のフォーメーション管理クラス .
 * 編隊メンバーは使い捨てのフォーメーション。
 * 使用する場合は、本クラスを継承し、appendFormationMember(Actor*) により
 * 編隊メンバーを追加していってください。
 * また、登録のアクターが破壊された場合は、編隊全滅判定のために
 * Actor::notifyDestroyed(); をコールしてください。
 * processFinal()を実装済みですので、オーバーライドする場合は注意して下さい。
 * @version 1.00
 * @since 2008/08/08
 * @author Masatoshi Tsuge
 */
class TreeFormation : public Formation {
private:
    /**
     * 使用不可 .
     * @param prm_pChild
     */
    virtual void appendChild(Actor* prm_pChild) override {
        throwCriticalException("使用不可です。");
    }

    /** [r]calledUpMember()用のカーソル */
    Actor* _pIte;
    bool _can_called_up;
    bool _is_append_member_experienced;

public:
    /**
     * コンストラクタ .
     * @param prm_name
     * @param prm_offset_frames_end 子が無くなったときに解放する猶予フレーム
     * @return
     */
    TreeFormation(const char* prm_name, frame prm_offset_frames_end);

    /**
     * 子が無ければ本オブジェクト解放という処理 .
     * 構成メンバーが全て sayonara() した場合、本フォーメーションオブジェクトが自動解放される
     * ようにするために実装済みです。
     * 下位で processFinal() の処理が必要な場合は、
     * オーバーライドして、その処理中での何処かで
     * <code>
     * TreeFormation::processFinal();
     * </code>
     * を呼び出してください、
     */
    virtual void processFinal() override;

    /**
     * 編隊のメンバーを登録します.
     * 編隊を構成するために、本メソッドを実行し、メンバーを予め配下アクターに設定する必要がある。<BR>
     * 最初に登録したアクターが、フォーメーションの種別となるため、同じ種別をappendFormationMember する必要がある。<BR>
     * 内部で自動で inactivateImmed() が実行され、最初は待機状態となる。<BR>
     * 構成メンバーを活動させるには、calledUpMember() を使用。<BR>
     * 構成メンバーを活動終了時は、sayonara() を使用。解放対象になる。<BR>
     * 編隊メンバーは使い捨てである。<BR>
     * @param prm_pChild 編隊のメンバーのアクター
     */
    virtual void appendFormationMember(Actor* prm_pChild);

    /**
     * 登録した編隊のメンバーを順番にアクティブにして取得します.
     * appendFormationMember(Actor*) により、登録した編隊メンバーを順番に取り出します。
     * 全て編隊メンバーを取得してしまった場合、nullptr を返します。
     * @param prm_formation_child_num 本フォーメーションの管理される要員数（＝編隊全滅数）。省略時は配下メンバー数となる。
     * @return 未活動の編隊登録メンバー。又は nullptr、未活動の編隊登録メンバーはもう無い。
     */
    Actor* calledUpMember(int prm_formation_child_num = INT_MAX);

    /**
     * calledUpMember() 可能な場合 true
     * @return true:未活動の編隊登録メンバーが未だ存在/false:もう存在しない。
     */
    inline bool canCalledUp() {
        return _can_called_up;
    }

    /**
     * メンバーが残っていれば解放します。
     * 継承してオーバーライドする場合は、処理内で
     * TreeFormation::onEnd() を呼び出して下さい。
     */
    virtual void onEnd() override;

    /**
     * 編隊に所属したアクターが全てさよなら(sayonara()が呼び出された)した場合コールバックされるメソッド .
     * 必要に応じて下位でオーバーライドし実装して下さい。
     */
    virtual void onSayonaraAll() override {
    }

    virtual ~TreeFormation();
};

}
#endif /*GGAF_CORE_TREEFORMATION_H_*/
