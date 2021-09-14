# Schedule Reader 2.0

Automatically convert your excel schedule from your teacher to an iCalendar file that you can import into services like Google Calendar with just some configuration.

## How to Get It?

### Download the binary version

Go to the [Release](https://github.com/Asiimoviet/ScheduleReader2.0/releases) and download the latest Version.

### Build it yourself

Download the repository and build it with ```make```
```
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
This is it is writtened completely on C++ instead of Python.

## Acknowledge
Thanks these awesome authors for making wonderful libraries for this project.
- [nlohmann/json](https://github.com/nlohmann/json)
- [troldal/OpenXLSX](https://github.com/troldal/OpenXLSX)
- [HowardHinnant/date](https://github.com/HowardHinnant/date)