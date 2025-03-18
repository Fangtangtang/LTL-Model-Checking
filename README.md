# LTL-Model-Checking
CS3959 course project

## 大作业要求
### LTL模型检验算法实现

1. Parser：transition system 以及 LTL formula的读取（读取格式见同单元的说明，可以假设transition system没有terminal state，LTL公式输入中每一个子公式都有括号）
2. 教材上从 LTL formula 到 GNBA 的等价构造
3. 教材上从 GNBA 到 NBA 的等价转换
4. 教材上 transition system 与 NBA 之间的product construction (Definition 4.62, Page 200)
5. 教材上检查 persistence property的nested depth-first search algorithm (Algorithm 8, Page 211)

### 提交
1. 带有注释的源代码（注释标注出各个模块的功能以及上述四个关键步骤对应的代码）
2. 编译方式以及使用方式
3. 实现文档（包括代码结构、数据结构等各个主要实现细节）

### 评估及测试方法

1 Parser：支持通过文件`TS.txt`输入一个transition system，以及另一个文件`benchmark.txt`输入数个LTL formula，输出transition system（以及各state）是否满足相应LTL formula。LTL formula的输入第一行包含两个数A和B，分别表示针对transition system所有初始状态的LTL formula行数A和针对各状态si的LTL formula行数B。其中针对si的LTL formula行的开头为int i。完整benchmark规模与样例类似，主要考察实现完成度。
   -  `TS.txt` Sample
      ```txt
         6 9
         0 
         0 1 2
         a b c
         0 1 1
         0 0 3
         3 2 1
         1 2 4
         2 2 1
         5 0 2
         5 1 1
         4 0 1
         4 1 5
         0 1
         0 1 2
         1 2
         0 2
         0 2
         0 1
      ```
    - `benchmark.txt` Sample
      ```txt
      1 3
      G(a \/ b)
      1 X(a /\ c)
      2 !(Fa)
      3 c U (!a)
      ```
      以Input Format中的transition system例子为准，逐行输出分析结果，1为满足，0为不满足：
      ```txt
      1
      1
      0
      0
      ```
2-4: 针对LTL formula的构造与转换，有三元组等形式的合理输出，并在文档中详细说明构造方法、有相应结果的截图

5: 实现教材中的Algorithm 8，在文档中写出具体实现方法

## Prerequisite
### Antlr 4
1. Download ANTLR. 
I use `antlr-4.12.0-complete.jar` for this project which can be found in `https://github.com/antlr/website-antlr4/tree/gh-pages/download`.

2. [Compile and install C++ runtime support](https://github.com/antlr/antlr4/tree/master/runtime/Cpp#compiling-on-linux)

   ```shell
   git clone git@github.com:antlr/antlr4.git antlr4
   cd antlr4/runtime/Cpp 
   mkdir build && mkdir run && cd build
   cmake .. -DANTLR_JAR_LOCATION=path/to/antlr-4.12.0-complete.jar
   make
   sudo DESTDIR=path/to/install/antlr4/runtime/Cpp make install
   ```
