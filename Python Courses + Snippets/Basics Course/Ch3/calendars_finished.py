#
# Example file for working with Calendars
#

import calendar

# create a plain text calendar
c = calendar.TextCalendar(calendar.SUNDAY)
string = c.formatmonth(2017, 1, 0, 0)
print(string)

# create an HTML formatted calendar
hc = calendar.HTMLCalendar(calendar.SUNDAY)
string = hc.formatmonth(2017, 1)
print(string)

# loop over the days of a month
# zeroes mean that the day of the week is in an overlapping month
for i in c.itermonthdays(2017, 8):
    print(i)

# The Calendar module provides useful utilities for the given locale,
# such as the names of days and months in both full and abbreviated forms
for name in calendar.month_name:
    print(name)

for day in calendar.day_name:
    print(day)

# Calculate days based on a rule: For example, consider
# a team meeting on the first Friday of every month.
# To figure out what days that would be for each month,
# we can use this script:
print("Team meetings will be on:")
for m in range(1, 13):
    # returns an array of weeks that represent the month
    cal = calendar.monthcalendar(2017, m)
    # The first Friday has to be within the first two weeks
    weekone = cal[0]
    weektwo = cal[1]

    if weekone[calendar.FRIDAY] != 0:
        meetday = weekone[calendar.FRIDAY]
    else:
        # if the first friday isn't in the first week, it must be in the second
        meetday = weektwo[calendar.FRIDAY]

    print("%10s %2d" % (calendar.month_name[m], meetday))
