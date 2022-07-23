# GLFWx64Project
use glew/glfw and opengl32.lib, build solution in vs2019. learn OpenGL frameworks.

Creating a window
The first thing we need to do before we start creating stunning graphics is to create an OpenGL context and an application window to draw in. However, those operations are specific per operating system and OpenGL purposefully tries to abstract itself from these operations. This means we have to create a window, define a context, and handle user input all by ourselves.

Luckily, there are quite a few libraries out there that provide the functionality we seek, some specifically aimed at OpenGL. Those libraries save us all the operation-system specific work and give us a window and an OpenGL context to render in. Some of the more popular libraries are GLUT, SDL, SFML and GLFW. On LearnOpenGL we will be using GLFW. Feel free to use any of the other libraries, the setup for most is similar to GLFW's setup.

GLFW
GLFW is a library, written in C, specifically targeted at OpenGL. GLFW gives us the bare necessities required for rendering goodies to the screen. It allows us to create an OpenGL context, define window parameters, and handle user input, which is plenty enough for our purposes.

The focus of this and the next chapter is to get GLFW up and running, making sure it properly creates an OpenGL context and that it displays a simple window for us to mess around in. This chapter takes a step-by-step approach in retrieving, building and linking the GLFW library. We'll use Microsoft Visual Studio 2019 IDE as of this writing (note that the process is the same on the more recent visual studio versions). If you're not using Visual Studio (or an older version) don't worry, the process will be similar on most other IDEs.

Building GLFW
GLFW can be obtained from their webpage's download page. GLFW already has pre-compiled binaries and header files for Visual Studio 2012 up to 2019, but for completeness' sake we will compile GLFW ourselves from the source code. This is to give you a feel for the process of compiling open-source libraries yourself as not every library will have pre-compiled binaries available. So let's download the Source package.

We'll be building all libraries as 64-bit binaries so make sure to get the 64-bit binaries if you're using their pre-compiled binaries.
Once you've downloaded the source package, extract it and open its content. We are only interested in a few items:

The resulting library from compilation.
The include folder.
Compiling the library from the source code guarantees that the resulting library is perfectly tailored for your CPU/OS, a luxury pre-compiled binaries don't always provide (sometimes, pre-compiled binaries are not available for your system). The problem with providing source code to the open world however is that not everyone uses the same IDE or build system for developing their application, which means the project/solution files provided may not be compatible with other people's setup. So people then have to setup their own project/solution with the given .c/.cpp and .h/.hpp files, which is cumbersome. Exactly for those reasons there is a tool called CMake.

CMake
CMake is a tool that can generate project/solution files of the user's choice (e.g. Visual Studio, Code::Blocks, Eclipse) from a collection of source code files using pre-defined CMake scripts. This allows us to generate a Visual Studio 2019 project file from GLFW's source package which we can use to compile the library. First we need to download and install CMake which can be downloaded on their download page.

Once CMake is installed you can choose to run CMake from the command line or through their GUI. Since we're not trying to overcomplicate things we're going to use the GUI. CMake requires a source code folder and a destination folder for the binaries. For the source code folder we're going to choose the root folder of the downloaded GLFW source package and for the build folder we're creating a new directory build and then select that directory.

Image of CMake's logo
Once the source and destination folders have been set, click the Configure button so CMake can read the required settings and the source code. We then have to choose the generator for the project and since we're using Visual Studio 2019 we will choose the Visual Studio 16 option (Visual Studio 2019 is also known as Visual Studio 16). CMake will then display the possible build options to configure the resulting library. We can leave them to their default values and click Configure again to store the settings. Once the settings have been set, we click Generate and the resulting project files will be generated in your build folder.

Compilation
In the build folder a file named GLFW.sln can now be found and we open it with Visual Studio 2019. Since CMake generated a project file that already contains the proper configuration settings we only have to build the solution. CMake should've automatically configured the solution so it compiles to a 64-bit library; now hit build solution. This will give us a compiled library file that can be found in build/src/Debug named glfw3.lib.

Once we generated the library we need to make sure the IDE knows where to find the library and the include files for our OpenGL program. There are two common approaches in doing this:

We find the /lib and /include folders of the IDE/compiler and add the content of GLFW's include folder to the IDE's /include folder and similarly add glfw3.lib to the IDE's /lib folder. This works, but it's is not the recommended approach. It's hard to keep track of your library and include files and a new installation of your IDE/compiler results in you having to do this process all over again.
Another approach (and recommended) is to create a new set of directories at a location of your choice that contains all the header files/libraries from third party libraries to which you can refer to from your IDE/compiler. You could, for instance, create a single folder that contains a Libs and Include folder where we store all our library and header files respectively for OpenGL projects. Now all the third party libraries are organized within a single location (that can be shared across multiple computers). The requirement is, however, that each time we create a new project we have to tell the IDE where to find those directories.
Once the required files are stored at a location of your choice, we can start creating our first OpenGL GLFW project.
Our first project
First, let's open up Visual Studio and create a new project. Choose C++ if multiple options are given and take the Empty Project (don't forget to give your project a suitable name). Since we're going to be doing everything in 64-bit and the project defaults to 32-bit, we'll need to change the dropdown at the top next to Debug from x86 to x64:

Image of how to switch from x86 to x64
Once that's done, we now have a workspace to create our very first OpenGL application!

Linking
In order for the project to use GLFW we need to link the library with our project. This can be done by specifying we want to use glfw3.lib in the linker settings, but our project does not yet know where to find glfw3.lib since we store our third party libraries in a different directory. We thus need to add this directory to the project first.

We can tell the IDE to take this directory into account when it needs to look for library and include files. Right-click the project name in the solution explorer and then go to VC++ Directories as seen in the image below:

Image of Visual Studio's VC++ Directories configuration
From there on out you can add your own directories to let the project know where to search. This can be done by manually inserting it into the text or clicking the appropriate location string and selecting the <Edit..> option. Do this for both the Library Directories and Include Directories:

Image of Visual Studio's Include Directories configuration
Here you can add as many extra directories as you'd like and from that point on the IDE will also search those directorie when searching for library and header files. As soon as your Include folder from GLFW is included, you will be able to find all the header files for GLFW by including <GLFW/..>. The same applies for the library directories.

Since VS can now find all the required files we can finally link GLFW to the project by going to the Linker tab and Input:

Image of Visual Studio's link configuration
To then link to a library you'd have to specify the name of the library to the linker. Since the library name is glfw3.lib, we add that to the Additional Dependencies field (either manually or using the <Edit..> option) and from that point on GLFW will be linked when we compile. In addition to GLFW we should also add a link entry to the OpenGL library, but this may differ per operating system:

OpenGL library on Windows
If you're on Windows the OpenGL library opengl32.lib comes with the Microsoft SDK, which is installed by default when you install Visual Studio. Since this chapter uses the VS compiler and is on windows we add opengl32.lib to the linker settings. Note that the 64-bit equivalent of the OpenGL library is called opengl32.lib, just like the 32-bit equivalent, which is a bit of an unfortunate name.

OpenGL library on Linux
On Linux systems you need to link to the libGL.so library by adding -lGL to your linker settings. If you can't find the library you probably need to install any of the Mesa, NVidia or AMD dev packages.

Then, once you've added both the GLFW and OpenGL library to the linker settings you can include the header files for GLFW as follows:


#include <GLFW/glfw3.h>
For Linux users compiling with GCC, the following command line options may help you compile the project: -lglfw3 -lGL -lX11 -lpthread -lXrandr -lXi -ldl. Not correctly linking the corresponding libraries will generate many undefined reference errors.
This concludes the setup and configuration of GLFW.

GLAD
We're still not quite there yet, since there is one other thing we still need to do. Because OpenGL is only really a standard/specification it is up to the driver manufacturer to implement the specification to a driver that the specific graphics card supports. Since there are many different versions of OpenGL drivers, the location of most of its functions is not known at compile-time and needs to be queried at run-time. It is then the task of the developer to retrieve the location of the functions he/she needs and store them in function pointers for later use. Retrieving those locations is OS-specific. In Windows it looks something like this:


// define the function's prototype
typedef void (*GL_GENBUFFERS) (GLsizei, GLuint*);
// find the function and assign it to a function pointer
GL_GENBUFFERS glGenBuffers  = (GL_GENBUFFERS)wglGetProcAddress("glGenBuffers");
// function can now be called as normal
unsigned int buffer;
glGenBuffers(1, &buffer);
As you can see the code looks complex and it's a cumbersome process to do this for each function you may need that is not yet declared. Thankfully, there are libraries for this purpose as well where GLAD is a popular and up-to-date library.

Setting up GLAD
GLAD is an open source library that manages all that cumbersome work we talked about. GLAD has a slightly different configuration setup than most common open source libraries. GLAD uses a web service where we can tell GLAD for which version of OpenGL we'd like to define and load all relevant OpenGL functions according to that version.

Go to the GLAD web service, make sure the language is set to C++, and in the API section select an OpenGL version of at least 3.3 (which is what we'll be using; higher versions are fine as well). Also make sure the profile is set to Core and that the Generate a loader option is ticked. Ignore the extensions (for now) and click Generate to produce the resulting library files.

GLAD by now should have provided you a zip file containing two include folders, and a single glad.c file. Copy both include folders (glad and KHR) into your include(s) directoy (or add an extra item pointing to these folders), and add the glad.c file to your project.

After the previous steps, you should be able to add the following include directive above your file:


#include <glad/glad.h> 
Hitting the compile button shouldn't give you any errors, at which point we're set to go for the next chapter where we'll discuss how we can actually use GLFW and GLAD to configure an OpenGL context and spawn a window. Be sure to check that all your include and library directories are correct and that the library names in the linker settings match the corresponding libraries.

Additional resources
GLFW: Window Guide: official GLFW guide on setting up and configuring a GLFW window.
Building applications: provides great info about the compilation/linking process of your application and a large list of possible errors (plus solutions) that may come up.
GLFW with Code::Blocks: building GLFW in Code::Blocks IDE.
Running CMake: short overview of how to run CMake on both Windows and Linux.
Writing a build system under Linux: an autotools tutorial by Wouter Verholst on how to write a build system in Linux.
Polytonic/Glitter: a simple boilerplate project that comes pre-configured with all relevant libraries; great for if you want a sample project without the hassle of having to compile all the libraries yourself.
Close X

原文	Creating a window
作者	JoeyDeVries
翻译	gjy_1992, Krasjet
校对	暂未校对
译注  来自谷歌翻译

注意，由于作者对教程做出了更新，之前本节使用的是GLEW库，但现在改为了使用GLAD库，关于GLEW配置的部分现在已经被修改，但我仍决定将这部分教程保留起来，放到一个历史存档中，如果有需要的话可以到这里来查看。

在我们画出出色的效果之前，首先要做的就是创建一个OpenGL上下文(Context)和一个用于显示的窗口。然而，这些操作在每个系统上都是不一样的，OpenGL有意将这些操作抽象(Abstract)出去。这意味着我们不得不自己处理创建窗口，定义OpenGL上下文以及处理用户输入。

幸运的是，有一些库已经提供了我们所需的功能，其中一部分是特别针对OpenGL的。这些库节省了我们书写操作系统相关代码的时间，提供给我们一个窗口和一个OpenGL上下文用来渲染。最流行的几个库有GLUT，SDL，SFML和GLFW。在教程里我们将使用GLFW。你可以随意选用其他类似的库，大多数库的配置方法和GLFW差不多。

GLFW
GLFW是一个专门针对OpenGL的C语言库，它提供了一些渲染物体所需的最低限度的接口。它允许用户创建OpenGL上下文、定义窗口参数以及处理用户输入，对我们来说这就够了。

本节和下一节的目标是把GLFW环境配好能且能够跑起来，并保证它正确创建了OpenGL上下文并显示出一个简单的窗口来让我们随意使用。这篇教程会一步步教你如何获取、编译、链接GLFW库。我们使用的是Microsoft Visual Studio 2019 IDE（操作过程在更新的Visual Studio都是相同的）。如果你用的不是Visual Studio（或者用的是它的旧版本）请不要担心，大多数IDE上的操作都是类似的。

构建GLFW
GLFW可以从它官方网站的下载页上获取。GLFW已提供为Visual Studio（2012到2019都有）预编译好的二进制版本和相应的头文件，但是为了完整性我们将从编译源代码开始。所以我们需要下载源代码包。

本教程中，我们将采用64位构建所有的库。因此如果您使用的是预编译的二进制文件，请确保你下载的是64位的二进制文件。

下载源码包之后，将其解压并打开。我们只需要里面的这些内容：

编译生成的库
include文件夹
从源代码编译库可以保证生成的库完全适合你的操作系统和CPU的，而预编译的二进制文件则并非总是提供（有时候，即便提供了预编译的二进制文件，也可能不适用于您的系统）。开放源代码所产生问题在于：并不是每个人都用相同的IDE或者构建系统来搞开发，因而提供的项目/解决方案文件可能和一些人的IDE不兼容。所以人们必须使用给定的.c/.cpp和.h/.hpp文件来自己建立项目/解决方案，这是一项很枯燥的工作。但因此也诞生了一个叫做CMake的工具。

CMake
CMake是一个工程文件生成工具。用户可以使用预定义好的CMake脚本，根据自己的选择（像是Visual Studio, Code::Blocks, Eclipse）生成不同IDE的工程文件。这允许我们从GLFW源码创建一个Visual Studio 2019工程文件，之后进行编译。首先，我们需要从这里下载安装CMake。

当CMake安装成功后，你可以选择从命令行或者GUI启动CMake，由于我们不想让事情变得太过复杂，我们选择用GUI。CMake需要一个源代码目录和一个存放编译结果的目标文件目录。源代码目录我们选择GLFW的源代码的根目录，然后我们新建一个 build 文件夹，选中作为目标目录。



在设置完源代码目录和目标目录之后，点击Configure(设置)按钮，让CMake读取设置和源代码。我们接下来需要选择工程的生成器，由于我们使用的是Visual Studio 2019，我们选择 Visual Studio 16 选项（因为Visual Studio 2019的内部版本号是16）。CMake会显示可选的编译选项用来配置最终生成的库。这里我们使用默认设置，并再次点击Configure(设置)按钮保存设置。保存之后，点击Generate(生成)按钮，生成的工程文件会在你的build文件夹中。

编译
在build文件夹里可以找到GLFW.sln文件，用Visual Studio 2019打开。因为CMake已经配置好了项目，并按照默认配置将其编译为64位的库，所以我们直接点击Build Solution(生成解决方案)按钮，然后在build/src/Debug文件夹内就会出现我们编译出的库文件glfw3.lib。

库生成完毕之后，我们需要让IDE知道库和头文件的位置。有两种方法：

找到IDE或者编译器的/lib和/include文件夹，添加GLFW的include文件夹里的文件到IDE的/include文件夹里去。用类似的方法，将glfw3.lib添加到/lib文件夹里去。虽然这样能工作，但这不是推荐的方式，因为这样会让你很难去管理库和include文件，而且重新安装IDE或编译器可能会导致这些文件丢失。
推荐的方式是建立一个新的目录包含所有的第三方库文件和头文件，并且在你的IDE或编译器中指定这些文件夹。我个人会使用一个单独的文件夹，里面包含Libs和Include文件夹，在这里存放OpenGL工程用到的所有第三方库和头文件。这样我的所有第三方库都在同一个位置（并且可以共享至多台电脑）。然而这要求你每次新建一个工程时都需要告诉IDE/编译器在哪能找到这些目录。
完成上面步骤后，我们就可以使用GLFW创建我们的第一个OpenGL工程了！

我们的第一个工程
首先，打开Visual Studio，创建一个新的项目。如果VS提供了多个选项，选择Visual C++，然后选择Empty Project(空项目)（别忘了给你的项目起一个合适的名字）。由于我们将在64位模式中执行所有操作，而新项目默认是32位的，因此我们需要将Debug旁边顶部的下拉列表从x86更改为x64：



现在我们终于有一个空的工作空间了，开始创建我们第一个OpenGL程序吧！

链接
为了使我们的程序使用GLFW，我们需要把GLFW库链接(Link)进工程。这可以通过在链接器的设置里指定我们要使用glfw3.lib来完成，但是由于我们将第三方库放在另外的目录中，我们的工程还不知道在哪寻找这个文件。于是我们首先需要将我们放第三方库的目录添加进设置。

要添加这些目录（需要VS搜索库和include文件的地方），我们首先进入Project Properties(工程属性，在解决方案窗口里右键项目)，然后选择VC++ Directories(VC++ 目录)选项卡（如下图）。在下面的两栏添加目录：



这里你可以把自己的目录加进去，让工程知道到哪去搜索。你需要手动把目录加在后面，也可以点击需要的位置字符串，选择选项，之后会出现类似下面这幅图的界面，图是选择Include Directories(包含目录)时的界面：



这里可以添加任意多个目录，IDE会从这些目录里寻找头文件。所以只要你将GLFW的Include文件夹加进路径中，你就可以使用<GLFW/..>来引用头文件。库文件夹也是一样的。

现在VS可以找到所需的所有文件了。最后需要在Linker(链接器)选项卡里的Input(输入)选项卡里添加glfw3.lib这个文件：



要链接一个库我们必须告诉链接器它的文件名。库名字是glfw3.lib，我们把它加到Additional Dependencies(附加依赖项)字段中(手动或者使用选项都可以)。这样GLFW在编译的时候就会被链接进来了。除了GLFW之外，你还需要添加一个链接条目链接到OpenGL的库，但是这个库可能因为系统的不同而有一些差别。

Windows上的OpenGL库
如果你是Windows平台，opengl32.lib已经包含在Microsoft SDK里了，它在Visual Studio安装的时候就默认安装了。由于这篇教程用的是VS编译器，并且是在Windows操作系统上，我们只需将opengl32.lib添加进连接器设置里就行了。值得注意的是，OpenGL库64位版本的文件名仍然是opengl32.lib（和32位版本一样），虽然很奇怪但确实如此。

Linux上的OpenGL库
在Linux下你需要链接libGL.so库文件，这需要添加-lGL到你的链接器设置中。如果找不到这个库你可能需要安装Mesa，NVidia或AMD的开发包，这部分因平台而异（而且我也不熟悉Linux）就不仔细讲解了。

接下来，如果你已经添加GLFW和OpenGL库到连接器设置中，你可以用如下方式添加GLFW头文件：

#include <GLFW\glfw3.h>
对于用GCC编译的Linux用户建议使用这个命令行选项-lglfw3 -lGL -lX11 -lpthread -lXrandr -lXi -ldl。没有正确链接相应的库会产生 undefined reference (未定义的引用) 这个错误。

GLFW的安装与配置就到此为止。

GLAD
到这里还没有结束，我们仍然还有一件事要做。因为OpenGL只是一个标准/规范，具体的实现是由驱动开发商针对特定显卡实现的。由于OpenGL驱动版本众多，它大多数函数的位置都无法在编译时确定下来，需要在运行时查询。所以任务就落在了开发者身上，开发者需要在运行时获取函数地址并将其保存在一个函数指针中供以后使用。取得地址的方法因平台而异，在Windows上会是类似这样：

// 定义函数原型
typedef void (*GL_GENBUFFERS) (GLsizei, GLuint*);
// 找到正确的函数并赋值给函数指针
GL_GENBUFFERS glGenBuffers  = (GL_GENBUFFERS)wglGetProcAddress("glGenBuffers");
// 现在函数可以被正常调用了
GLuint buffer;
glGenBuffers(1, &buffer);
你可以看到代码非常复杂，而且很繁琐，我们需要对每个可能使用的函数都要重复这个过程。幸运的是，有些库能简化此过程，其中GLAD是目前最新，也是最流行的库。

配置GLAD
GLAD是一个开源的库，它能解决我们上面提到的那个繁琐的问题。GLAD的配置与大多数的开源库有些许的不同，GLAD使用了一个在线服务。在这里我们能够告诉GLAD需要定义的OpenGL版本，并且根据这个版本加载所有相关的OpenGL函数。

打开GLAD的在线服务，将语言(Language)设置为C/C++，在API选项中，选择3.3以上的OpenGL(gl)版本（我们的教程中将使用3.3版本，但更新的版本也能用）。之后将模式(Profile)设置为Core，并且保证选中了生成加载器(Generate a loader)选项。现在可以先（暂时）忽略扩展(Extensions)中的内容。都选择完之后，点击生成(Generate)按钮来生成库文件。

GLAD现在应该提供给你了一个zip压缩文件，包含两个头文件目录，和一个glad.c文件。将两个头文件目录（glad和KHR）复制到你的Include文件夹中（或者增加一个额外的项目指向这些目录），并添加glad.c文件到你的工程中。

经过前面的这些步骤之后，你就应该可以将以下的指令加到你的文件顶部了：

#include <glad/glad.h> 
点击编译按钮应该不会给你提示任何的错误，到这里我们就已经准备好继续学习下一节去真正使用GLFW和GLAD来设置OpenGL上下文并创建一个窗口了。记得确保你的头文件和库文件的目录设置正确，以及链接器里引用的库文件名正确。如果仍然遇到错误，可以先看一下评论有没有人遇到类似的问题，请参考额外资源中的例子或者在下面的评论区提问。

附加资源
GLFW: Window Guide：GLFW官方的配置GLFW窗口的指南。
Building applications：提供了很多编译或链接相关的信息和一大列错误及对应的解决方案。
GLFW with Code::Blocks：使用Code::Blocks IDE编译GLFW。
Running CMake：简要的介绍如何在Windows和Linux上使用CMake。
Writing a build system under Linux：Wouter Verholst写的一个autotools的教程，讲的是如何在Linux上编写构建系统，尤其是针对这些教程。
Polytonic/Glitter：一个简单的样板项目，它已经提前配置了所有相关的库；如果你想要很方便地搞到一个LearnOpenGL教程的范例工程，这也是很不错的。
Powered by MkDocs and Yeti
