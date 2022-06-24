   
    /// Library definitions
    #include <stdio.h>
    #include <string.h>
    #include <stdlib.h>
    #include <conio.h>
    #include <ctype.h>
    #include <stdbool.h>

    /// Import custom headers
    #include "definitions.h"
    #include "functions.h"
    #include "menus.h"

    /// Main file
    int main(void) {

        //- Prepare terminal
        clrscr();
        esqncs();
        
        //- Initialize a new container
        Container container;
        container.count = 0;
        StartMenu(&container);
        
        //- Prevent abrupt termination
        return 0;
    }