import re
from bs4 import BeautifulSoup
import urllib3
import time

def try_again(max_tries=3):
    def decorator(func):
        def wrapper(*args, **kwargs):
            result = []
            for _ in range(max_tries):
                result = func(*args, **kwargs)
                if result:
                    break
                # sleep for 1 second
                time.sleep(1)
            return result
        return wrapper
    return decorator

@try_again()
def get_links(url, url_startswith="", use_regex=False):
    http = urllib3.PoolManager()
    html_page = http.request('GET', url).data
    soup = BeautifulSoup(html_page, features="html.parser")
    links = []

    for link in soup.findAll('a', attrs={'href': re.compile("^https?://(www\\.)?" + (url_startswith if use_regex else re.escape(url_startswith)))}):
        links.append(link.get('href'))

    return links

print("~" * 80)
print(get_links("https://www.reddit.com/r/listentothis/", "youtube"))

print("~" * 80)
print(get_links("https://www.reddit.com/r/listentothis/", "(youtube)|(youtu.be)", True))
