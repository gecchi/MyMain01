// 固定アニメーションテストサンプルプログラム


#include <windows.h>


//enum class day_of_week {SUNDAY, MONDAY, TUESDAY, WEDNESDAY, THURSDAY, FRYDAY, SATURDAY};
enum day_of_week2 {day_of_week, SUNDAY2, MONDAY2, TUESDAY2, WEDNESDAY2, THURSDAY2, FRYDAY2, SATURDAY2};

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
	//day_of_week2 today = 1;today->
	return 0;
}
