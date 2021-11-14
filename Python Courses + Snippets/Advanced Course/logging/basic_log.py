import logging


def main():
    logging.basicConfig(level=logging.DEBUG,
                        filename="output.log",
                        filemode="a")

    logging.debug("debug msg")
    logging.info("info msg")
    logging.warning("warning msg")
    logging.error("error msg")
    logging.critical("critical msg")

    logging.info("heres a {} variable and an int {}:".format("string", 10))


if __name__ == '__main__':
    main()
