const units = [
    "", "one", "two", "three", "four", "five", "six", "seven",
    "eight", "nine", "ten", "eleven", "twelve", "thirteen", "fourteen",
    "fifteen", "sixteen", "seventeen", "eighteen", "nineteen"
]

const tens = [
    "",        // 0
    "",        // 1
    "twenty",  // 2
    "thirty",  // 3
    "forty",   // 4
    "fifty",   // 5
    "sixty",   // 6
    "seventy", // 7
    "eighty",  // 8
    "ninety"   // 9
]

function convertNonZero(n, b) {
    if (n < 0) return "negative " + convertNonZero(-n);
    if (n < 20) return ((b & units[n] != "") ? "and " : "") + units[n];
    if (n < 100) return (b ? "and " : "") + tens[~~(n / 10)] + ((n % 10 != 0) ? "-" : "") + units[n % 10];
    if (n < 1000) return units[~~(n / 100)] + " hundred" + ((n % 100 != 0) ? " " : "") + convertNonZero(n % 100, true);
    if (n < 1000000) return convertNonZero(~~(n / 1000)) + " thousand" + ((n % 1000 != 0) ? " " : "") + convertNonZero(n % 1000, true);
    if (n < 1000000000) return convertNonZero(~~(n / 1000000)) + " million" + (n % 1000000 != 0 ? " " : "") + convertNonZero(n % 1000000, true);
    if (n < 1000000000000) return convertNonZero(~~(n / 1000000000)) + " billion" + (n % 1000000000 != 0 ? " " : "") + convertNonZero(n % 1000000000, true);
    if (n < 1000000000000000) return convertNonZero(~~(n / 1000000000000)) + " trillion" + (n % 1000000000000 != 0 ? " " : "") + convertNonZero(n % 1000000000000, true);
    return convertNonZero(~~(n / 1000000000000000)) + " quadrillion" + (n % 1000000000000000 != 0 ? " " : "") + convertNonZero(n % 1000000000000000, true);
}

function numberToEnglish(n) {
    if (n == Infinity) return "infinity";
    if (n == -Infinity) return "negative infinity";
    if (isNaN(n)) throw  Error("NaN");
    if (n == 0) return "zero";
    if (n.toString().includes(".")) {
        let parts = n.toString().split(".")
        return numberToEnglish(parseInt(parts[0])) + " point " + parts[1].split("").map(x => numberToEnglish(parseInt(x))).join(" ");
    }
    return convertNonZero(n);
}

