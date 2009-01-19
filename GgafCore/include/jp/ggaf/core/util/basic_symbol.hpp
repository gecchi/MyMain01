#ifndef BASIC_SYMBOL_H_
#define BASIC_SYMBOL_H_
namespace GgafCore {


template<class Key, class Comp =less<Key> >
class basic_symbol {

public:
	typedef unsigned long            hash_type;
//	typedef Key                      Key;
//	typedef set<Key, Comp> set<Key, Comp>;
	static set<Key, Comp>& key_pool();
	const Key* k;

	basic_symbol()
	  { k = &(*key_pool().insert(Key()).first); };
	basic_symbol(const Key& key)
	  { k = &(*key_pool().insert(key).first); };
	basic_symbol(const basic_symbol& sym)
	  : k(sym.k) {};

	basic_symbol& operator=(const basic_symbol& sym)
	  { k = sym.k; return *this; };
	basic_symbol& operator=(const Key& key)
	  { k = &(*key_pool().insert(key).first); return *this; };

	const Key& key() const  { return *k; };
	hash_type hash() const       { return hash_type(k); };

private:


};

template<class Key, class Comp>
set<Key, Comp>&
basic_symbol<Key, Comp>::key_pool() {
	static set<Key, Comp> pool;
	return pool;
}

template<class K, class C>
inline bool operator==(const basic_symbol<K,C>& x, const basic_symbol<K,C>& y)
  { return x.hash() == y.hash(); }

template<class K, class C>
inline bool operator!=(const basic_symbol<K,C>& x, const basic_symbol<K,C>& y)
  { return x.hash() != y.hash(); }

template<class K, class C>
inline bool operator<(const basic_symbol<K,C>& x, const basic_symbol<K,C>& y)
  { return x.hash() < y.hash(); }

template<class K, class C>
inline bool operator<=(const basic_symbol<K,C>& x, const basic_symbol<K,C>& y)
  { return x.hash() <= y.hash(); }

template<class K, class C>
inline bool operator>(const basic_symbol<K,C>& x, const basic_symbol<K,C>& y)
  { return x.hash() > y.hash(); }

template<class K, class C>
inline bool operator>=(const basic_symbol<K,C>& x, const basic_symbol<K,C>& y)
  { return x.hash() >= y.hash(); }

typedef basic_symbol<string>  string_symbol;
typedef basic_symbol<wstring> wstring_symbol;


}
#endif /*BASIC_SYMBOL_H_*/
