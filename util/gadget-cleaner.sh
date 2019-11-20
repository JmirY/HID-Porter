#gadget-cleaner.sh
#JMIRY

#!bin/bash

subsys_path="/config/usb_gadget"
g_mouse_name="g_mouse"
g_kbd_name="g_kbd"
g_mouse_path="${subsys_path}/${g_mouse_name}"
g_kbd_path="${subsys_path}/${g_kbd_name}"

#-----clean up gadget mouse-----
echo "" > "${g_mouse_path}/UDC"
rmdir "${g_mouse_path}/strings/0x409"

rm "${g_mouse_path}/configs/c.1/hid.usb0"
rmdir "${g_mouse_path}/configs/c.1/strings/0x409"
rmdir "${g_mouse_path}/configs/c.1"
rmdir "${g_mouse_path}/functions/hid.usb0"
rmdir "${g_mouse_path}"

#-----clean up gadget keyboard-----
echo "" > "${g_kbd_path}/UDC"
rmdir "${g_kbd_path}/strings/0x409"

rm "${g_kbd_path}/configs/c.1/hid.usb0"
rmdir "${g_kbd_path}/configs/c.1/strings/0x409"
rmdir "${g_kbd_path}/configs/c.1"
rmdir "${g_kbd_path}/functions/hid.usb0"
rmdir "${g_kbd_path}"