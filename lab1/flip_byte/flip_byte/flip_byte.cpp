#include "stdafx.h"
#include "flip_byte_utils.h"

using namespace std;

int main(int argc, char * argv[])
{
	if (!CheckInput(argc, argv))
	{
		return 1;
	}
	unsigned char processedNumber = stoi(argv[1], nullptr);
	unsigned char flipedNumber = FlipByte(processedNumber);
	cout << static_cast<int> (flipedNumber) << endl;
	cout << "(" << static_cast<int> (processedNumber) << "(10) = " << bitset<8>(processedNumber) << "(2)";
	cout << ", ����� ��������� ������� ����� ������ ����� ����������� � ";
	cout << "(" << bitset<8>(flipedNumber) << "(2)) = " << static_cast<int> (flipedNumber) << "(10))" << endl;
    return 0;
}

