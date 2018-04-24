#ifndef AXI_WRAPPER_H
#define AXI_WRAPPER_H

#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <unistd.h>

class AXI_Wrapper
{
        private:
                uint32_t base;
                uint32_t *MappedBase;
                int fd = 0;


                int openDevMem(void)
                {
                        fd = open("/dev/mem",O_RDWR|O_SYNC);
                        return fd;
                }


        public:
                AXI_Wrapper(uint32_t baseAddr)
                {
                        base = baseAddr;
                        fd = openDevMem();
                        if(fd < 0)
                        {
                            std::cout << "Can't open /dev/mem" << std::endl;
                            //printf("Can't open /dev/mem\n");
                        }
                        else
                        {
                            MappedBase = (uint32_t *) mmap(NULL, 256*1024, PROT_READ|PROT_WRITE, MAP_SHARED, fd, base);
                            if(MappedBase == NULL)
                            {
                                //printf("Can't mmap :(\n");
                                std::cout << "Can't mmap :(" << std::endl;
                            }
                        }
                }

                ~AXI_Wrapper();

                uint32_t read(uint32_t offset)
                {
                        uint32_t value = *(MappedBase + (((unsigned int)offset)>>2));
                        return value;
                }

                int write(uint32_t offset, uint32_t value)
                {
                        *(MappedBase + (((unsigned int)offset)>>2)) = value;
                        if(*(MappedBase + (((unsigned int)offset)>>2)) == value)
                        {
                                return 0;
                        }
                        else
                        {
                                //printf("Warning: Address did fully not assume the given value. The assumed value is: %x\n", *(MappedBase + (((unsigned int)offset)>>2)));
                                std::cout << "Warning: Address did fully not assume the given value. The assumed value is: %x" << std::endl;
                                std::cout << *(MappedBase + (((unsigned int)offset)>>2)) << std::endl;
                                return 1;
                        }
                }

                uint32_t getBaseAddr(void)
                {
                        return base;
                }

                int setBaseAddr(uint32_t baseAddr)
                {
                        base = baseAddr;
                        return 0;
                }
                int getFD()
                {
                    return fd;
                }
};


#endif // AXI_WRAPPER_H
