#include "AXI_Wrapper.h"


	AXI_Wrapper::AXI_Wrapper(void)
    {
		length = 128*1024;
		emu = false;
		fd_open = false;
		mapped = false;
		base = 0x00000000;
		MappedBase = NULL;
		MappedBase32 = NULL;
		Emu_data.reserve(length/4);
	}
	
	AXI_Wrapper::AXI_Wrapper(uint32_t Length)
    {
		length = Length;
		emu = false;
		fd_open = false;
		mapped = false;
		base = 0x00000000;
		MappedBase = NULL;
		MappedBase32 = NULL;
		Emu_data.reserve(32*1024);
	}


	int AXI_Wrapper::openDevMem(void)
	{
		int fd = open("/dev/mem",O_RDWR|O_SYNC);
		fd_open = true;
		if(fd < 0)
		{
			std::cout << "Error in AXI_Wrapper::openDevMem(void): Can't open /dev/mem\n";
			fd_open = false;
		}
		return fd;
	}


	int AXI_Wrapper::Init(uint32_t baseAddr)
	{
		emu = false;
		if(mapped)
		{
			munmap(MappedBase, length);
			mapped = false;
		}
		
		base = baseAddr;
		fd = openDevMem();
		if(fd_open)
		{
			MappedBase = mmap(NULL, length, PROT_READ|PROT_WRITE, MAP_SHARED, fd, base);
			MappedBase32 = (uint32_t *) MappedBase;
		}
		else
		{
			std::cout << "Error in AXI_Wrapper::Init(uint32_t baseAddr): Can't map, because /dev/mem is not opened." << std::endl;
			return 1;
		}

		if(MappedBase == NULL)
		{
			std::cout << "Error in AXI_Wrapper::Init(uint32_t baseAddr): Can't Map.\n";
			mapped = false;
			return 1;
		}
		else
		{
			std::cout << "Mapping was successful. Or there was an unknown error, in which case: RIP.\n" << std::endl; //Debugging comment
			mapped = true;
			return 0;
		}
	}


	int AXI_Wrapper::Init_Emu(uint32_t baseAddr)
	{
		emu = true;
		if(mapped)
		{
			munmap(MappedBase, length);
			mapped = false;
		}
		for(int i = 0; i < length/4; i++)
		{
			Emu_data.push_back(0x12345678);
		}
		base = baseAddr;
		return 0;
	}


	int AXI_Wrapper::unmap(void)
	{
		if(mapped)
		{
			if(MappedBase == NULL)
			{
				std::cout << "Warning in AXI_Wrapper::unmap(void): Can't unmap, because there is no mapping." << std::endl;
			}
			else
			{
				munmap(MappedBase, length);
			}			
			mapped = false;
		}
		emu = false;
		return 0;
	}


	uint32_t AXI_Wrapper::read(uint32_t offset)
	{
		if(offset > length-1)
		{
			std::cout << "Error in AXI_Wrapper::read(uint32_t offset): Offset ist larger than the mapped area. Returning standard value 0x00000000." << std::endl;
			return 0;
		}
	
		uint32_t value;
		if(mapped)
		{
			value = *(MappedBase32 + (((unsigned int)offset)>>2));
		}
		else if(emu) 
		{
			value = Emu_data.at(((unsigned int)offset)>>2);
		}
		else 
		{
			std::cout << "Error in AXI_Wrapper::read(uint32_t offset): No Mapping initialized. Returning standard value 0x00000000." << std::endl;
			value = 0;
		}
		return value;
	}


	int AXI_Wrapper::write(uint32_t offset, uint32_t value)
	{
		if(offset > length-1)
		{
			std::cout << "Error in AXI_Wrapper::write(uint32_t offset, uint32_t value): Offset ist larger than the mapped area." << std::endl;
			return 1;
		}

		if(mapped)
		{
			*(MappedBase32 + (((unsigned int)offset)>>2)) = value;
			if(*(MappedBase32 + (((unsigned int)offset)>>2)) == value)
			{
				return 0;
			}
			else
			{
				std::cout << "Warning in AXI_Wrapper::write(uint32_t offset, uint32_t value): Address did fully not assume the given value. The assumed value is " << std::hex << *(MappedBase32 + (((unsigned int)offset)>>2)) << "." << std::dec << std::endl;
				return 2;
			}
		}
		else if(emu)
		{
			Emu_data.at(((unsigned int)offset)>>2) = value;
			return 0;
		}
		else 
		{
			std::cout << "Error in AXI_Wrapper::write(uint32_t offset, uint32_t value): No Mapping initialized." << std::endl;
			return 1;
		}
	}


	uint32_t AXI_Wrapper::getBaseAddr(void)
	{
		return base;
	}

	
	bool AXI_Wrapper::is_mapped(void)
	{
		return mapped;
	}
	
	
	bool AXI_Wrapper::dev_mem_open(void)
	{
		return fd_open;
	}
