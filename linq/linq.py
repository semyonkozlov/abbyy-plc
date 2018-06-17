import collections


class Enumerable:
    def __init__(self, sequence):
        self.sequence = sequence

    def select(self, func):
        return Enumerable(map(func, self.sequence))

    def _flatten(self):
        for subsequence in self.sequence:
            yield from subsequence

    def flatten(self):
        return Enumerable(self._flatten())

    def where(self, pred):
        return Enumerable(filter(pred, self.sequence))

    def _take(self, k):
        for i, element in enumerate(self.sequence):
            if i == k:
                break
            yield element

    def take(self, k):
        return Enumerable(self._take(k))

    def _group_by(self, key_func):
        dict = collections.defaultdict(list)
        for element in self.sequence:
            dict[key_func(element)].append(element)

        return dict.items()

    def group_by(self, key_func):
        return Enumerable(self._group_by(key_func))

    def order_by(self, key_func):
        return Enumerable(sorted(self.sequence, key=key_func))

    def to_list(self):
        return list(self.sequence)