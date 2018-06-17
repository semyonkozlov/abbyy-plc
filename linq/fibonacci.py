from linq import Enumerable


def fibonacci():
    a, b = 0, 1
    while True:
        yield a
        a, b = b, a + b


def main():
    result = Enumerable(fibonacci()) \
        .where(lambda x: x % 3 == 0) \
        .select(lambda x: x ** 2 if x % 2 == 0 else x) \
        .take(5) \
        .to_list()

    print(result)


if __name__ == '__main__':
    main()
