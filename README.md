# final_proj

## Introduction

Our project is a basketball player management system that allows users to manage and organize basketball player information.

This project is developed based on the Linux Ubuntu environment and uses GTK as an extension for UI development.

You are strongly recommended to compile the source code in the Ubuntu environment and install GTK before compiling.

## Table of Contents

- [final\_proj](#final_proj)
  - [Introduction](#introduction)
  - [Table of Contents](#table-of-contents)
  - [Environment Setup](#environment-setup)
    - [Installing a Virtual Machine for Linux Ubuntu](#installing-a-virtual-machine-for-linux-ubuntu)
    - [Installing GTK](#installing-gtk)
  - [Features](#features)
    - [Login System](#login-system)
      - [User Registration](#user-registration)
      - [User Login](#user-login)
    - [Player Information Management](#player-information-management)
      - [Add Player](#add-player)
      - [Edit Player Information](#edit-player-information)
      - [Delete Player](#delete-player)
      - [Sort Players](#sort-players)
      - [View All Players](#view-all-players)
      - [Search Player](#search-player)
  - [Remind](#remind)

## Environment Setup

To set up the project environment, please follow the instructions below:

1. Install the Linux Ubuntu operating system on your computer. Refer to the [Installing a Virtual Machine for Linux Ubuntu](https://chat.openai.com/c/b64a15ff-f9bc-420d-8f95-bd0b448c4f98#installing-a-virtual-machine-for-linux-ubuntu) section for detailed instructions.
2. Install GTK for UI development. Refer to the [Installing GTK](https://chat.openai.com/c/b64a15ff-f9bc-420d-8f95-bd0b448c4f98#installing-gtk) section for detailed instructions.

### Installing a Virtual Machine for Linux Ubuntu

To set up a virtual machine for Linux Ubuntu, follow these steps:

1. Download a virtualization software such as [VirtualBox](https://www.virtualbox.org/) or [VMware Player](https://www.vmware.com/products/workstation-player.html).
2. Install the virtualization software on your computer by following the provided instructions.
3. Download the Linux Ubuntu ISO file from the official website ([https://ubuntu.com/download](https://ubuntu.com/download)). Choose the appropriate version based on your system architecture (32-bit or 64-bit).
4. Launch the virtualization software and create a new virtual machine.
5. Configure the virtual machine settings, such as the allocated memory and storage space. Assign at least 2 GB of RAM for smooth operation.
6. During the virtual machine creation process, choose to install the Linux Ubuntu ISO file you downloaded earlier as the operating system for the virtual machine.
7. Follow the installation wizard to complete the Linux Ubuntu installation process within the virtual machine.

Now you have a virtual machine running Linux Ubuntu. You can proceed to install GTK for UI development.

### Installing GTK

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

Now you have successfully installed GTK in your Linux Ubuntu virtual machine. You can proceed with compiling the source code of the `final_proj` project.

## Features

### Login System

#### User Registration

The user registration functionality allows new users to create an account within the system. They can provide their desired username and password, which will be securely stored in the system's hash table for future authentication.

#### User Login

The user login functionality enables registered users to log in to the system using their credentials. Upon successful login, users gain access to their account and the associated features and data.

### Player Information Management

#### Add Player

The "Add Player" functionality allows users to add new players to their respective teams. Users can provide details such as the player's name, position, and statistics, which will be stored in the linked list structure.

#### Edit Player Information

The "Edit Player Information" functionality enables users to modify the information of existing players within their teams. They can update player details such as position, statistics, or any other relevant information.

#### Delete Player

The "Delete Player" functionality allows users to remove players from their teams. Users can select the player they want to delete, and the system will remove the corresponding player's information from the linked list.

#### Sort Players

The "Sort Players" functionality allows users to sort players within their teams or across all teams based on specific criteria. They can choose to sort players by name, scoring rate, or any other relevant statistics. This functionality helps in organizing and comparing player data.

#### View All Players

The "View All Players" functionality allows users to see the player information for all teams in the system. It provides a comprehensive view of all players, their respective teams, and their details, facilitating easy access to information across teams.

#### Search Player

The "Search Player" functionality allows users to search for specific players by entering their names. Users can input the exact player name they are looking for, and the system will retrieve the corresponding player's information, providing a convenient way to find specific players within the system.

## Remind

This project is developed based on the Linux Ubuntu environment and uses GTK as an extension for UI development.

You are strongly recommended to compile the source code in the Ubuntu environment and install GTK before compiling.
