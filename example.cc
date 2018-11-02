#include <iostream>
#include <cstdint>

#include "i2c_master.h"

int main() {
	i2c::i2c_master interface("/dev/i2c-0", 0x28);
	i2c::data testData(16);
	for (int i = 16; i > 0; i--)
		testData[(16 - i)] = i;
	interface.write_bytes(testData, 0x00);
	testData = interface.read_bytes(16);
	for (size_t i = 0; i < testData.size(); i++)
		std::cout << "testData[" << std::dec << i << "] = 0x" << std::hex << (unsigned short int)testData[i] << std::endl;
	return 0;
}
