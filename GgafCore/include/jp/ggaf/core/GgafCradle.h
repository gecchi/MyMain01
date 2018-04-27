#ifndef GGAFCORE_GGAFCRADLE_H_
#define GGAFCORE_GGAFCRADLE_H_
#include "GgafCommonHeader.h"
#include "jp/ggaf/core/GgafObject.h"
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
 * 神に渡すゆりかごを表したクラスで、 命（インスタンス）１つを内部保持します。<BR>
 * またゆりかごオブジェクト同士で連結リストを作成でき、そのリストは神が操作することになります。<BR>
 * @version 1.00
 * @since 2007/12/17
 * @author Masatoshi Tsuge
 */
class GgafCradle : public GgafObject {
    friend class GgafGod;

private:
    /** 望んだ人 */
    GgafObject* _pWisher;
    /** 受取予定人(nullptrの場合は、だれでも受け取れる) */
    GgafObject* _pReceiver;
    /** 望んだ時刻 */
    DWORD _time_of_wants;
    /** 祝福開始時刻 */
    DWORD _time_of_create_begin;
    /** 祝福完了時刻 */
    DWORD _time_of_create_finish;
    /** 一つ次のゆりかご */
    GgafCradle* _pCradle_next;
    /** 一つ前のゆりかご */
    GgafCradle* _pCradle_prev;
    /** 先頭のゆりかごフラグ */
    bool _is_first_cradle_flg;
    /** 最後のゆりかごフラグ */
    bool _is_last_cradle_flg;
    /** 祝福メソッド */
    GgafObject* (*_pFunc)(void*, void*, void*);
    /** 祝福メソッドのパラメータ1 */
    void* _pArg1;
    /** 祝福メソッドのパラメータ2 */
    void* _pArg2;
    /** 祝福メソッドのパラメータ3 */
    void* _pArg3;

public:
    /** ゆりかご番号 */
    uint64_t _cradle_no;
    /** 進捗具合（0:未着手/1:祝福中/2:祝福済み） */
    int _progress;
    /** 命への臍の緒 */
    GgafObject* _pObject_creation;

public:
    GgafCradle(uint64_t prm_cradle_no);

    std::string getDebuginfo();

    virtual ~GgafCradle();
};

}
#endif /*GGAFCORE_GGAFCRADLE_H_*/
