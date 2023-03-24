#ifndef GGAF_CORE_NODE_H_
#define GGAF_CORE_NODE_H_
#include "jp/ggaf/GgafCommonHeader.h"
#include "jp/ggaf/core/Object.h"

#include <cstring>
#include "jp/ggaf/core/util/Util.h"
#include "jp/ggaf/core/exception/CriticalException.h"

namespace GgafCore {

/**
 * 要素同士を環状双方向連結リスト(内部収納)で、ツリー構造を作ることができるテンプレートです。.
 * 所謂ツリーノードだが、兄弟ノードが環状双方向連結リストで結合し前後位置関係の概念がある。
 * また、兄弟ノードに先頭ノード、末尾ノードの概念もある。先頭ノードと末尾ノードはフラグで管理。
 * 環状なので先頭ノード、末尾ノードは互いに連結している。
 * ノードは実値（要素インスタンス）を指すわけではなく、ノードのオブジェクト自身を実値としている。
 * つまり、コンテナに非ず。<BR>
 * 少しでも参照回数を減らし、パフォーマンスを上げようとた為・・・。<BR>
 *
 * <B>【解説】</B><BR>
 * <PRE STYLE="font-size:12px">
 * ・・⇔Ｐ⇔・・・
 *       ↓
 * (Ｅ)⇔Ａ⇔Ｂ⇔Ｃ⇔Ｄ⇔Ｅ⇔(Ａ)
 *           │  └────────────┐
 *           ↓                            ↓
 *     (Ｈ)⇔Ｆ⇔Ｇ⇔Ｈ⇔(Ｆ)        (Ｌ)⇔Ｉ⇔Ｊ⇔Ｋ⇔Ｌ⇔(Ｉ)
 *               ↓  ↓                        ↓      ↓
 *                 ・・・                              ・・・
 * </PRE>
 * 上図のような構造を採る事が出来ます。<BR>
 * 中段の「(Ｅ)⇔Ａ⇔Ｂ⇔Ｃ⇔Ｄ⇔Ｅ⇔(Ａ)」は要素（インスタンス）が環状の双方向でポインタを指しあっている事を示しています。<BR>
 * 両端の「(Ｅ)」と「(Ａ)」は、連結リストの先頭と末尾も、お互い連結している事を明示しています。(環状になっている)<BR>
 * 上図で自身のインスタンスを「Ｃ」とした場合、「Ｃ」の視点から各要素を次のように呼称、及び定義することとします。<BR>
 * <TABLE BORDER="1">
 * <TR><TD>「Ｃ」</TD><TD>自ノード</TD></TR>
 * <TR><TD>「Ａ」</TD><TD>先頭(First)ノード。 自ノードが所属する連結リスト（兄弟ノード）の先頭という意味です。「Ａ」 は _is_first_flg が true になっています。(他ノードは false)</TD></TR>
 * <TR><TD>「Ｅ」</TD><TD>末尾(Last)ノード。 自ノードが所属する連結リスト（兄弟ノード）の最後という意味です。「Ｅ」 は _is_last_flg が true になっています。(他のノードは false)</TD></TR>
 * <TR><TD>「Ｄ」</TD><TD>次(Next)ノード。上図では左から右が正順序としています。_pNextポインタが指している要素になります。</TD></TR>
 * <TR><TD>「Ｂ」</TD><TD>前(Prev)ノード。_pPrev が指しているポインタです。</TD></TR>
 * <TR><TD>「Ｐ」</TD><TD>親(Parent)ノード。自ノードが所属する連結リストの１つ上の階層のノードです。_pParent ポインタが指している要素です。全てのノードは直近の親ノードのポインタを持っています。</TD></TR>
 * <TR><TD>「Ｉ，Ｊ，Ｋ，Ｌ」</TD><TD>「Ｃ」子(Child)ノードと呼びます。</TD></TR>
 * <TR><TD>「Ｉ」</TD><TD> 子ノードの中で特に「Ｉ」は子ノードの先頭ノードと呼び、自ノードの _pChildFirst ポインタが指している要素となっています。</TD></TR>
 * </TABLE>
 * <BR>
 *
 * <B>【その他用語補足】</B>
 * <TABLE BORDER="1">
 * <TR>
 * <TD>「他ノード」「他」</TD>
 * <TD>自ノード以外のノード全てを指しています。</TD>
 * </TR><TR>
 * <TD>「配下ノード」「配下」</TD>
 * <TD>ノード同士のツリー階層構造上において、自ノード<B>に</B>ぶら下がる全てのノードを指しています。自ノードは含まれません。</TD>
 * </TR><TR>
 * <TD>「自ツリー」</TD>
 * <TD>自ノードを頂点とする、自ノード＋配下ノードで構成されるツリー構造自体を指します。</TD>
 * </TR><TR>
 * <TD>「自ツリーノード」</TD>
 * <TD>自ノードを頂点とする、自ノード＋配下ノードで構成されるツリー構造のノード全てを指します。</TD>
 * </TR><TR>
 * <TD>「自所属ツリー」</TD>
 * <TD>自ノードが含まれているツリー構造の全てを指します。</TD>
 * </TR><TR>
 * <TD>「ノードクラス」</TD>
 * <TD>Node実装クラス、或いはNode実装クラスを直接・間接継承しているクラスを指します。</TD>
 * </TR><TR>
 * <TD>「上位」「下位」</TD>
 * <TD>ノードクラスのクラス継承関係を表しています。
 * 本ドキュメントでは、クラス継承関係の表現は「スーパー」「子」又は「親」「子」と言わずに<B>「上位」「下位」</B>で統一することにします。<BR>
 * 「親」「子」と表現した場合はそれぞれ親ノード、子ノードのツリー構造の事を表現するものとします。（ややこしいですね）<BR>
 * ＜例＞<BR>
 * ・下位のHogehogeで実装されたコレコレ。<BR>
 *     → 意味：Hogehogeクラスが継承し、そこで実装されているコレコレ<BR>
 * ・子のHogehogeで実装されたコレコレ。<BR>
 *     → 意味：ツリー構造の子ノードにあたるHogehogeクラスオブジェクトがで実装されているコレコレ<BR>
 * </TD>
 * </TR>
 * </TABLE>
 * @tparam T 管理する要素の型（この型のポインタ型が内部で管理される。）
 * @version 1.00
 * @since 2008/09/08
 * @author Masatoshi Tsuge
 */

template<class T>
class Node : public Object {

public:
    /** [r]ノード識別名(50文字まで) */
    char* _name;
    /** [r]ノード識別名のハッシュ値 */
    hashval _name_hash;
    /** [r]クラス名（デバッグで使用します） */
    const char* _class_name;
    /** [r]親ノード */
    T* _pParent;
    /** [r]次ノード */
    T* _pNext;
    /** [r]前ノード */
    T* _pPrev;
    /** [r]子ノードの先頭ノード */
    T* _pChildFirst;
    /** [r]先頭ノードフラグ (自ノードが先頭ノードの場合 true)*/
    bool _is_first_flg;
    /** [r]末尾ノードフラグ (自ノードが末尾ノードの場合 true)*/
    bool _is_last_flg;
    /** [r]子ノードの数 */
    int _child_num;

public:
    /**
     * コンストラクタ
     * @param prm_name ノード名称（ユニークにして下さい）
     */
    explicit Node(const char* prm_name);

    /**
     * デストラクタ。自ツリーノードを解放します。 .
     * 自ノードが子ノードを持つ場合、子ノードを解放してから自身を解放する。<BR>
     * 自ノードが最終ノードだった場合、自ノードを連結から離脱し、前ノードを最終ノードフラグをセットして、自身を解放する。<BR>
     * 自ノードが先頭ノードだった場合、自ノードを連結から離脱し、次ノードを親ノード の 子ノードの先頭ノード、さらに 先頭ノードフラグをセットし、自身を解放する。<BR>
     * 自ノードが中間ノードだった場合、両隣のノードの連結を再構築した後解放する。<BR>
     * 自ノードの連結が自身を指す（１人ぼっちだった）場合、親ノード の 子ノードの先頭ノード（自分を指していた）をnullptrに変更してから解放する。<BR>
     * 次のような構造の場合、ノード P をdeleteすると、解放順は①～⑬の順序となる。<BR>
     * ノード間で参照関係がある場合は、注意が必要。<BR>
     * <pre>
     * (Ｐ)⇔⑬Ｐ⇔(Ｐ)
     *         ↓
     * (Ｅ)⇔⑫Ａ⇔⑧Ｂ⇔③Ｃ⇔②Ｄ⇔①Ｅ⇔(Ａ)
     *         │    └────────────┐
     *         ↓                              ↓
     * (Ｈ)⇔⑪Ｆ⇔⑩Ｇ⇔⑨Ｈ⇔(Ｆ)    (Ｌ)⇔⑦Ｉ⇔⑥Ｊ⇔⑤Ｋ⇔④Ｌ⇔(Ｉ)
     *
     * ※子が存在すればそちらを優先で末尾ノードから解放していく。
     * </pre>
     */
    virtual ~Node();

    /**
     * ノード名取得 .
     * @return ノード名称
     */
    inline virtual char* getName() const {
        return _name;
    }

    /**
     * クラス名取得 .
     * @return クラス名称
     */
    inline virtual const char* getClassName() const {
        return _class_name;
    }

    /**
     * １つ上の親ノードを設定する。
     * @param    prm_pParent    親ノード
     */
    inline virtual void setParent(T* prm_pParent) {
        _pParent = prm_pParent;
    }

    /**
     * 自ツリーノードを連結リストから切り離し、独立する。 .
     * 切り離され穴が開いた部分は、周りのノードが穴を埋めます（再連結します）<BR>
     * 自ノードに子がぶら下がっていた場合、それらも切り離されたことになります。<BR>
     * @return    T* 自ノードのポインタ
     */
    virtual T* extract();

    /**
     * 自ノードを、最終ノードへ移動する .
     * 子ノードも道連れにして移動します。自ノードと子ノードの関係は崩れません。<BR>
     *<PRE>
     * ----------------「実行前」
     *         親
     *         ↓
     * （Ｅ）⇔Ａ⇔Ｂ⇔Ｃ⇔Ｄ⇔Ｅ⇔（Ａ）
     * -----------------------
     *        ↓ 上図で自分が「Ｃ」とした場合、次のような状態になる
     * ----------------「実行後」
     *         親
     *         ↓
     * （Ｅ）⇔Ａ⇔Ｂ⇔Ｄ⇔Ｅ⇔Ｃ⇔（Ａ）
     * -----------------------
     * </PRE>
     */
    virtual void moveLast();

    /**
     * 自ノードを、先頭ノードへ移動する .
     * 子ノードも道連れにして移動します。自ノードと子ノードの関係は崩れません。<BR>
     *<PRE>
     * ----------------「実行前」
     *       親
     *       ↓
     * (Ｅ)⇔Ａ⇔Ｂ⇔Ｃ⇔Ｄ⇔Ｅ⇔(Ａ)
     * -----------------------
     *        ↓ 上図で自分が「Ｃ」とした場合、次のような状態になる
     * ----------------「実行後」
     *       親
     *       ↓
     * (Ｅ)⇔Ｃ⇔Ａ⇔Ｂ⇔Ｄ⇔Ｅ⇔(Ｃ)
     * -----------------------
     * </PRE>
     */
    virtual void moveFirst();

    /**
     * 次のノード取得する。
     * @return    T*    次ノード
     */
    inline virtual T* getNext() const {
        return _pNext;
    }

    /**
     * 前のノード取得する。
     * @return    T*    前ノード
     */
    inline virtual T* getPrev() const {
        return _pPrev;
    }

    /**
     * １つ上の親ノード取得する。
     * @return    T*    親ノード
     */
    inline virtual T* getParent() const {
        return _pParent;
    }

    /**
     * 引数ノードを子ノードの最後に追加する .
     * 追加される場所は以下の図のようになります。<BR>
     *<PRE>
     * ----------------「実行前」
     *       Ｃ
     *       ↓
     * (Ｋ)⇔Ｉ⇔Ｊ⇔Ｋ⇔(Ｉ)
     * -----------------------
     *         ↓ 上図で自分が「Ｃ」とした場合、ここにノード「Ｘ」appendChild すると
     *         ↓ 次のような状態になる
     * ----------------「実行後」
     *       Ｃ
     *       ↓
     * (Ｘ)⇔Ｉ⇔Ｊ⇔Ｋ⇔Ｘ⇔(Ｉ)
     * -----------------------
     * </PRE>
     *
     * @param   prm_pChild    インスタンス生成済みノードのポインタ
     */
    virtual void appendChild(T* prm_pChild);

    /**
     * 引数ノードを子ノードの先頭に追加する .
     * 追加される場所は以下の図のようになります。<BR>
     *<PRE>
     * ----------------「実行前」
     *       Ｃ
     *       ↓
     * (Ｋ)⇔Ｉ⇔Ｊ⇔Ｋ⇔(Ｉ)
     * -----------------------
     *         ↓ 上図で自分が「Ｃ」とした場合、ここにノード「Ｘ」prependChild すると
     *         ↓ 次のような状態になる
     * ----------------「実行後」
     *       Ｃ
     *       ↓
     * (Ｋ)⇔Ｘ⇔Ｉ⇔Ｊ⇔Ｋ⇔(Ｘ)
     * -----------------------
     * </PRE>
     *
     * @param   prm_pChild    インスタンス生成済みノードのポインタ
     */
    virtual void prependChild(T* prm_pChild);

    /**
     * 子ノードをノード名称を指定して取得する .
     * 存在しない場合はエラー<BR>
     * 内部で char* の比較を見つかるまで行うため、やや重いです。<BR>
     * 毎フレーム実行されるような使用は避けるべきです。<BR>
     * @param    prm_child_name    子ノード名
     * @return    T*    最初にヒットした子ノード名に対応する子ノードのポインタ
     */
    virtual T* getChildByName(const char* prm_child_name);

    /**
     * 引数のノードが子ノードに存在する場合取得する .
     * @param prm_pChild 子ノード
     * @return 存在する場合子ノードが返る、存在しない場合 nullptr が返る
     */
    virtual T* getChild(T* prm_pChild) const;

    /**
     * 子ノードを先頭からのインデックス指定で取得する .
     * 0 は _pChildFirst と同じ。
     * @param prm_index インデックス(0～)
     * @return
     */
    virtual T* getChild(int prm_index) const;

    /**
     * 子ノードのグループの先頭ノードを取得する .
     * 子ノードが存在しない場合はnullptr。
     * @return    T*    子ノードの先頭ノード
     */
    inline virtual T* getChildFirst() const {
        return _pChildFirst;
    }

    /**
     * 子ノードのグループの末尾ノードを取得する .
     * 子ノードが存在しない場合はnullptr。
     * @return T*   子ノードの末尾ノード
     */
    inline virtual T* getChildLast() const {
        if (_pChildFirst) {
            return _pChildFirst->_pPrev;
        } else {
            return nullptr;
        }
    }

    /**
     * 子ノード存在チェック .
     * 内部で char* の比較を見つかるまで行うため、重いです。<BR>
     * 毎フレーム実行されるような使用は避けるべきです。<BR>
     * @param    prm_child_actor_name    存在チェックする子ノード名
     * @return    bool true:存在する／false:存在しない
     */
    virtual bool hasChild(char* prm_child_actor_name) const;

    /**
     * 子ノード数を取得する .
     * @return  T*  子ノード数
     */
    inline virtual int getNumChild() const {
        return _child_num;
    }

    /**
     * 自ノードが先頭ノードか調べる .
     * @return    bool true:先頭ノード／false:先頭ノードではない
     */
    inline virtual bool isFirst() const {
        return _is_first_flg;
    }

    /**
     * 自ノードが末尾ノードか調べる .
     * @return    bool true:末尾ノード／false:末尾ノードではない
     */
    inline virtual bool isLast() const {
        return _is_last_flg;
    }

    virtual std::string toString() override {
        return getName();
    }

};

//////////////////////////////////////////////////////////////////

/**
 * ここからは実装部
 */
template<class T>
Node<T>::Node(const char* prm_name) :
    Object(),
    _name(nullptr),
    _class_name("Node<T>"),
    _pParent(nullptr),
    _pNext((T*)this),
    _pPrev((T*)this),
    _pChildFirst(nullptr),
    _is_first_flg(true),
    _is_last_flg(true),
    _child_num(0)
{
    _name_hash = UTIL::easy_hash(prm_name);
    int len = strlen(prm_name);
    _name = NEW char[len+1];
    strcpy(_name, prm_name);
}

template<class T>
T* Node<T>::extract() {
    if (_pParent) {
        //連結から外す
        _pParent->_child_num--;
        T* pMyNext = _pNext;
        T* pMyPrev = _pPrev;
        if (_is_first_flg && _is_last_flg) {
            //連結が自分のみ場合
            _pParent->_pChildFirst = nullptr;
        } else {
            //連結がから抜け出す場合
            //両隣のノード同士を繋ぎ、自分を指さなくする。
            pMyPrev->_pNext = pMyNext;
            pMyNext->_pPrev = pMyPrev;
            if (_is_last_flg) {
                pMyPrev->_is_last_flg = true;
            }
            if (_is_first_flg) {
                pMyNext->_is_first_flg = true;
                _pParent->_pChildFirst = pMyNext;
            }
        }
        _pParent = nullptr;
        _pNext = (T*)this;
        _pPrev = (T*)this;
        _is_first_flg = true;
        _is_last_flg = true;
        //ツリーは維持するので、_pChildFirst そのまま（nullptrにしない）
        return ((T*)this);
    } else {
        //TODO:ココに処理が来る場合は、extract()する必要なし。
        //_pParentが居ない＝何所にも所属してない＝extract()する必要なし。
        //と、解釈されているが、これは、要素を追加するためのメソッドが現在 appendChild() prependChild() のみであることが前提となる。
        //appendChild() prependChild() のみで作られるツリー構造は、親の頂点は常に唯一となるからだ。
        //しかし将来、addNext() のように隣に要素を追加するメソッドを作らなければいけなくなった場合、
        //親の頂点が横並び手をつなぎ、台形のような構造を採れるようにした場合は、
        //ここの場所に横連結からのみ切り離す処理を追加する必要がある事を忘れずに。
        return ((T*)this);
    }
}

template<class T>
void Node<T>::moveLast() {
    if (_is_last_flg) { //既に最終ノードならば何もしない
        return;
    } else if (_is_first_flg) { //先頭ノードならば、親の指している先頭ノードを次へずらす
        _pParent->_pChildFirst = _pNext;
        _pPrev->_is_last_flg = false;
        _is_first_flg = false;
        _is_last_flg = true;
        _pNext->_is_first_flg = true;
    } else { //中間ノード時
        //両隣のノード同士を繋ぐ
        _pPrev->_pNext = _pNext;
        _pNext->_pPrev = _pPrev;
        //末尾ノードと先頭ノードの間にもぐりこませる
        T* pFirst = _pParent->_pChildFirst; //現First
        T* pLast = pFirst->_pPrev;        //現Last
        pLast->_is_last_flg = false;      //現LastのLastだフラグ解除
        _is_last_flg = true;              //俺が新Lastだフラグセット
        _pPrev = pLast;                   //俺の前は現Lastで
        _pNext = pFirst;                  //俺の次は現Firstだ。
        pLast->_pNext = (T*)this;         //現Lastの次は俺で
        pFirst->_pPrev = (T*)this;        //現Firstの前は俺となる。
    }
}

template<class T>
void Node<T>::moveFirst() {
    if (_is_first_flg) { //既に先頭ノードならば何もしない
        return;
    } else if (_is_last_flg) { //末尾ノードならば、親の指している先頭ノードを前にずらす
        _pParent->_pChildFirst = (T*)this;
        _pPrev->_is_last_flg = true;
        _is_first_flg = true;
        _is_last_flg = false;
        _pNext->_is_first_flg = false;
    } else { //中間ノード時
        //両隣のノード同士を繋ぐ
        _pPrev->_pNext = _pNext;
        _pNext->_pPrev = _pPrev;
        //末尾ノードと先頭ノードの間にもぐりこませる
        T* pFirst = _pParent->_pChildFirst; //現First
        T* pLast = pFirst->_pPrev;        //現Last
        pFirst->_is_first_flg = false;    //現FirstのFirstだフラグ解除
        _is_first_flg = true;             //俺が新Firstだフラグセット
        _pPrev = pLast;                   //俺の前は現Lastで、
        _pNext = pFirst;                  //俺の次は現Firstだ。
        pLast->_pNext = (T*)this;         //現Lastの次は俺で、
        pFirst->_pPrev = (T*)this;        //現Firstの前は俺となる。
        _pParent->_pChildFirst = (T*)this;  //さらに、親のChildFirstとなるのだ。
    }
}

template<class T>
T* Node<T>::getChildByName(const char* prm_child_name) {
#ifdef MY_DEBUG
    if (_pChildFirst == nullptr) {
        throwCriticalException("[Node<" << _class_name << ">::getChild()] Error! _pChildFirstがnullptrです。");
    }
#endif
    T* pNodeTemp = _pChildFirst;
    do {
        if (strcmp(pNodeTemp->getName(), prm_child_name) == 0) {
            break;
        }
#ifdef MY_DEBUG
        if (pNodeTemp->_is_last_flg) {
            throwCriticalException("[Node<" << _class_name << ">::getChild()] Error! 子ノードは存在しません。(prm_child_actor_name=" << prm_child_name << ")");
        }
#endif
        pNodeTemp = pNodeTemp->_pNext;
    } while (true);
    return pNodeTemp;
}

template<class T>
T* Node<T>::getChild(T* prm_pChild) const {
    if (_pChildFirst == nullptr) {
        return nullptr;
    }
    T* pNodeTemp = _pChildFirst;
    do {
        if (prm_pChild == pNodeTemp) {
            break;
        }
        if (pNodeTemp->_is_last_flg) {
            return nullptr;
        }
        pNodeTemp = pNodeTemp->_pNext;
    } while (true);
    return pNodeTemp;
}

template<class T>
T* Node<T>::getChild(int prm_index) const {
    T* pNodeTemp = _pChildFirst;
    for (int i = 0; i < prm_index; i++) {
        pNodeTemp = pNodeTemp->_pNext;
    }
    return pNodeTemp;
}

template<class T>
bool Node<T>::hasChild(char* prm_child_actor_name) const {
    if (_pChildFirst == nullptr) {
        return false;
    } else {
        T* pNodeTemp = _pChildFirst;
        do {
            if (strcmp(pNodeTemp->getName(), prm_child_actor_name) == 0) {
                return true;
            }
            if (pNodeTemp->_is_last_flg) {
                return false;
            } else {
                pNodeTemp = pNodeTemp->_pNext;
            }
        } while (true);
    }
}

template<class T>
void Node<T>::appendChild(T* prm_pChild) {
#ifdef MY_DEBUG
    if (prm_pChild->_pParent) {
        throwCriticalException("[Node<" << _class_name << ">::appendChild()] Error! 引数ノードは既に所属("
                << prm_pChild->_pParent->_name << "に所属)しています(this=" << _name << "/prm_pChild=" << prm_pChild->getName() << ")");
    }
#endif
    prm_pChild->_pParent = (T*)this;
    prm_pChild->_is_last_flg = true;
    if (_pChildFirst == nullptr) { //最初の子
        prm_pChild->_is_first_flg = true;
        _pChildFirst = prm_pChild;
        _pChildFirst->_pNext = prm_pChild;
        _pChildFirst->_pPrev = prm_pChild;
    } else {  //２つ目以降の子
        prm_pChild->_is_first_flg = false;
        T* pChildLast = _pChildFirst->_pPrev;
        pChildLast->_is_last_flg = false;
        pChildLast->_pNext = prm_pChild;
        prm_pChild->_pPrev = pChildLast;
        prm_pChild->_pNext = _pChildFirst;
        _pChildFirst->_pPrev = prm_pChild;
    }
    _child_num++;
}

template<class T>
void Node<T>::prependChild(T* prm_pChild) {
#ifdef MY_DEBUG
    if (prm_pChild->_pParent) {
        throwCriticalException("[Node<" << _class_name << ">::prependChild()] Error! 引数ノードは既に所属("
                << prm_pChild->_pParent->_name << "に所属)しています(this=" << _name << "/prm_pChild=" << prm_pChild->getName() << ")");
    }
#endif
    prm_pChild->_pParent = (T*)this;
    prm_pChild->_is_first_flg = true;
    if (_pChildFirst == nullptr) { //最初の子
        prm_pChild->_is_last_flg = true;
        prm_pChild->_pNext = prm_pChild;
        prm_pChild->_pPrev = prm_pChild;
    } else {
        prm_pChild->_is_last_flg = false;
        T* pChildLast = _pChildFirst->_pPrev;
        pChildLast->_pNext = prm_pChild;
        prm_pChild->_pPrev = pChildLast;
        prm_pChild->_pNext = _pChildFirst;
        _pChildFirst->_pPrev = prm_pChild;
        _pChildFirst->_is_first_flg = false;
    }
    _pChildFirst = prm_pChild;

    _child_num++;
}

/*
 template<class T>
 bool Node<T>::isNamed(const char* prm_name) {
 char*::size_type iLen = prm_name.length();
 if (prm_name.rfind('*') == iLen-1) {}
 return _name;
 }
 */


template<class T>
Node<T>::~Node() {
    //自分に子がある場合
    if (_pChildFirst) {
        //まず子をdelete
        if (_pChildFirst->_is_last_flg) {
            //子ノードは１つの場合
            GGAF_DELETE(_pChildFirst);
            _pChildFirst = nullptr;
        } else {
            //子ノードは２つ以上の場合
            T* pChildLast = _pChildFirst->_pPrev;
            T* pChildLastPrev = pChildLast->_pPrev;
            while (true) {
                GGAF_DELETE(pChildLast); //末尾からdelete
                if (pChildLastPrev->_is_first_flg) {
                    GGAF_DELETE(_pChildFirst); //pChildLastPrev == _pChildFirst である
                    _pChildFirst = nullptr;
                    break;
                }
                pChildLast = pChildLastPrev;
                pChildLastPrev = pChildLastPrev->_pPrev;
            }
        }
    }

    //子がない状態の場合
    if (_pParent) {
        _pParent->_child_num--;
        //連結から外す
        T* pMyNext = _pNext;
        T* pMyPrev = _pPrev;
        if (_is_first_flg && _is_last_flg) {
            //連結しているノードが無く、自分のみ場合
            _pParent->_pChildFirst = nullptr;
            _pParent = nullptr;
            _pNext = (T*)this;
            _pPrev = (T*)this;
            _pChildFirst = nullptr;
        } else {
            //連結がから抜け出す場合
            //両隣のノード同士を繋ぎ、自分を指さなくする。
            pMyPrev->_pNext = pMyNext;
            pMyNext->_pPrev = pMyPrev;
            if (_is_last_flg) {
                pMyPrev->_is_last_flg = true;
            }
            if (_is_first_flg) {
                pMyNext->_is_first_flg = true;
                _pParent->_pChildFirst = pMyNext;
            }
            _pParent = nullptr;
            _pNext = (T*)this;
            _pPrev = (T*)this;
            _pChildFirst = nullptr;
            _is_first_flg = true;
            _is_last_flg = true;
        }
    }
    GGAF_DELETEARR(_name);
}

}
#endif /*GGAF_CORE_NODE_H_*/
