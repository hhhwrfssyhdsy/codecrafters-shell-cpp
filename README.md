[![progress-banner](https://backend.codecrafters.io/progress/shell/62bfa88d-05fa-4e8b-98bf-309d5d71be07)](https://app.codecrafters.io/users/codecrafters-bot?r=2qF)

This is a starting point for C++ solutions to the
["Build Your Own Shell" Challenge](https://app.codecrafters.io/courses/shell/overview).

In this challenge, you'll build your own POSIX compliant shell that's capable of
interpreting shell commands, running external programs and builtin commands like
cd, pwd, echo and more. Along the way, you'll learn about shell command parsing,
REPLs, builtin commands, and more.

**Note**: If you're viewing this repo on GitHub, head over to
[codecrafters.io](https://codecrafters.io) to try the challenge.


# Project Structure
- `include` contains all the head files that the project requires.
   - `core` include all the functions that provide the function for system call, such as **command execute**, **path search**, **environment varieties**.
   - `navigation` include all the functions that helps users navigate their file path.


- `src` is the source codes corresponding to directory `include`