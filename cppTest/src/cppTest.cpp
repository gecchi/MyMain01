// 固定アニメーションテストサンプルプログラム


#include <windows.h>

class Hoge {};


template<class T>
class TemplateObjctAccesser {
public:
	T* value;

	TemplateObjctAccesser(){};

	virtual ~TemplateObjctAccesser(){};
};


template<class T>
class TemplateManager {
public:
	TemplateObjctAccesser<T>* accesser;

	TemplateManager(TemplateObjctAccesser<T> * a) {
		accesser = a;
	};
	virtual T* setAccessValue(T* id) {
		return processSetValue(id);
	};
	virtual T* processSetValue(T* id) = 0;
	virtual ~TemplateManager(){};
};

class HogeAccesser : public TemplateObjctAccesser<Hoge> {
public:
	HogeAccesser() : TemplateObjctAccesser<Hoge>() {};
	~HogeAccesser() {};
};

class HogeManager : public TemplateManager<Hoge> {
public:
	HogeManager(HogeAccesser* ac) : TemplateManager<Hoge>(ac) {};
	Hoge* processSetValue(Hoge* hoge) {
		accesser->value = hoge;
		return hoge;
	}
	~HogeManager() {};
};



int main(int argc,char *argv[]) {
	Hoge* h = new Hoge();
	HogeAccesser* hacc = new HogeAccesser();
	HogeManager* manager = new HogeManager(hacc);
	Hoge* x = manager->setAccessValue(h);

	return 0;
}
