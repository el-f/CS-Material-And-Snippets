package Snippets;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.Comparator;
import java.util.List;
import java.util.regex.Pattern;

@SuppressWarnings("unused") // For completeness of class.
public class TableList {

    private static final String[] B_LINE = { "-", "━" };
    private static final String[] CROSSING = { "+", "╈" };
    private static final String[] VERTICAL_T_SEP = { "|", "│" };
    private static final String[] VERTICAL_B_SEP = { "|", "┃" };
    private static final String T_LINE = "─";
    private static final String CORNER_TL = "┌";
    private static final String CORNER_TR = "┐";
    private static final String CORNER_BL = "┗";
    private static final String CORNER_BR = "┛";
    private static final String CROSSING_L = "┢";
    private static final String CROSSING_R = "┪";
    private static final String CROSSING_T = "┬";
    private static final String CROSSING_B = "┻";

    private final String[] descriptions;
    private final List<String[]> table;
    private final int[] tableSizes;
    private final int rows;
    private int filterColIdx;
    private String filter;
    private boolean enableUnicode;
    private Comparator<String[]> comparator;
    private int spacing;
    private final Alignment[] alignments;

    public TableList(String... descriptions) {
        int columns = descriptions.length;
        this.rows = columns;
        this.descriptions = descriptions;
        this.table = new ArrayList<>();
        this.tableSizes = new int[columns];
        this.updateSizes(descriptions);
        this.spacing = 1;
        this.alignments = new Alignment[columns];
        Arrays.fill(alignments, Alignment.LEFT);
    }

    private void updateSizes(String[] elements) {
        for (int i = 0; i < tableSizes.length; i++) {
            if (elements[i] != null) {
                tableSizes[i] = Math.max(tableSizes[i], elements[i].length());
            }
        }
    }

    public TableList setComparator(Comparator<String[]> c) {
        this.comparator = c;
        return this;
    }

    public TableList sortBy(int column) {
        return this.setComparator(Comparator.comparing(strings -> strings[column]));
    }

    public TableList align(int column, Alignment alignment) {
        alignments[column] = alignment;
        return this;
    }

    public TableList withSpacing(int spacing) {
        this.spacing = spacing;
        return this;
    }

    /**
     * Adds a row to the table with the specified elements.
     */
    public TableList addRow(String... elements) {
        if (elements.length != rows) {
            throw new IllegalArgumentException();
        }
        table.add(elements);
        updateSizes(elements);
        return this;
    }

    public TableList filterBy(int par0, String pattern) {
        this.filterColIdx = par0;
        this.filter = pattern;
        return this;
    }

    public TableList withUnicode(boolean enableUnicode) {
        this.enableUnicode = enableUnicode;
        return this;
    }

    public void print() {
        StringBuilder line = null;

        if (enableUnicode) {
            for (int i = 0; i < rows; i++) {
                if (line != null) {
                    line.append(CROSSING_T);
                } else {
                    line = new StringBuilder();
                    line.append(CORNER_TL);
                }
                for (int j = 0; j < tableSizes[i] + 2 * spacing; j++) {
                    line.append(T_LINE);
                }
            }
            assert line != null;
            line.append(CORNER_TR);
            System.out.println(line);

            line = null;
        }

        // print header
        for (int i = 0; i < rows; i++) {
            if (line != null) {
                line.append(getSymbol(VERTICAL_T_SEP));
            } else {
                line = new StringBuilder();
                if (enableUnicode) {
                    line.append(getSymbol(VERTICAL_T_SEP));
                }
            }
            StringBuilder part = new StringBuilder(descriptions[i]);
            while (part.length() < tableSizes[i] + spacing) {
                part.append(" ");
            }
            for (int j = 0; j < spacing; j++) {
                line.append(" ");
            }
            line.append(part);
        }
        if (enableUnicode) {
            line.append(getSymbol(VERTICAL_T_SEP));
        }
        System.out.println(line);

        // print vertical separator
        line = null;
        for (int i = 0; i < rows; i++) {
            if (line != null) {
                line.append(getSymbol(CROSSING));
            } else {
                line = new StringBuilder();
                if (enableUnicode) {
                    line.append(CROSSING_L);
                }
            }
            for (int j = 0; j < tableSizes[i] + 2 * spacing; j++) {
                line.append(getSymbol(B_LINE));
            }
        }
        if (enableUnicode) {
            assert line != null;
            line.append(CROSSING_R);
        }
        System.out.println(line);

        line = null;
        List<String[]> localTable = table;

        if (filter != null) {
            Pattern p = Pattern.compile(filter);
            localTable.removeIf(arr -> {
                String s = arr[filterColIdx];
                return !p.matcher(s).matches();
            });
        }

        if (localTable.isEmpty()) {
            String[] sa = new String[rows];
            localTable.add(sa);
        }

        localTable.forEach(arr -> {
            for (int i = 0; i < arr.length; i++) {
                if (arr[i] == null) {
                    arr[i] = "";
                }
            }
        });

        if (comparator != null) {
            localTable.sort(comparator);
        }

        for (String[] strings : localTable) {
            for (int i = 0; i < rows; i++) {
                if (line != null) {
                    line.append(getSymbol(VERTICAL_B_SEP));
                } else {
                    line = new StringBuilder();
                    if (enableUnicode) {
                        line.append(getSymbol(VERTICAL_B_SEP));
                    }
                }
                StringBuilder part = new StringBuilder();
                for (int j = 0; j < spacing; j++) {
                    part.append(" ");
                }
                if (strings[i] != null) {
                    switch (alignments[i]) {
                        case LEFT:
                            part.append(strings[i]);
                            break;
                        case RIGHT:
                            for (int j = 0; j < tableSizes[i] - strings[i].length(); j++) {
                                part.append(" ");
                            }
                            part.append(strings[i]);
                            break;
                        case CENTER:
                            for (int j = 0; j < (tableSizes[i] - strings[i].length()) / 2; j++) {
                                part.append(" ");
                            }
                            part.append(strings[i]);
                            break;
                    }
                }
                while (part.length() < tableSizes[i] + spacing) {
                    part.append(" ");
                }
                for (int j = 0; j < spacing; j++) {
                    part.append(" ");
                }
                line.append(part);
            }
            if (enableUnicode) {
                assert line != null;
                line.append(getSymbol(VERTICAL_B_SEP));
            }
            System.out.println(line);

            line = null;
        }

        if (enableUnicode) {
            for (int i = 0; i < rows; i++) {
                if (line != null) {
                    line.append(CROSSING_B);
                } else {
                    line = new StringBuilder();
                    line.append(CORNER_BL);
                }
                for (int j = 0; j < tableSizes[i] + 2 * spacing; j++) {
                    line.append(getSymbol(B_LINE));
                }
            }
            assert line != null;
            line.append(CORNER_BR);
            System.out.println(line);
        }

    }

    private String getSymbol(String[] strs) {
        return strs[enableUnicode ? 1 : 0];
    }

    public enum Alignment {
        LEFT,
        CENTER,
        RIGHT
    }

}