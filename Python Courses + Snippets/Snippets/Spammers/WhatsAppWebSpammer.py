from selenium import webdriver
from time import sleep

# Made By Denis Karabitski (github.com/denisaka1)


class WhatsAppSpammer:
    type_tab = None
    enter_button = None
    name = None

    def __init__(self):
        # read from file in stream
        self.driver = webdriver.Chrome()
        self.driver.get('https://web.whatsapp.com/')
        sleep(10)

        self.name = input("\nEnter victims name: ")
        answer = input("What would you like to do?\n"
                       "1) deploy from file\n"
                       "2) deploy your message\n")

        if answer == '1':
            self.deploy_from_file()
        elif answer == '2':
            message = input("What message should the victim get?")
            self.deploy_message(message)
        else:
            print("\nError")

        # sleep(10)

    def find_person_by_name(self):

        search_button = self.driver.find_element_by_xpath('//*[@id="side"]/div[1]/div/label/div/div[2]')
        search_button.click()

        search_button.send_keys(self.name)
        sleep(1)  # add delay

        # get list of all familiar names after the search
        list_of_similar_names = self.driver.find_elements_by_xpath(
            '//*[@id="pane-side"]/div[1]/div/div/*/div/div/div[2]/div[1]/div[1]/span/span')
        for link in list_of_similar_names:
            sleep(0.5)  # add delay
            if self.name in link.get_attribute('title'):
                link.click()
                break

    def assign_variables(self):
        sleep(0.5)
        # open Type a message bar
        self.type_tab = self.driver.find_element_by_xpath('//*[@id="main"]/footer/div[1]/div[2]/div/div[2]')
        self.enter_button = self.driver.find_element_by_xpath('//*[@id="main"]/footer/div[1]/div[3]')
        self.type_tab.click()

    def deploy_message(self, message):
        self.find_person_by_name()
        self.assign_variables()
        for i in range(25):
            self.type_tab.send_keys(message)
            self.enter_button.click()

    def deploy_from_file(self):
        file = open("pastas/shrek", "r").read().splitlines()

        self.find_person_by_name()
        self.assign_variables()

        for line in file:  # loop through file
            for word in line.split(' '):  # loop through lines
                self.type_tab.send_keys(word)
                self.enter_button.click()


def main():
    WhatsAppSpammer()


if __name__ == '__main__':
    main()
