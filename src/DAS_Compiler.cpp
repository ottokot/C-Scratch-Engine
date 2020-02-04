#include "DAS.h"
#include "../start_state.cpp"
int main(int argc, char* args[])
{
	DAS_Main(new start_state);
	return 0;
}
