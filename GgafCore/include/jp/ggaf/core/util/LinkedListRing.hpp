#ifndef GGAF_CORE_LINKEDLISTRING_H_
#define GGAF_CORE_LINKEDLISTRING_H_
#include "GgafCommonHeader.h"
#include "jp/ggaf/core/Object.h"

#include "jp/ggaf/core/exception/CriticalException.h"

namespace GgafCore {

/**
 * 環状双方向連結リスト(外部収納)を構築。.
 * <B>【解説】</B><BR>
 * オブジェクトへポインタの環状双方向連結リストを作成します。<BR>
 * 例えば、次のようなコードを書くと
 * <pre><code>
 * Object* A = new Object();
 * Object* B = new Object();
 * Object* C = new Object();
 * Object* D = new Object();
 * Object* E = new Object();
 * LinkedListRing<Object> ring_list = LinkedListRing<Object>();
 * ring_list.addLast(A);
 * ring_list.addLast(B);
 * ring_list.addLast(C);
 * ring_list.addLast(D);
 * ring_list.addLast(E);
 * </code></pre>
 *
 * ５つの要素で下図のような構造を採る事が出来ます。<BR>
 * <pre>
 * -------------------------------------------------
 * ([E])⇔[A]!⇔[B]⇔[C]⇔[D]⇔[E]⇔([A]!)
 * -------------------------------------------------
 *
 * -------------------------------------------------
 * イメージ図   [Ａ]!
 *             ／  ＼
 *          [Ｅ]    [Ｂ]
 *            \      /
 *           [Ｄ]ー[Ｃ]
 * --------------------------------------------------
 * 先頭要素     :[A]     (=getFirst();)
 * 中間要素     :[B]～[D]
 * 末尾要素     :[E]     (=getLast(); =getFirst()->getPrev();)
 * カレント要素 :[A]     (=getCurrent();)
 * </pre>
 * テンプレート引数は内部保持するポインタの型を指定します。<BR>
 * つまり、「LinkedListRing<Object*>();」ではなく「LinkedListRing<Object>();」とすることとします。<BR>
 * 『[A]』の『 [ ] 』 は、『要素』と呼ばれる入れ物（コンテナ）を表し、『[A]』の『A』は要素が保持する『値』を表しています。<BR>
 * 図の『⇔』は、要素同士がお互いポインタを指しあっている事を示しています。<BR>
 * "!" はカレント要素(カーソルが指しているようなもの)で、本テンプレートメソッドによる機能の基準となる要素です。<BR>
 * 両端の『([E])』と『([A]!)』という表記は、要素リストの先頭と末尾が、お互い連結している事を示しています。<BR>
 * 環状になっているため終端が無く、永遠に next 或いは prev が可能です。<BR>
 * next 或いは prev での終端はありませんが、内部フラグによってリストの先頭要素、末尾要素は管理されています。<BR>
 * 上図では、『[A]』 を先頭要素、『[E]』 を末尾要素、として内部管理されており、通常の線形リストのような使い方も可能です。<BR>
 * [捕捉]<BR>
 * 本クラスの説明で、「要素」という表現は、実はインナークラスの Elemオブジェクトへのポインタの事を指し、<BR>
 * 「要素の値」という表現は Elem オブジェクトのメンバ _pValue を指します。<BR>
 * 「要素の値」の型は T* です。上の例では Object* 型を指します。Object の値自体ではありません。
 * <BR>
 * @tparam T 管理する要素の型（この型のポインタ型が内部で管理される。）
 * @version 1.00
 * @since 2008/12/19
 * @author Masatoshi Tsuge
 */
template<class T>
class LinkedListRing: public Object {

public:
    /**
     * コンテナ .
     * 値をラップし、前後ポインタを保持。
     */
    class Elem {
    public:
        /** [r]実際の要素の値 */
        const T* _pValue;
        /** [r]次要素 */
        Elem* _pNext;
        /** [r]前要素 */
        Elem* _pPrev;
        /** [r]関連要素配列 */
        Elem** _papRelation;
        /** [r]先頭要素フラグ (自要素が先頭要素の場合 true)*/
        bool _is_first_flg;
        /** [r]末尾要素フラグ (自要素が末尾要素の場合 true)*/
        bool _is_last_flg;
        /** [r/w]delete時に_pValueもdeleteするかどうかのフラグ */
        bool _is_delete_value;
        /** [r]先頭要素からのインデックス(0～)。createIndex()実行で作成される */
        int _idx;

    public:
        /**
         * コンストラクタ
         * @param prm_pValue 値（ポインタ）
         * @param prm_relation_num 追加確保する関連要素数
         * @param prm_is_delete_value true  : LinkedListRingインスタンスdelete時に、要素(_pValue)もdeleteする。<BR>
         *                            false : 要素(_pValue)をdeleteしない。
         */
        Elem(const T* prm_pValue, int prm_relation_num,
                bool prm_is_delete_value = true) {
            _pValue = prm_pValue;
            _pNext = _pPrev = nullptr;
            if (prm_relation_num == 0) {
                _papRelation = nullptr;
            } else {
                _papRelation = NEW Elem*[prm_relation_num];
                for (int i = 0; i < prm_relation_num; i++) {
                    _papRelation[i] = nullptr;
                }
            }
            _is_first_flg = _is_last_flg = false;
            _is_delete_value = prm_is_delete_value;
            _idx = -1;
        }
        /**
         * 要素の値を返す。
         * @return 値
         */
        inline T* getValue() const {
            return (T*) _pValue;
        }
        /**
         * 要素を一方的に関連付ける .
         * @param prm_connection_index 要素関連接続番号
         * @param prm_pOppElem 被関連要素
         */
        void connect(int prm_connection_index, Elem* prm_pOppElem) {
            _papRelation[prm_connection_index] = prm_pOppElem;
        }
        /**
         * デストラクタ.
         * 内部保持する要素の値もdeleteされます。<BR>
         */
        ~Elem() {
            if (_is_delete_value) {
                GGAF_DELETE(_pValue);
            }
            GGAF_DELETEARR_NULLABLE(_papRelation);
        }
    }; //class Elem

    /** [r]先頭要素 */
    Elem* _pElem_first;
    /** [r]カレント要素 */
    Elem* _pElemActive;
    /** [r]要素数 */
    int _num_elem;
    /** [r]関連要素数 */
    int _relation_num;
    /** [r]インデックスに対する要素値の配列、createIndex()実行で作成される */
    const T** _papLinearVal;

public:
    /**
     * コンストラクタ .
     * 拡張関連要素数とは、next prev 以外にリレーションを行う枝数です。
     * @param prm_extend_relation_num 拡張関連要素数
     */
    LinkedListRing(int prm_extend_relation_num = 0);

    /**
     * デストラクタ.
     * 内部保持する要素の値は、nullptrで無い場合、それぞれ delete により解放されます。<BR>
     * TODO:delete[] やその他の解放方法に対応
     */
    virtual ~LinkedListRing();

    /**
     * 引数の値を、カレント要素の「次」に追加する。
     * 追加される場所は以下の図のようになります。
     * <pre>
     * ---「実行前」------------------------------
     * ([E])⇔[A]⇔[B]⇔[C]!⇔[D]⇔[E]⇔([A])
     * -------------------------------------------
     *               ↓ addNext(X) 実行。カレント要素 [C] の「次」に挿入される。
     * ---「実行後」------------------------------
     * ([E])⇔[A]⇔[B]⇔[C]!⇔[X]⇔[D]⇔[E]⇔([A])
     * -------------------------------------------
     * </pre>
     * <BR>
     * 基本的にカレント要素は変化しません、但し初めての addNext は、<BR>
     * 引数の値の要素はカレント要素になります。<BR>
     * ２回目以降 addNext() は、カレント要素に影響を与えません。<BR>
     * <pre>
     * ---「実行前」------------------------------
     * nullptr(要素なし)
     * -------------------------------------------
     *               ↓ addNext(A)
     * -------------------------------------------
     * ([A]!)⇔[A]!⇔([A]!)
     * -------------------------------------------
     *               ↓ addNext(B)
     * -------------------------------------------
     * ([B])⇔[A]!⇔[B]⇔([A]!)
     * -------------------------------------------
     *               ↓ addNext(C)
     * -------------------------------------------
     * ([B])⇔[A]!⇔[C]⇔[B]⇔([A]!)
     * -------------------------------------------
     * </pre>
     * <BR>
     * カレント要素が末尾の状態で本メソッドを実行し、末尾の「次」に挿入を行った場合、<BR>
     * 引数の値が、末尾の要素値になります。（引数の値の要素が、先頭にはなりません）<BR>
     * <pre>
     * ---「実行前」------------------------------
     * ([E]!)⇔[A]⇔[B]⇔[C]⇔[D]⇔[E]!⇔([A])
     * -------------------------------------------
     *               ↓ addNext(X)
     * ---「実行後」------------------------------
     * ([X])⇔[A]⇔[B]⇔[C]⇔[D]⇔[E]!⇔[X]⇔([A])
     * -------------------------------------------
     * </pre>
     * createIndex() によって作成された内部インデックスは破棄されます。
     *
     * @param prm_pNew インスタンス生成済み要素のポインタ
     * @param prm_is_delete_value true  : リストのdelete時に、引数の追加要素値についてもdeleteを発行する。(Tのヘッダincludeを忘れずに！)<BR>
     *                            false : リストのdelete時に、引数の追加要素値について何も行わない。
     */
    virtual void addNext(const T* prm_pNew, bool prm_is_delete_value = true);

    /**
     * 引数の値を、カレント要素の「前」に追加する。カレント要素は変化しない .
     * 追加される場所は以下の図のようになります。
     * <pre>
     * ---「実行前」------------------------------
     * ([E])⇔[A]⇔[B]⇔[C]!⇔[D]⇔[E]⇔([A])
     * -------------------------------------------
     *               ↓ addPrev(X)
     * ---「実行後」------------------------------
     * ([E])⇔[A]⇔[B]⇔[X]⇔[C]!⇔[D]⇔[E]⇔([A])
     * -------------------------------------------
     * </pre>
     * <BR>
     * 基本的にカレント要素は変化しません、但し初めての addPrev() は、
     * 引数の値はカレント要素値となります。<BR>
     * ２回目以降 addPrev() は、カレント要素に影響を与えません。<BR>
     * <pre>
     * ---「実行前」------------------------------
     * nullptr(要素なし)
     * -------------------------------------------
     *               ↓ addPrev(A)
     * -------------------------------------------
     * ([A]!)⇔[A]!⇔([A]!)
     * -------------------------------------------
     *               ↓ addPrev(B)
     * -------------------------------------------
     * ([A]!)⇔[B]⇔[A]!⇔([B])
     * -------------------------------------------
     *               ↓ addPrev(C)
     * -------------------------------------------
     * ([A]!)⇔[B]⇔[C]⇔[A]!⇔([B])
     * -------------------------------------------
     * </pre>
     * <BR>
     * カレント要素が先頭の状態で本メソッドを実行し、先頭の「前」に挿入を行った場合、<BR>
     * 引数の値の要素が先頭になります。（引数の値の要素が末尾にはなりません）<BR>
     * <pre>
     * ---「実行前」------------------------------
     * ([E])⇔[A]!⇔[B]⇔[C]⇔[D]⇔[E]⇔([A]!)
     * -------------------------------------------
     *               ↓ addPrev(X)
     * ---「実行後」------------------------------
     * ([E])⇔[X]⇔[A]!⇔[B]⇔[C]⇔[D]⇔[E]⇔([X])
     * -------------------------------------------
     * </pre>
     * createIndex() によって作成された内部インデックスは破棄されます。
     *
     * @param prm_pNew 新しい要素の値
     * @param prm_is_delete_value true  : リストのdelete時に、引数の追加要素値についてもdeleteを発行する。(Tのヘッダincludeを忘れずに！)<BR>
     *                            false : リストのdelete時に、引数の追加要素について何も行わない。
     */
    virtual void addPrev(const T* prm_pNew, bool prm_is_delete_value = true);

    /**
     * 引数の値を、末尾(_is_last_flg が true)として追加する .
     * 追加される場所は以下の図のようになります。
     * <pre>
     * ---「実行前」------------------------------
     * ([E])⇔[A]⇔[B]⇔[C]!⇔[D]⇔[E]⇔([A])
     * -------------------------------------------
     *               ↓ addLast(X)
     * ---「実行後」------------------------------
     * ([X])⇔[A]⇔[B]⇔[C]!⇔[D]⇔[E]⇔[X]⇔([A])
     * -------------------------------------------
     * </pre>
     * <BR>
     * 基本的にカレント要素は変化しません、但し初めての addLast() は、
     * 引数の値はカレント要素になります。<BR>
     * ２回目以降 addLast() は、カレント要素に影響を与えません。<BR>
     * <pre>
     * ---「実行前」------------------------------
     * nullptr(要素なし)
     * -------------------------------------------
     *               ↓ addLast(A)
     * -------------------------------------------
     * ([A]!)⇔[A]!⇔([A]!)
     * -------------------------------------------
     *               ↓ addLast(B)
     * -------------------------------------------
     * ([B])⇔[A]!⇔[B]⇔([A]!)
     * -------------------------------------------
     *               ↓ addLast(C)
     * -------------------------------------------
     * ([C])⇔[A]!⇔[B]⇔[C]⇔([A]!)
     * -------------------------------------------
     * </pre>
     * createIndex() によって作成された内部インデックスは破棄されます。
     *
     * @param prm_pNew 新しい要素の値
     * @param prm_is_delete_value true  : リストのインスタンスdelete時に、引数の追加要素値についてもdeleteを発行する。(Tのヘッダincludeを忘れずに！)<BR>
     *                            false : リストのインスタンスdelete時に、引数の追加要素値について何も行わない。
     */
    virtual void addLast(const T* prm_pNew, bool prm_is_delete_value = true);

    /**
     * 引数の値を、先頭(_is_first_flg が true)として追加する .
     * 追加される場所は以下の図のようになります。
     * <pre>
     * ---「実行前」------------------------------
     * ([E])⇔[A]⇔[B]⇔[C]!⇔[D]⇔[E]⇔([A])
     * -------------------------------------------
     *               ↓ addFirst(X)
     * ---「実行後」------------------------------
     * ([E])⇔[X]⇔[A]⇔[B]⇔[C]!⇔[D]⇔[E]⇔([X])
     * -------------------------------------------
     * </pre>
     * <BR>
     * 基本的にカレント要素は変化しません、但し初めての addFirst() は、
     * 引数の値はカレント要素なります。<BR>
     * ２回目以降 addFirst() は、カレント要素に影響を与えません。<BR>
     * <pre>
     * ---「実行前」------------------------------
     * nullptr(要素なし)
     * -------------------------------------------
     *               ↓ addFirst(A)
     * -------------------------------------------
     * ([A]!)⇔[A]!⇔([A]!)
     * -------------------------------------------
     *               ↓ addFirst(B)
     * -------------------------------------------
     * ([A]!)⇔[B]⇔[A]!⇔([B])
     * -------------------------------------------
     *               ↓ addFirst(C)
     * -------------------------------------------
     * ([A]!)⇔[C]⇔[B]⇔[A]!⇔([C])
     * -------------------------------------------
     * </pre>
     * createIndex() によって作成された内部インデックスは破棄されます。
     *
     * @param prm_pNew 新しい要素の値
     * @param prm_is_delete_value true  : リストのdelete時に、引数の追加要素値についてもdeleteを発行する。(Tのヘッダincludeを忘れずに！)<BR>
     *                            false : リストのdelete時に、引数の追加要素値について何も行わない。
     */
    virtual void addFirst(const T* prm_pNew, bool prm_is_delete_value = true);

    /**
     * カレント要素を一つ進め、その要素の値を得る .
     * <pre>
     * ---「実行前」------------------------------
     * ([E])⇔[A]⇔[B]⇔[C]!⇔[D]⇔[E]⇔([A])
     * -------------------------------------------
     *               ↓ next()実行。カレント要素を「次」に進め、値 D をゲット
     * ---「実行後」------------------------------
     * ([E])⇔[A]⇔[B]⇔[C]⇔[D]!⇔[E]⇔([A])
     * -------------------------------------------
     * </pre>
     * <BR>
     * カレント要素が末尾の状態で本メソッドを実行すると、<BR>
     * 先頭がカレント要素になります。<BR>
     * <pre>
     * ---「実行前」------------------------------
     * ([E]!)⇔[A]⇔[B]⇔[C]⇔[D]⇔[E]!⇔([A])
     * -------------------------------------------
     *               ↓  next()実行。カレント要素を「次(＝先頭)」に進め、値 A をゲット
     * ---「実行後」------------------------------
     * ([E])⇔[A]!⇔[B]⇔[C]⇔[D]⇔[E]⇔([A]!)
     * -------------------------------------------
     * </pre>
     * @return カレント要素を一つ進めた後、その要素の値を返す
     */
    virtual T* next();

    /**
     * カレント要素を一つ戻し、その要素の値を得る .
     * <pre>
     * ---「実行前」------------------------------
     * ([E])⇔[A]⇔[B]⇔[C]!⇔[D]⇔[E]⇔([A])
     * -------------------------------------------
     *               ↓ prev() 実行。値 B をゲット
     * ---「実行後」------------------------------
     * ([E])⇔[A]⇔[B]!⇔[C]⇔[D]⇔[E]⇔([A])
     * -------------------------------------------
     * </pre>
     * <BR>
     * カレント要素が先頭の状態で本メソッドを実行すると、<BR>
     * 末尾がカレント要素になります。<BR>
     * <pre>
     * ---「実行前」------------------------------
     * ([E])⇔[A]!⇔[B]⇔[C]⇔[D]⇔[E]⇔([A]!)
     * -------------------------------------------
     *               ↓   prev() 実行。カレント要素を「前(＝末尾)」に移動、値 E をゲット
     * ---「実行後」------------------------------
     * ([E]!)⇔[A]⇔[B]⇔[C]⇔[D]⇔[E]!⇔([A])
     * -------------------------------------------
     * </pre>
     * @return カレント要素を一つ前に戻した後、その要素の値を返す
     */
    virtual T* prev();

    /**
     * カレント要素を先頭に戻し、その要素の値を得る .
     * <pre>
     * ---「実行前」------------------------------
     * ([E])⇔[A]⇔[B]⇔[C]!⇔[D]⇔[E]⇔([A])
     * -------------------------------------------
     *               ↓ カレントを先頭に移動、その要素の値 A をゲット
     * ---「実行後」------------------------------
     * ([E])⇔[A]!⇔[B]⇔[C]⇔[D]⇔[E]⇔([A])
     * -------------------------------------------
     * </pre>
     * @return カレント要素を先頭に戻した後、その要素の値を返す
     */
    virtual T* first();
    /**
     * カレント要素を末尾へ移動。 .
     * <pre>
     * ---「実行前」------------------------------
     * ([E])⇔[A]⇔[B]⇔[C]!⇔[D]⇔[E]⇔([A])
     * -------------------------------------------
     *               ↓ カレントを末尾に移動、その要素の値 E をゲット
     * ---「実行後」------------------------------
     * ([E]!)⇔[A]⇔[B]⇔[C]⇔[D]⇔[E]!⇔([A])
     * -------------------------------------------
     * </pre>
     * @return カレント要素を末尾へ移動した後の、その要素の値
     */
    virtual T* last();

    /**
     * カレント要素を指定の先頭要素からの絶対インデックスに移動させ、その要素の値を得る .
     * <pre>
     * ---「実行前」------------------------------
     * ([E])⇔[A]⇔[B]⇔[C]!⇔[D]⇔[E]⇔([A])
     * -------------------------------------------
     *               ↓ current(1); カレントを移動、その要素の値 B をゲット
     * ---「実行後」------------------------------
     * ([E])⇔[A]⇔[B]!⇔[C]⇔[D]⇔[E]⇔([A])
     *         0    1     2    3    4
     * -------------------------------------------
     * </pre>
     * @param n 先頭要素からの絶対インデックス
     * @return カレント要素が移動した後の、その要素の値
     */
    virtual T* current(int n);

    /**
     * カレント要素を関連要素へ移動させ、その要素の値を得る  .
     * 引数の関連要素接続番号が範囲外の場合、又は関連未設定の場合エラー
     * @param prm_connection_index 関連要素接続番号
     * @return カレント要素が関連要素へ移動した後の、その要素の値
     */
    virtual T* gotoRelation(int prm_connection_index);

    /**
     * カレント要素の次の要素の値を取得する。カレント要素は変化しない .
     * <pre>
     * ---「実行前」------------------------------
     * ([E])⇔[A]⇔[B]⇔[C]!⇔[D]⇔[E]⇔([A])
     * -------------------------------------------
     *               ↓ getNext() 実行。特に変化せずに、値 D をゲット
     * ---「実行後」------------------------------
     * ([E])⇔[A]⇔[B]⇔[C]!⇔[D]⇔[E]⇔([A])
     * -------------------------------------------
     * </pre>
     * カレント要素が末尾の状態で本メソッドを実行すると、<BR>
     * 先頭要素の値を取得することになります。<BR>
     * <pre>
     * ---「実行前」------------------------------
     * ([E]!)⇔[A]⇔[B]⇔[C]⇔[D]⇔[E]!⇔([A])
     * -------------------------------------------
     *               ↓  getNext() 実行。特に変化せずに、値 A をゲット
     * ---「実行後」------------------------------
     * (![E])⇔[A]⇔[B]⇔[C]⇔[D]⇔[E]!⇔([A])
     * -------------------------------------------
     * </pre>
     * @return 次の要素の値
     */
    virtual T* getNext() const;

    /**
     * カレント要素のｎ番目の要素の値を取得する。カレント要素は変化しない .
     * getNext(1) は、getNext() と同じです。getNext(0) は getCurrent()と同じです。
     * <pre>
     * ---「実行前」------------------------------
     * ([E])⇔[A]⇔[B]⇔[C]!⇔[D]⇔[E]⇔([A])
     *                   0     1    2     3
     *   2     3    4    5
     * -------------------------------------------
     *               ↓ getNext(2) 実行。特に変化せずに、値 E をゲット
     * ---「実行後」------------------------------
     * ([E])⇔[A]⇔[B]⇔[C]!⇔[D]⇔[E]⇔([A])
     * -------------------------------------------
     * </pre>
     * @param n インデックス
     * @return カレント要素からｎ番目の要素の値 (但し n >= 0)
     */
    virtual T* getNext(int n) const;

    /**
     * カレント要素をの１つ前の要素の値を取得する。カレント要素は変化しない .
     * <pre>
     * ---「実行前」------------------------------
     * ([E])⇔[A]⇔[B]⇔[C]!⇔[D]⇔[E]⇔([A])
     * -------------------------------------------
     *               ↓ getPrev() 実行。特に変化せずに、値 B をゲット
     * ---「実行後」------------------------------
     * ([E])⇔[A]⇔[B]⇔[C]!⇔[D]⇔[E]⇔([A])
     * -------------------------------------------
     * </pre>
     * @return 前の要素の値
     */
    virtual T* getPrev() const;

    /**
     * カレント要素のｎ番目前の要素の値を取得する。カレント要素は変化しない .
     * getPrev(1) は、getPrev() と同じです。getPrev(0) は get()と同じです。
     * <pre>
     * ---「実行前」------------------------------
     * ([E])⇔[A]⇔[B]⇔[C]!⇔[D]⇔[E]⇔([A])
     *   3     2    1    0
     *                   5     4    3     2
     * -------------------------------------------
     *               ↓ getPrev(2) 実行。特に変化せずに、値 A をゲット
     * ---「実行後」------------------------------
     * ([E])⇔[A]⇔[B]⇔[C]!⇔[D]⇔[E]⇔([A])
     * -------------------------------------------
     * </pre>
     * @param n インデックス
     * @return カレント要素からｎ番目前の要素の値 (但し n >= 0)
     */
    virtual T* getPrev(int n) const;

    /**
     * 先頭の要素の値を取得する。カレント要素は変化しない .
     * <pre>
     * ---「実行前」------------------------------
     * ([E])⇔[A]⇔[B]⇔[C]!⇔[D]⇔[E]⇔([A])
     * -------------------------------------------
     *               ↓ 変化せずに[A]をゲット
     * ---「実行後」------------------------------
     * ([E])⇔[A]⇔[B]⇔[C]!⇔[D]⇔[E]⇔([A])
     * -------------------------------------------
     * </pre>
     * @return 先頭の要素の値
     */
    virtual T* getFirst() const;

    /**
     * 先頭要素のｎ番目の要素の値を取得する。カレント要素は変化しない .
     * getFromFirst(0) は、getFirst() と同じです。
     * <pre>
     * ---「実行前」------------------------------
     * ([E])⇔[A]⇔[B]⇔[C]!⇔[D]⇔[E]⇔([A])
     *         0    1    2     3    4     5
     *   4     5    6
     * -------------------------------------------
     *               ↓ getFromFirst(3) 実行。特に変化せずに、値 D をゲット
     * ---「実行後」------------------------------
     * ([E])⇔[A]⇔[B]⇔[C]!⇔[D]⇔[E]⇔([A])
     * -------------------------------------------
     * </pre>
     * @param n インデックス
     * @return 先頭要素からｎ番目の要素の値 (但し n >= 0)
     */
    virtual T* getFromFirst(int n) const;

    /**
     * 末尾の要素の値を取得する。カレント要素は変化しない .
     * <pre>
     * ---「実行前」------------------------------
     * ([E])⇔[A]⇔[B]⇔[C]!⇔[D]⇔[E]⇔([A])
     * -------------------------------------------
     *               ↓ getLast() 実行。特に変化せずに、値 E をゲット
     * ---「実行後」------------------------------
     * ([E])⇔[A]⇔[B]⇔[C]!⇔[D]⇔[E]⇔([A])
     * -------------------------------------------
     * </pre>
     * @return 末尾の要素の値
     */
    virtual T* getLast() const;

    /**
     * カレント要素の値（保持している内容）を取得する .
     * <pre>
     * ---「実行前」------------------------------
     * ([E])⇔[A]⇔[B]⇔[C]!⇔[D]⇔[E]⇔([A])
     * -------------------------------------------
     *               ↓ 実行。特に変化せずに、値 C をゲット
     * ---「実行後」------------------------------
     * ([E])⇔[A]⇔[B]⇔[C]!⇔[D]⇔[E]⇔([A])
     * -------------------------------------------
     * </pre>
     * @return  カレント要素の値
     */
    virtual T* getCurrent() const;

    /**
     * 関連要素の値を取得する。カレント要素は変化しない .
     * @param prm_connection_index 関連要素接続番号
     * @return 関連要素の値／引数が範囲外の場合、又は関連未設定の場合 nullptr
     */
    virtual T* getRelation(int prm_connection_index) const;

    /**
     * 現在のカレント要素は、先頭から何番目か(0～)を返す。
     * getCurrent() がnullptr の場合は -1 を返す。
     * @return カレント要素のインデックス
     */
    virtual int getCurrentIndex() const;

    /**
     * カレント要素がリストの末尾であるかどうか判定する .
     * <pre>
     * -------------------------------------------
     * ([E]!)⇔[A]⇔[B]⇔[C]⇔[D]⇔[E]!⇔([A])
     * -------------------------------------------
     * 上図の場合 true
     * </pre>
     * @return true:末尾である／false:そうでは無い
     */
    virtual bool isLast() const;

    /**
     * カレント要素がリストの先頭であるかどうか判定する .
     * <pre>
     * -------------------------------------------
     * ([E])⇔[A]!⇔[B]⇔[C]⇔[D]⇔[E]⇔([A]!)
     * -------------------------------------------
     * 上図の場合 true
     * </pre>
     * @return true:末尾である／false:そうでは無い
     */
    virtual bool isFirst() const;

    /**
     * カレント要素に値を上書き設定する。 .
     * <pre>
     * ---「実行前」------------------------------
     * ([E])⇔[A]⇔[B]⇔[C]!⇔[D]⇔[E]⇔([A])
     * -------------------------------------------
     *               ↓ replace(X) … 値 X を上書きして、元々の値 C をゲット
     * ---「実行後」------------------------------
     * ([E])⇔[A]⇔[B]⇔[X]!⇔[D]⇔[E]⇔([A])
     * -------------------------------------------
     *
     * ※但し、上書き前の元の要素設定時に、自動 delete フラグはそのままとなります。
     * </pre>
     * @param prm_pVal 新しい要素の値
     * @return 元の設定要素が自動 delete の場合 nullptr ／ 元の設定要素が自動 delete ではない場合、上書きされる前の要素(解放に利用される事を想定。)
     */
    virtual T* replace(const T* prm_pVal);

    /**
     * カレント要素を抜き取る .
     * 新たなカレント要素は next の要素に変わる。
     * <pre>
     * ---「実行前」------------------------------
     * ([E])⇔[A]⇔[B]⇔[C]!⇔[D]⇔[E]⇔([A])
     * -------------------------------------------
     *               ↓ remove() … 要素 [C] を抜き取る。そして値 C をゲット
     * ---「実行後」------------------------------
     * ([E])⇔[A]⇔[B]⇔[D]!⇔[E]⇔([A])
     * -------------------------------------------
     * </pre>
     *
     * <BR>
     * カレント要素が末尾だった場合<BR>
     * 新たなカレント要素は先頭要素に変わる。
     * <pre>
     * ---「実行前」------------------------------
     * ([E]!)⇔[A]⇔[B]⇔[C]⇔[D]⇔[E]!⇔([A])
     * -------------------------------------------
     *               ↓ remove() … 要素 [E] を抜き取る。そして値 E をゲット
     * ---「実行後」------------------------------
     * ([D])⇔[A]!⇔[B]⇔[C]⇔[D]⇔([A]!)
     * -------------------------------------------
     * </pre>
     * createIndex() によって作成された内部インデックスは破棄されます。（必要であれば再作成してください）
     * 抜き取った値の解放等が必要な場合は、戻り値を使用して呼び元で行って下さい。
     * @return 抜き取る前にカレント要素だった要素の値
     */
    virtual T* remove();

    /**
     * 全ての要素を抜き取る .
     */
    virtual void removeAll();

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
     * LinkedListRing<Object> ring_list = LinkedListRing<Object>();
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
    virtual int indexOf(const T* prm_pVal) const;

    /**
     * 要素数を返す .
     * <pre>
     * -------------------------------------------
     * ([E])⇔[A]⇔[B]⇔[C]!⇔[D]⇔[E]⇔([A])
     * -------------------------------------------
     * </pre>
     * 上図の場合、length() は 5 を返す
     * また、要素が無い場合は 0 を返します。
     * @return 要素数
     */
    virtual int length() const;

    /**
     * 先頭要素を返す .
     * <pre>
     * -------------------------------------------
     * ([E])⇔[A]⇔[B]⇔[C]!⇔[D]⇔[E]⇔([A])
     * -------------------------------------------
     * </pre>
     * 上図の場合、getElemFirst() は要素 [A] を返す（値 A では無い）。
     * @return
     */
    Elem* getElemFirst() const {
        return _pElem_first;
    }

    /**
     * カレント要素を返す .
     * <pre>
     * -------------------------------------------
     * ([E])⇔[A]⇔[B]⇔[C]!⇔[D]⇔[E]⇔([A])
     * -------------------------------------------
     * </pre>
     * 上図の場合、getElemActive() は要素 [C] を返す（値 C では無い）。
     * @return
     */
    Elem* getElemActive() const {
        return _pElemActive;
    }

    /**
     * 先頭からｎ番目の要素を返す .
     * <pre>
     * -------------------------------------------
     * ([E])⇔[A]⇔[B]⇔[C]!⇔[D]⇔[E]⇔([A])
     *         0    1    2     3    4     5
     *   4     5
     * -------------------------------------------
     * </pre>
     * 上図の場合、getElemFromFirst(3) は要素 [D] を返す（値 D では無い）。
     * @param n 先頭からのインデックス(但し n >= 0)
     * @return 先頭からｎ番目の要素
     */
    Elem* getElemFromFirst(int n) const {
        if (_pElem_first == nullptr) {
            return nullptr;
        }
        Elem* pElem = _pElem_first;
        int x = n % _num_elem;
        for (int i = 0; i < x; i++) {
            pElem = pElem->_pNext;
        }
        return pElem;
    }

    /**
     * インデックスを作成 .
     * 要素値への参照を、配列に別途内部保持し参照時に利用します。
     * インデックスが引数で値を取得するメソッドのパフォーマンスが上がります。
     * 但し要素数を変更すると、再構築の必要があります。
     * 要素値を追加後、要素数が変化しないリストならば、本メソッドを実行しましょう。
     */
    void createIndex();

    /**
     * 全ての要素値に対して指定の関数を実行させる .
     * 要素地のポインタが、引数関数ポインタの pFuncの第１引数 T* に渡ってきます。
     * prm1, prm2, prm3 は、引数関数ポインタの void*, void*, void* に渡ってきます。(キャプチャ的に使って！)<BR>
     * <BR>
     * ＜使用例＞<BR>
     * フォーメーションの編隊メンバーのオブジェクト(Actor*)が、LinkedListRingリスト(listFollowers_)に
     * 管理されているとする。<BR>
     * この編隊メンバー全員に、加速命令(order1)を出す。加速の速度は int velo_mv_ とする。
     * といった場合、以下のような感になる。<BR>
     * <BR>
     * <code><pre>
     *
     * class FormationXXX : public DepositoryFormation {
     * public :
     *     int velo_mv_;
     *     LinkedListRing<Actor> listFollowers_;
     *
     *     static void FormationXXX::order1(Actor* prm_pActor, void* p1, void* p2, void* p3) {
     *         //個々のメンバー加速
     *         EnemyXXX* pEnemyXXX = (EnemyDelheid*)prm_pActor; //実装の型にキャスト
     *         int velo_mv = *((velo*)p1);                       //キャプチャ引数を元の型に戻す
     *         pEnemyXXX->getVecVehicle()->setMvVelo(velo_mv);         //加速設定
     *     }
     *
     *     void processBehavior() {
     *         //全ての編隊メンバーに加速支持を出す。
     *         velo_mv_ = 3000; //速度
     *         listFollowers_.executeFunc(FormationXXX::order1, &velo_mv_, nullptr, nullptr);
     *     }
     * }
     *
     * </pre></code>
     * @param pFunc 要素値に実行させたい関数。パラメータは(T*, void*, void*, void*) 固定。T* 要素の値が渡される。
     * @param prm1 渡したい引数その１
     * @param prm2 渡したい引数その２
     * @param prm3 渡したい引数その３
     */
    void executeFunc(void (*pFunc)(T*, void*, void*, void*), void* prm1, void* prm2, void* prm3) {
        if (_pElemActive == nullptr) {
            return;
        } else {
            Elem* pElem = _pElem_first;
            int n = _num_elem;
            for (int i = 0; i < n; i++) {
                pFunc((T*) pElem->_pValue, prm1, prm2, prm3);
                pElem = pElem->_pNext;
            }
            return;
        }
    }
};

//////////////////////////////////////////////////////////////////

/**
 * ここからは実装部
 */

template<class T>
LinkedListRing<T>::LinkedListRing(int prm_extend_relation_num) :
        Object() {
    _num_elem = 0;
    _pElemActive = nullptr;
    _pElem_first = nullptr;
    _relation_num = prm_extend_relation_num;
    _papLinearVal = nullptr;
}


template<class T>
void LinkedListRing<T>::addNext(const T* prm_pNew,
        bool prm_is_delete_value) {
//#ifdef MY_DEBUG
//    if (prm_pNew == nullptr) {
//        throwCriticalException("[LinkedListRing::addNext()] Error! 引数がnullptrです");
//    }
//#endif
    Elem* pElem = NEW Elem(prm_pNew, _relation_num, prm_is_delete_value);
    if (_pElem_first == nullptr) {
        //最初の１つ
        pElem->_is_last_flg = true;
        pElem->_is_first_flg = true;
        pElem->_pNext = pElem;
        pElem->_pPrev = pElem;
        _pElemActive = pElem;
        _pElem_first = pElem;
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
    if (_papLinearVal) {
        GGAF_DELETEARR(_papLinearVal);
    }
}

template<class T>
void LinkedListRing<T>::addPrev(const T* prm_pNew,
        bool prm_is_delete_value) {
//#ifdef MY_DEBUG
//    if (prm_pNew == nullptr) {
//        throwCriticalException("[LinkedListRing::addPrev()] Error! 引数がnullptrです");
//    }
//#endif
    Elem* pElem = NEW Elem(prm_pNew, _relation_num, prm_is_delete_value);
    if (_pElem_first == nullptr) {
        //最初の１つ
        pElem->_is_last_flg = true;
        pElem->_is_first_flg = true;
        pElem->_pNext = pElem;
        pElem->_pPrev = pElem;
        _pElemActive = pElem;
        _pElem_first = pElem;
    } else {
        Elem* pMy = _pElemActive;
        if (pMy->_is_first_flg) {
            pMy->_is_first_flg = false;
            pElem->_is_first_flg = true;
            pElem->_is_last_flg = false;
            _pElem_first = pElem;
        }
        Elem* pMyPrev = _pElemActive->_pPrev;
        pMyPrev->_pNext = pElem;
        pElem->_pPrev = pMyPrev;
        pElem->_pNext = pMy;
        pMy->_pPrev = pElem;
    }
    _num_elem++;
    if (_papLinearVal) {
        GGAF_DELETEARR(_papLinearVal);
    }
}

template<class T>
void LinkedListRing<T>::addLast(const T* prm_pNew,
        bool prm_is_delete_value) {
//#ifdef MY_DEBUG
//    if (prm_pNew == nullptr) {
//        throwCriticalException("[LinkedListRing::addLast()] Error! 引数がnullptrです");
//    }
//#endif
    Elem* pElem = NEW Elem(prm_pNew, _relation_num, prm_is_delete_value);

    if (_pElem_first == nullptr) {
        //最初の１つ
        pElem->_is_first_flg = true;
        pElem->_is_last_flg = true;
        pElem->_pNext = pElem;
        pElem->_pPrev = pElem;
        _pElemActive = pElem;
        _pElem_first = pElem;
    } else {
        //２つ目以降
        pElem->_is_first_flg = false;
        pElem->_is_last_flg = true;
        Elem* pLastElem = _pElem_first->_pPrev;
        pLastElem->_is_last_flg = false;
        pLastElem->_pNext = pElem;
        pElem->_pPrev = pLastElem;
        pElem->_pNext = _pElem_first;
        _pElem_first->_pPrev = pElem;
    }
    _num_elem++;
    if (_papLinearVal) {
        GGAF_DELETEARR(_papLinearVal);
    }
}

template<class T>
void LinkedListRing<T>::addFirst(const T* prm_pNew,
        bool prm_is_delete_value) {
//#ifdef MY_DEBUG
//    if (prm_pNew == nullptr) {
//        throwCriticalException("[LinkedListRing::addFirst()] Error! 引数がnullptrです");
//    }
//#endif
    Elem* pElem = NEW Elem(prm_pNew, _relation_num, prm_is_delete_value);
    if (_pElem_first == nullptr) {
        //最初の１つ
        pElem->_is_first_flg = true;
        pElem->_is_last_flg = true;
        pElem->_pNext = pElem;
        pElem->_pPrev = pElem;
        _pElemActive = pElem;
        _pElem_first = pElem;
    } else {
        Elem* pFirstElem = _pElem_first;
        Elem* pLastElem = _pElem_first->_pPrev;
        pLastElem->_pNext = pElem;
        pElem->_pPrev = pLastElem;
        pElem->_pNext = pFirstElem;
        pFirstElem->_pPrev = pElem;
        pFirstElem->_is_first_flg = false;

        pElem->_is_first_flg = true;
        pElem->_is_last_flg = false;
        _pElem_first = pElem;
    }
    _num_elem++;
    if (_papLinearVal) {
        GGAF_DELETEARR(_papLinearVal);
    }
}

template<class T>
T* LinkedListRing<T>::next() {
    _pElemActive = _pElemActive->_pNext;
    return (T*) _pElemActive->_pValue;
}

template<class T>
T* LinkedListRing<T>::prev() {
    _pElemActive = _pElemActive->_pPrev;
    return (T*) _pElemActive->_pValue;
}

template<class T>
T* LinkedListRing<T>::first() {
    _pElemActive = _pElem_first;
    return (T*) _pElemActive->_pValue;
}

template<class T>
T* LinkedListRing<T>::last() {
    _pElemActive = _pElem_first->_pPrev; //環状なので、先頭の一つ前は末尾
    return (T*) _pElemActive->_pValue;
}

template<class T>
T* LinkedListRing<T>::current(int n) {
    Elem* pElem = _pElem_first;
    for (int i = 0; i < n; i++) {
        pElem = pElem->_pNext;
    }
    _pElemActive = pElem;
    return (T*) _pElemActive->_pValue;
}

template<class T>
T* LinkedListRing<T>::gotoRelation(int prm_connection_index) {
#ifdef MY_DEBUG
    if (_relation_num-1 < prm_connection_index) {
        throwCriticalException("LinkedListRing<T>::gotoRelation 接続要素番号の範囲外です。prm_connection_index="<<prm_connection_index);
    }
#endif
    _pElemActive = _pElemActive->_papRelation[prm_connection_index];
#ifdef MY_DEBUG
    if (_pElemActive == nullptr) {
        throwCriticalException("LinkedListRing<T>::gotoRelation 接続要素番号の要素が未設定です。prm_connection_index="<<prm_connection_index);
    }
#endif
    return (T*) _pElemActive->_pValue;
}

template<class T>
T* LinkedListRing<T>::getNext() const {
    return (T*) _pElemActive->_pNext->_pValue;
}

template<class T>
T* LinkedListRing<T>::getNext(int n) const {
#ifdef MY_DEBUG
    if (n < 0) {
        throwCriticalException("LinkedListRing<T>::getNext 引数には正の整数を設定する必要があります n="<<n);
    }
#endif
    if (_papLinearVal) { //インデックスあり
        int i = _pElemActive->_idx + n;
        return (T*) _papLinearVal[(i >= _num_elem ? (i % _num_elem) : i)];
    } else { //インデックスなし
        Elem* pElem = _pElemActive;
        int x = n % _num_elem;
        for (int i = 0; i < x; i++) {
            pElem = pElem->_pNext;
        }
        return (T*) pElem->_pValue;
    }
}

//template<class T>
//T* LinkedListRing<T>::getFromCurrent(int n) const {
//    if (_papLinearVal) { //インデックスあり
//      int i = _pElemActive->_idx + n;
//      if (i >= _num_elem) {
//          return (T*)_papLinearVal[(i % _num_elem)];
//      } else if (i < 0) {
//          int x = (-i) % _num_elem;
//          if (x == 0) {
//              return (T*)_papLinearVal[0];
//          } else {
//              return (T*)_papLinearVal[_num_elem - x];
//          }
//
//      } else {
//          return (T*)_papLinearVal[i];
//      }
//    } else { //インデックスなし
//      Elem* pElem = _pElemActive;
//      if (n > 0) {
//          for (int i = 0; i < n; i++) {
//              pElem = pElem->_pNext;
//          }
//      } else if (n < 0) {
//          for (int i = 0; i > n; i--) {
//              pElem = pElem->_pPrev;
//          }
//      }
//        return (T*)pElem->_pValue;
//    }
//}

template<class T>
T* LinkedListRing<T>::getFromFirst(int n) const {
#ifdef MY_DEBUG
    if (n < 0) {
        throwCriticalException("LinkedListRing<T>::getFromFirst 引数には正の整数を設定する必要があります n="<<n);
    }
#endif
    Elem* pElem = _pElem_first;
    if (pElem == nullptr) {
        return nullptr;
    }
    if (_papLinearVal) { //インデックスあり
        return (T*) _papLinearVal[(n >= _num_elem ? (n % _num_elem) : n)];
    } else { //インデックスなし
        int x = n % _num_elem;
        for (int i = 0; i < x; i++) {
            pElem = pElem->_pNext;
        }
        return (T*) pElem->_pValue;
    }
}

template<class T>
T* LinkedListRing<T>::getPrev() const {
    return (T*) _pElemActive->_pPrev->_pValue;
}

template<class T>
T* LinkedListRing<T>::getPrev(int n) const {
#ifdef MY_DEBUG
    if (n < 0) {
        throwCriticalException("LinkedListRing<T>::getPrev 引数には正の整数を設定する必要があります n="<<n);
    }
#endif
    if (_papLinearVal) { //インデックスあり
        int i = _pElemActive->_idx - (n % _num_elem);
        return (T*) _papLinearVal[(i >= 0 ? i : _num_elem + i)];
    } else { //インデックスなし
        Elem* pElem = _pElemActive;
        int x = n % _num_elem;
        for (int i = 0; i < x; i++) {
            pElem = pElem->_pPrev;
        }
        return (T*) pElem->_pValue;
    }
}

template<class T>
T* LinkedListRing<T>::getFirst() const {
    return (T*) _pElem_first->_pValue;
}

template<class T>
T* LinkedListRing<T>::getLast() const {
    return (T*) _pElem_first->_pPrev->_pValue; //環状なので、先頭の一つ前は末尾
}

template<class T>
T* LinkedListRing<T>::getCurrent() const {
    if (_pElemActive == nullptr) {
        return nullptr;
    } else {
        return (T*) _pElemActive->_pValue;
    }
}

template<class T>
T* LinkedListRing<T>::getRelation(int prm_connection_index) const {
#ifdef MY_DEBUG
    if (_relation_num-1 < prm_connection_index) {
        throwCriticalException("LinkedListRing<T>::getRelation 接続要素番号の範囲外です。prm_connection_index="<<prm_connection_index);
    }
#endif
    Elem* pE = _pElemActive->_papRelation[prm_connection_index];
    if (pE) {
        return (T*) pE->_pValue;
    } else {
        return nullptr;
    }
}

template<class T>
int LinkedListRing<T>::getCurrentIndex() const {
    if (_pElemActive == nullptr) {
        return -1;
    } else {
        if (_papLinearVal) {
            return _pElemActive->_idx;
        } else {
            //従来の方法
            Elem* pElem = _pElem_first;
            int n = _num_elem;
            for (int i = 0; i < n; i++) {
                if (pElem == _pElemActive) {
                    return i;
                } else {
                    pElem = pElem->_pNext;
                }
            }
            return -1;
        }
    }
}

template<class T>
bool LinkedListRing<T>::isLast() const {
    return _pElemActive->_is_last_flg;
}

template<class T>
bool LinkedListRing<T>::isFirst() const {
    return _pElemActive->_is_first_flg;
}

template<class T>
T* LinkedListRing<T>::replace(const T* prm_pVal) {
#ifdef MY_DEBUG
    if (_pElemActive == nullptr) {
        throwCriticalException("LinkedListRing<T>::replace カレント要素が存在しません");
    }
#endif
    const T* pValue = _pElemActive->_pValue;
    bool is_delete_value = _pElemActive->_is_delete_value;
    _pElemActive->_pValue = prm_pVal;

    if (_papLinearVal) {
        _papLinearVal[_pElemActive->_idx] = prm_pVal;
    }

    if (is_delete_value) {
        GGAF_DELETE(pValue);
        return nullptr;
    } else {
        return (T*) pValue;
    }

}

template<class T>
T* LinkedListRing<T>::remove() {
    Elem* pMy = _pElemActive;
    if (pMy) {
        if (_papLinearVal) {
            //要素数が変更されるのでインデックスは無効化にする
            GGAF_DELETEARR(_papLinearVal);
        }
        const T* pRetValue =  nullptr;
        _num_elem--;
        if (pMy->_is_first_flg && pMy->_is_last_flg) {
            //要素が１つの場合
            _pElemActive = nullptr;
            _pElem_first = nullptr;
            pRetValue = pMy->_pValue;
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
                _pElem_first = pMyNext;
                pMyNext->_is_first_flg = true; //次の要素が新しい先頭になる
            }
            _pElemActive = pMyNext; //カレント要素は next に更新。
            pRetValue = pMy->_pValue;
        }
        if (pMy->_is_delete_value) {
            GGAF_DELETE(pMy); //~Elem() pRetValue は deleteされる
            return nullptr;
        } else {
            GGAF_DELETE(pMy); //~Elem() pRetValue は deleteされない
            return (T*) pRetValue;
        }
    } else {
        return nullptr;
    }
}

template<class T>
void LinkedListRing<T>::removeAll() {
    if (_papLinearVal) {
        //要素数が変更されるのでインデックスは無効にする
        GGAF_DELETEARR(_papLinearVal);
    }

    Elem* pElem = _pElem_first;
    while (pElem) {
        if (pElem->_is_last_flg) {
            GGAF_DELETE(pElem);
            break;
        } else {
            Elem* pTmp = pElem->_pNext;
            GGAF_DELETE(pElem);
            pElem = pTmp;
        }
    }
    _num_elem = 0;
    _pElemActive = nullptr;
    _pElem_first = nullptr;
}

template<class T>
int LinkedListRing<T>::indexOf(const T* prm_pVal) const {
    if (_pElem_first == nullptr) {
        return -1;
    }
    int r = 0;
    Elem* pElem = _pElem_first;
    while (true) {
        if (pElem->_pValue == prm_pVal) {
            return r;
        } else {
            if (pElem->_is_last_flg) {
                break;
            } else {
                pElem = pElem->_pNext;
                r++;
            }
        }
    }
    return -1;
}

template<class T>
int LinkedListRing<T>::length() const {
    return _num_elem;
}

template<class T>
void LinkedListRing<T>::createIndex() {
    if (_papLinearVal) {
        GGAF_DELETEARR(_papLinearVal);
    }
    Elem* p = _pElem_first;
    int len = length();
    _papLinearVal = NEW const T*[len];
    for (int i = 0; i < len; i++) {
        p->_idx = i;
        _papLinearVal[i] = p->_pValue;
        p = p->_pNext;
    }
}

template<class T>
LinkedListRing<T>::~LinkedListRing() {
    _TRACE_("LinkedListRing<T>::~LinkedListRing() _num_elem="<<_num_elem);
    //自分に子がある場合
    if (_pElem_first) {
        //まず子をdelete
        if (_num_elem == 1) {
            //子要素は１つの場合
            GGAF_DELETE(_pElem_first);
            _pElem_first = nullptr;
            _pElemActive = nullptr;
            _num_elem = 0;

        } else {
            //子要素は２つ以上の場合
            Elem* pLast = _pElem_first->_pPrev;
            Elem* pLastPrev = pLast->_pPrev;
            while (true) {
                GGAF_DELETE(pLast); //末尾からdelete
                if (pLastPrev->_is_first_flg) {
                    GGAF_DELETE(_pElem_first); //pChildLastPrev == _pChildFirst である
                    _pElem_first = nullptr;
                    _pElemActive = nullptr;
                    _num_elem = 0;
                    break;
                }
                pLast = pLastPrev;
                pLastPrev = pLastPrev->_pPrev;
            }
        }
    }

    if (_papLinearVal) {
        GGAF_DELETEARR(_papLinearVal);
    }
}

}
#endif /*GGAF_CORE_LINKEDLISTRING_H_*/
