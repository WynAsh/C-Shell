
This is a repository for the mid submission of the mini-project-1 of the course Operating Systems and Networks. It is programmed in C and is made to mimic the shell of a linux operating system.

### How to run?:
To run and use this shell download zip and unzip and write the following commands in terminal: 
 ``` sh
  make 
 ./a.out 
 ```

### Functionality:
- Upon entering the terminal, the screen is cleared, and the shell is launched.
- The shell is invoked from the home folder (represented by ~).
- Input commands are executed based on the current directory and the command itself unless working directory was changed.
- To indicate the end of input, press Enter after entering a command.
- Typing exit in the Terminal exits the shell.
- The shell supports directory switching and command execution.

### File Information:
- `main.c`: Contains the main function and the function that reads the input from the user.
- `commands.c`: Contains the functions that execute the commands.
- `dir.c`: Contains the functions that have relation to directory
- `history.c`: Contains the functions for the pastevents command to store previous commands
- `LL.c`: Contains the functions that have relation to linked list
- `prompt.c`: Contains the functions that have relation to the prompt at the beginning of the line
- `userio.c`: Contains the functions that have relation to the user input and output


# Assumptions
- The maximum length of the command is 4095 characters.
- The user will not enter more than 10 arguments.
- Quotations functionality in terminal not handled, as mentions in the doubts document
