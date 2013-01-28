#ifndef GGAFORDER_H_
#define GGAFORDER_H_
namespace GgafCore {

/**
 * 商品（インスタンス）の注文クラス .
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
    UINT32 _id;
    /** 進捗具合（0:未着手/1:製造中/2:製造済み） */
    int _progress;
    /** 商品へのポインタ */
    GgafObject* _pObject_creation;

public:
    GgafOrder(UINT32 prm_id);
    virtual ~GgafOrder();
};

}
#endif /*GGAFORDER_H_*/
