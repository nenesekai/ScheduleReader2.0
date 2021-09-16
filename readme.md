# Schedule Reader 2.0

中文｜[Eng](readme_en.md)

还在每节课上课前打开Office查看课程表吗？还在一个个把你自己的课程打进去日历软件吗？本软件可以自动把你Excel的课程表转换到可以被各大日历服务所识别的iCalendar文件。只需要一次配置，就可以在每周发课程表的时候自动转换生成然后导入到你所喜爱的日历软件里面去。

这是我写的第一个真正没有烂尾的项目，求求你了给个小小的星星吧

## 适配的日历软件

导出的格式为iCalendar文件。该文件可以被大部分的日历服务所识别且导入。这些是被测试过的平台。

| 服务 | 可用程度 |
| --- | --- |
| 谷歌日历 | ✅ |
| 苹果日历 | ✅ |

其他的平台理论可用，只是没有经过测试。欢迎在Issue中提出任何你遇到的无法正常识别的平台。

## 如何下载？

### 下载编译好的版本

在[Release](https://github.com/Asiimoviet/ScheduleReader2.0/releases)中下载最新的版本

### 自己编译

把这个仓库clone下来，然后使用```make```编译
``` bash
git clone https://github.com/Asiimoviet/ScheduleReader2.0
cd ScheduleReader2.0
make
```

## 如何使用？

在针对你的课程表配置后，命令行跑编译后的```schedule```，运行```schedule --help```以获得相关的帮助

通用格式：
```./schedule --file 课程表文件 --config 配置文件 --output [输出到的地方]```

## 如何配置？

现在的配置文件不完善，先不写了。可以参考在examples里面的[配置文件](examples/config.json)

## 相对1.0有什么不同？
1.0是使用Python写的，2.0是用C++写的。理论上兼容性更好，效率更高。

## 用到的库
- [nlohmann/json](https://github.com/nlohmann/json)
- [troldal/OpenXLSX](https://github.com/troldal/OpenXLSX)
- [HowardHinnant/date](https://github.com/HowardHinnant/date)