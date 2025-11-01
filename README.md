经过不懈努力，
终于明白这个项目的运行是
需要在“编辑配置”里修改
1.“程序实参” 
2.“工作目录”
因为程序编译运行后的可执行文件会存在于“cmake...”之中
此时如果传入实参"texts/某某.txt"就会导致程序找不到该文件
所以要将工作目录改为speller的根目录（打开后包含两个.c文件的这个目录）


//我会（在你缺）好好复习目录的表达的ww


反思：发现TIME在check上花的最多
因为每当从目标txt提取一个词后
通过hash，想找出这个词，
（如果找不到该词）最差要搜索n遍（遍历table[n]下的每一个词），
时间复杂度是On

优化思路
优化哈希算法，提高table[N]中N的大小
我目前决定的方法
1.在load时计算该单词前2个字母序号的乘积（a1,z26)
创建出一个26*26的哈希表
2.或者用前两个字母序号的和，这样哈希表就是26+26的大小（还是太小了）

哈喽算法中对哈希算法设计的描述：
6.3.2   哈希算法的设计¶
哈希算法的设计是一个需要考虑许多因素的复杂问题。然而对于某些要求不高的场景，我们也能设计一些简单的哈希算法。

加法哈希：对输入的每个字符的 ASCII 码进行相加，将得到的总和作为哈希值。
乘法哈希：利用乘法的不相关性，每轮乘以一个常数，将各个字符的 ASCII 码累积到哈希值中。
异或哈希：将输入数据的每个元素通过异或操作累积到一个哈希值中。
旋转哈希：将每个字符的 ASCII 码累积到一个哈希值中，每次累积之前都会对哈希值进行旋转操作。

# speller

A student-friendly variant of CS50's Pset5 speller configured for cross-platform builds (Windows, Linux, macOS) using CMake.

## Build

Using CMake (recommended):

```sh
# from the speller directory
cmake -S . -B build
cmake --build build --config Release
```

The resulting executable will be at `build/speller` (or `build/Release/speller.exe` on Windows with MSVC).

If you prefer Make (on Unix-like systems only), a legacy `Makefile` is included, but CMake is recommended for Windows compatibility.

## Run

```sh
# default dictionary
./build/speller texts/lalaland.txt

# specify dictionary
./build/speller dictionaries/small texts/cat.txt
```

## Notes for students
- `dictionary.c` contains TODOs for you to implement: `load`, `check`, `hash`, `size`, and `unload`.
- Timing uses standard C `clock()` for portability (no `sys/resource.h`).
- Keep your implementation within the provided API in `dictionary.h`.
