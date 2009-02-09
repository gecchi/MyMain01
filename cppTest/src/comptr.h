// Com_ptrクラス (2006. 8. 10)

// DirectXのインターフェイスの参照カウンタやコピーなどの問題を解決する。
// デバッグ時にはインターフェイスの使用状況をDEBUG.txtというファイル名で
// 外部に出力します。
// デバッグ時にこの機能をOFFにするには下の
// OUTPUT_INTERFACEUSAGE定数をコメントアウトしてください。

#pragma once 

#include <windows.h>


#define OUTPUT_INTERFACEUSAGE

#ifdef OUTPUT_INTERFACEUSAGE
   #if _DEBUG
   // デバッグ時にファイル出力
   #include <fstream>
   using namespace std;
   #endif
#endif



namespace IKD{

template <class T>
class Com_ptr
{
private:
   T** m_ppInterface;   // インターフェイスへのダブルポインタ
   static T* m_NullPtr;	// NULLポインタ

protected:
   // 参照カウンタ増加
   void AddRef(T* pInterface){
		#if _DEBUG
			#ifdef OUTPUT_INTERFACEUSAGE
				// デバッグ版では参照カウントを出力する
				ULONG c = pInterface->AddRef();
				ofstream ofs;
				ofs.open("DEBUG.txt", ios::app);
				ofs << pInterface << "\t[" << c << "]" << endl;
				ofs.close();
            #else
				pInterface->AddRef();
			#endif// OUTPUT_INTERFACEUSAGE
		#else
			// リリースモード
			pInterface->AddRef();
		#endif
   }

	// 参照カウンタ減少
	void Release(T* pInterface){
		ULONG c;
		c = pInterface->AddRef() - 1;   // 現在の参照カウンタ数を取得
		pInterface->Release();
		if(c<=1)
			delete m_ppInterface;
		pInterface->Release();      // 今回の呼び出しによるReleaseはここ
		#if _DEBUG
			#ifdef OUTPUT_INTERFACEUSAGE
				// 一度参照カウンタ数を増加して正しいカウンタ数を得る
				ofstream ofs;
				ofs.open("DEBUG.txt", ios::app);
				ofs << pInterface << "\t[" << c-1 << "]" << endl;
				ofs.close();
			#endif// OUTPUT_INTERFACEUSAGE
		#endif
	}

public:
   // デフォルトコンストラクタ
   // コンストラクタはexplicit宣言します。
   // よってfunc(Com_ptr<IHoge> v)という関数に対して、
   // func(pIHoge)のような暗黙型変換代入は出来ません。
   // 通常、ポインタの引渡し時にすでに参照カウンタは
   // インクリメントされているので、AddRefは行いません。
	explicit Com_ptr(T* pInterface = NULL, BOOL add=FALSE){
		#if _DEBUG
			#ifdef OUTPUT_INTERFACEUSAGE
				// デバッグ版では参照カウントの初期値を出力する
				ofstream ofs;
				ofs.open("DEBUG.txt", ios::app);
				ofs << pInterface << "\t[" << 1 << "]" << endl;
				ofs.close();
			#endif// OUTPUT_INTERFACEUSAGE
		#endif
		if(pInterface && add)
			pInterface->AddRef();
		m_ppInterface = new T*;	// ポインタ格納領域を確保
		if(pInterface)
			*m_ppInterface = pInterface;
		else
			*m_ppInterface = m_NullPtr;
	}

	// 暗黙型キャストコピーコンストラクタ
	template<class T2> Com_ptr( Com_ptr<T2>& src ){
		// ここにくるということは、初期化されていない状態であるため、
		// 問答無用でアップキャストして所有権を取得する
		if(src.GetPtr()!=NULL){
			m_ppInterface = (T**)src.GetPtrPtr();	// 共有
			*m_ppInterface = src.GetPtr();			// 型チェック用
			// 参照カウンタ増加
			AddRef( *m_ppInterface );
		}
		else
		{
			// 相手がNULLなので新規作成
			m_ppInterface = new T*;
			*m_ppInterface = m_NullPtr;
		}
	}


	// コピーコンストラクタ
	Com_ptr(const Com_ptr<T> &src)
	{
		if(*src.m_ppInterface)
		{
			// コピー元と共有するので参照カウンタを1つ増やす
			(*src.m_ppInterface)->AddRef();
			m_ppInterface = src.m_ppInterface;
		}
		else
		{
			// NULL代入なので新規作成
			m_ppInterface = new T*;
			*m_ppInterface = m_NullPtr;
		}
	}

	// コピーコンストラクタ(NULL代入用)
	Com_ptr(const int nullval)
	{
		m_ppInterface = new T*;	// ポインタ格納領域を改めて確保
		*m_ppInterface = m_NullPtr;
	}


	// デストラクタ
	virtual ~Com_ptr()
	{
		if(*m_ppInterface)
		{
			Release(*m_ppInterface);
		}
		else
			delete m_ppInterface;
	}

	/////////////////////////////////////////////
	// 演算子
	/////////////////////
	// =代入演算子（明示的コピー）
	Com_ptr<T>& operator =(const Com_ptr<T>& src){
		if(*m_ppInterface)
		{
			// 同グループの場合は何もしない
			if( *m_ppInterface == *src.m_ppInterface )
				return *this;
			// 自分の持つCOMオブジェクトの参照カウンタを1つ減らす
			Release(*m_ppInterface);
		}
		else
		{
			// 相手と共有するか新規作成になるためいったん保持しているダブルポインタを消去
			// NULLポインタの共有者はいないため、この作業は他人に迷惑をかけない
			delete m_ppInterface;
		}

		// コピー元の参照カウンタを1つ増やす
		if(*src.m_ppInterface)
		{
			(*src.m_ppInterface)->AddRef();
			m_ppInterface  = src.m_ppInterface;		// 共有
		}
		else
		{
			// 相手がNULLである
			m_ppInterface  = new T*;
			*m_ppInterface = m_NullPtr;
		}

		return *this;
	}

	// ->アロー演算子
	T* operator ->(){ return *m_ppInterface; }

	// =代入演算子（新規インターフェイス登録）
	void operator =(T* pInterface){
		// 自分のインターフェイスの参照カウンタを1つ減らす
		if(*m_ppInterface){
			Release(*m_ppInterface);	// もし自分が最後の一人だったらここでメンバ変数の消去がある
		}
		else
		{
			// いったん消す
			delete m_ppInterface;
		}
		// 自分は新しい人になるので、
		// 新しいダブルポインタを作成
			m_ppInterface = new T*;

		// 新規代入
		if(pInterface)
			*m_ppInterface = pInterface;
		else
			*m_ppInterface = m_NullPtr;
	}

	// !=比較演算子
	bool operator !=(T* ptr){
		if(ptr != *m_ppInterface)
			return true;
		return false;
	}

	// !=比較演算子
	bool operator !=(Com_ptr<T> &src){
		if(*m_ppInterface != *src.m_ppInterface)
			return true;
		return false;
	}

	// ==比較演算子
	bool operator ==(T* ptr){
		if(ptr == *m_ppInterface)
			return true;
		return false;
	}

	// ==比較演算子
	bool operator ==(Com_ptr<T> &src){
		if(*m_ppInterface == *src.m_ppInterface)
			return true;
		return false;
	}

	// !単項演算子
	bool operator !(){
		if( *m_ppInterface == NULL )
			return true;
		return false;
	}

// メンバ関数
	// 参照カウンタ数を取得
	ULONG GetRefCnt()
	{
		if(*m_ppInterface){
			ULONG c = (*m_ppInterface)->AddRef()-1;
			(*m_ppInterface)->Release();
			return c;
		}
		return 0;
	}

	// アップキャストコピー
	template<class T1> void UpcastCopy(Com_ptr<T1> & src ){
		// 自分のインターフェイスの参照カウンタを1つ減らす
		if(*m_ppInterface)
			Release(*m_ppInterface);

		// コピー元の参照カウンタを1つ増やす
		if(src.GetPtr())
		{
			src.GetPtr()->AddRef();
			m_ppInterface = src.GetPtrPtr();	// 共有
			*m_ppInterface = src.GetPtr();		// チェック用代入
		}
		else
		{
			// NULLコピーなので新規作成
			m_ppInterface = new T*;
			*m_ppInterface = m_NullPtr;
		}
	}

	// ポインタ取得
	T* GetPtr(){return *m_ppInterface;}

	// ダブルポインタを取得
	T** GetPtrPtr(){return m_ppInterface;}

	// インターフェイス生成関数へ渡す専用関数
	T** ToCreator(){
		if(*m_ppInterface)
		{
			Release(*m_ppInterface);
			m_ppInterface = new T*;
		}
		return m_ppInterface;
	}

	// COMスワップ
	bool Swap( Com_ptr<T> &src )
	{
		// 引数のCOMオブジェクトと自身とを入れ替える
		// ただし双方が有効なCOMオブジェクトを持っている時に限る

		// オブジェクトチェック
		if( *m_ppInterface == NULL || src.GetPtr()==NULL)
			return false;

		// 参照カウンタ数のチェック
		ULONG SrcRef = src->AddRef()-1;
		src->Release();

		ULONG MeRef = (*m_ppInterface)->AddRef()-1;
		(*m_ppInterface)->Release();

		// 引数のCOMオブジェクトを取得
		T *pReleaseObj, *pAddObj;
		if(MeRef<=SrcRef){
			pReleaseObj = src.GetPtr();
			pAddObj = *m_ppInterface;
		}
		else
		{
			pReleaseObj = *m_ppInterface;
			pAddObj = src.GetPtr();
		}

		// 互いの参照カウント数を交換
		ULONG i;
		ULONG Cnt = ((int)(SrcRef-MeRef))>0?(SrcRef-MeRef):MeRef-SrcRef;
		for(i=0; i<Cnt; i++){
			pReleaseObj->Release();
			pAddObj->AddRef();
		}

		// COMポインタ内のポインタ交換
		T* pTmp = *src.m_ppInterface;
		*src.m_ppInterface = *m_ppInterface;
		*m_ppInterface = pTmp;

		return true;
	}
};


template <class T>
T* Com_ptr<T>::m_NullPtr = NULL;

}