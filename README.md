# namecheck
2022秋软工实践 第二次结对编程作业
## 实验环境
本次作业编程语言为**C++**，编译器可使用**Dev-C++5.11 C11标准**

![img](https://img-community.csdnimg.cn/images/432cf73aac054f528d3579727aaed204.JPG "#left")

## 运行方式
#### 1.generatedata文件中的作为一个项目，使用data.cpp编译运行生成考勤表
#### 2.test文件中的作为另外一个项目，用main.cpp编译运行输出抽点方案和E。（五门课程数据需要与编译完项目放在同一文件夹中，因此在test文件夹中也存放了五门课程的数据。

## 数据集
文件夹data中有五个文件（按课程分），分别为：course1.txt, course2.txt, course3.txt, course4.txt, course5.txt

<h6>编码方式需从UTF-8改成ANSI</h6>

输出档案内容一共有90行25列，每列分别为姓名，学号，绩点，是否是班委，信任值（过往考勤率和辅导员评价等得出评分，绩点从高到低来设置这个信任值）20次课程的出勤率
