# sudo apt install redis-server
# sudo systemctl enable redis-server.service
# sudo systemctl start redis-server.service

# pip/pip3 install git+https://github.com/YashSinha1996/redis-simple-cache.git

# cache functions with a in memory redis instance

from redis_cache import cache_it, cache_it_json


@cache_it(limit=1000, expire=5)
def function_that_takes_a_long_time(i):
    print(f"function was called with input {i}")
    return i**2


if __name__ == '__main__':
    for i in range(10):
        print(i, function_that_takes_a_long_time(2))