#ifndef __I2C_MASTER_H__
#define __I2C_MASTER_H__

#include <cstdint>
#include <vector>

namespace i2c {
	using data = std::vector<uint8_t>;

	class i2c_master {
		public:
			i2c_master(std::string & devname, const unsigned short int slave_addr);
			i2c_master(const char * devname, const unsigned short int slave_addr);
			~i2c_master();
			void set_slave_addr(const unsigned short int slave_addr);
			void write_bytes(i2c::data data, const unsigned short int addr = 0x00);
			i2c::data read_bytes(const unsigned short int count, const unsigned short int addr = 0x00);
		private:
			int fd;
			uint8_t slave_addr;
	};
}

#endif
