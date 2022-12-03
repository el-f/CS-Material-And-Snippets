from table_list import TableList


def to_typed_mark_info(mark_info):
    return mark_info[0], int(mark_info[1]), float(mark_info[2])


class WeightedAvgCalculator:
    def __init__(self, file_path):
        if not file_path:
            raise ValueError("File path is required")
        
        self.marks = []
        self.all_naz = None
        self.init_list_from_file(file_path)

    def init_list_from_file(self, file_path):
        with open(file_path) as f:
            for line in f:
                line = line.strip()
                if line and not line.startswith("#"):
                    self.marks.append(to_typed_mark_info(line.split(",")))
        self.all_naz = sum(x[2] for x in self.marks)

    def get_avg(self):
        return sum(x[1] * x[2] / self.all_naz for x in self.marks)

    def print_average(self):
        print("Average - %.3f" % self.get_avg())

    def print_rounded_average(self):
        print("Rounded Average - %d" % round(self.get_avg()))

    def print_range(self, low, high):
        print(
            "%2d Marks at Range of ( %3d - %3d ) Out of %d Marks"
            % (
                len([x for x in self.marks if int(x[1]) in range(low, high + 1)]),
                low,
                high,
                len(self.marks),
            )
        )

    def print_all_ranges(self):
        for i in range(0, 100, 10):
            if any(int(x[1]) in range(i, i + 10) for x in self.marks):
                self.print_range(i, i + 9)
        self.print_range(100, 100)

    def print_all(self):
        tl = TableList("#", "Course", "%", "NZ").with_unicode()
        for idx, t in enumerate(self.marks):
            tl.add_row(idx + 1, t[0], t[1], t[2])
        tl.pretty_print()

        
if __name__ == "__main__":
    print("All Marks:")
    wac = WeightedAvgCalculator("E:/Elfein/Afeka/myMarks")
    wac.print_all()
    wac.print_average()
    wac.print_rounded_average()
    wac.print_all_ranges()

    print("\nTechnology Marks:")
    wac = WeightedAvgCalculator("E:/Elfein/Afeka/myTechnologyMarks")
    wac.print_all()
    wac.print_average()
    wac.print_rounded_average()
    wac.print_all_ranges()
