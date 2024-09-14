# Multi-threaded Slowloris Attack Tool

A multi-threaded Slowloris attack tool designed to overwhelm web servers by sending a flood of incomplete HTTP requests, keeping connections alive and consuming server resources. This tool allows users to specify the number of threads to increase the effectiveness of the attack.

⚠️ **Important:** This tool is for educational and authorized network testing **only**. Unauthorized use is illegal and unethical.

## Features
- Sends partial HTTP headers to the target web server.
- Multi-threaded for increased speed and efficiency.
- User-friendly CLI for packet customization.
- Signal handling (Ctrl+C) to stop the attack gracefully.

## Requirements
- C compiler (GCC recommended)
- Root/Administrator privileges (required for raw sockets)

## Compilation

To compile the program, ensure you have `gcc` installed, then run:

```bash
gcc -o slowloris slowloris.c -lpthread
```

# Usage

To run the tool, you need to have root or administrator privileges. Example usage:

```bash
sudo ./slowloris
```

You will be prompted to enter:

   - The remote host's IP address.
   - The number of threads to use for the attack.

# Example

```
Enter the remote host's IP address: 192.168.1.100
Enter the number of threads to use: 10
```

The tool will then start sending incomplete HTTP requests to the target.

# Ethical Considerations

This tool should only be used in controlled environments where you have explicit permission from the network owner. Unauthorized usage can lead to serious legal consequences.

# License

This project is licensed under the MIT License. See the LICENSE file for details.

# Disclaimer

This software is provided "as-is" without any warranties. The author is not responsible for any damages caused by the misuse of this tool.
