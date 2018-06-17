from linq import Enumerable


def main():
    with open(__file__, 'r') as file:
        Enumerable(file.readlines()) \
            .select(lambda x: x.split()) \
            .flatten() \
            .group_by(lambda x: x) \
            .select(lambda x: (x[0], len(x[1]))) \
            .order_by(lambda x: -x[1]) \
            .select(lambda x: print(f'{x[0]} : {x[1]}')) \
            .to_list()


if __name__ == '__main__':
    main()
