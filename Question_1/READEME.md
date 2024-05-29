Prerequisites:
Linux Environment: Ensure you have a Linux environment available, either a physical machine, virtual machine, or a Linux-based development environment like WSL (Windows Subsystem for Linux).

Git: Install Git on your local system to clone the repository from GitHub.

Clang and LLVM: Install Clang and LLVM on your Linux system. You can do this using the package manager of your Linux distribution. For example, on Ubuntu:

RUn code -->
sudo apt-get update
sudo apt-get install clang llvm

Installation:

Clone the repository from GitHub to your local system: git clone https://github.com/your_username/ebpf-project.git
Navigate to the Project Directory: cd Question_1

Running the Code

Compile eBPF Program:
Run the following command to compile the eBPF program (tcp_drop_port.c): go run .

Loading eBPF Program:
The program will compile the eBPF program and attempt to load it using the ip command with xdpgeneric. Make sure you have sufficient privileges to execute sudo commands.

Verify Successful Loading:
If the eBPF program is loaded successfully, you will see the message "eBPF program loaded successfully!".

Keep the Program Running:
The program will continue running, waiting for you to exit. You can press Ctrl+C to exit the program.

Configuration (Optional):
If you want to configure the port number to drop packets for, you can modify the port variable in the tcp_drop_port.c file. By default, it's set to 4040.

Notes:
Ensure that you are running the code in a Linux environment with sufficient permissions to load eBPF programs using sudo.
If you encounter any errors during compilation or loading of the eBPF program, refer to the error messages for troubleshooting.
