
# final_proj

This project is developed based on the Linux Ubuntu environment and uses GTK as an extension for UI development.

You are strongly recommended to compile the source code in the Ubuntu environment and install GTK before compiling.

## Table of Contents

- [Installing a Virtual Machine for Linux Ubuntu](#installing-a-virtual-machine-for-linux-ubuntu)
- [Installing GTK](#installing-gtk)

## Installing a Virtual Machine for Linux Ubuntu

To set up a virtual machine for Linux Ubuntu, follow these steps:

1. Download a virtualization software such as [VirtualBox](https://www.virtualbox.org/) or [VMware Player](https://www.vmware.com/products/workstation-player.html).
2. Install the virtualization software on your computer by following the provided instructions.
3. Download the Linux Ubuntu ISO file from the official website ([https://ubuntu.com/download](https://ubuntu.com/download)). Choose the appropriate version based on your system architecture (32-bit or 64-bit).
4. Launch the virtualization software and create a new virtual machine.
5. Configure the virtual machine settings, such as the allocated memory and storage space. Assign at least 2 GB of RAM for smooth operation.
6. During the virtual machine creation process, choose to install the Linux Ubuntu ISO file you downloaded earlier as the operating system for the virtual machine.
7. Follow the installation wizard to complete the Linux Ubuntu installation process within the virtual machine.

Now you have a virtual machine running Linux Ubuntu. You can proceed to install GTK for UI development.

## Installing GTK

GTK is a widely used toolkit for creating graphical user interfaces (GUI) in Linux. To install GTK in your Linux Ubuntu virtual machine, perform the following steps:

1. Launch the terminal in the Linux Ubuntu virtual machine.
2. Update the package lists and upgrade the existing packages by running the following commands:

```bash
sudo apt update
sudo apt upgrade
```

3. Install the necessary packages for GTK development:

```bash
sudo apt install libgtk-3-dev
```

4. After the installation is complete, you can verify the installation by checking the GTK version:

```bash
pkg-config --modversion gtk+-3.0
```

This command should display the version number of GTK installed on your system.

Now you have successfully installed GTK in your Linux Ubuntu virtual machine. You can proceed with compiling and running the source code of the `final_proj` project.
