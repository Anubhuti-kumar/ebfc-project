package main

import (
	"fmt"
	"os"
	"os/exec"
)

func main() {
	// Compile eBPF program
	compileCmd := exec.Command("clang", "-O2", "-target", "bpf", "-c", "ebpf/tcp_drop_port.c", "-o", "ebpf/tcp_drop_port.o")
	compileCmd.Stdout = os.Stdout
	compileCmd.Stderr = os.Stderr
	if err := compileCmd.Run(); err != nil {
		fmt.Fprintf(os.Stderr, "Error compiling eBPF program: %v\n", err)
		os.Exit(1)
	}

	// Load eBPF program
	loadCmd := exec.Command("sudo", "ip", "link", "set", "dev", "lo", "xdpgeneric", "obj", "ebpf/tcp_drop_port.o", "sec", "filter")
	loadCmd.Stdout = os.Stdout
	loadCmd.Stderr = os.Stderr
	if err := loadCmd.Run(); err != nil {
		fmt.Fprintf(os.Stderr, "Error loading eBPF program: %v\n", err)
		os.Exit(1)
	}

	fmt.Println("eBPF program loaded successfully!")

	// Keep the program running
	fmt.Println("Press Ctrl+C to exit...")
	select {}
}
