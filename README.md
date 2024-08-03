# 2024 年全国大学生电子设计竞赛

 [B题_单相功率分析仪.pdf](Static\B题_单相功率分析仪.pdf) 

#### 硬件方案:

主控TMS28335、电流和电压互感器芯片都行。

#### 软件方案:

电压互感器和电流互感器采集，ADC采样，电流信号采用DFT计算得到THD和各次谐波。精度指标基本可以达标。

功耗实现不了，28335功耗太大，最终通过ADC周期性采样，并且结束后ADC掉电运算，系统时钟压到60MHZ，实现功耗500mW左右。

#### 参考文章

[TMS320F28335 调用TI的FPU库实现FFT](https://zhuanlan.zhihu.com/p/687784799)

[简明FFT公式](https://blog.csdn.net/weixin_50497501/article/details/135336133)

[交流有功功率、无功功率、视在功率计算](https://blog.csdn.net/xinghuanmeiying/article/details/103599919)

 [非正弦状态下有功功率和功率因数测试_陈国炎.pdf](Static\非正弦状态下有功功率和功率因数测试_陈国炎.pdf) 

 [用电能计量芯片-ADE7763测量功率因数.pdf](Static\用电能计量芯片-ADE7763测量功率因数.pdf) 

#### 补充

FFT有试过TI官方FPU库，计算速度不够快。[CONTROLSUITE下载](https://www.ti.com.cn/tool/cn/CONTROLSUITE)

采样仿真可以使用 [Analog_Sample.py](Analog_Sample.py) 生成采样数据。

#### 实物

<img src="./Static/%E5%AE%9E%E7%89%A9%E5%9B%BE.png" alt="实物图" style="zoom: 33%;" />