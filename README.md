# StarShell

![License](https://img.shields.io/badge/license-MIT-blue.svg)

**StarShell** is a simple implementation of a Unix-like shell in C. It provides basic shell functionality and includes features such as command history, process tracking, and support for various built-in commands.

## Table of Contents

- [Features](#features)
- [Getting Started](#getting-started)
  - [Prerequisites](#prerequisites)
  - [Building](#building)
  - [Running](#running)
- [Usage](#usage)
- [Command History](#command-history)
- [Built-in Commands](#built-in-commands)
- [Contributing](#contributing)
- [License](#license)

## Features

- Basic command execution
- Built-in commands (`ls`, `cd`, `rmdir`, `mkdir`, `rm`, `touch`, `cp`, `history`, `exit`, `quit`)
- Command history with recall (up to 15 commands)
- Process tracking with associated PIDs
- Support for running external programs in `/bin`, `/usr/bin`, and `/usr/local/bin`

## Getting Started

### Prerequisites

To build and run **StarShell**, you will need:

- GCC (GNU Compiler Collection)
- Unix-like operating system (Linux preferred)

### Building

Clone the repository and navigate to the project directory:

```bash
git clone https://github.com/pxs4528/shell
```

Compile the shell using the provided Makefile:

```bash
make
```

### Running

To start the shell, simply run the compiled binary:

```bash
./msh
```

## Usage

Once the shell is running, you can enter commands as you would in a regular Unix shell. Here are some examples:

```bash
ls -l              # List files in the current directory
cd /path/to/dir    # Change directory
mkdir mydir        # Create a directory
rm myfile.txt      # Remove a file
history            # Display command history
exit               # Exit the shell
```

## Command History

**StarShell** keeps track of the last 15 commands entered. You can use the `history` command to view the command history. To recall a specific command from history, use `!n`, where `n` is the command number from the history list.

## Built-in Commands

The shell includes several built-in commands for convenience:

- `ls`: List files in the current directory.
- `cd`: Change the current working directory.
- `rmdir`: Remove a directory.
- `mkdir`: Create a directory.
- `rm`: Remove a file.
- `touch`: Create an empty file.
- `cp`: Copy files or directories.
- `history`: Display command history.
- `exit`/`quit`: Exit the shell.

## Contributing

Contributions are welcome! If you find a bug or have an improvement in mind, please open an issue or create a pull request.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

---

**StarShell** is developed and maintained by Parth Sharma(https://github.com/pxs4528).
