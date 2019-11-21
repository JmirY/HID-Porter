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

#-----Random product id generator-----
# generate random product id
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

# check if 'id' is duplicated
# param 1: id, param 2: array
function is_dup()
{
    id=$1; shift; arr=$@
    for element in ${arr[@]}
    do
        if [ "${element}" == "${id}" ]; then
            echo "true"; return
        fi
    done
    echo "false"
}

# create random product ids
arr_size=$(expr ${num_of_gadget} \* 2)
product_ids=()

i=0
while [ ${i} -lt ${arr_size} ]
do
    # make 4-digit-id
    id=$(generate_id)
    while [ $(is_dup ${id} ${product_ids[@]}) == "true" ]
    do
        id=$(generate_id)
    done
    product_ids[$i]=${id}
    i=$(($i+1))
done
#--------Reusable information---------

prog_path=$(dirname $0)
subsys_path="/config/usb_gadget"
# device info
vendor_id="0x1717"
config_name="g_conf"
# function info
mouse_desc="${prog_path}/mouse_desc.bin"
kbd_desc="${prog_path}/kbd_desc.bin"

#---------create gadget mouse---------
i=1
while [ $i -le ${num_of_gadget} ]
do
    g_mouse_path="${subsys_path}/g_mouse$i"
    mkdir "${g_mouse_path}"

    # fill device info
    echo ${vendor_id} > "${g_mouse_path}/idVendor"
    echo ${mouse1_product_id} > "${g_mouse_path}/idProduct"
    mkdir "${g_mouse_path}/strings/0x409"
    echo "XS" > "${g_mouse_path}/strings/0x409/manufacturer"
    echo "Gadget Mouse"$i > "${g_mouse_path}/strings/0x409/product"
    echo "xsgadget" > "${g_mouse_path}/strings/0x409/serialnumber"

    # fill configuration info
    mkdir "${g_mouse_path}/configs/c.1"
    mkdir "${g_mouse_path}/configs/c.1/strings/0x409"
    echo "${config_name}" > "${g_mouse_path}/configs/c.1/strings/0x409/configuration"

    # fill function info
    mkdir "${g_mouse_path}/functions/hid.usb0"
    echo "2" > "${g_mouse_path}/functions/hid.usb0/protocol"
    echo "1" > "${g_mouse_path}/functions/hid.usb0/subclass"
    echo "4" > "${g_mouse_path}/functions/hid.usb0/report_length"
    cat "${mouse_desc}" > "${g_mouse_path}/functions/hid.usb0/report_desc"

    # create symbolic link of function
    ln -s "${g_mouse_path}/functions/hid.usb0" "${g_mouse_path}/configs/c.1"

    i=$(($i+1))
done

#-------create gadget keyboard--------
i=1
while [ $i -le ${num_of_gadget} ]
    g_kbd_path="${subsys_path}/g_kbd$i"
    mkdir "${g_kbd_path}"

    # fill device info
    echo ${vendor_id} > "${g_kbd_path}/idVendor"
    echo ${kbd1_product_id} > "${g_kbd_path}/idProduct"
    mkdir "${g_kbd_path}/strings/0x409"
    echo "XS" > "${g_kbd_path}/strings/0x409/manufacturer"
    echo "Gadget KBD"$i > "${g_kbd_path}/strings/0x409/product"
    echo "xsgadget" > "${g_kbd_path}/strings/0x409/serialnumber"

    # fill configuration info
    mkdir "${g_kbd_path}/configs/c.1"
    mkdir "${g_kbd_path}/configs/c.1/strings/0x409"
    echo "${config_name}" > "${g_kbd_path}/configs/c.1/strings/0x409/configuration"

    # fill function info
    mkdir "${g_kbd_path}/functions/hid.usb0"
    echo "1" > "${g_kbd_path}/functions/hid.usb0/protocol"
    echo "1" > "${g_kbd_path}/functions/hid.usb0/subclass"
    echo "8" > "${g_kbd_path}/functions/hid.usb0/report_length"
    cat "${kbd_desc}" > "${g_kbd_path}/functions/hid.usb0/report_desc"

    # create symbolic link of function
    ln -s "${g_kbd_path}/functions/hid.usb0" "${g_kbd_path}/configs/c.1"
done