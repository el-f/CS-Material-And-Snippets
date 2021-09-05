package Snippets;

//  my solution for this kata: 58c5577d61aefcf3ff000081
public class RailFenceCipher {

    public static void main(String[] args) {
        System.out.println(encode("WEAREDISCOVEREDFLEEATONCE", 3));
        System.out.println(decode("WECRLTEERDSOEEFEAOCAIVDEN", 3));
        String s = "123456789ABCDEF";
        System.out.println(decode(encode(s, 4), 4).equals(s));
        System.out.println(encode(decode(s, 4), 4).equals(s));
    }

    // just build the matrix and traverse it the way shown.
    static String encode(String s, int n) {
        if (n <= 1 || s == null || s.isEmpty()) return s;
        int rail = 0, adder = 1, length = s.length();
        char[][] rails = new char[n][length];
        for (int index = 0; index < length; index++, rail += adder) {
            rails[rail][index] = s.charAt(index);

            if (adder == 1 && rail == n - 1) adder = -1;
            else if (rail == 0) adder = 1;
        }

        StringBuilder builder = new StringBuilder();
        for (char[] row : rails) for (char c : row) if (c != 0) builder.append(c);
        return builder.toString();
    }

    /*
        a game of indexes...
        the function for the gap is n * 2 - 2;
        each rail the gap changes by 2 and alternates,
        but always is totaled to the original n * 2 - 2 value.
     */
    static String decode(String s, int n) {
        if (n <= 1 || s == null || s.isEmpty()) return s;
        int bigGap = n * 2 - 2;
        int rail = 0, gap = bigGap, length = s.length();
        char[] decoded = new char[length];
        int decodedIndex = 0;
        boolean subtract = false;

        for (int index = 0; index < length; index++) {
            decoded[decodedIndex] = s.charAt(index);

            if (rail == 0 || rail == n - 1) decodedIndex += bigGap;
            else decodedIndex += subtract ? (bigGap - gap) : gap;
            subtract = !subtract;

            if (decodedIndex >= length) {
                rail++;
                decodedIndex = rail;
                subtract = false;
                gap -= 2;
            }
        }

        return String.valueOf(decoded);
    }

}
