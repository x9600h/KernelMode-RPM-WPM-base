# KernelMode RPM\WPM base 
 
## Describtion 
IOCTL driver and user mode communication base for reading and writing process memory
## Writeup

**A base for reading\writing process memory directly from the Windows kernel.**

**Communication is implemented on IOCTL requests.** 

**This implementation wouldn't bypass any of popular ring0 anti-cheats.**

**To use it for bypassing purposes you should reverse engineering specific programmes that prevent the use of cheats.**

More info: 
https://learn.microsoft.com/en-us/windows-hardware/drivers/kernel/

