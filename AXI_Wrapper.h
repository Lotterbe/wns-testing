class AXI_Wrapper
{
        private:
                uint32_t base;
                uint32_t *MappedBase;
                int fd;


                int openDevMem(void)
                {
                        int fd = open("/dev/mem",O_RDWR|O_SYNC);
                        if(fd < 0)
                        {
                                printf("Can't open /dev/mem\n");
                        }
                        return fd;
                }

        public:
                AXI_Wrapper(uint32_t baseAddr)
                {
                        base = baseAddr;
                        int fd = openDevMem();
                        MappedBase = (uint32_t *) mmap(NULL, 256*1024, PROT_READ|PROT_WRITE, MAP_SHARED, fd, base);
                        if(MappedBase == NULL)
                        {
                                printf("Can't mmap :(\n");
                        }
                }

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
                                printf("Warning: Address did fully not assume the given value.\n");
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
};

