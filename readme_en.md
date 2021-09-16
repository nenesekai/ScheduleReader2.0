# Schedule Reader 2.0

Still opening up Office to check your next class? Still typing every single courses every week manually? Schedule Reader can automatically convert your Excel Schedule to iCalendar file that can be imported into the majority of the calendar platforms with only one configurating.

## Where Can I Use It

The output file is in iCalendar format, and it can be imported to basically any calendar services. Here are the tested platforms

| Services | Usability |
| --- | --- |
| Google Calendar | ✅ |
| Apple Calendar | ✅ |

Others will possibly be usable. They are just not tested yet. Feel free to file an issue if you run into platforms that have some issues.

## How to Get It?

### Download the binary version

Go to the [Release](https://github.com/Asiimoviet/ScheduleReader2.0/releases) and download the latest Version.

### Build it yourself

Download the repository and build it with ```make```
``` bash
git clone https://github.com/Asiimoviet/ScheduleReader2.0
cd ScheduleReader2.0
make
```

## How to use it?

### Usage and Options

Run ```schedule --help``` to get usage and options

### Configurations

When running the program, you will be asked to provide a config file that tells the program the location of elements in your excel file.

Here are the keys of config:
- exclude
- exclude_all
- days
- courses
- monday
- location_length
- time_sep
- hm_sep

You can find the [minimal config](examples/config_minimal.json) and [example config](examples/config.json) in the examples folder.

## What is different in 2.0?
This is it is writtened completely on C++ instead of Python. So it is cross-platform supported and high efficient.

## Dependences
Thanks these awesome authors for making wonderful libraries that this project depends on.
- [nlohmann/json](https://github.com/nlohmann/json)
- [troldal/OpenXLSX](https://github.com/troldal/OpenXLSX)
- [HowardHinnant/date](https://github.com/HowardHinnant/date)