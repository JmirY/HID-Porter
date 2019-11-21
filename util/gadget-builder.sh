#gadget-builder.sh
#JMIRY

#!bin/bash

### Prerequisite
# User must mounts configfs on / dir.
# Kernel module 'libcomposite' has to be loaded,
# then subsystem directory 'usb_gadget' will be appeared
### After execution
# Input dummy HCD instance's name to /configfs/{gadget}/UDC
# ex) echo dummy_udc.0 > UDC
# To check dummy HCD instances, $(ls /sys/class/udc)

# USER MUST DEFINE THIS VARIABLE
# define the number of gadget set (mouse & keyboard)
num_of_gadget=2

# functions
function generate_id()
{
    MIN=999
    MAX=10000
    id=0
    while [ ${id} -le ${MIN} ]
    do
        id=${RANDOM}
        id=`expr ${id} % ${MAX}`
    done
    echo ${id}
}

# create random product ids
arr_size=$(expr ${num_of_gadget} \* 2)
product_ids=()

i=0
while [ ${i} -lt ${arr_size} ]
do
    # make 4-digit-id
    id=$(generate_id)
    product_ids[$i]=${id}
    i=$(($i+1))
done

prog_path=$(dirname $0)
subsys_path="/config/usb_gadget"
# device info
vendor_id="0x1717"
config_name="g_conf"
# function info
mouse_desc=${prog_path}"/mouse_desc.bin"
kbd_desc=${prog_path}"/kbd_desc.bin"

#-----create gadget mouse1-----
g_mouse_path=${subsys_path}"/g_mouse1"
mkdir ${g_mouse_path}

# fill device info
echo ${vendor_id} > ${g_mouse_path}"/idVendor"
echo ${mouse1_product_id} > ${g_mouse_path}"/idProduct"
mkdir ${g_mouse_path}"/strings/0x409"
echo "XS" > ${g_mouse_path}"/strings/0x409/manufacturer"
echo "Gadget Mouse1" > ${g_mouse_path}"/strings/0x409/product"
echo "xsgadget" > ${g_mouse_path}"/strings/0x409/serialnumber"

# fill configuration info
mkdir ${g_mouse_path}"/configs/c.1"
mkdir ${g_mouse_path}"/configs/c.1/strings/0x409"
echo ${config_name} > ${g_mouse_path}"/configs/c.1/strings/0x409/configuration"

# fill function info
mkdir ${g_mouse_path}"/functions/hid.usb0"
echo "2" > ${g_mouse_path}"/functions/hid.usb0/protocol"
echo "1" > ${g_mouse_path}"/functions/hid.usb0/subclass"
echo "4" > ${g_mouse_path}"/functions/hid.usb0/report_length"
cat ${mouse_desc} > ${g_mouse_path}"/functions/hid.usb0/report_desc"

# create symbolic link of function
ln -s ${g_mouse_path}"/functions/hid.usb0" ${g_mouse_path}"/configs/c.1"

#-----create gadget mouse2-----
g_mouse_path=${subsys_path}"/g_mouse2"
mkdir ${g_mouse_path}

# fill device info
echo ${vendor_id} > ${g_mouse_path}"/idVendor"
echo ${mouse2_product_id} > ${g_mouse_path}"/idProduct"
mkdir ${g_mouse_path}"/strings/0x409"
echo "XS" > ${g_mouse_path}"/strings/0x409/manufacturer"
echo "Gadget Mouse2" > ${g_mouse_path}"/strings/0x409/product"
echo "xsgadget" > ${g_mouse_path}"/strings/0x409/serialnumber"

# fill configuration info
mkdir ${g_mouse_path}"/configs/c.1"
mkdir ${g_mouse_path}"/configs/c.1/strings/0x409"
echo ${config_name} > ${g_mouse_path}"/configs/c.1/strings/0x409/configuration"

# fill function info
mkdir ${g_mouse_path}"/functions/hid.usb0"
echo "2" > ${g_mouse_path}"/functions/hid.usb0/protocol"
echo "1" > ${g_mouse_path}"/functions/hid.usb0/subclass"
echo "4" > ${g_mouse_path}"/functions/hid.usb0/report_length"
cat ${mouse_desc} > ${g_mouse_path}"/functions/hid.usb0/report_desc"

# create symbolic link of function
ln -s ${g_mouse_path}"/functions/hid.usb0" ${g_mouse_path}"/configs/c.1"

#-----create gadget keyboard1-----
g_kbd_path=${subsys_path}"/g_kbd1"
mkdir ${g_kbd_path}

# fill device info
echo ${vendor_id} > ${g_kbd_path}"/idVendor"
echo ${kbd1_product_id} > ${g_kbd_path}"/idProduct"
mkdir ${g_kbd_path}"/strings/0x409"
echo "XS" > ${g_kbd_path}"/strings/0x409/manufacturer"
echo "Gadget KBD1" > ${g_kbd_path}"/strings/0x409/product"
echo "xsgadget" > ${g_kbd_path}"/strings/0x409/serialnumber"

# fill configuration info
mkdir ${g_kbd_path}"/configs/c.1"
mkdir ${g_kbd_path}"/configs/c.1/strings/0x409"
echo ${config_name} > ${g_kbd_path}"/configs/c.1/strings/0x409/configuration"

# fill function info
mkdir ${g_kbd_path}"/functions/hid.usb0"
echo "1" > ${g_kbd_path}"/functions/hid.usb0/protocol"
echo "1" > ${g_kbd_path}"/functions/hid.usb0/subclass"
echo "8" > ${g_kbd_path}"/functions/hid.usb0/report_length"
cat ${kbd_desc} > ${g_kbd_path}"/functions/hid.usb0/report_desc"

# create symbolic link of function
ln -s ${g_kbd_path}"/functions/hid.usb0" ${g_kbd_path}"/configs/c.1"

#-----create gadget keyboard2-----
g_kbd_path=${subsys_path}"/g_kbd2"
mkdir ${g_kbd_path}

# fill device info
echo ${vendor_id} > ${g_kbd_path}"/idVendor"
echo ${kbd2_product_id} > ${g_kbd_path}"/idProduct"
mkdir ${g_kbd_path}"/strings/0x409"
echo "XS" > ${g_kbd_path}"/strings/0x409/manufacturer"
echo "Gadget KBD2" > ${g_kbd_path}"/strings/0x409/product"
echo "xsgadget" > ${g_kbd_path}"/strings/0x409/serialnumber"

# fill configuration info
mkdir ${g_kbd_path}"/configs/c.1"
mkdir ${g_kbd_path}"/configs/c.1/strings/0x409"
echo ${config_name} > ${g_kbd_path}"/configs/c.1/strings/0x409/configuration"

# fill function info
mkdir ${g_kbd_path}"/functions/hid.usb0"
echo "1" > ${g_kbd_path}"/functions/hid.usb0/protocol"
echo "1" > ${g_kbd_path}"/functions/hid.usb0/subclass"
echo "8" > ${g_kbd_path}"/functions/hid.usb0/report_length"
cat ${kbd_desc} > ${g_kbd_path}"/functions/hid.usb0/report_desc"

# create symbolic link of function
ln -s ${g_kbd_path}"/functions/hid.usb0" ${g_kbd_path}"/configs/c.1"