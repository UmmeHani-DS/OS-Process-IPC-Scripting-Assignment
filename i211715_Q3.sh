#!/bin/bash

user()
{
    echo ""

    #Taking user and pass input
    read -p "Enter username: " username
    read -p "Enter password: " pass

    #Creating user
    sudo useradd -m -p "$pass" "$username"
    echo "User Created"

    #Assigning user priveleges
    echo "Granting Admin Priveleges"
    sudo usermod -aG sudo "$username"
    echo "Admin previleges have been assigned"
}

diplay_apps()
{
    echo ""
    echo "Diplay Installed apps"
    apt list --installed
}

Dropbox()
{
    echo ""
    echo "Dropbox is being installed"
    cd Downloads/
    sudo apt-get update
    sudo apt install nautilus-dropbox
    echo "Dropbox has been Installed"

}

change_settings()
{
    echo ""
    echo "Changing IP Settings"
    ip addr show
    sudo ip addr add 10.0.0.1/24 dev eth0
    ip addr show
    
    echo "Changing Gateway"
    sudo ip route add default via 10.0.0.254
    nameserver 8.8.8.8 
    nameserver 8.8.4.4
    sudo sed -i 's/nameserver.*/nameserver 8.8.8.8/' /etc/resolv.conf
    echo "IP configuration is now set."
}

display_help()
{
    echo ""

    echo "Help Menu For Commands And Process"

    echo "-uc to create a new user and assign administrator privileges"

    echo "-ld to list installed applications"

    echo "-ins to install Dropbox"

    echo "-ipcon to change IP settings for this user"

    echo "-help to display help again"    

    echo "-e to exit"    
}


echo ""

echo "21i-1715 - UMM E HANI"

echo "Enter -help to display commands: "

read choice

while :
do
    case $choice in

    -uc) user;;

    -ld) diplay_apps;;

    -ins) Dropbox;;

    -ipcon) change_settings;;

    -help) display_help;;

    -e) exit 0;;

    *) echo "Invalid option. Use --help for usage information.";;

    esac

    echo ""
    
    echo "Enter command: "

    read choice

done