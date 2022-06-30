package Snippets;

import org.apache.commons.lang3.StringUtils;

public class StringsIntoColumns {
    public static String columnize(String[] input, int cols) {
        int[] maxes = new int[cols];
        int len = input.length;

        for (int i = 0, col = 0; i < len; i++, col = i % cols) {
            maxes[col] = Math.max(maxes[col], input[i].length());
        }

        StringBuilder sb = new StringBuilder();
        for (int i = 0, col = 0; i < len; i++, col = i % cols) {
            sb.append(StringUtils.rightPad(input[i], maxes[col], ' '));
            if (i != len - 1) sb.append(col == cols - 1 ? "\n" : " | ");
        }

        return sb.toString();
    }
}
