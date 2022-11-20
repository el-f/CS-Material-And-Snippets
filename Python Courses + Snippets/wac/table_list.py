class TableList:
    def __init__(self, *headers):
        self.headers = headers
        self.rows = []

    def add_row(self, *row):
        self.rows.append(row)

    def print(self):
        # find the max length of each column
        colLens = [len(x) for x in self.headers]
        for row in self.rows:
            for i, col in enumerate(row):
                colLens[i] = max(colLens[i], len(str(col)))

        # print the headers
        for i, col in enumerate(self.headers):
            print(col.ljust(colLens[i]), end=" | ")
        print()

        # print the rows
        for row in self.rows:
            for i, col in enumerate(row):
                print(str(col).ljust(colLens[i]), end=" | ")
            print()

    def with_unicode(self, unicode=True):
        self.T_LINE = "-"
        if unicode:
            self.B_LINE = "━"
            self.CROSSING = " ╈ "
            self.VERTICAL_T_SEP = ' │ '
            self.VERTICAL_B_SEP = ' ┃ '
            self.CORNER_BL = ' ┗'
            self.CORNER_BR = '┛'
            self.CORNER_TL = ' ┏'
            self.CORNER_TR = '┓'
            self.CROSSING_L = ' ┢'
            self.CROSSING_R = '┪'
            self.CROSSING_U = ' ┳ '
            self.CROSSING_B = ' ┻ '
        else:
            self.B_LINE = "-"
            self.CROSSING = "+"
            self.VERTICAL_T_SEP = ' | '
            self.VERTICAL_B_SEP = ' | '
            self.CORNER_BL = '+'
            self.CORNER_BR = '+'
            self.CORNER_TL = '+'
            self.CORNER_TR = '+'
            self.CROSSING_L = '+'
            self.CROSSING_R = '+'
            self.CROSSING_U = '+'
            self.CROSSING_B = '+'
        return self
      
      
    def pretty_print(self):
        colLens = [len(x) + 2 for x in self.headers]
        for row in self.rows:
            for i, col in enumerate(row):
                colLens[i] = max(colLens[i], len(str(col)))

        print(self.CORNER_TL + self.T_LINE.join([self.B_LINE * (x + 2) for x in colLens]) + self.CORNER_TR)
        print(self.VERTICAL_T_SEP + self.VERTICAL_T_SEP.join([x.ljust(colLens[i]) for i, x in enumerate(self.headers)]) + self.VERTICAL_T_SEP)
        print(self.CROSSING_L + self.T_LINE.join([self.B_LINE * (x + 2) for x in colLens]) + self.CROSSING_R)
        
        for row in self.rows:
            print(self.VERTICAL_B_SEP + self.VERTICAL_B_SEP.join([str(x).ljust(colLens[i]) for i, x in enumerate(row)]) + self.VERTICAL_B_SEP)
        print(self.CORNER_BL + self.T_LINE.join([self.B_LINE * (x + 2) for x in colLens]) + self.CORNER_BR)