#include <cerrno>
#include <cstdint>
#include <cstring>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>
#include <system_error>

#include "i2c_master.h"

namespace i2c {
	i2c_master::i2c_master(std::string & devname, const unsigned short int slave_addr) {
		i2c_master(devname.c_str(), slave_addr);
	}

	i2c_master::i2c_master(const char * devname, const unsigned short int slave_addr) {
		/* attempt to open interface */
		if ((this->fd = open(devname, O_RDWR)) < 0) {
			throw std::system_error(std::error_code(errno, std::system_category()), "Error opening interface");
		}
		this->set_slave_addr(slave_addr);
	}

	i2c_master::~i2c_master() {
		close(this->fd);
	}

	void i2c_master::set_slave_addr(const unsigned short int slave_addr) {
		this->slave_addr = (uint8_t)(slave_addr);
		if (ioctl(this->fd, I2C_SLAVE, this->slave_addr) < 0) {
			throw std::system_error(std::error_code(errno, std::system_category()), "Error setting slave address");
		}
	}

	void i2c_master::write_bytes(i2c::data data, const unsigned short int addr) {
		data.insert(data.begin(), (uint8_t)(addr));
		if ((unsigned)write(this->fd, data.data(), data.size()) != data.size()) {
			throw std::system_error(std::error_code(errno, std::system_category()), "Error writing to slave");
		}
	}

	i2c::data i2c_master::read_bytes(const unsigned short int count, const unsigned short int addr) {
		i2c::data buf(count);

		this->write_bytes(i2c::data(0), addr);
		if (read(this->fd, buf.data(), count) != count) {
			throw std::system_error(std::error_code(errno, std::system_category()), "Error reading from slave");
		}
		return buf;
	}
}
