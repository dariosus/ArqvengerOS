#include "shell/help/help.h"
#include "mcurses/mcurses.h"
#include "library/stdio.h"
#include "shell/info.h"

/**
 * Command that shows the commands supported by the shell, as well as a brief description.
 *
 * @param argv A string containing everything that came after the command.
 */
void help(char* argv) {

    const Command* commands;
    size_t numCommands, i;

    commands = getShellCommands(&numCommands);

    setBold(1);
    printf("Commands:\n");
    setBold(0);

    for (i = 0; i < numCommands; i++) {
        setBold(1);
        printf("\t%s", commands[i].name);
        setBold(0);
        printf(": %s\n", commands[i].desc);
    }

    putchar('\n');
    printf("You can use functions keys 1 through 4 to switch between shells.\n");
}

/**
 * Print manual page for the help command.
 */
void manHelp(void) {
    setBold(1);
    printf("Usage:\n\thelp\n");
    setBold(0);
}
