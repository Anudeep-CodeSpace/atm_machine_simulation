Simulating ATM machine on a console using purely c programming.

Couldn't mask the password due to limitations in the console....

// Append the following code to enable getch() function in c
char getch() {
    struct termios oldt, newt;
    char ch;
    tcgetattr(STDIN_FILENO, &oldt);  // get the terminal settings
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);  // disable canonical mode and echo
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);  // apply the new settings
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);  // restore old settings
    return ch;
}

whenever the PIN is taken as input we can replace the scanf with the following code

int i = 0
while((ch = getch()) != '\r') {
    putch('*');
    pass[i++] = ch;
}
pass[i] = '\0'

getch() and putch() are included in the conio.h file which i will attach to the repo. Paste it in the compiler include path to enjoy some Privacy!!
