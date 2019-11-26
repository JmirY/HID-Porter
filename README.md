# HID-Porter
### Virtual KM switch for Linux-hosted VMs.
### User can send mouse/keyboard input to VM selectively.
---
## Prerequisites  
- Configfs  
    This file system has to be mounted somewhere.  
    Recent linux kernel already mounts configfs at ***/sys/kernel/config*** .  
    However,  
    ***/config*** is recommended as mount point.  
    > Gadget-builder script consider ***/config*** as mount point of configfs by default.  
    User can change it by editing ***util/gadget-builder.sh***

- Linux kernel module   
    - dummy_hcd  
        > The maximum number of dummy HCD can be created is 2 by default.  
          Should change module source to expand limit.  
  
      Following three modules need to be recompiled if user want to link more than 2 VMs.
    - udc_core
    - libcomposite 
    - usb_f_hid  
        A variable in this file defines the max number of HID gadgets can be created.  
        Default value is 4.  So user has to modify this value to expand the limit.
            
***Configfs*** and module ***dummy_hcd*** may be disbaled for default kernel user.  
User should edit kernel configuration to enable those.  

## How to Build  
Use ***g++*** with ***-pthread*** option
```bash
$ g++ -o HID-Porter < src > -pthread
```

## How to Use  
```bash
# run as root user
$ sudo ./HID-Porter
<<<<< HID-Porter >>>>>
# input host HID node path
--> Input info about host
--> Mouse device node : /dev/hidraw0
--> Keyboard device node : /dev/hidraw1
--> How many VMs want to attach? (up to 9): 2
# HID-Porter will find gadget node automatically
# As HID-Porter initiated properly,
# message will be printed as below
--> Porters are working :)
```
Use ***Alt + "number key"*** to switch active system.  
As an example,  
Alt + 1  ->  Host  
Alt + 2  ->  Guest no.1  
Alt + 3  ->  Guest no.2  
. . .  
  
Send SIGINT ( Ctrl + C ) to stop the program.