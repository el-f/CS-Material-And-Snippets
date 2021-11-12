fun main() {
    val testCases = listOf(
        // 'bookExample'
        arrayOf(
            "1 2 3 4 5 6 7 8/a b c/1,b,1;1,,2;2,b,3;2,b,5;2,,7;3,a,4; 3,c,4;4,c,2;4,c,7;5,a,6;5,b,6;6,c,2; 6,c,7;6,,2;7,b,8/1/8",
            "1 2 3 4 5 6 7 8 9 10/a b c/1,a,10;1,c,10;1,b,2;2,a,5;2,b,3;2 ,c,4;3,a,5;3,b,3;3,c,9;4,a,10;4,b,10;4,c,7;5,a,10;5,b,6;5,c,7;6,a,5;6, b,8;6,c,4;7,a,10;7,b,6;7,c,10;8,a,10;8,b,6;8,c,7;9,a,10;9,b,6;9,c,7;10 ,a,10;10,b,10;10,c,10/1/3 2 6"
        ),

        // 'noEpsilonTransitions'
        arrayOf(
            "1 2 3 4/a b/1,a,1;1,b,1;1,a,2;2,a,3;2,b,3;3,a ,4;3,b,4/1/4",
            "0 1 2 3 4 5 6 7/a b/3,b,7; 0,a,1; 7,a,1; 3,a,6; 7,b,0; 4,b,5; 2,b,5; 1,b,3; 0,b,0; 1,a,2; 2,a,4; 4,a,4; 5,b,7; 5,a,6; 6,a,2; 6,b,3/0/4 5 6 7"
        ),

        // 'deterministic'
        arrayOf("0 1/a/0,a,1;1,a,1/0/", "0 1/a/0,a,1;1,a,1/0/"),

        // 'emptyLanguage'
        arrayOf("0/a/0,,0/0/", "0 1/a/0,a,1;1,a,1/0/"),

        // |w| is odd
        arrayOf(
            "1 2/0 1/1,0,1;1,1,2;2,0,2;2,1,1/1/2",
            "1 2/0 1/1,0,1;1,1,2;2,0,2;2,1,1/1/2"
        ),

        // all possible w
        arrayOf(
            "0/a/0,,0;0,a,0/0/0",
            "0/a/0,a,0/0/0"
        )
    )
    testCases.forEach { tc: Array<String> ->
        try {
            val ndfsmENC = tc[0]
            val dfsmENC = tc[1]
            val dfsm = DFSM(dfsmENC)
            val ndfsm = NDFSM(ndfsmENC)
            val ndfsmConverted = ndfsm.toDFSM()
            dfsm.minimize().toCanonicForm().prettyPrint(System.out)
            println()
            ndfsmConverted.minimize().toCanonicForm().prettyPrint(System.out)
            println("~~~~~~~~~~~~~~")
        } catch (e: Exception) {
            e.printStackTrace()
        }
    }
}