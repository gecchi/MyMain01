#ifndef GGAF_CORE_CRADLE_H_
#define GGAF_CORE_CRADLE_H_
#include "jp/ggaf/GgafCommonHeader.h"
#include "jp/ggaf/core/Object.h"
#include <string>
#include <windows.h>
#ifdef __GNUG__
    #undef __in
    #undef __out
#endif

namespace GgafCore {

/**
 * 命（インスタンス）のゆりかごクラス .
 * ゆりかご番号(_cradle_no) + 受取予定人(_pReceiver) で命は管理されユニークになります。
 * 管理者に渡すゆりかごを表したクラスで、 命（インスタンス）１つを内部保持します。<BR>
 * またゆりかごオブジェクト同士で連結リストを作成でき、そのリストは管理者が操作することになります。<BR>
 * @version 1.00
 * @since 2007/12/17
 * @author Masatoshi Tsuge
 */
class Cradle : public Object {
    friend class Caretaker;

private:
    /** 望んだ人 */
    Object* _pWisher;
    /** 受取予定人(nullptrの場合は、だれでも受け取れる) */
    Object* _pReceiver;
    /** 望んだ時刻 */
    DWORD _time_of_wants;
    /** 祝福開始時刻 */
    DWORD _time_of_create_begin;
    /** 祝福完了時刻 */
    DWORD _time_of_create_finish;
    /** 一つ次のゆりかご */
    Cradle* _pCradle_next;
    /** 一つ前のゆりかご */
    Cradle* _pCradle_prev;
    /** 先頭のゆりかごフラグ */
    bool _is_first_cradle_flg;
    /** 最後のゆりかごフラグ */
    bool _is_last_cradle_flg;
    /** 祝福メソッド */
    Object* (*_pFunc)(void*, void*, void*);
    /** 祝福メソッドのパラメータ1 */
    void* _pArg1;
    /** 祝福メソッドのパラメータ2 */
    void* _pArg2;
    /** 祝福メソッドのパラメータ3 */
    void* _pArg3;

public:
    /** ゆりかご番号 */
    uint64_t _cradle_no;
    /** 進捗状況（0:未着手/1:祝福中/2:祝福済み） */
    int _progress_no;
    /** 命への臍の緒 */
    Object* _pObject_creation;

public:
    Cradle(uint64_t prm_cradle_no);

    std::string getDebuginfo();

    virtual ~Cradle();
};

}
#endif /*GGAF_CORE_CRADLE_H_*/
