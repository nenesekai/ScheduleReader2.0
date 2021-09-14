# Schedule Reader 2.0

Automatically convert your excel schedule from your teacher to an iCalendar file that you can import into services like Google Calendar with just some configuration.

## Usage and Options

Use ```schedule --help``` to get usage and options

## Configuration

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

You can find the minimal config and example config in the examples folder.