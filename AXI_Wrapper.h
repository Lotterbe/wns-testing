#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <vector>

class AXI_Wrapper
{
        private:
                uint32_t base, length;
				uint32_t *MappedBase32;
                void *MappedBase;
				std::vector<uint32_t> Emu_data;
                int fd;
				bool emu, fd_open, mapped;

				int openDevMem(void);

        public:
                AXI_Wrapper();
				AXI_Wrapper(uint32_t Length);
                
				int Init(uint32_t baseAddr);
				int Init_Emu(uint32_t baseAddr);
				int unmap();
				
                uint32_t read(uint32_t offset);
                int write(uint32_t offset, uint32_t value);

                uint32_t getBaseAddr(void);
				bool is_mapped(void);
				bool dev_mem_open(void);
};

