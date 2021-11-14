import time
import schedule


# the python version of cron

def test_function():
    print(f'test called at {time.time()}')


def test_function_2():
    print(f'test 2 called at {time.time()}')


if __name__ == '__main__':
    schedule.every(1).seconds.do(test_function)
    schedule.every(3).seconds.do(test_function_2)
    # schedule.every(1).days.do(daily_task)
    # schedule.every().thursday.at("10:00").do(day_time_task)

    while True:
        schedule.run_pending()
