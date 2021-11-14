from string import Template


def main():
    str1 = "you're watching {0} by {1}".format("movie", "tarantino")
    print(str1)

    templ = Template("youre watching ${title} by ${author}")

    str2 = templ.substitute(title="Django", author="Tarantino")
    print(str2)

    data = {
        "author": "Hitchcock",
        "title": "Vertigo"
    }
    print(templ.substitute(data))
    

if __name__ == '__main__':
    main()
