#ifndef GGAFCORE_GGAFORDER_H_
#define GGAFCORE_GGAFORDER_H_
#include "GgafCommonHeader.h"
#include "jp/ggaf/core/GgafObject.h"
#include <windows.h>

namespace GgafCore {

/**
 * 商品（インスタンス）の注文クラス .
 * 注文識別ID(_order_id) + 受取予定人(_pReceiver) で商品は管理されユニークになります。
 * 工場(GgafFactory)に渡す注文を表したクラスで、 商品（インスタンス）１つを内部保持します。<BR>
 * また注文オブジェクト同士で連結リストを作成でき、そのリストは工場(GgafFactory)が操作することになります。<BR>
 * @version 1.00
 * @since 2007/12/17
 * @author Masatoshi Tsuge
 */
class GgafOrder : public GgafObject {
    friend class GgafGod;
    friend class GgafFactory;

private:
    /** 発注者 */
    GgafObject* _pOrderer;
    /** 受取予定人(nullptrの場合は、だれでも受け取れる) */
    GgafObject* _pReceiver;
    /** 発注時刻 */
    DWORD _time_of_order;
    /** 製造開始時刻 */
    DWORD _time_of_create_begin;
    /** 製造完了時刻 */
    DWORD _time_of_create_finish;
    /** 一つ次の注文 */
    GgafOrder* _pOrder_next;
    /** 一つ前の注文 */
    GgafOrder* _pOrder_prev;
    /** 先頭の注文フラグ */
    bool _is_first_order_flg;
    /** 最後の注文フラグ */
    bool _is_last_order_flg;
    /** 商品製造メソッド */
    GgafObject* (*_pFunc)(void*, void*, void*);
    /** 商品製造メソッドのパラメータ1 */
    void* _pArg1;
    /** 商品製造メソッドのパラメータ2 */
    void* _pArg2;
    /** 商品製造メソッドのパラメータ3 */
    void* _pArg3;

public:
    /** 注文識別ID */
    uint64_t _order_id;
    /** 進捗具合（0:未着手/1:製造中/2:製造済み） */
    int _progress;
    /** 商品へのポインタ */
    GgafObject* _pObject_creation;

public:
    GgafOrder(uint64_t prm_order_id);
    virtual ~GgafOrder();
};

}
#endif /*GGAFCORE_GGAFORDER_H_*/
