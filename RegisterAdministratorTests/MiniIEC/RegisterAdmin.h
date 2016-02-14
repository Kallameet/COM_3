#ifndef REGISTERADMIN_H
#define REGISTERADMIN_H

#include "Object.h"
#include "TACEntry.h"

class RegisterAdmin : public Object 
{
public:
	 int GetRegister();
	 int GetRegister(TACEntry* dacEntry);
	 int AssignRegister(TACEntry* dacEntry);
	 void FreeRegister(int regNum);
};

#endif