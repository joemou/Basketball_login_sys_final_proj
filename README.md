# final_proj

This project is developed based on linux ubuntu environment and used GTK as extension for UI development.

You are strongly recommended to compile the source code in ubuntu environment and install GTK before compile.

Following are some instructions for installing a virtual machine for linux ubuntu and GTK.

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

<pre><div class="bg-black rounded-md mb-4"><div class="flex items-center relative text-gray-200 bg-gray-800 px-4 py-2 text-xs font-sans justify-between rounded-t-md"><span>bash</span><button class="flex ml-auto gap-2"><svg stroke="currentColor" fill="none" stroke-width="2" viewBox="0 0 24 24" stroke-linecap="round" stroke-linejoin="round" class="h-4 w-4" height="1em" width="1em" xmlns="http://www.w3.org/2000/svg"><path d="M16 4h2a2 2 0 0 1 2 2v14a2 2 0 0 1-2 2H6a2 2 0 0 1-2-2V6a2 2 0 0 1 2-2h2"></path><rect x="8" y="2" width="8" height="4" rx="1" ry="1"></rect></svg>Copy code</button></div><div class="p-4 overflow-y-auto"><code class="!whitespace-pre hljs language-bash">sudo apt update
sudo apt upgrade
</code></div></div></pre>

3. Install the necessary packages for GTK development:

<pre><div class="bg-black rounded-md mb-4"><div class="flex items-center relative text-gray-200 bg-gray-800 px-4 py-2 text-xs font-sans justify-between rounded-t-md"><span>bash</span><button class="flex ml-auto gap-2"><svg stroke="currentColor" fill="none" stroke-width="2" viewBox="0 0 24 24" stroke-linecap="round" stroke-linejoin="round" class="h-4 w-4" height="1em" width="1em" xmlns="http://www.w3.org/2000/svg"><path d="M16 4h2a2 2 0 0 1 2 2v14a2 2 0 0 1-2 2H6a2 2 0 0 1-2-2V6a2 2 0 0 1 2-2h2"></path><rect x="8" y="2" width="8" height="4" rx="1" ry="1"></rect></svg>Copy code</button></div><div class="p-4 overflow-y-auto"><code class="!whitespace-pre hljs language-bash">sudo apt install libgtk-3-dev
</code></div></div></pre>

4. After the installation is complete, you can verify the installation by checking the GTK version:

<pre><div class="bg-black rounded-md mb-4"><div class="flex items-center relative text-gray-200 bg-gray-800 px-4 py-2 text-xs font-sans justify-between rounded-t-md"><span>bash</span><button class="flex ml-auto gap-2"><svg stroke="currentColor" fill="none" stroke-width="2" viewBox="0 0 24 24" stroke-linecap="round" stroke-linejoin="round" class="h-4 w-4" height="1em" width="1em" xmlns="http://www.w3.org/2000/svg"><path d="M16 4h2a2 2 0 0 1 2 2v14a2 2 0 0 1-2 2H6a2 2 0 0 1-2-2V6a2 2 0 0 1 2-2h2"></path><rect x="8" y="2" width="8" height="4" rx="1" ry="1"></rect></svg>Copy code</button></div><div class="p-4 overflow-y-auto"><code class="!whitespace-pre hljs language-bash">pkg-config --modversion gtk+-3.0
</code></div></div></pre>

This command should display the version number of GTK installed on your system.

Now you have successfully installed GTK in your Linux Ubuntu virtual machine. You can proceed with compiling and running the source code of the `final_proj` project.
