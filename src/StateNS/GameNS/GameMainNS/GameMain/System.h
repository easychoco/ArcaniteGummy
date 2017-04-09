#pragma once

#include <string>
#include <vector>



namespace StateNS {
namespace GameNS {

namespace GameMainNS{

class Child;

class System
{
public:
	System();
	~System();
	void initialize();
	void update();
	void draw() const;

private:

};




}
}
}