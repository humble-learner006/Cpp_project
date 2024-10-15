# 头文件的定义以及作用
头文件（Header File）是一个文件，通常以.h或.hpp为扩展名，包含了函数、类、变量的声明以及宏定义等。头文件的主要作用是将**代码的声明和实现分离**，方便代码的组织和重用。
头文件的作用
1.	声明函数和类：头文件中**包含函数和类的声明**，使得这些函数和类可以在多个源文件中使用。
2.	代码重用：通过包含头文件，不同的源文件可以**共享相同的声明，避免重复代码。**
3.	提高可读性：将声明和实现分离，使代码更清晰、更易于维护。
## 头文件只包含声明，不包含实现和定义
为了避免重复定义和链接错误。头文件的作用是提供声明，而不是定义。具体原因如下：
1. **避免重复定义**：如果在头文件中定义变量，那么每次包含这个头文件的源文件都会有一个变量的定义，这会导致链接器错误（multiple definition error）。通过使用[`extern`](vscode-file://vscode-app/c:/Users/62589/AppData/Local/Programs/Microsoft%20VS%20Code/resources/app/out/vs/code/electron-sandbox/workbench/workbench.esm.html)关键字声明变量，告诉编译器这些变量在其他地方定义。
2. **分离声明和定义**：头文件通常用于声明函数和变量，而定义则放在源文件中。这种分离有助于代码的组织和模块化。
3. **链接阶段处理**：[`extern`](vscode-file://vscode-app/c:/Users/62589/AppData/Local/Programs/Microsoft%20VS%20Code/resources/app/out/vs/code/electron-sandbox/workbench/workbench.esm.html)关键字告诉编译器这些变量在其他地方定义，链接器会在链接阶段找到这些变量的定义并将它们连接起来。
# 头文件引用失败
头文件引用失败通常是因为编译器找不到头文件的位置。确保头文件存在并且路径正确。以下是解决这个问题的步骤：
1.	确保头文件存在：确保01_hello_SDL.h文件存在于项目目录中。
2.	检查路径：如果头文件不在源文件的同一目录中，需要提供正确的相对路径或绝对路径。
3.	项目设置：确保你的IDE（如Visual Studio）项目设置中包含头文件的目录。

# 例子
## Declarations vs. Definitions
1.	Declaration: A declaration tells the compiler about the name and type of a function, variable, or class, but it doesn't allocate memory or provide the implementation. Declarations are typically found in header files (.h).
2.	Definition: A definition provides the actual implementation and allocates memory. Definitions are typically found in source files (.cpp).
## Header Files and Source Files
•	Header File (01_hello_SDL.h): This file contains the declarations of functions, constants, and other entities. By including this file, other source files know about the existence and interface of these functions and constants.
•	Source File (01_hello_SDL.cpp): This file contains the definitions of the functions declared in the header file. It provides the actual implementation.
## How It Works
When you include 01_hello_SDL.h in main.cpp, the compiler knows about the hello_SDL function's declaration. This allows you to call hello_SDL in main.cpp without any issues. During the linking phase, the linker combines the compiled object files (main.o and 01_hello_SDL.o) and resolves the references to the actual function definitions.
## e.g.
### header file
```cpp
// 01_hello_SDL.h
#ifndef HELLO_SDL_H
#define HELLO_SDL_H

#include <SDL.h>
#include <stdio.h>

// Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

// Function declaration
int hello_SDL();

#endif // HELLO_SDL_H
```
### source file
```cpp
// 01_hello_SDL.cpp
#include "01_hello_SDL.h"

int hello_SDL()
{
    // The window we'll be rendering to
    SDL_Window* window = NULL;
    
    // The surface contained by the window
    SDL_Surface* screenSurface = NULL;

    // Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
    }
    else
    {
        // Create window
        window = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
        if( window == NULL )
        {
            printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
        }
        else
        {
            // Get window surface
            screenSurface = SDL_GetWindowSurface( window );

            // Fill the surface white
            SDL_FillRect( screenSurface, NULL, SDL_MapRGB( screenSurface->format, 0xFF, 0xFF, 0xFF ) );
            
            // Update the surface
            SDL_UpdateWindowSurface(window);
            
            // Hack to get window to stay up
            SDL_Event e; 
            bool quit = false; 
            while( quit == false ){ 
                while( SDL_PollEvent( &e ) ){ 
                    if( e.type == SDL_QUIT ) 
                        quit = true; 
                } 
            }
        }
    }

    // Destroy window
    SDL_DestroyWindow( window );

    // Quit SDL subsystems
    SDL_Quit();

    return 0;
}
```
### main file
```cpp
#include "01_hello_SDL.h"

int main(int argc, char* args[])
{
    hello_SDL();
    return 0;
}


```
