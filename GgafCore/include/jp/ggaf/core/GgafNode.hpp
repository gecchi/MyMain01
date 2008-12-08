#ifndef GGAFNODE_H_
#define GGAFNODE_H_
/**
 * 要素同士を環状双方向連結リストのツリー構造を作ることができるテンプレートです。.
 *
 * <B>【解説】</B><BR>
 * <PRE>
 * 　･･⇔Ｐ⇔･･･
 * 　　　↓
 * (Ｅ)⇔Ａ⇔Ｂ⇔Ｃ⇔Ｄ⇔Ｅ⇔(Ａ)
 * 　　　　　　│　└────────────┐
 * 　　　　　　↓　　　　　　　　　　　　　　↓
 * 　　　(Ｈ)⇔Ｆ⇔Ｇ⇔Ｈ⇔(Ｆ)　　　　(Ｌ)⇔Ｉ⇔Ｊ⇔Ｋ⇔Ｌ⇔(Ｉ)
 * 　　　　　　　　↓　↓　　　　　　　　　　　　↓　　　↓
 * 　　　　　　　　　･･･　　　　　　　　　　　　　　　･･･
 * </PRE>
 * 上図のような構造を採る事が出来ます。<BR>
 * 中段の「(Ｅ)⇔Ａ⇔Ｂ⇔Ｃ⇔Ｄ⇔Ｅ⇔(Ａ)」は要素（インスタンス）が環状の双方向でポインタを指しあっている事を示しています。<BR>
 * 両端の「(Ｅ)」と「(Ａ)」は、連結リストの先頭と末尾も、お互い連結している事を明示しています。(環状になっている)<BR>
 * 上図で自身のインスタンスを「Ｃ」とした場合、「Ｃ」の視点から各要素を次のように呼称、及び定義することとします。<BR>
 * <TABLE BORDER="1">
 * <TR><TD>「Ｃ」</TD><TD>自ノード</TD></TR>
 * <TR><TD>「Ａ」</TD><TD>先頭(First)ノード。 自ノードが所属する連結リストの先頭という意味です。「Ａ」 は _isFirst が true になっています。(他ノードは false)</TD></TR>
 * <TR><TD>「Ｅ」</TD><TD>末尾(Last)ノード。 自ノードが所属する連結リストの最後という意味です。「Ｅ」 は _isLast が true になっています。(他のノードは false)</TD></TR>
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
 * ＜例＞下位で実装された･･･。</TD>
 * </TR>
 * </TABLE>
 * @version 1.00
 * @since 2008/06/20
 * @auther Masatoshi Tsuge
 */

template<class T>
class GgafNode : public GgafObject {

protected:
public:

	/** ID */
	string _id;
	/** ノード名 */
	string _name;
	/** クラス名 */
	string _class_name;

	/** 親ノード */
	T* _pParent;
	/** 次ノード */
	T* _pNext;
	/** 前ノード */
	T* _pPrev;
	/** 子ノードの先頭ノード */
	T* _pSubFirst;

	/** 先頭ノードフラグ (自ノードが先頭ノードの場合 true)*/
	bool _isFirst;
	/** 末尾ノードフラグ (自ノードが末尾ノードの場合 true)*/
	bool _isLast;
	/** ループ用 */
	T* _pNodeTemp;

	/**
	 * コンストラクタ
	 * @param prm_name ノード名称（ユニークにして下さい）
	 */
	GgafNode(string prm_name);

	/**
	 * デストラクタ。自ツリーノードを解放します。 .
	 * 自ノードが子ノードを持つ場合、子ノードを解放してから自身を開放する。<BR>
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
	virtual string getName();

	/**
	 * クラス名取得 .
	 * @return クラス名称
	 */
	virtual string getClassName();


	/**
	 * ノード名問い合わせ
	 */
//	virtual bool isNamed(string prm_name);


	/**
	 * １つ上の親ノードを設定する。
	 * @param	prm_pParent	親ノード
	 */
	void setParent(T* prm_pParent);

	/**
	 * 自ツリーノードを連結リストから切り離し、独立する。 .
	 * 切り離され穴が開いた部分は、周りのノードが穴を埋めます（再連結します）<BR>
	 * 自ノードに子がぶら下がっていた場合、それらも切り離されたことになります。<BR>
	 * @return	T* 自ノードのポインタ
	 *
	 */
	T* tear();

	/**
	 * 自ノードを、最終ノードへ移動する .
	 * 子ノードも道連れにして移動します。自ノードと子ノードの関係は崩れません。<BR>
	 *<PRE>
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
	void moveLast();

	/**
	 * 自ノードを、先頭ノードへ移動する .
	 * 子ノードも道連れにして移動します。自ノードと子ノードの関係は崩れません。<BR>
	 *<PRE>
	 * ----------------「実行前」
	 *      親
	 *      ↓
	 * (Ｅ)⇔Ａ⇔Ｂ⇔Ｃ⇔Ｄ⇔Ｅ⇔(Ａ)
	 * -----------------------
	 *        ↓ 上図で自分が「Ｃ」とした場合、次のような状態になる
	 * ----------------「実行後」
	 *      親
	 *      ↓
	 * (Ｅ)⇔Ｃ⇔Ａ⇔Ｂ⇔Ｄ⇔Ｅ⇔(Ｃ)
	 * -----------------------
	 * </PRE>
	 */
	 void moveFirst();


	/**
	 * 次のノード取得する。
	 * @return	T*	次ノード
	 */
	T* getNext();

	/**
	 * 前のノード取得する。
	 * @return	T*	前ノード
	 */
	T* getPrev();

	/**
	 * １つ上の親ノード取得する。
	 * @return	T*	親ノード
	 */
	T* getParent();

	/**
	 * 親ノードを全て検索し取得する。
	 * 存在しない場合はエラー
	 * @param	prm_parent_name	親ノード名
	 * @return	T*	親ノード
	 */
	T* getParent(string prm_parent_name);

	/**
	 * 引数ノードを子ノードとして追加する .
	 * 追加される場所は以下の図のようになります。<BR>
	 *<PRE>
	 * ----------------「実行前」
	 *      Ｃ
	 *      ↓
	 * (Ｋ)⇔Ｉ⇔Ｊ⇔Ｋ⇔(Ｉ)
	 * -----------------------
	 *        ↓ 上図で自分が「Ｃ」とした場合、ここにノード「Ｘ」addSubLast すると
	 *        ↓ 次のような状態になる
	 * ----------------「実行後」
	 *      Ｃ
	 *      ↓
	 * (Ｘ)⇔Ｉ⇔Ｊ⇔Ｋ⇔Ｘ⇔(Ｉ)
	 * -----------------------
	 * </PRE>
	 *
	 * @param	prm_pSub	インスタンス生成済みノードのポインタ
	 */
	void addSubLast(T* prm_pSub);

	/**
	 * 子ノードをノード名称を指定して取得する .
	 * 存在しない場合はエラー
	 * @param	prm_sub_actor_name	子ノード名
	 * @return	T*	最初にヒットした子ノード名に対応する子ノードのポインタ
	 */
	T* getSub(string prm_sub_actor_name);

	/**
	 * 子ノードのグループの先頭ノードを取得する .
	 * 子ノードが存在しない場合はエラー。
	 * @return	T*	子ノードの先頭ノード
	 */
	T* getSubFirst();

	/**
	 * 子ノード存在チェック .
	 * @param	prm_sub_actor_name	存在チェックする子ノード名
	 * @return	bool true:存在する／false:存在しない
	 */
	bool hasSub(string prm_sub_actor_name);

	/**
	 * 自ノードが先頭ノードか調べる .
	 * @return	bool true:先頭ノード／false:先頭ノードではない
	 */
	bool isFirst();

	/**
	 * 自ノードが末尾ノードか調べる .
	 * @return	bool true:末尾ノード／false:末尾ノードではない
	 */
	bool isLast();

};



//////////////////////////////////////////////////////////////////

/**
 * ここからは実装部
 */

template<class T>
GgafNode<T>::GgafNode(string prm_name) : GgafObject() ,
_name("NOT_OBJECT_YET"),
_pParent(NULL),
_pSubFirst(NULL),
_isFirst(false),
_isLast(false)
{
	_pNext = (T*)this;
	_pPrev = (T*)this;
	_name = prm_name;
	//_id = GgafUtil::itos(GgafObject::_iObjectNo);
	TRACE("template<class T> GgafNode<T>::GgafNode("+_name+")");
	_class_name = "GgafNode<T>";

}


template<class T>
T* GgafNode<T>::tear() {
	if (_pParent != NULL) {
		//連結から外す
		T* pMyNext = _pNext;
		T* pMyPrev = _pPrev;
		if (_isFirst && _isLast) {
			//連結が自分のみ場合
			_pParent -> _pSubFirst = NULL;
		} else {
			//連結がから抜け出す場合
			//両隣のノード同士を繋ぎ、自分を指さなくする。
			pMyPrev -> _pNext = pMyNext;
			pMyNext -> _pPrev = pMyPrev;
			if (_isLast) {
				pMyPrev -> _isLast = true;
			}
			if (_isFirst) {
				pMyNext -> _isFirst = true;
				_pParent -> _pSubFirst = pMyNext;
			}
		}
		_pParent = NULL;
		_pNext = (T*)this;
		_pPrev = (T*)this;
		_isFirst = true;
		_isLast = true;
		return (T*)this;
	} else {
		throw_GgafCriticalException("[GgafNode<"<<_class_name<<">::tear()] ＜警告＞ "<<getName()<<"は、何所にも所属していません");
	}

}


template<class T>
void GgafNode<T>::moveLast() {
	if (_isLast) { //既に最終ノードならば何もしない
		return;
	} else if (_isFirst) {  //先頭ノードならば、親の指している先頭ノードを次へずらす
		_pParent -> _pSubFirst = _pNext;
		_pPrev->_isLast = false;
		_isFirst = false;
		_isLast = true;
		_pNext->_isFirst = true;
	} else { //中間ノード時
		//両隣のノード同士を繋ぐ
		_pPrev -> _pNext = _pNext;
		_pNext -> _pPrev = _pPrev;
		//末尾ノードと先頭ノードの間にもぐりこませる
		_pParent -> _pSubFirst -> _pPrev -> _isLast = false;
		_isLast = true;
		_pPrev = _pParent -> _pSubFirst -> _pPrev;
		_pNext = _pParent -> _pSubFirst;
		_pParent -> _pSubFirst -> _pPrev -> _pNext = (T*)this;
		_pParent -> _pSubFirst -> _pPrev = (T*)this;
	}
}




template<class T>
void GgafNode<T>::moveFirst() {
	if (_isFirst) { //既に先頭ノードならば何もしない
		return;
	} else if (_isLast) {  //末尾ノードならば、親の指している先頭ノードを前にずらす
		_pParent -> _pSubFirst = (T*)this;
		_pPrev->_isLast = true;
		_isFirst = true;
		_isLast= false;
		_pNext -> _isFirst = false;
	} else { //中間ノード時
		//両隣のノード同士を繋ぐ
		_pPrev -> _pNext = _pNext;
		_pNext -> _pPrev = _pPrev;
		//末尾ノードと先頭ノードの間にもぐりこませる
		_pParent -> _pSubFirst -> _isFirst = false;
		_isFirst = true;
		_pPrev = _pParent -> _pSubFirst -> _pPrev;
		_pNext = _pParent -> _pSubFirst;
		_pParent -> _pSubFirst -> _pPrev -> _pNext = (T*)this;
		_pParent -> _pSubFirst -> _pPrev = (T*)this;
		_pParent -> _pSubFirst = (T*)this;
	}
}


template<class T>
void GgafNode<T>::setParent(T* prm_pParent) {
	_pParent = prm_pParent;
}

template<class T>
T* GgafNode<T>::getNext() {
	return (T*)_pNext;
}

template<class T>
T* GgafNode<T>::getPrev() {
	return (T*)_pPrev;
}


template<class T>
T* GgafNode<T>::getParent() {
	if (_pParent == NULL) {
		throw_GgafCriticalException("[GgafNode<"<<_class_name<<">::getParent()] Error! 親ノードがありません。");
	}
	return (T*)_pParent;
}


template<class T>
T* GgafNode<T>::getParent(string prm_parent_name) {
	_pNodeTemp = (T*)this;
	while(true) {
		_pNodeTemp = _pNodeTemp->_pParent;
		if (_pNodeTemp == NULL) {
			throw_GgafCriticalException("[GgafNode<"<<_class_name<<">::getParent()] Error! 親ノードがありません。(prm_parent_name="+prm_parent_name+")");
		} else if (_pNodeTemp->_name == prm_parent_name) {
			break;
		}
	}
	return _pNodeTemp;
}

template<class T>
T* GgafNode<T>::getSub(string prm_sub_actor_name) {
	if (_pSubFirst == NULL) {
		throw_GgafCriticalException("[GgafNode<"<<_class_name<<">::getSub()] Error! _pSubFirstがNULLです。");
	}
	_pNodeTemp = _pSubFirst;
	do {
		if(_pNodeTemp -> getName() == prm_sub_actor_name) {
			break;
		}
		if (_pNodeTemp -> _isLast) {
			throw_GgafCriticalException("[GgafNode<"<<_class_name<<">::getSub()] Error! 子ノードは存在しません。(prm_sub_actor_name="+prm_sub_actor_name+")");
		} else {
			_pNodeTemp = _pNodeTemp -> _pNext;
		}
	} while(true);
	return _pNodeTemp;
}

template<class T>
T* GgafNode<T>::getSubFirst() {
	return (T*)_pSubFirst;
}


template<class T>
bool GgafNode<T>::hasSub(string prm_sub_actor_name) {
	if (_pSubFirst == NULL) {
		return false;
	} else {
		_pNodeTemp = _pSubFirst;
		do {
			if(_pNodeTemp -> getName() == prm_sub_actor_name) {
				return true;
			}
			if (_pNodeTemp -> _isLast) {
				return false;
			} else {
				_pNodeTemp = _pNodeTemp -> _pNext;
			}
		} while(true);
	}
}


template<class T>
void GgafNode<T>::addSubLast(T* prm_pSub) {
	if (prm_pSub->_pParent != NULL) {
		throw_GgafCriticalException("[GgafNode<"<<_class_name<<">::addSubLast()] Error! ノードは既に所属しています(this="<<_name<<"/prm_pSub="+prm_pSub->getName()+")");
	}
	prm_pSub -> _pParent = (T*)this;
	prm_pSub -> _isLast = true;
	//prm_pSub -> _pScene_Platform = _pScene_Platform;

	if (_pSubFirst == NULL) {
		prm_pSub -> _isFirst = true;
		_pSubFirst = prm_pSub;
		_pSubFirst->_pNext = prm_pSub;
		_pSubFirst->_pPrev = prm_pSub;
	} else {
		prm_pSub -> _isFirst = false;
		T* pSubLast = _pSubFirst->_pPrev;
		pSubLast -> _isLast = false;
		pSubLast->_pNext = prm_pSub;
		prm_pSub->_pPrev = pSubLast;
		prm_pSub->_pNext = _pSubFirst;
		_pSubFirst->_pPrev = prm_pSub;
	}

}


template<class T>
string GgafNode<T>::getName() {
	return _name;
}

template<class T>
string GgafNode<T>::getClassName() {
	return _class_name;
}
/*
template<class T>
bool GgafNode<T>::isNamed(string prm_name) {
	string::size_type iLen = prm_name.length();
	if (prm_name.rfind('*') == iLen-1) {}


	return _name;
}
*/

template<class T>
bool GgafNode<T>::isLast() {
	return _isLast;
}

template<class T>
bool GgafNode<T>::isFirst() {
	return _isFirst;
}

template<class T>
GgafNode<T>::~GgafNode() {
	//自分に子がある場合
	if (_pSubFirst) {
		//まず子をdelete
		if (_pSubFirst->_isLast) {
			//子ノードは１つの場合
			DELETE_IMPOSSIBLE_NULL(_pSubFirst);
			_pSubFirst = NULL;
		} else {
			//子ノードは２つ以上の場合
			T* pSubLast = _pSubFirst -> _pPrev;
			T* pSubLastPrev = pSubLast -> _pPrev;
			while(true) {
				DELETE_IMPOSSIBLE_NULL(pSubLast); //末尾からdelete
				if (pSubLastPrev -> _isFirst) {
					DELETE_IMPOSSIBLE_NULL(_pSubFirst); //pSubLastPrev == _pSubFirst である
					_pSubFirst = NULL;
					break;
				}
				pSubLast = pSubLastPrev;
				pSubLastPrev = pSubLastPrev -> _pPrev;
			}
		}
	}

	//子がない状態の場合
	if (_pParent) {
		//連結から外す
		T* pMyNext = _pNext;
		T* pMyPrev = _pPrev;
		if (_isFirst && _isLast) {
			//連結しているノードが無く、自分のみ場合
			_pParent -> _pSubFirst = NULL;
			_pParent = NULL;
			_pNext = (T*)this;
			_pPrev = (T*)this;
			_pSubFirst = NULL;
		} else {
			//連結がから抜け出す場合
			//両隣のノード同士を繋ぎ、自分を指さなくする。
			pMyPrev -> _pNext = pMyNext;
			pMyNext -> _pPrev = pMyPrev;
			if (_isLast) {
				pMyPrev -> _isLast = true;
			}
			if (_isFirst) {
				pMyNext -> _isFirst = true;
				_pParent -> _pSubFirst = pMyNext;

			}
			_pParent = NULL;
			_pNext = (T*)this;
			_pPrev = (T*)this;
			_pSubFirst = NULL;
			_isFirst = true;
			_isLast = true;
		}
	}

//	_TRACE_("...deleted GgafNode<"<<_class_name<<">("<<_name<<") ID="<<_id);
	//_TRACE_("...deleted GgafNode<"<<_class_name<<">("<<_name<<")");

}

#endif /*GGAFNODE_H_*/
