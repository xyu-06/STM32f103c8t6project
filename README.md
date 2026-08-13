<div align="center">

# 🧠 STM32F103C8T6 学习工程集

**从 GPIO 到 PWM 电机控制的单片机学习之路**

</div>

<div align="center">

![芯片](https://img.shields.io/badge/芯片-STM32F103C8T6-03234B?style=for-the-badge&logo=arm&logoColor=white)
![语言](https://img.shields.io/badge/语言-C-00599C?style=for-the-badge&logo=c&logoColor=white)
![标准库](https://img.shields.io/badge/标准库-V3.5-47A248?style=for-the-badge)
![Keil](https://img.shields.io/badge/IDE-Keil%20MDK5-7B3FE4?style=for-the-badge)
![VS Code](https://img.shields.io/badge/编辑器-VS%20Code-007ACC?style=for-the-badge&logo=visualstudiocode&logoColor=white)
![仓库](https://img.shields.io/badge/仓库-持续更新-4CAF50?style=for-the-badge)

</div>

---

## 📋 项目简介

STM32F103C8T6 单片机系统学习项目合集，覆盖 **GPIO → 中断 → 定时器 → PWM** 完整学习路线。全部基于 **STM32 标准外设库 V3.5**，Keil MDK5 (ARMCC V5) 编译调试，部分工程配置 VS Code 开发环境。

> 📅 持续更新中，代码与学习笔记同步归档

---

## 🗺️ 学习路线

```mermaid
graph LR
    A[2-1 工程模板] --> B[3-1~3-5 GPIO 基础]
    B --> C[4 OLED 显示]
    C --> D[5-1 外部中断+消抖]
    D --> E[5-2 旋转编码器]
    E --> F[6-1 定时器中断]
    F --> G[6-2 定时器外部时钟]
    G --> H[6-3 PWM 呼吸灯]
    H --> I[6-5 PWM 电机控制]
    style A fill:#e3f2fd
    style I fill:#c8e6c9
```

---

## 📖 工程列表

### 🔧 Keil 工程（`Keil_projects/`）

#### 基础篇（2~4 章）：工程模板 & GPIO

| 章节 | 工程 | 学习要点 |
|:---:|---|---|
| 2-1 | STM32工程模版 | 标准库工程结构、启动文件 |
| 3-1 | LED闪烁 | GPIO 输出、延时 |
| 3-2 | LED流水灯 | GPIO 多引脚控制 |
| 3-3 | 蜂鸣器 | GPIO 驱动有源蜂鸣器 |
| 3-4 | 按键控制LED | GPIO 输入、按键检测 |
| 3-5 | 光敏模块蜂鸣器 | 传感器输入检测 |
| 4 | OLED屏幕 | 模拟 I2C 驱动 OLED 显示 |

#### 进阶篇（5~6 章）：中断 & 定时器

| 章节 | 工程 | 学习要点 |
|:---:|---|---|
| 5-1 | 对射式红外传感器计数（阻塞消抖） | 外部中断、阻塞消抖 |
| 5-1 | 对射式红外传感器计数（时间戳状态机消抖） | 外部中断、时间戳状态机消抖 ⭐ |
| 5-2 | 旋转编码器计数 | 正交解码计数 |
| 5-2 | 旋转编码器计数（外部中断不推荐） | 中断方案对比 |
| 6-1 | 定时器定时中断 | TIM 定时中断 |
| 6-1 | 定时器定时中断（systick最简定时） | SysTick 简单定时 |
| 6-2 | 定时器外部时钟 | TIM 外部时钟模式 |

### 💻 VS Code 工程（`VSCode_projects/`）

带 `.vscode` 配置，VS Code 编写（自动补全）+ Keil 编译调试：

| 工程 | 说明 |
|---|---|
| 5-1 对射式红外传感器计数（时间戳状态机消抖） | VS Code 配置版 |
| 6-3 LED呼吸灯 | PWM 输出控制 LED 亮度 ⭐ |
| 6-5 PWM电机 | PWM + 电机正反转/调速（按键控制）⭐ |

---

## 📒 学习笔记（`Notes/`）

按日期归档，记录知识点、踩坑、易混概念与代码参考：

| 日期 | 笔记 | 主题 |
|---|---|---|
| 2026-08-12 | 按键消抖与电机控制 | 按键消抖三方法、外部中断、时间戳、PWM 电机控制 |
| 2026-08-13 | PWM输出与VS环境配置 | PWM 原理/四种模式、VS Code+Keil 配置、按键检测四方法 |

---

## 🛠️ 开发环境

| 组件 | 说明 |
|---|---|
| 芯片 | STM32F103C8T6（Cortex-M3，64KB Flash，20KB RAM） |
| 标准库 | STM32F10x Standard Peripheral Library V3.5 |
| 编译器 | Keil ARMCC V5.06 |
| IDE | Keil MDK5（编译/下载/调试）+ VS Code（代码编辑） |

---

## 🚀 快速开始

### 方式一：纯 Keil

1. 用 Keil MDK5 打开任一工程的 `project.uvprojx`
2. 编译 → 下载 → 运行

### 方式二：VS Code + Keil（推荐）

1. VS Code 打开 `VSCode_projects/` 下工程文件夹
2. 安装 Microsoft C/C++ 插件
3. `Ctrl+Shift+B` 调用 Keil 命令行编译
4. Keil 打开 `project.uvprojx` 下载调试

---

## 📂 目录结构

```
STM32F103C8T6学习工程集
├── Keil_projects/       # 纯 Keil 工程（第2~6章）
│   ├── 2-1STM32工程模版/
│   ├── 3-1LED闪烁/
│   ├── ...
│   └── 6-2定时器外部时钟/
├── VSCode_projects/     # 带 VS Code 配置的工程
│   ├── 5-1对射式红外传感器计数（时间戳状态机消抖）/
│   ├── 6-3LED呼吸灯/
│   └── 6-5PWM电机/
├── Notes/               # 学习笔记
│   ├── 2026-08-12_按键消抖与电机控制.md
│   └── assets/          # 笔记配图（SVG）
├── .gitignore           # 忽略编译产物
└── README.md
```

---

## ⚠️ 说明

- ✅ 各工程均包含完整标准库源码（`Library/`、`Start/`），可直接编译
- ✅ 编译产物（`Objects/`、`Listings/`、`DebugConfig/`）已被 `.gitignore` 排除，仓库干净
- 💡 部分章节包含多种实现方案（如 5-1 两种消抖方式），可对比学习

---

## 📌 学习路线建议

1. **2-1 ~ 4 章**：工程结构 + GPIO 基础
2. **5 章**：外部中断 + 消抖（重点：时间戳状态机消抖）
3. **6 章**：定时器 + PWM（LED 呼吸灯、电机控制）
4. **后续方向**：串口通信、ADC、I2C/SPI 传感器、RTOS

---

<div align="center">

*持续学习中，工程与笔记随进度更新* 🚀

</div>
