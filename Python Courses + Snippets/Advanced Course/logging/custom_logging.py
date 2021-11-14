import logging

extData = {
    'user': 'Elazar@exmaple.com'
}


def main():
    frmt_str = "User: %(user)s %(asctime)s: %(levelname)s: %(funcName)s Line:%(lineno)d %(message)s"
    date_str = "%m/%d/%Y %I:%M:%S %p"

    logging.basicConfig(level=logging.DEBUG,
                        filename="custom_output.log",
                        filemode="w",
                        format=frmt_str,
                        datefmt=date_str
                        )

    logging.info("info msg", extra=extData)
    logging.warning("warning msg", extra=extData)
    my_function()


def my_function():
    logging.debug("debug lvl msg from myfunc", extra=extData)


if __name__ == '__main__':
    main()
