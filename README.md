# cgame3

## 简介

- 这是一个c语言写的小游戏
- 目前才刚开工，还没有什么内容
- 开发平台:
  - [x] Arch Linux
  - [ ] Ubuntu Linux
  - [ ] Debian Linux
  - [ ] Deepin Linux

## 使用

- 通过源代码
  - 必要的软件:***gcc***
    - 如果没有，Debian Linux or Ubuntu Linux使用以下命令安装gcc

      ``` sh
      sudo apt install gcc
      ```

  - 下载源代码到本地
    - 使用git克隆此仓库到本地：

      ``` sh
      git clone https://github.com/Youlanjie/cgame3.git
      ```

    - 或者从[这里](https://github.com/YouLanjie/cgame3/archive/refs/heads/master.zip)下载压缩包并解压
    - 再或者直接复制源代码，如果这样注意一定要复制include里的文件
  - 编译
    - 使用make自动编译：

      ```sh
      make
      ```

    - 或者 **进入cgame3/src/** 目录，使用gcc手动编译所有c文件：

      ``` sh
      gcc *.c */*.c -o main
      ```

- 其实在仓库的母文件夹下的bin目录就存放着已经编译好了的ELF文件，只要你的CPU架构是x86\_64的，就可以直接执行

