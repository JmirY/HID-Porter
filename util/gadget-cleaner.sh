#gadget-cleaner.sh
#JMIRY

#!bin/bash

# check args
if [ $# == 0 ]; then
    echo "Usage : ./gadget-cleaner.sh [num_of_gadget]"
    exit
fi
# define the number of gadget set (mouse & keyboard)
num_of_gadget=$1

#--------Reusable information---------
subsys_path="/config/usb_gadget"

#--------clean up gadget mouse--------
i=1
while [ $i -le ${num_of_gadget} ]
do
    g_mouse_path="${subsys_path}/g_mouse$i"
    echo "" > "${g_mouse_path}/UDC"
    rmdir "${g_mouse_path}/strings/0x409"

    rm "${g_mouse_path}/configs/c.1/hid.usb0"
    rmdir "${g_mouse_path}/configs/c.1/strings/0x409"
    rmdir "${g_mouse_path}/configs/c.1"
    rmdir "${g_mouse_path}/functions/hid.usb0"
    rmdir "${g_mouse_path}"
    
    i=$(expr $i + 1)
done

#------clean up gadget keyboard-------
i=1
while [ $i -le ${num_of_gadget} ]
do
    g_kbd_path="${subsys_path}/g_kbd$i"
    echo "" > "${g_kbd_path}/UDC"
    rmdir "${g_kbd_path}/strings/0x409"

    rm "${g_kbd_path}/configs/c.1/hid.usb0"
    rmdir "${g_kbd_path}/configs/c.1/strings/0x409"
    rmdir "${g_kbd_path}/configs/c.1"
    rmdir "${g_kbd_path}/functions/hid.usb0"
    rmdir "${g_kbd_path}"

    i=$(expr $i + 1)
done