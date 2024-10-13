This tutorial covers the first major stepping stone（重要的第一步）: getting a window to pop up.  
  
Now that you have SDL set up, it's time to make a bare bones（基础的） SDL graphics application that renders a quad（四边形 on the screen.
We're also going to include C standard IO to print errors to the console. You're probably more used to using iostream, but I use `printf` in my applications because it's more ***thread safe***.
- what is thread safe

## structure
此处代码块不是完整程序
```c
#include <SDL.h>

const int SCREEN_WIDTH 
const int SCREEN_HIGHT

int main( int argc, char* args[] )


//The window we'll be rendering to
SDL_Window* window = NULL;
//SDL_Window 是类名，此处创建了空指针

//The surface contained by the window
SDL_Surface* screenSurface = NULL;
//同理

//Initialize SDL
if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
    }
//SDL init会有返还值，返还值错误会打印报错

```

### //什么时候必须用这种？而不能用 简单的 int main (){}
It's important that we have the arguments of the function be an integer followed by a char* array and the return type be an integer. Any other type of main function will cause an undefined reference to main. SDL requires this type of main so it is compatible with multiple platforms
### 有关空指针
在编程时，一般也是先将指针初始化为空，再对其进行赋值操作。
```c
int* p1=0;        
//0是唯一不必转换就可以赋值给指针的数据，在ASCII编码中，编号为0的字符就是空
int* p2=NULL; 
//NULL是一个宏定义，起作用和0相同
```

### flag
>You can't call any SDL functions without initializing SDL first. Since all we care about is using SDL's video subsystem, we will only be passing it the SDL_INIT_VIDEO flag.

此处flag是什么意思

## 创建一个窗口SDL_CreateWindow()
("<name>", x pos, y pos, width, hight, flag)
