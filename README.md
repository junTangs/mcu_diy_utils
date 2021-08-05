# mcu_diy_utils（MDU）

### 介绍
mcu develop/diy utils code and interface


### driver interface
 MDU 定义了简易的驱动接口,从而实现对底层驱动的简单屏蔽和包装，从而实现上层传感器驱动的通用，减少移植工作。
 
##### How to use
 - step1 : 将`driver`目录下的`interface_def.h`包含到工程中，复制`interface_templete.h`和`interface_templete.c`创建相应的`interface_platform.h`和`inferace_platform.c`。
 - step2 : 在`interface_platform.h`中定义相应的接口，并在相应的.c文件中实现相应的接口函数，并在`interface_platform.c`中将相应接口函数传递给接口实例。
 - step3 : 在工程中需要使用驱动的地方包含`inferace_platform.h`,即可通过函数指针方式调用相应接口


##### 已实现接口移植平台：
- tm4c123g lunchpad : hardware i2c , switch1,2


### utility alogrithm
MDU 实现了简单的算法实现，从而实现开箱即用，同时提供了部分算法的python封装。

##### 已实现算法：
- 1d Kalman Filter（一维卡尔曼滤波）
- simple PID（简单PID控制器）
- fsm （有限状态机）

### version
- 2021/8/5 ver.alpha 0.0.1

### 代码贡献和致谢

如果你喜欢本代码，欢迎star，同时欢迎对代码中存在的问题提出您的宝贵建议。

### email
如果有任何疑问，欢迎通过以下方式联系：
    richard_tangs_98@163.com