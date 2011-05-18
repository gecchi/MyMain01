#ifndef GGAFLINKEDLISTRING_H_
#define GGAFLINKEDLISTRING_H_
namespace GgafCore {

/**
 * 要素（同一型インスタンスへのポインタ）の環状双方向連結リストを構築するテンプレートです。.
 * <B>【解説】</B><BR>
 * 連結リストの先頭と末尾が繋がっているということで、『環状』と表現しています。<BR>
 *
 * 例えば、次のようなコードを書くと
 * <pre><code>
 * Object* A = new Object();
 * Object* B = new Object();
 * Object* C = new Object();
 * Object* D = new Object();
 * Object* E = new Object();
 * GgafLinkedListRing<Object> ring_list = GgafLinkedListRing<Object>();
 * ring_list.addLast(A);
 * ring_list.addLast(B);
 * ring_list.addLast(C);
 * ring_list.addLast(D);
 * ring_list.addLast(E);
 * </code></pre>
 *
 * ５つの要素で下図のような構造を採る事が出来ます。<BR>
 * <pre>
 * --------------------------------
 * (E)⇔A!⇔B⇔C⇔D⇔E⇔(A!)
 * --------------------------------
 * </pre>
 * テンプレート引数は内部保持するポインタの型を指定します。<BR>
 * つまり、「GgafLinkedListRing<Object*>();」ではなく「GgafLinkedListRing<Object>();」とすることとします。<BR>
 * 図の『⇔』は、要素（正確には要素を保持する入れ物）同士がお互いポインタを指しあっている事を示しています。<BR>
 * "!" はカレント要素(カーソルが指しているようなもの)で、本テンプレートメソッドによる機能の基準となる要素です。<BR>
 * 両端の「(E)」と「(A!)」という表記は、連結リストの先頭と末尾が、お互い連結している事を示しています。<BR>
 * 環状になっているため終端が無く、永遠に next 或いは prev が可能です。<BR>
 * 終端が無いですが、内部フラグによって先頭要素、末尾要素は管理されています。<BR>
 * 上図では、A を先頭要素、E を末尾要素、として内部管理されており、通常のリストのような使い方も可能です。<BR>
 * [注意]<BR>
 * 本クラスの説明で、「要素」という表現は、実はインナークラスの Elemオブジェクトへのポインタの事を指し、<BR>
 * 「要素の値」という表現は各「要素」の _pValue を指します。<BR>
 * 「要素の値」の型は T* です。上の例では Object* 型を指します。Object の値自体ではありません。
 * <BR>
 * @version 1.00
 * @since 2008/12/19
 * @author Masatoshi Tsuge
 */
template<class T>  //T:管理する要素のポインタの型
class GgafLinkedListRing : public GgafObject {

public:

    /**
     * 専用の要素値ラップクラス .
     * 実際の要素値をラッピングし、前後ポインタを保持
     */
    class Elem {
    public:
        /** 実際の要素の値 */
        T* _pValue;
        /** 次要素 */
        Elem* _pNext;
        /** 前要素 */
        Elem* _pPrev;
        /** 先頭要素フラグ (自要素が先頭要素の場合 true)*/
        bool _is_first_flg;
        /** 末尾要素フラグ (自要素が末尾要素の場合 true)*/
        bool _is_last_flg;
        /** delete時に_pValueもdeleteするかどうかのフラグ */
        bool _is_delete_value;

        /**
         * コンストラクタ
         * @param prm_pValue 値（ポインタ）
         * @param prm_is_delete_value true  : GgafLinkedListRingインスタンスdelete時に、要素(_pValue)もdeleteする。
         *                            false : 要素(_pValue)をdeleteしない。
         */
        Elem(T* prm_pValue, bool prm_is_delete_value = true) {
            _pValue = prm_pValue;
            _pNext = _pPrev = NULL;
            _is_first_flg = _is_last_flg = false;
            _is_delete_value = prm_is_delete_value;
        }

        /**
         * デストラクタ.
         * 内部保持する要素の値もdeleteされます。<BR>
         */
        ~Elem() {
            if (_is_delete_value) {
                DELETE_IMPOSSIBLE_NULL(_pValue);
            }
        }
    };

    /** [r]先頭要素 */
    Elem* _pElemFirst;

    /** [r]カレント要素 */
    Elem* _pElemActive;

    /** [r]要素数 */
    int _num_elem;

    /**
     * コンストラクタ
     */
    GgafLinkedListRing();

    /**
     * デストラクタ.
     * 内部保持する要素の値は、NULLで無い場合、それぞれ delete により解放されます。<BR>
     * TODO:delete[] やその他の解放方法に対応
     */
    virtual ~GgafLinkedListRing();

    Elem* getElemFirst() {
        return _pElemFirst;
    }

    Elem* getElemActive() {
        return _pElemActive;
    }

    /**
     * カレント要素の値（保持している内容）を取得する .
     *<pre>
     * ---「実行前」-------------
     * (E)⇔A⇔B⇔C!⇔D⇔E⇔(A)
     * --------------------------
     *               ↓ 変化せずにCをゲット
     * ---「実行後」-------------
     * (E)⇔A⇔B⇔C!⇔D⇔E⇔(A)
     * --------------------------
     * </pre>
     * @return	カレント要素の値
     */
    virtual T* getCurrent();

    /**
     * カレント要素を一つ進める。 .
     *<pre>
     * ---「実行前」-------------
     * (E)⇔A⇔B⇔C!⇔D⇔E⇔(A)
     * --------------------------
     *               ↓ next()実行。カレント要素を「次」に進めDをゲット
     * ---「実行後」-------------
     * (E)⇔A⇔B⇔C⇔D!⇔E⇔(A)
     * --------------------------
     * </pre>
     * <BR>
     * カレント要素が末尾の状態で本メソッドを実行すると、<BR>
     * 先頭がカレント要素になります。<BR>
     * <pre>
     * ---「実行前」-------------
     * (E!)⇔A⇔B⇔C⇔D⇔E!⇔(A)
     * --------------------------
     *               ↓  next()実行。カレント要素を「次（＝先頭）」に進めAをゲット
     * ---「実行後」-------------
     * (E)⇔A!⇔B⇔C⇔D⇔E⇔(A!)
     * --------------------------
     * </pre>
     * @return カレント要素を一つ進めた後の、その要素の値。
     */
    virtual T* next();

    /**
     * カレント要素の次の要素の値を取得する。カレント要素は変化しない .
     *<pre>
     * ---「実行前」-------------
     * (E)⇔A⇔B⇔C!⇔D⇔E⇔(A)
     * --------------------------
     *               ↓ getNext()実行。変化せずにDをゲット
     * ---「実行後」-------------
     * (E)⇔A⇔B⇔C!⇔D⇔E⇔(A)
     * --------------------------
     * </pre>
     * カレント要素が末尾の状態で本メソッドを実行すると、<BR>
     * 先頭要素の値を取得することになります。<BR>
     * <pre>
     * ---「実行前」-------------
     * (E!)⇔A⇔B⇔C⇔D⇔E!⇔(A)
     * --------------------------
     *               ↓  getNext()実行。変化せずにAをゲット
     * ---「実行後」-------------
     * (!E)⇔A⇔B⇔C⇔D⇔E!⇔(A)
     * --------------------------
     * </pre>
     * @return 次の要素の値
     */
    virtual T* getNext();

    /**
     * カレント要素のｎ番目の要素の値を取得する。カレント要素は変化しない .
     * getNext(1) は、getNext() と同じです。getNext(0) は getCurrent()と同じです。
     *<pre>
     * ---「実行前」-------------
     * (E)⇔A⇔B⇔C!⇔D⇔E⇔(A)
     * --------------------------
     *               ↓ getNext(2) … 変化せずにEをゲット
     * ---「実行後」-------------
     * (E)⇔A⇔B⇔C!⇔D⇔E⇔(A)
     * --------------------------
     * </pre>
     * @param n インデックス
     * @return カレント要素からｎ番目の要素の値
     */
    virtual T* getNext(int n);

    virtual T* getNextFromFirst(int n);

    /**
     * カレント要素を一つ戻す。 .
     *<pre>
     * ---「実行前」-------------
     * (E)⇔A⇔B⇔C!⇔D⇔E⇔(A)
     * --------------------------
     *               ↓ Bをゲット
     * ---「実行後」-------------
     * (E)⇔A⇔B!⇔C⇔D⇔E⇔(A)
     * --------------------------
     * </pre>
     * @return カレント要素を一つ戻した後の、その要素の値
     */
    virtual T* prev();

    /**
     * カレント要素をの１つ前の要素の値を取得する。カレント要素は変化しない .
     *<pre>
     * ---「実行前」-------------
     * (E)⇔A⇔B⇔C!⇔D⇔E⇔(A)
     * --------------------------
     *               ↓ 変化せずにBをゲット
     * ---「実行後」-------------
     * (E)⇔A⇔B⇔C!⇔D⇔E⇔(A)
     * --------------------------
     * </pre>
     * @return 前の要素の値
     */
    virtual T* getPrev();

    /**
     * カレント要素のｎ番目前の要素の値を取得する。カレント要素は変化しない .
     * getPrev(1) は、getPrev() と同じです。getPrev(0) は get()と同じです。
     *<pre>
     * ---「実行前」-------------
     * (E)⇔A⇔B⇔C!⇔D⇔E⇔(A)
     * --------------------------
     *               ↓ getPrev(2) … 変化せずにAをゲット
     * ---「実行後」-------------
     * (E)⇔A⇔B⇔C!⇔D⇔E⇔(A)
     * --------------------------
     * </pre>
     * @param n インデックス
     * @return カレント要素からｎ番目前の要素の値
     */
    virtual T* getPrev(int n);

    /**
     * カレント要素を先頭に戻す。 .
     *<pre>
     * ---「実行前」-------------
     * (E)⇔A⇔B⇔C!⇔D⇔E⇔(A)
     * --------------------------
     *               ↓ カレントを先頭にしてAをゲット
     * ---「実行後」-------------
     * (E)⇔A!⇔B⇔C⇔D⇔E⇔(A)
     * --------------------------
     * </pre>
     * @return カレント要素を先頭に戻した後の、その要素の値
     */
    virtual T* first();

    /**
     * 先頭の要素の値を取得する。カレント要素は変化しない .
     *<pre>
     * ---「実行前」-------------
     * (E)⇔A⇔B⇔C!⇔D⇔E⇔(A)
     * --------------------------
     *               ↓ 変化せずにAをゲット
     * ---「実行後」-------------
     * (E)⇔A⇔B⇔C!⇔D⇔E⇔(A)
     * --------------------------
     * </pre>
     * @return 先頭の要素の値
     */
    virtual T* getFirst();

    /**
     * カレント要素を末尾へ移動。 .
     *<pre>
     * ---「実行前」-------------
     * (E)⇔A⇔B⇔C!⇔D⇔E⇔(A)
     * --------------------------
     *               ↓ カレントを末尾にしてEをゲット
     * ---「実行後」-------------
     * (E)⇔A⇔B⇔C⇔D⇔E!⇔(A)
     * --------------------------
     * </pre>
     * @return カレント要素を末尾へ移動した後の、その要素の値
     */
    virtual T* last();

    /**
     * 末尾の要素の値を取得する。カレント要素は変化しない .
     *<pre>
     * ---「実行前」-------------
     * (E)⇔A⇔B⇔C!⇔D⇔E⇔(A)
     * --------------------------
     *               ↓ 変化せずにEをゲット
     * ---「実行後」-------------
     * (E)⇔A⇔B⇔C!⇔D⇔E⇔(A)
     * --------------------------
     * </pre>
     * @return 末尾の要素の値
     */
    virtual T* getLast();

    /**
     * カレント要素がリストの末尾であるか判定する .
     *<pre>
     * --------------------------
     * (E)⇔A⇔B⇔C⇔D⇔E!⇔(A)
     * --------------------------
     * 上図の場合true
     * </pre>
     * @return true:末尾である／false:そうでは無い
     */
    virtual bool isLast();

    /**
     * カレント要素がリストの先頭であるか判定する .
     *<pre>
     * --------------------------
     * (E)⇔A!⇔B⇔C⇔D⇔E⇔(A)
     * --------------------------
     * 上図の場合true
     * </pre>
     * @return true:末尾である／false:そうでは無い
     */
    virtual bool isFirst();

    /**
     * カレント要素に値を上書き設定する。 .
     *<pre>
     * ---「実行前」-------------
     * (E)⇔A⇔B⇔C!⇔D⇔E⇔(A)
     * --------------------------
     *               ↓ set(X) … Xを上書きして元のCをゲット
     * ---「実行後」-------------
     * (E)⇔A⇔B⇔X!⇔D⇔E⇔(A)
     * --------------------------
     * </pre>
     * 元の要素の値の解放等は、戻り値を使用して呼び元で行って下さい。
     * @return 上書きされる前の要素の値
     */
    virtual T* set(T* prm_pVal);

    /**
     * カレント要素を抜き取る .
     * 新たなカレント要素は next の要素に変わる。
     * <pre>
     * ---「実行前」-------------
     * (E)⇔A⇔B⇔C!⇔D⇔E⇔(A)
     * --------------------------
     *               ↓ remove() … C抜き出してゲット
     * ---「実行後」-------------
     * (E)⇔A⇔B⇔D!⇔E⇔(A)
     * --------------------------
     * </pre>
     *
     * <BR>
     * カレント要素が末尾だった場合<BR>
     * 新たなカレント要素は先頭要素に変わる。
     * <pre>
     * ---「実行前」-------------
     * (E!)⇔A⇔B⇔C⇔D⇔E!⇔(A)
     * --------------------------
     *               ↓ remove() … Eを抜き出してゲット
     * ---「実行後」-------------
     * (D)⇔A!⇔B⇔C⇔D⇔(A!)
     * --------------------------
     * </pre>
     *
     * 抜き取った値の解放等が必要な場合は、戻り値を使用して呼び元で行って下さい。
     * @return 抜き取る前にカレント要素だった要素の値
     */
    virtual T* remove();

    /**
     * 引数が先頭から何番目かを返す。
     * 内部保持している要素の値はポインタのため、値の比較ではなくポインタ(アドレス)が一致した
     * インデックスを返します。インデックスは0からの数値です。
     * <pre><code>
     * Object* A = new Object();
     * Object* B = new Object();
     * Object* C = new Object();
     * Object* D = new Object();
     * Object* E = new Object();
     * GgafLinkedListRing<Object> ring_list = GgafLinkedListRing<Object>();
     * ring_list.addLast(A);
     * ring_list.addLast(B);
     * ring_list.addLast(C);
     * ring_list.addLast(D);
     *
     * int a = ring_list.indexOf(A);   // a = 0 となる
     * int b = ring_list.indexOf(B);   // b = 1 となる
     * int c = ring_list.indexOf(C);   // c = 2 となる
     * int d = ring_list.indexOf(D);   // d = 3 となる
     * int e = ring_list.indexOf(E);   // e = -1 となる(存在しない場合の戻り値)
     * </code></pre>
     * @param prm_pVal インデックスを調べたい要素
     * @return 存在する場合、そのインデックス(0～)を返す、存在しない場合 -1 を返す。
     */
    virtual int indexOf(T* prm_pVal);

    /**
     * 引数要素を、末尾(_is_last_flg が true)として追加する .
     * 追加される場所は以下の図のようになります。
     *<pre>
     * ---「実行前」-------------
     * (E)⇔A⇔B⇔C!⇔D⇔E⇔(A)
     * --------------------------
     *               ↓ addLast(X)
     * ---「実行後」-------------
     * (X)⇔A⇔B⇔C!⇔D⇔E⇔X⇔(A)
     * --------------------------
     * </pre>
     * <BR>
     * また、初めてのaddLastは、引数要素はカレント要素なり、<BR>
     * ２回目以降addLastを行なってもカレント要素を影響しません。<BR>
     * <pre>
     * ---「実行前」-------------
     * NULL(要素なし)
     * --------------------------
     *               ↓ addLast(A)
     * --------------------------
     * (A!)⇔A!⇔(A!)
     * --------------------------
     *               ↓ addLast(B)
     * --------------------------
     * (B)⇔A!⇔B⇔(A!)
     * --------------------------
     *               ↓ addLast(C)
     * --------------------------
     * (C)⇔A!⇔B⇔C⇔(A!)
     * --------------------------
     * </pre>
     * @param prm_pNew 新しい要素の値
     * @param prm_is_delete_value true  : リストのインスタンスdelete時に、引数の追加要素値についてもdeleteを発行する。
     *                            false : リストのインスタンスdelete時に、引数の追加要素値について何も行わない。
     */
    virtual void addLast(T* prm_pNew, bool prm_is_delete_value = true);

    /**
     * 引数要素を、先頭(_is_first_flg が true)として追加する .
     * 追加される場所は以下の図のようになります。
     *<pre>
     * ---「実行前」-------------
     * (E)⇔A⇔B⇔C!⇔D⇔E⇔(A)
     * --------------------------
     *               ↓ addFirst(X)
     * ---「実行後」-------------
     * (E)⇔X⇔A⇔B⇔C!⇔D⇔E⇔(X)
     * --------------------------
     * </pre>
     * <BR>
     * また、初めてのaddFirstは、引数要素はカレント要素なり、<BR>
     * ２回目以降addFirstを行なってもカレント要素を影響しません。<BR>
     * <pre>
     * ---「実行前」-------------
     * NULL(要素なし)
     * --------------------------
     *               ↓ addFirst(A)
     * --------------------------
     * (A!)⇔A!⇔(A!)
     * --------------------------
     *               ↓ addFirst(B)
     * --------------------------
     * (A!)⇔B⇔A!⇔(B)
     * --------------------------
     *               ↓ addFirst(C)
     * --------------------------
     * (A!)⇔C⇔B⇔A!⇔(C)
     * --------------------------
     * </pre>
     * @param prm_pNew 新しい要素の値
     * @param prm_is_delete_value true  : リストのdelete時に、引数の追加要素値についてもdeleteを発行する。
     *                            false : リストのdelete時に、引数の追加要素値について何も行わない。
     */
    virtual void addFirst(T* prm_pNew, bool prm_is_delete_value = true);

    /**
     * 引数要素を、カレント要素の「次」に追加する .
     * 追加される場所は以下の図のようになります。
     * <pre>
     * ---「実行前」-------------
     * (E)⇔A⇔B⇔C!⇔D⇔E⇔(A)
     * --------------------------
     *               ↓ addNext(X)
     * ---「実行後」-------------
     * (E)⇔A⇔B⇔C!⇔X⇔D⇔E⇔(A)
     * --------------------------
     * </pre>
     * <BR>
     * 初めての addNext は、引数要素はカレント要素なり、<BR>
     * ２回目以降 addNext は、カレント要素を影響しません。<BR>
     * <pre>
     * ---「実行前」-------------
     * NULL(要素なし)
     * --------------------------
     *               ↓ addNext(A)
     * --------------------------
     * (A!)⇔A!⇔(A!)
     * --------------------------
     *               ↓ addNext(B)
     * --------------------------
     * (B)⇔A!⇔B⇔(A!)
     * --------------------------
     *               ↓ addNext(C)
     * --------------------------
     * (B)⇔A!⇔C⇔B⇔(A!)
     * --------------------------
     * </pre>
     * <BR>
     * カレント要素が末尾の状態で本メソッドを実行しても、<BR>
     * 引数の要素が末尾になります。（引数の要素が先頭にはなりません）<BR>
     * <pre>
     * ---「実行前」-------------
     * (E!)⇔A⇔B⇔C⇔D⇔E!⇔(A)
     * --------------------------
     *               ↓ addNext(X)
     * ---「実行後」-------------
     * (X)⇔A⇔B⇔C⇔D⇔E!⇔X⇔(A)
     * --------------------------
     * </pre>
     * @param prm_pNew インスタンス生成済み要素のポインタ
     * @param prm_is_delete_value true  : リストのdelete時に、引数の追加要素値についてもdeleteを発行する。
     *                            false : リストのdelete時に、引数の追加要素値について何も行わない。
     */
    virtual void addNext(T* prm_pNew, bool prm_is_delete_value = true);


    /**
     * 引数要素を、カレント要素の「前」に追加する .
     * 追加される場所は以下の図のようになります。
     * <pre>
     * ---「実行前」-------------
     * (E)⇔A⇔B⇔C!⇔D⇔E⇔(A)
     * --------------------------
     *               ↓ addPrev(X)
     * ---「実行後」-------------
     * (E)⇔A⇔B⇔X⇔C!⇔D⇔E⇔(A)
     * --------------------------
     * </pre>
     * <BR>
     * 初めての addPrev は、引数要素はカレント要素なり、<BR>
     * ２回目以降 addPrev は、カレント要素を影響しません。<BR>
     * <pre>
     * ---「実行前」-------------
     * NULL(要素なし)
     * --------------------------
     *               ↓ addPrev(A)
     * --------------------------
     * (A!)⇔A!⇔(A!)
     * --------------------------
     *               ↓ addPrev(B)
     * --------------------------
     * (A!)⇔B⇔A!⇔(B)
     * --------------------------
     *               ↓ addPrev(C)
     * --------------------------
     * (A!)⇔B⇔C⇔A!⇔(B)
     * --------------------------
     * </pre>
     * <BR>
     * カレント要素が先頭の状態で本メソッドを実行しても、<BR>
     * 引数の要素が先頭になります。（引数の要素が末尾にはなりません）<BR>
     * <pre>
     * ---「実行前」-------------
     * (E)⇔A!⇔B⇔C⇔D⇔E⇔(A!)
     * --------------------------
     *               ↓ addPrev(X)
     * ---「実行後」-------------
     * (E)⇔X⇔A!⇔B⇔C⇔D⇔E⇔(X)
     * --------------------------
     * </pre>
     * @param prm_pNew 新しい要素の値
     * @param prm_is_delete_value true  : リストのdelete時に、引数の追加要素値についてもdeleteを発行する。
     *                            false : リストのdelete時に、引数の追加要素について何も行わない。
     */
    virtual void addPrev(T* prm_pNew, bool prm_is_delete_value = true);


    /**
     * 要素数を返す .
     *<pre>
     * --------------------------
     * (E)⇔A⇔B⇔C!⇔D⇔E⇔(A)
     * --------------------------
     * </pre>
     * 上図の場合、length()は5を返す
     * また、要素が無い場合は 0 を返します。
     * @return 要素数
     */
    virtual int length();
};

//////////////////////////////////////////////////////////////////

/**
 * ここからは実装部
 */

template<class T>
GgafLinkedListRing<T>::GgafLinkedListRing() :
    GgafObject() {
    _num_elem = 0;
    _pElemActive = NULL;
    _pElemFirst = NULL;
}

template<class T>
T* GgafLinkedListRing<T>::getCurrent() {
    if (_pElemActive == NULL) {
        return NULL;
    } else {
        return _pElemActive->_pValue;
    }
}

template<class T>
T* GgafLinkedListRing<T>::next() {
    _pElemActive = _pElemActive->_pNext;
    return _pElemActive->_pValue;
}

template<class T>
T* GgafLinkedListRing<T>::getNext() {
    return _pElemActive->_pNext->_pValue;
}

template<class T>
T* GgafLinkedListRing<T>::getNext(int n) {
    Elem* pElem_return = _pElemActive;
    for (int i = 0; i < n; i++) {
        pElem_return = pElem_return->_pNext;
    }
    return pElem_return->_pValue;
}

template<class T>
T* GgafLinkedListRing<T>::getNextFromFirst(int n) {
    if (_pElemFirst == NULL) {
        return NULL;
    }
    Elem* pElem_return = _pElemFirst;
    for (int i = 0; i < n; i++) {
        pElem_return = pElem_return->_pNext;
    }
    return pElem_return->_pValue;
}




template<class T>
T* GgafLinkedListRing<T>::prev() {
    _pElemActive = _pElemActive->_pPrev;
    return _pElemActive->_pValue;
}

template<class T>
T* GgafLinkedListRing<T>::getPrev() {
    return _pElemActive->_pPrev->_pValue;
}

template<class T>
T* GgafLinkedListRing<T>::getPrev(int n) {
    Elem* pElem_return = _pElemActive;
    for (int i = 0; i < n; i++) {
        pElem_return = pElem_return->_pPrev;
    }
    return pElem_return->_pValue;
}

template<class T>
T* GgafLinkedListRing<T>::first() {
    _pElemActive = _pElemFirst;
    return _pElemActive->_pValue;
}

template<class T>
T* GgafLinkedListRing<T>::getFirst() {
    return _pElemFirst->_pValue;
}

template<class T>
T* GgafLinkedListRing<T>::last() {
    _pElemActive = _pElemFirst->_pPrev; //環状なので、先頭の一つ前は末尾
    return _pElemActive->_pValue;
}

template<class T>
T* GgafLinkedListRing<T>::getLast() {
    return _pElemFirst->_pPrev->_pValue; //環状なので、先頭の一つ前は末尾
}


template<class T>
bool GgafLinkedListRing<T>::isLast() {
    return _pElemActive->_is_last_flg;
}

template<class T>
bool GgafLinkedListRing<T>::isFirst() {
    return _pElemActive->_is_first_flg;
}

template<class T>
T* GgafLinkedListRing<T>::set(T* prm_pVal) {
    T* ret = _pElemActive->_pValue;
    _pElemActive->_pValue = prm_pVal;
    return ret;
}

template<class T>
T* GgafLinkedListRing<T>::remove() {
    Elem* pMy = _pElemActive;
    _num_elem--;
    if (pMy->_is_first_flg && pMy->_is_last_flg) {
        //要素が１つの場合
        _pElemActive = NULL;
        _pElemFirst = NULL;
        T* r = pMy->_pValue;
        DELETE_IMPOSSIBLE_NULL(pMy);
        return r;
    } else {
        //連結から外す
        Elem* pMyNext = _pElemActive->_pNext;
        Elem* pMyPrev = _pElemActive->_pPrev;
        //両隣のノード同士を繋ぎ、自分を指さなくする。
        pMyPrev->_pNext = pMyNext;
        pMyNext->_pPrev = pMyPrev;
        if (pMy->_is_last_flg) { //抜き取られる要素が末尾だったなら
            pMyPrev->_is_last_flg = true; //一つ前の要素が新しい末尾になる
        }
        if (pMy->_is_first_flg) { //抜き取られる要素が先頭だったなら
            _pElemFirst = pMyNext;
            pMyNext->_is_first_flg = true; //次の要素が新しい先頭になる
        }
        _pElemActive = pMyNext; //カレント要素は next に更新。
        T* r = pMy->_pValue;
        DELETE_IMPOSSIBLE_NULL(pMy);
        return r;
    }
}


template<class T>
int GgafLinkedListRing<T>::indexOf(T* prm_pVal) {
    if (_pElemFirst == NULL) {
        return -1;
    }
    int r = 0;
    Elem* pElem = _pElemFirst;
    while (true) {
        if (pElem->_pValue == prm_pVal) {
            return r;
        } else {
            if (pElem->_is_last_flg) {
                break;
            } else {
                pElem = pElem -> _pNext;
                r++;
            }
        }
    }
    return -1;
}

template<class T>
void GgafLinkedListRing<T>::addLast(T* prm_pNew, bool prm_is_delete_value) {
    if (prm_pNew == NULL) {
        throwGgafCriticalException("[GgafLinkedListRing::addLast()] Error! 引数がNULLです");
    }
    Elem* pElem = NEW Elem(prm_pNew, prm_is_delete_value);

    if (_pElemFirst == NULL) {
        //最初の１つ
        pElem->_is_first_flg = true;
        pElem->_is_last_flg = true;
        pElem->_pNext = pElem;
        pElem->_pPrev = pElem;
        _pElemActive = pElem;
        _pElemFirst = pElem;
    } else {
        //２つ目以降
        pElem->_is_first_flg = false;
        pElem->_is_last_flg = true;
        Elem* pLastElem = _pElemFirst->_pPrev;
        pLastElem->_is_last_flg = false;
        pLastElem->_pNext = pElem;
        pElem->_pPrev = pLastElem;
        pElem->_pNext = _pElemFirst;
        _pElemFirst->_pPrev = pElem;
    }
    _num_elem++;
}


template<class T>
void GgafLinkedListRing<T>::addFirst(T* prm_pNew, bool prm_is_delete_value) {
    if (prm_pNew == NULL) {
        throwGgafCriticalException("[GgafLinkedListRing::addLast()] Error! 引数がNULLです");
    }
    Elem* pElem = NEW Elem(prm_pNew, prm_is_delete_value);
    if (_pElemFirst == NULL) {
        //最初の１つ
        pElem->_is_first_flg = true;
        pElem->_is_last_flg = true;
        pElem->_pNext = pElem;
        pElem->_pPrev = pElem;
        _pElemActive = pElem;
        _pElemFirst = pElem;
    } else {
        Elem* pFirstElem = _pElemFirst;
        Elem* pLastElem = _pElemFirst->_pPrev;
        pLastElem->_pNext = pElem;
        pElem->_pPrev = pLastElem;
        pElem->_pNext = pFirstElem;
        pFirstElem->_pPrev = pElem;
        pFirstElem->_is_first_flg = false;

        pElem->_is_first_flg = true;
        pElem->_is_last_flg = false;
        _pElemFirst = pElem;
    }
    _num_elem++;
}


template<class T>
void GgafLinkedListRing<T>::addNext(T* prm_pNew, bool prm_is_delete_value) {
    if (prm_pNew == NULL) {
        throwGgafCriticalException("[GgafLinkedListRing::addLast()] Error! 引数がNULLです");
    }
    Elem* pElem = NEW Elem(prm_pNew, prm_is_delete_value);
    if (_pElemFirst == NULL) {
        //最初の１つ
        pElem->_is_last_flg = true;
        pElem->_is_first_flg = true;
        pElem->_pNext = pElem;
        pElem->_pPrev = pElem;
        _pElemActive = pElem;
        _pElemFirst = pElem;
    } else {
        Elem* pMy = _pElemActive;
        if (pMy->_is_last_flg) {
            pMy->_is_last_flg = false;
            pElem->_is_last_flg = true;
            pElem->_is_first_flg = false;
        }
        Elem* pMyNext = _pElemActive->_pNext;
        pMy->_pNext = pElem;
        pElem->_pPrev = pMy;
        pElem->_pNext = pMyNext;
        pMyNext->_pPrev = pElem;
    }
    _num_elem++;
}

template<class T>
void GgafLinkedListRing<T>::addPrev(T* prm_pNew, bool prm_is_delete_value) {
    if (prm_pNew == NULL) {
        throwGgafCriticalException("[GgafLinkedListRing::addLast()] Error! 引数がNULLです");
    }
    Elem* pElem = NEW Elem(prm_pNew, prm_is_delete_value);
    if (_pElemFirst == NULL) {
        //最初の１つ
        pElem->_is_last_flg = true;
        pElem->_is_first_flg = true;
        pElem->_pNext = pElem;
        pElem->_pPrev = pElem;
        _pElemActive = pElem;
        _pElemFirst = pElem;
    } else {
        Elem* pMy = _pElemActive;
        if (pMy->_is_first_flg) {
            pMy->_is_first_flg = false;
            pElem->_is_first_flg = true;
            pElem->_is_last_flg = false;
            _pElemFirst = pElem;
        }
        Elem* pMyPrev = _pElemActive->_pPrev;
        pMyPrev->_pNext = pElem;
        pElem->_pPrev = pMyPrev;
        pElem->_pNext = pMy;
        pMy->_pPrev = pElem;
    }
    _num_elem++;
}


template<class T>
int GgafLinkedListRing<T>::length() {
    return _num_elem;
}

template<class T>
GgafLinkedListRing<T>::~GgafLinkedListRing() {
    _TRACE_("GgafLinkedListRing<T>::~GgafLinkedListRing() BEGIN _num_elem="<<_num_elem);
    //自分に子がある場合
    if (_pElemFirst) {
        //まず子をdelete
        if (_num_elem == 1) {
            //子要素は１つの場合
            DELETE_IMPOSSIBLE_NULL(_pElemFirst);
            _pElemFirst = NULL;
            _pElemActive = NULL;
            _num_elem = 0;

        } else {
            //子要素は２つ以上の場合
            Elem* pLast = _pElemFirst->_pPrev;
            Elem* pLastPrev = pLast->_pPrev;
            while (true) {
                DELETE_IMPOSSIBLE_NULL(pLast); //末尾からdelete
                if (pLastPrev->_is_first_flg) {
                    DELETE_IMPOSSIBLE_NULL(_pElemFirst); //pSubLastPrev == _pSubFirst である
                    _pElemFirst = NULL;
                    _pElemActive = NULL;
                    _num_elem = 0;
                    break;
                }
                pLast = pLastPrev;
                pLastPrev = pLastPrev->_pPrev;
            }
        }
    }
}

}
#endif /*GGAFLINKEDLISTRING_H_*/
