#include <iostream>

#include "MyGame.h"

class class1 {
public:
	class1(int i) {
		class1_int = i;
	}

	virtual class1* GetType() = 0;
	virtual void Help() {};

	int class1_int;
};

class class2 : public class1{
public:
	class2(int c) : class1(c) {
		class2_int = 200;
	}

	virtual void Help() override {
		class1_int = 2;
	}

	virtual class1* GetType() {
		return this;
	}

	int class2_int;
};


int main() {


	//class2 myClass = class2(10);
	//class2* myClass2 = dynamic_cast<class2*>(myClass.GetType());




	
	MyGame game = MyGame();
	
	game.CreateEngine(160, 120, 6, 6); // 160, 120
	game.Run();


	system("pause");
	return 0;
}
