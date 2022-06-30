package Snippets;

public class CutPasteFixer {

    public static String fixCutPaste(String text) {
        return text.replaceAll("(\\P{Alpha}*+(?:(?<!\\p{Alpha})\\p{Alpha}++\\P{Alpha}*?)+?)\\1+", "$1");
    }

}
