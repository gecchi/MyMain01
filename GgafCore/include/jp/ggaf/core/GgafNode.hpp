﻿#ifndef GGAFNODE_H_
#define GGAFNODE_H_
namespace GgafCore {

/**
 * 要素同士を環状双方向連結リストのツリー構造を作ることができるテンプレートです。.
 *
 * <B>【解説】</B><BR>
 * <PRE STYLE="font-size:12px">
 * 　・・⇔Ｐ⇔・・・
 * 　　　↓
 * (Ｅ)⇔Ａ⇔Ｂ⇔Ｃ⇔Ｄ⇔Ｅ⇔(Ａ)
 * 　　　　　│　└────────────┐
 * 　　　　　↓　　　　　　　　　　　　　　↓
 * 　　(Ｈ)⇔Ｆ⇔Ｇ⇔Ｈ⇔(Ｆ)　　　　(Ｌ)⇔Ｉ⇔Ｊ⇔Ｋ⇔Ｌ⇔(Ｉ)
 * 　　　　　　　↓　↓　　　　　　　　　　　　↓　　　↓
 * 　　　　　　　　・・・　　　　　　　　　　　　　　　・・・
 * </PRE>
 * 上図のような構造を採る事が出来ます。<BR>
 * 中段の「(Ｅ)⇔Ａ⇔Ｂ⇔Ｃ⇔Ｄ⇔Ｅ⇔(Ａ)」は要素（インスタンス）が環状の双方向でポインタを指しあっている事を示しています。<BR>
 * 両端の「(Ｅ)」と「(Ａ)」は、連結リストの先頭と末尾も、お互い連結している事を明示しています。(環状になっている)<BR>
 * 上図で自身のインスタンスを「Ｃ」とした場合、「Ｃ」の視点から各要素を次のように呼称、及び定義することとします。<BR>
 * <TABLE BORDER="1">
 * <TR><TD>「Ｃ」</TD><TD>自ノード</TD></TR>
 * <TR><TD>「Ａ」</TD><TD>先頭(First)ノード。 自ノードが所属する連結リストの先頭という意味です。「Ａ」 は _is_first_flg が true になっています。(他ノードは false)</TD></TR>
 * <TR><TD>「Ｅ」</TD><TD>末尾(Last)ノード。 自ノードが所属する連結リストの最後という意味です。「Ｅ」 は _is_last_flg が true になっています。(他のノードは false)</TD></TR>
 * <TR><TD>「Ｄ」</TD><TD>次(Next)ノード。上図では左から右が正順序としています。_pNextポインタが指している要素になります。</TD></TR>
 * <TR><TD>「Ｂ」</TD><TD>前(Prev)ノード。_pPrev が指しているポインタです。</TD></TR>
 * <TR><TD>「Ｐ」</TD><TD>親(Parent)ノード。自ノードが所属する連結リストの１つ上の階層のノードです。_pParent ポインタが指している要素です。全てのノードは直近の親ノードのポインタを持っています。</TD></TR>
 * <TR><TD>「Ｉ，Ｊ，Ｋ，Ｌ」</TD><TD>「Ｃ」子(Sub)ノードと呼びます。</TD></TR>
 * <TR><TD>「Ｉ」</TD><TD> 子ノードの中で特に「Ｉ」は子ノードの先頭ノードと呼び、自ノードの _pSubFirst ポインタが指している要素となっています。</TD></TR>
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
 * <TD>GgafNode実装クラス、或いはGgafNode実装クラスを直接・間接継承しているクラスを指します。</TD>
 * </TR><TR>
 * <TD>「上位」「下位」</TD>
 * <TD>ノードクラスのクラス継承関係を表しています。
 * クラス継承関係の表現は「スーパー」「サブ」又は「親」「子」と言わずに<B>「上位」「下位」</B>で統一することにします。<BR>
 * 「親」「子」と表現した場合はそれぞれ親ノード、子ノードのツリー構造の事を表現するものとします。（ややこしいですね）<BR>
 * ＜例＞<BR>
 * ・下位のHogehogeで実装されたコレコレ。<BR>
 * 　　→ 意味：Hogehogeクラスが継承し、そこで実装されているコレコレ<BR>
 * ・サブのHogehogeで実装されたコレコレ。<BR>
 * 　　→ 意味：ツリー構造の子ノードにあたるHogehogeクラスオブジェクトがで実装されているコレコレ<BR>
 * </TD>
 * </TR>
 * </TABLE>
 * @version 1.00
 * @since 2008/09/08
 * @author Masatoshi Tsuge
 */

template<class T>
class GgafNode : public GgafObject {

private:
    /** ループ用 */
    T* _pNodeTemp;

protected:
    /** [r]ID */
    char* _id;
    /** [r]ノード識別名(50文字まで) */
    char* _name;
    /** [r]クラス名 */
    const char* _class_name;

    /** [r]親ノード */
    T* _pParent;
    /** [r]次ノード */
    T* _pNext;
    /** [r]前ノード */
    T* _pPrev;
    /** [r]子ノードの先頭ノード */
    T* _pSubFirst;
    /** [r]先頭ノードフラグ (自ノードが先頭ノードの場合 true)*/
    bool _is_first_flg;
    /** [r]末尾ノードフラグ (自ノードが末尾ノードの場合 true)*/
    bool _is_last_flg;

public:
    /**
     * コンストラクタ
     * @param prm_name ノード名称（ユニークにして下さい）
     */
    GgafNode(const char* prm_name);

    /**
     * デストラクタ。自ツリーノードを解放します。 .
     * 自ノードが子ノードを持つ場合、子ノードを解放してから自身を解放する。<BR>
     * 自ノードが最終ノードだった場合、自ノードを連結から離脱し、前ノードを最終ノードフラグをセットして、自身を解放する。<BR>
     * 自ノードが先頭ノードだった場合、自ノードを連結から離脱し、次ノードを親ノード の 子ノードの先頭ノード、さらに 先頭ノードフラグをセットし、自身を解放する。<BR>
     * 自ノードが中間ノードだった場合、両隣のノードの連結を再構築した後解放する。<BR>
     * 自ノードの連結が自身を指す（１人ぼっちだった）場合、親ノード の 子ノードの先頭ノード（自分を指していた）をNULLに変更してから解放する。<BR>
     */
    virtual ~GgafNode();

    /**
     * ノード名取得 .
     * @return ノード名称
     */
    virtual char* getName(){
        return _name;
    }

    /**
     * クラス名取得 .
     * @return クラス名称
     */
    virtual const char* getClassName() {
        return _class_name;
    }

    /**
     * ノード名問い合わせ
     */
    //	virtual bool isNamed(const char* prm_name);

    /**
     * １つ上の親ノードを設定する。
     * @param	prm_pParent	親ノード
     */
    virtual void setParent(T* prm_pParent){
        _pParent = prm_pParent;
    }

    /**
     * 自ツリーノードを連結リストから切り離し、独立する。 .
     * 切り離され穴が開いた部分は、周りのノードが穴を埋めます（再連結します）<BR>
     * 自ノードに子がぶら下がっていた場合、それらも切り離されたことになります。<BR>
     * @return	T* 自ノードのポインタ
     */
    virtual T* extract();

    /**
     * 自ノードを、最終ノードへ移動する .
     * 子ノードも道連れにして移動します。自ノードと子ノードの関係は崩れません。<BR>
     *<PRE STYLE="font-size:18px">
     * ----------------「実行前」
     *       親
     *       ↓
     * （Ｅ）⇔Ａ⇔Ｂ⇔Ｃ⇔Ｄ⇔Ｅ⇔（Ａ）
     * -----------------------
     *        ↓ 上図で自分が「Ｃ」とした場合、次のような状態になる
     * ----------------「実行後」
     *       親
     *       ↓
     * （Ｅ）⇔Ａ⇔Ｂ⇔Ｄ⇔Ｅ⇔Ｃ⇔（Ａ）
     * -----------------------
     * </PRE>
     */
    virtual void moveLast();

    /**
     * 自ノードを、先頭ノードへ移動する .
     * 子ノードも道連れにして移動します。自ノードと子ノードの関係は崩れません。<BR>
     *<PRE STYLE="font-size:18px">
     * ----------------「実行前」
     * 　　　親
     * 　　　↓
     * (Ｅ)⇔Ａ⇔Ｂ⇔Ｃ⇔Ｄ⇔Ｅ⇔(Ａ)
     * -----------------------
     *        ↓ 上図で自分が「Ｃ」とした場合、次のような状態になる
     * ----------------「実行後」
     * 　　　親
     * 　　　↓
     * (Ｅ)⇔Ｃ⇔Ａ⇔Ｂ⇔Ｄ⇔Ｅ⇔(Ｃ)
     * -----------------------
     * </PRE>
     */
    virtual void moveFirst();

    /**
     * 次のノード取得する。
     * @return	T*	次ノード
     */
    virtual T* getNext() {
        return _pNext;
    }

    /**
     * 前のノード取得する。
     * @return	T*	前ノード
     */
    virtual T* getPrev() {
        return _pPrev;
    }

    /**
     * １つ上の親ノード取得する。
     * @return	T*	親ノード
     */
    virtual T* getParent();

    /**
     * 親ノードを全て検索し取得する。
     * 存在しない場合はエラー <BR>
     * 内部で char* の比較を見つかるまで行うため、重いです。<BR>
     * 毎フレーム実行されるような使用は避けるべきです。<BR>
     * @param	prm_parent_name	親ノード名
     * @return	T*	親ノード
     */
    virtual T* getParent(char* prm_parent_name);

    /**
     * 引数ノードを子ノードとして追加する .
     * 追加される場所は以下の図のようになります。<BR>
     *<PRE STYLE="font-size:18px">
     * ----------------「実行前」
     *       Ｃ
     *       ↓
     * (Ｋ)⇔Ｉ⇔Ｊ⇔Ｋ⇔(Ｉ)
     * -----------------------
     *         ↓ 上図で自分が「Ｃ」とした場合、ここにノード「Ｘ」addSubLast すると
     *         ↓ 次のような状態になる
     * ----------------「実行後」
     *       Ｃ
     *       ↓
     * (Ｘ)⇔Ｉ⇔Ｊ⇔Ｋ⇔Ｘ⇔(Ｉ)
     * -----------------------
     * </PRE>
     *
     * @param   prm_pSub    インスタンス生成済みノードのポインタ
     */
    virtual void addSubLast(T* prm_pSub);

    /**
     * 子ノードをノード名称を指定して取得する .
     * 存在しない場合はエラー<BR>
     * 内部で char* の比較を見つかるまで行うため、重いです。<BR>
     * 毎フレーム実行されるような使用は避けるべきです。<BR>
     * @param	prm_sub_actor_name	子ノード名
     * @return	T*	最初にヒットした子ノード名に対応する子ノードのポインタ
     */
    virtual T* getSub(char* prm_sub_actor_name);

    /**
     * 子ノードのグループの先頭ノードを取得する .
     * 子ノードが存在しない場合はエラー。
     * @return	T*	子ノードの先頭ノード
     */
    virtual T* getSubFirst() {
        return _pSubFirst;
    }

    /**
     * 子ノード存在チェック .
     * 内部で char* の比較を見つかるまで行うため、重いです。<BR>
     * 毎フレーム実行されるような使用は避けるべきです。<BR>
     * @param	prm_sub_actor_name	存在チェックする子ノード名
     * @return	bool true:存在する／false:存在しない
     */
    virtual bool hasSub(char* prm_sub_actor_name);


    /**
     * 子ノード数を取得する .
     * @return  T*  子ノード数
     */
    virtual int getNumSub();


    /**
     * 自ノードが先頭ノードか調べる .
     * @return	bool true:先頭ノード／false:先頭ノードではない
     */
    virtual bool isFirst() {
        return _is_first_flg;
    }

    /**
     * 自ノードが末尾ノードか調べる .
     * @return	bool true:末尾ノード／false:末尾ノードではない
     */
    virtual bool isLast(){
        return _is_last_flg;
    }

};

//////////////////////////////////////////////////////////////////

/**
 * ここからは実装部
 */

template<class T>
GgafNode<T>::GgafNode(const char* prm_name) : GgafObject(),
_name("NOT_OBJECT_YET"),
_pParent(NULL),
_pSubFirst(NULL),
_is_first_flg(false),
_is_last_flg(false)
{
    _pNext = (T*)this;
    _pPrev = (T*)this;
    _name = NEW char[51];
    strcpy(_name, prm_name);
    //_id = GgafUtil::itos(GgafObject::_iObjectNo);
    TRACE("template<class T> GgafNode<T>::GgafNode(" << _name << ")");
    _class_name = "GgafNode<T>";
}

template<class T>
T* GgafNode<T>::extract() {
    if (_pParent != NULL) {
        //連結から外す
        T* pMyNext = _pNext;
        T* pMyPrev = _pPrev;
        if (_is_first_flg && _is_last_flg) {
            //連結が自分のみ場合
            _pParent->_pSubFirst = NULL;
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
                _pParent->_pSubFirst = pMyNext;
            }
        }
        _pParent = NULL;
        _pNext = (T*)this;
        _pPrev = (T*)this;
        _is_first_flg = true;
        _is_last_flg = true;
        return (T*)this;
    } else {
        //要素を追加するためのメソッドが、現在 addSubLast() のみであるため、親がいないことはツリーの頂点であることと同値。
        //TODO:将来、addNext() のような隣に要素を追加するメソッドを作らなければいけなくなった場合、
        //     この場所に横連結から切り離す処理を追加するのを忘れずに。
        TRACE("[GgafNode<" << _class_name << ">::extract()] ＜警告＞ " << getName() << "は、何所にも所属していません。既に独立してました");
        return (T*)this;
    }
}

template<class T>
void GgafNode<T>::moveLast() {
    if (_is_last_flg) { //既に最終ノードならば何もしない
        return;
    } else if (_is_first_flg) { //先頭ノードならば、親の指している先頭ノードを次へずらす
        _pParent->_pSubFirst = _pNext;
        _pPrev->_is_last_flg = false;
        _is_first_flg = false;
        _is_last_flg = true;
        _pNext->_is_first_flg = true;
    } else { //中間ノード時
        //両隣のノード同士を繋ぐ
        _pPrev->_pNext = _pNext;
        _pNext->_pPrev = _pPrev;
        //末尾ノードと先頭ノードの間にもぐりこませる
        _pParent->_pSubFirst->_pPrev->_is_last_flg = false;
        _is_last_flg = true;
        _pPrev = _pParent->_pSubFirst->_pPrev;
        _pNext = _pParent->_pSubFirst;
        _pParent->_pSubFirst->_pPrev->_pNext = (T*)this;
        _pParent->_pSubFirst->_pPrev = (T*)this;
    }
}

template<class T>
void GgafNode<T>::moveFirst() {
    if (_is_first_flg) { //既に先頭ノードならば何もしない
        return;
    } else if (_is_last_flg) { //末尾ノードならば、親の指している先頭ノードを前にずらす
        _pParent->_pSubFirst = (T*)this;
        _pPrev->_is_last_flg = true;
        _is_first_flg = true;
        _is_last_flg = false;
        _pNext->_is_first_flg = false;
    } else { //中間ノード時
        //両隣のノード同士を繋ぐ
        _pPrev->_pNext = _pNext;
        _pNext->_pPrev = _pPrev;
        //末尾ノードと先頭ノードの間にもぐりこませる
        _pParent->_pSubFirst->_is_first_flg = false;
        _is_first_flg = true;
        _pPrev = _pParent->_pSubFirst->_pPrev;
        _pNext = _pParent->_pSubFirst;
        _pParent->_pSubFirst->_pPrev->_pNext = (T*)this;
        _pParent->_pSubFirst->_pPrev = (T*)this;
        _pParent->_pSubFirst = (T*)this;
    }
}


template<class T>
T* GgafNode<T>::getParent() {
    if (_pParent == NULL) {
        _TRACE_("[GgafNode<" << _class_name << ">::getParent()] ＜警告＞ 親ノードがありません。NULLを返します。");
    }
    return (T*)_pParent;
}

template<class T>
T* GgafNode<T>::getParent(char* prm_parent_name) {
    _pNodeTemp = (T*)this;
    while (true) {
        _pNodeTemp = _pNodeTemp->_pParent;
        if (_pNodeTemp == NULL) {
            _TRACE_("[GgafNode<" << _class_name << ">::getParent("<<prm_parent_name<<")] ＜警告＞ 親ノードを遡って検索しましたがありません。NULLを返します。");
            return NULL;
        } else if (GgafUtil::strcmp_ascii(_pNodeTemp->_name, prm_parent_name) == 0) {
            break;
        }
    }
    return _pNodeTemp;
}

template<class T>
T* GgafNode<T>::getSub(char* prm_sub_actor_name) {
#ifdef MY_DEBUG
    if (_pSubFirst == NULL) {
        throwGgafCriticalException("[GgafNode<" << _class_name << ">::getSub()] Error! _pSubFirstがNULLです。");
    }
#endif
    _pNodeTemp = _pSubFirst;
    do {
        if (GgafUtil::strcmp_ascii(_pNodeTemp->getName(), prm_sub_actor_name) == 0) {
            break;
        }
#ifdef MY_DEBUG
        if (_pNodeTemp->_is_last_flg) {
            throwGgafCriticalException("[GgafNode<" << _class_name << ">::getSub()] Error! 子ノードは存在しません。(prm_sub_actor_name=" << prm_sub_actor_name << ")");
        }
#endif
        _pNodeTemp = _pNodeTemp->_pNext;
    } while (true);
    return _pNodeTemp;
}

template<class T>
bool GgafNode<T>::hasSub(char* prm_sub_actor_name) {
    if (_pSubFirst == NULL) {
        return false;
    } else {
        _pNodeTemp = _pSubFirst;
        do {
            if (GgafUtil::strcmp_ascii(_pNodeTemp->getName(), prm_sub_actor_name)) {
                return true;
            }
            if (_pNodeTemp->_is_last_flg) {
                return false;
            } else {
                _pNodeTemp = _pNodeTemp->_pNext;
            }
        } while (true);
    }
}

template<class T>
int GgafNode<T>::getNumSub() {
    if (_pSubFirst == NULL) {
        return 0;
    }
    int n = 1;
    _pNodeTemp = _pSubFirst;
    do {
        if (_pNodeTemp->isLast()) {
            break;
        }
        _pNodeTemp = _pNodeTemp->_pNext;
        n++;
    } while (true);
    return n;
}


template<class T>
void GgafNode<T>::addSubLast(T* prm_pSub) {
#ifdef MY_DEBUG
    if (prm_pSub->_pParent != NULL) {
        throwGgafCriticalException("[GgafNode<" << _class_name << ">::addSubLast()] Error! ノードは既に所属("
                << prm_pSub->_pParent->_name << "に所属)しています(this=" << _name << "/prm_pSub=" << prm_pSub->getName() << ")");
    }
#endif
    prm_pSub->_pParent = (T*)this;
    prm_pSub->_is_last_flg = true;
    //prm_pSub->_pScene_Platform = _pScene_Platform;

    if (_pSubFirst == NULL) {
        prm_pSub->_is_first_flg = true;
        _pSubFirst = prm_pSub;
        _pSubFirst->_pNext = prm_pSub;
        _pSubFirst->_pPrev = prm_pSub;
    } else {
        prm_pSub->_is_first_flg = false;
        T* pSubLast = _pSubFirst->_pPrev;
        pSubLast->_is_last_flg = false;
        pSubLast->_pNext = prm_pSub;
        prm_pSub->_pPrev = pSubLast;
        prm_pSub->_pNext = _pSubFirst;
        _pSubFirst->_pPrev = prm_pSub;
    }

}

/*
 template<class T>
 bool GgafNode<T>::isNamed(const char* prm_name) {
 char*::size_type iLen = prm_name.length();
 if (prm_name.rfind('*') == iLen-1) {}


 return _name;
 }
 */


template<class T>
GgafNode<T>::~GgafNode() {
    //自分に子がある場合
    if (_pSubFirst) {
        //まず子をdelete
        if (_pSubFirst->_is_last_flg) {
            //子ノードは１つの場合
            DELETE_IMPOSSIBLE_NULL(_pSubFirst);
            _pSubFirst = NULL;
        } else {
            //子ノードは２つ以上の場合
            T* pSubLast = _pSubFirst->_pPrev;
            T* pSubLastPrev = pSubLast->_pPrev;
            while (true) {
                DELETE_IMPOSSIBLE_NULL(pSubLast); //末尾からdelete
                if (pSubLastPrev->_is_first_flg) {
                    DELETE_IMPOSSIBLE_NULL(_pSubFirst); //pSubLastPrev == _pSubFirst である
                    _pSubFirst = NULL;
                    break;
                }
                pSubLast = pSubLastPrev;
                pSubLastPrev = pSubLastPrev->_pPrev;
            }
        }
    }

    //子がない状態の場合
    if (_pParent) {
        //連結から外す
        T* pMyNext = _pNext;
        T* pMyPrev = _pPrev;
        if (_is_first_flg && _is_last_flg) {
            //連結しているノードが無く、自分のみ場合
            _pParent->_pSubFirst = NULL;
            _pParent = NULL;
            _pNext = (T*)this;
            _pPrev = (T*)this;
            _pSubFirst = NULL;
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
                _pParent->_pSubFirst = pMyNext;
            }
            _pParent = NULL;
            _pNext = (T*)this;
            _pPrev = (T*)this;
            _pSubFirst = NULL;
            _is_first_flg = true;
            _is_last_flg = true;
        }
    }
    DELETEARR_IMPOSSIBLE_NULL(_name);
}

}
#endif /*GGAFNODE_H_*/
