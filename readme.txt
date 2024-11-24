Simple Shell Program

Description:
This program is a simple interactive shell implemented in C. It allows users to execute Linux commands from a custom command-line interface. The shell searches for the specified command in the system's PATH, executes it in a child process, and returns control to the user after execution.

Features:
- Custom shell prompt: GroupShell$
- Supports basic Linux commands (e.g., ls, pwd, echo, etc.).
- Command parsing and argument handling.
- Searches for executables using the PATH environment variable.
- Executes commands using the execv() system call.
- Exits gracefully when the exit command is issued.

Requirements:
- Linux operating system.
- GCC compiler.
- Basic knowledge of Linux commands.

Usage Instructions:
1. Compile the program:
   gcc -o simple_shell main.c

2. Run the shell:
   ./simple_shell

3. Execute commands:
   - Enter valid Linux commands at the GroupShell$ prompt.
   - Example:
     GroupShell$ ls

4. Exit the shell:
   - Type exit at the prompt to terminate the program.

Limitations:
- Does not support advanced shell features like piping (|) or redirection (> or <).
- Commands must be available in the system's PATH.
- Minimal error handling for malformed inputs.

Code Structure:
- main(): The entry point of the program; handles the shell loop.
- printPrompt(): Displays the shell prompt.
- readCommand(): Reads user input.
- parseCommand(): Parses the input into a structured format.
- parsePath(): Reads the system's PATH and prepares an array of directories.
- lookupPath(): Searches for a command in the directories of PATH.
- execv(): Executes the command in a child process.

Acknowledgments:
By: Group 27 [ Naman Subedi (L20615286) and Vijender Reddy Sirrapu (L20610709) ]
This program is developed as part of the COSC 4302 Operating Systems course group project.
We extend our heartfelt gratitude to Dr. Bo Sun for giving us the opportunity to apply course concepts through this hands-on project.
Our sincere thanks also go to the CS department at Lamar University for fostering a learning environment that emphasizes practical, experiential education.

Enjoy using the Simple Shell!